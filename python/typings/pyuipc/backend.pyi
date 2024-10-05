import pyuipc.core
import pyuipc.geometry
from typing import Iterator

class SceneVisitor:
    class GeometrySlotSpan:
        def __init__(self, *args, **kwargs) -> None: ...
        def __getitem__(self, arg0: int) -> pyuipc.geometry.GeometrySlot: ...
        def __iter__(self) -> Iterator[pyuipc.geometry.GeometrySlot]: ...
        def __len__(self) -> int: ...
        def __setitem__(self, arg0: int, arg1: pyuipc.geometry.GeometrySlot) -> None: ...
    def __init__(self, arg0: pyuipc.core.Scene) -> None: ...
    def begin_pending(self) -> None: ...
    def constitution_tabular(self) -> pyuipc.core.ConstitutionTabular: ...
    def contact_tabular(self) -> pyuipc.core.ContactTabular: ...
    def geometries(self) -> SceneVisitor.GeometrySlotSpan: ...
    def info(self) -> json: ...
    def pending_geometries(self) -> SceneVisitor.GeometrySlotSpan: ...
    def pending_rest_geometries(self) -> SceneVisitor.GeometrySlotSpan: ...
    def rest_geometries(self) -> SceneVisitor.GeometrySlotSpan: ...
    def solve_pending(self) -> None: ...

class WorldVisitor:
    def __init__(self, *args, **kwargs) -> None: ...
    def scene(self) -> SceneVisitor: ...
