#include <app/test_common.h>
#include <app/asset_dir.h>
#include <uipc/geometry.h>
#include <uipc/geometry/utils/label_surface.h>
#include <uipc/geometry/utils/extract_surface.h>
#include <uipc/geometry/utils/flip_inward_triangles.h>
#include <uipc/geometry/utils/label_triangle_orient.h>

using namespace uipc;
using namespace uipc::geometry;

TEST_CASE("extract_surface", "[surface]")
{
    {
        vector<Vector3>  Vs = {Vector3{0.0, 0.0, 0.0},
                               Vector3{1.0, 0.0, 0.0},
                               Vector3{0.0, 1.0, 0.0},
                               Vector3{0.0, 0.0, 1.0}};
        vector<Vector4i> Ts = {Vector4i{0, 1, 2, 3}};

        auto mesh    = tetmesh(Vs, Ts);
        auto labeled = label_surface(mesh);
        // parent_id should be present in the labeled mesh
        REQUIRE(labeled.triangles().find<IndexT>(builtin::parent_id));
        auto surface = extract_surface(labeled);

        REQUIRE(surface.vertices().size() == 4);
        auto pos_view = surface.positions().view();
        REQUIRE(std::ranges::equal(Vs, pos_view));

        REQUIRE(surface.edges().size() == 6);
        REQUIRE(surface.triangles().size() == 4);
        REQUIRE(surface.tetrahedra().size() == 0);
        // parent_id should not be present in the surface mesh, we remove it in the extract_surface function
        REQUIRE(!surface.triangles().find<IndexT>(builtin::parent_id));
    }

    {
        SimplicialComplexIO io;
        auto mesh = io.read_msh(fmt::format("{}cube.msh", AssetDir::tetmesh_path()));
        auto labeled = label_surface(mesh);
        auto surface = extract_surface(labeled);

        REQUIRE(surface.vertices().size() == 8);  // cube surf mesh has 8 vertices
        REQUIRE(surface.edges().size() == 18);    // cube surf mesh has 18 edges
        REQUIRE(surface.triangles().size() == 12);  // cube surf mesh has 12 triangles, 6 faces * 2 triangles per face
        REQUIRE(surface.tetrahedra().size() == 0);  // cube surf mesh has no tetrahedra

        io.write_obj(fmt::format("{}cube_unflipped_surf.obj", AssetDir::output_path()), surface);

        auto oriented        = label_triangle_orient(labeled);
        auto flipped         = flip_inward_triangles(oriented);
        auto surface_flipped = extract_surface(flipped);
        io.write_obj(fmt::format("{}cube_flipped_surf.obj", AssetDir::output_path()),
                     surface_flipped);
    }
}