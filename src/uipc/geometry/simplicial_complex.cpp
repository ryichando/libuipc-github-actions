#include <uipc/geometry/simplicial_complex.h>
#include <uipc/common/log.h>
#include <uipc/builtin/attribute_name.h>
#include <uipc/builtin/geometry_type.h>

namespace uipc::geometry
{
SimplicialComplex::SimplicialComplex(const AbstractSimplicialComplex& asc,
                                     span<const Vector3>              positions)
    : m_asc{asc}
{
    UIPC_ASSERT(positions.size() == m_asc.vertices().size(),
                "Number of vertices in the simplicial complex ({}) does not match the number of positions ({}).",
                m_asc.vertices().size(),
                positions.size());

    m_vertex_attributes.resize(m_asc.vertices().size());
    m_edge_attributes.resize(m_asc.edges().size());
    m_triangle_attributes.resize(m_asc.triangles().size());
    m_tetrahedron_attributes.resize(m_asc.tetrahedra().size());

    auto pos   = m_vertex_attributes.create<Vector3, false>(builtin::position,
                                                          Vector3::Zero());
    auto view_ = view(*pos);
    std::copy(positions.begin(), positions.end(), view_.begin());
}

AttributeSlot<Vector3>& SimplicialComplex::positions() noexcept
{
    return *m_vertex_attributes.find<Vector3>(builtin::position);
}

const AttributeSlot<Vector3>& SimplicialComplex::positions() const noexcept
{
    return *m_vertex_attributes.find<Vector3>(builtin::position);
}

auto SimplicialComplex::vertices() noexcept -> VertexAttributes
{
    return VertexAttributes(m_asc.m_vertices, m_vertex_attributes);
}

auto SimplicialComplex::vertices() const noexcept -> CVertexAttributes
{
    return CVertexAttributes(m_asc.m_vertices, m_vertex_attributes);
}

auto SimplicialComplex::edges() noexcept -> EdgeAttributes
{
    return EdgeAttributes(m_asc.m_edges, m_edge_attributes);
}

auto SimplicialComplex::edges() const noexcept -> CEdgeAttributes
{
    return CEdgeAttributes(m_asc.m_edges, m_edge_attributes);
}

auto SimplicialComplex::triangles() noexcept -> TriangleAttributes
{
    return TriangleAttributes(m_asc.m_triangles, m_triangle_attributes);
}

auto SimplicialComplex::triangles() const noexcept -> CTriangleAttributes
{
    return CTriangleAttributes(m_asc.m_triangles, m_triangle_attributes);
}

auto SimplicialComplex::tetrahedra() noexcept -> TetrahedronAttributes
{
    return TetrahedronAttributes(m_asc.m_tetrahedra, m_tetrahedron_attributes);
}

auto SimplicialComplex::tetrahedra() const noexcept -> CTetrahedronAttributes
{
    return CTetrahedronAttributes(m_asc.m_tetrahedra, m_tetrahedron_attributes);
}

IndexT SimplicialComplex::dim() const noexcept
{
    if(m_asc.m_tetrahedra.size() > 0)
        return 3;
    if(m_asc.m_triangles.size() > 0)
        return 2;
    if(m_asc.m_edges.size() > 0)
        return 1;
    return 0;
}

std::string_view SimplicialComplex::get_type() const noexcept
{
    return builtin::SimplicialComplex;
}
}  // namespace uipc::geometry