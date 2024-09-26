#include <uipc/geometry/implicit_geometry.h>
#include <uipc/builtin/implicit_geometry_uid_collection.h>
#include <uipc/builtin/geometry_type.h>
#include <uipc/builtin/attribute_name.h>

namespace uipc::geometry
{
ImplicitGeometry::ImplicitGeometry()
{
    // Set the implicit geometry UID to 0 (Empty).
    m_meta.create<U64, false>(builtin::implicit_geometry_uid, 0ull);
}

const builtin::UIDInfo& ImplicitGeometry::uid_info() const noexcept
{
    U64 uid = m_meta.find<U64>(builtin::implicit_geometry_uid)->view()[0];
    return builtin::ImplicitGeometryUIDCollection::instance().find(uid);
}

std::string_view ImplicitGeometry::name() const noexcept
{
    return uid_info().name;
}

std::string_view ImplicitGeometry::get_type() const noexcept
{
    return uipc::builtin::ImplicitGeometry;
}
}  // namespace uipc::geometry