#include <pyuipc/geometry/implicit_geometry.h>
#include <uipc/geometry/implicit_geometry.h>

namespace pyuipc::geometry
{
using namespace uipc::geometry;

PyImplicitGeometry::PyImplicitGeometry(py::module& m)
{
    auto class_ImplicitGeometry =
        py::class_<ImplicitGeometry, Geometry, S<ImplicitGeometry>>(m, "ImplicitGeometry");

    class_ImplicitGeometry.def(py::init<>());
}
}  // namespace pyuipc::geometry