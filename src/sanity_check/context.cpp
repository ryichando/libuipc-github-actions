#include <context.h>
#include <uipc/common/zip.h>
#include <uipc/backend/visitors/geometry_visitor.h>
#include <uipc/builtin/geometry_type.h>
#include <uipc/builtin/attribute_name.h>
#include <uipc/backend/visitors/scene_visitor.h>
#include <uipc/common/unordered_map.h>
#include <uipc/geometry/utils/extract_surface.h>
#include <uipc/geometry/utils/apply_transform.h>
#include <uipc/geometry/utils/merge.h>

namespace uipc::sanity_check
{
namespace detail
{
    using namespace uipc::geometry;

    static void collect_geometry_with_surf(span<S<GeometrySlot>> geos,
                                           vector<const SimplicialComplex*>& simplicial_complex_has_surf,
                                           vector<IndexT>& surf_geo_ids)
    {
        using namespace uipc::geometry;
        // 1) find all simplicial complex with surface
        simplicial_complex_has_surf.reserve(geos.size());

        for(auto& geo : geos)
        {
            if(geo->geometry().type() == builtin::SimplicialComplex)
            {
                auto simplicial_complex =
                    dynamic_cast<SimplicialComplex*>(&geo->geometry());

                UIPC_ASSERT(simplicial_complex, "type mismatch, why can it happen?");

                switch(simplicial_complex->dim())
                {
                    case 0:
                        if(simplicial_complex->vertices().find<IndexT>(builtin::is_surf))
                        {
                            simplicial_complex_has_surf.push_back(simplicial_complex);
                            surf_geo_ids.push_back(geo->id());
                        }
                        break;
                    case 1:
                        if(simplicial_complex->edges().find<IndexT>(builtin::is_surf))
                        {
                            simplicial_complex_has_surf.push_back(simplicial_complex);
                            surf_geo_ids.push_back(geo->id());
                        }
                        break;
                    case 2:
                    case 3:
                        if(simplicial_complex->triangles().find<IndexT>(builtin::is_surf))
                        {
                            simplicial_complex_has_surf.push_back(simplicial_complex);
                            surf_geo_ids.push_back(geo->id());
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }

    static void create_basic_sanity_check_attributes(span<S<GeometrySlot>> geos,
                                                     const unordered_map<IndexT, IndexT>& geo_id_to_object_id)
    {
        for(auto& geo : geos)
        {
            if(geo->geometry().type() == builtin::SimplicialComplex)
            {
                auto simplicial_complex =
                    dynamic_cast<SimplicialComplex*>(&geo->geometry());

                UIPC_ASSERT(simplicial_complex, "type mismatch, why can it happen?");

                // 1) label original_index for each vertex, edge, triangle, tetrahedron
                {
                    auto OI = simplicial_complex->vertices().create<IndexT>(
                        "sanity_check/original_index");
                    auto OI_view = view(*OI);

                    std::iota(OI_view.begin(), OI_view.end(), 0);
                }

                if(simplicial_complex->dim() >= 1)
                {
                    auto OI = simplicial_complex->edges().create<IndexT>("sanity_check/original_index");
                    auto OI_view = view(*OI);

                    std::iota(OI_view.begin(), OI_view.end(), 0);
                }

                if(simplicial_complex->dim() >= 2)
                {
                    auto OI = simplicial_complex->triangles().create<IndexT>(
                        "sanity_check/original_index");
                    auto OI_view = view(*OI);

                    std::iota(OI_view.begin(), OI_view.end(), 0);
                }

                if(simplicial_complex->dim() == 3)
                {
                    auto OI = simplicial_complex->tetrahedra().create<IndexT>(
                        "sanity_check/original_index");
                    auto OI_view = view(*OI);

                    std::iota(OI_view.begin(), OI_view.end(), 0);
                }

                // 2) label vertices with geometry_id and object_id
                {
                    auto geo_id = simplicial_complex->vertices().find<IndexT>(
                        "sanity_check/geometry_id");
                    if(!geo_id)
                        geo_id = simplicial_complex->vertices().create<IndexT>(
                            "sanity_check/geometry_id");

                    std::ranges::fill(view(*geo_id), geo->id());

                    auto obj_id = simplicial_complex->vertices().find<IndexT>("sanity_check/object_id");

                    if(!obj_id)
                        obj_id = simplicial_complex->vertices().create<IndexT>("sanity_check/object_id");

                    std::ranges::fill(view(*obj_id), geo_id_to_object_id.at(geo->id()));
                }
            }
        }
    }

    static void label_vertices_with_contact_element_id(span<S<GeometrySlot>> geos)
    {
        for(auto& geo : geos)
        {
            if(geo->geometry().type() == builtin::SimplicialComplex)
            {
                auto simplicial_complex =
                    dynamic_cast<SimplicialComplex*>(&geo->geometry());
                UIPC_ASSERT(simplicial_complex, "type mismatch, why can it happen?");

                auto contact_element_id =
                    simplicial_complex->meta().find<IndexT>(builtin::contact_element_id);

                IndexT CID = 0;

                if(contact_element_id)
                    CID = contact_element_id->view()[0];

                auto vertex_contact_element_id =
                    simplicial_complex->vertices().find<IndexT>("sanity_check/contact_element_id");

                if(!vertex_contact_element_id)
                    vertex_contact_element_id =
                        simplicial_complex->vertices().create<IndexT>("sanity_check/contact_element_id");

                std::ranges::fill(view(*vertex_contact_element_id), CID);
            }
        }
    }

    static void destory_sanity_check_attributes(backend::SceneVisitor& scene_visitor)
    {
        auto geos      = scene_visitor.geometries();
        auto rest_geos = scene_visitor.rest_geometries();

        vector<std::string>                    collection_names;
        vector<geometry::AttributeCollection*> collections;

        // remove all [sanity_check/xxx] Attibute Collection
        for(auto&& [geo_slot, rest_geo_slot] : zip(geos, rest_geos))
        {
            std::array<geometry::Geometry*, 2> local_geos = {
                &geo_slot->geometry(), &rest_geo_slot->geometry()};

            for(geometry::Geometry* geo : local_geos)
            {
                backend::GeometryVisitor geo_visitor{*geo};
                collection_names.clear();
                collections.clear();
                geo_visitor.collect_attribute_collections(collection_names, collections);

                for(auto&& [_, collection] : zip(collection_names, collections))
                {
                    vector<std::string> attribute_names = collection->names();
                    std::string_view    prefix          = "sanity_check/";

                    auto [iter, end] = std::ranges::remove_if(
                        attribute_names,
                        [prefix](const std::string& name)
                        { return name.find(prefix) == std::string::npos; });

                    attribute_names.erase(iter, end);

                    for(const std::string& parm_name : attribute_names)
                    {
                        collection->destroy(parm_name);
                    }
                }
            }
        }
    }

    static SimplicialComplex extract_surface_with_instance_id(span<const SimplicialComplex*> sc)
    {
        if(sc.empty())
            return SimplicialComplex{};

        // 1) extract the surface from each simplicial complex
        vector<SimplicialComplex> surfaces;
        surfaces.reserve(sc.size());

        std::transform(sc.begin(),
                       sc.end(),
                       std::back_inserter(surfaces),
                       [](const SimplicialComplex* simplicial_complex)
                       {
                           if(simplicial_complex->dim() == 3)
                               return extract_surface(*simplicial_complex);
                           else
                               return *simplicial_complex;
                       });

        // 2) find out all the surface instances, apply the transformation
        SizeT total_surface_instances = std::accumulate(
            sc.begin(),
            sc.end(),
            0ull,
            [](SizeT acc, const SimplicialComplex* simplicial_complex)
            { return acc + simplicial_complex->instances().size(); });

        vector<SimplicialComplex> all_surfaces;
        all_surfaces.reserve(total_surface_instances);

        for(auto& surface : surfaces)
        {
            vector<SimplicialComplex> instances = apply_transform(surface);

            // label vertices with instance id
            for(auto&& [I, instance] : enumerate(instances))
            {
                auto instance_id =
                    instance.vertices().find<IndexT>("sanity_check/instance_id");

                if(!instance_id)
                    instance_id = instance.vertices().create<IndexT>("sanity_check/instance_id");

                std::ranges::fill(view(*instance_id), I);
            }

            std::move(instances.begin(), instances.end(), std::back_inserter(all_surfaces));
        }

        vector<const SimplicialComplex*> surfaces_ptr(total_surface_instances);

        std::transform(all_surfaces.begin(),
                       all_surfaces.end(),
                       surfaces_ptr.begin(),
                       [](SimplicialComplex& surface) { return &surface; });

        return merge(surfaces_ptr);
    }
}  // namespace detail

class Context::Impl
{
  public:
    Impl(core::Scene& s) noexcept
        : m_scene(s)
    {
    }

    ~Impl() = default;

    void init()
    {
        build_geo_id_to_object_id();

        auto scene_visitor = backend::SceneVisitor{m_scene};
        detail::create_basic_sanity_check_attributes(scene_visitor.geometries(),
                                                     m_geo_id_to_object_id);

        auto& info           = scene_visitor.info();
        auto  enable_contact = info["contact"]["enable"].get<bool>();
        if(enable_contact)
        {
            detail::label_vertices_with_contact_element_id(scene_visitor.geometries());
        }
    }

    void deinit()
    {
        auto scene_visitor = backend::SceneVisitor{m_scene};
        detail::destory_sanity_check_attributes(scene_visitor);
    }

    void build_geo_id_to_object_id() const noexcept
    {
        auto scene_visitor = backend::SceneVisitor{m_scene};

        auto N = m_scene.objects().created_count();

        auto& map = m_geo_id_to_object_id;

        for(IndexT objI = 0; objI < N; ++objI)
        {
            auto obj = m_scene.objects().find(objI);
            if(obj)
            {
                auto geo_ids = obj->geometries().ids();
                for(auto geo_id : geo_ids)
                {
                    map[geo_id] = objI;
                }
            }
        }
    }

    const geometry::SimplicialComplex& scene_simplicial_surface() const noexcept
    {
        if(m_scene_simplicial_surface)
            return *m_scene_simplicial_surface;

        auto scene_visitor = backend::SceneVisitor{m_scene};

        m_scene_simplicial_surface = uipc::make_unique<geometry::SimplicialComplex>();

        vector<const geometry::SimplicialComplex*> simplicial_complex_has_surf;
        vector<IndexT>                             surf_geo_ids;

        detail::collect_geometry_with_surf(scene_visitor.geometries(),
                                           simplicial_complex_has_surf,
                                           surf_geo_ids);

        m_scene_simplicial_surface = uipc::make_unique<geometry::SimplicialComplex>(
            detail::extract_surface_with_instance_id(simplicial_complex_has_surf));

        return *m_scene_simplicial_surface;
    }


  private:
    core::Scene&                           m_scene;
    mutable U<geometry::SimplicialComplex> m_scene_simplicial_surface;
    mutable unordered_map<IndexT, IndexT>  m_geo_id_to_object_id;
};

Context::Context(SanityCheckerCollection& c, core::Scene& s) noexcept
    : SanityChecker(c, s)
    , m_impl(uipc::make_unique<Impl>(s))
{
}

Context::~Context() {}

const geometry::SimplicialComplex& Context::scene_simplicial_surface() const noexcept
{
    return m_impl->scene_simplicial_surface();
}

void Context::init() noexcept
{
    m_impl->init();
}

void Context::deinit() noexcept
{
    m_impl->deinit();
}

U64 Context::get_id() const noexcept
{
    return 0;
}
SanityCheckResult Context::do_check(backend::SceneVisitor&) noexcept
{
    // Do nothing, this checker is only for providing context for other checkers
    return SanityCheckResult::Success;
}

REGISTER_SANITY_CHECKER(Context);
}  // namespace uipc::sanity_check
