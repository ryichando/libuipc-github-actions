import numpy
from . import backend as backend, builtin as builtin, constitution as constitution, engine as engine, geometry as geometry, world as world
from pyuipc.engine import Engine as Engine
from pyuipc.world import Scene as Scene, SceneIO as SceneIO, World as World
from typing import ClassVar, overload

class AngleAxis:
    def __init__(self, arg0: float, arg1: numpy.ndarray[numpy.float64]) -> None: ...
    @staticmethod
    def Identity() -> AngleAxis: ...
    def angle(self) -> float: ...
    def axis(self) -> numpy.ndarray[numpy.float64]: ...

class Float:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def One() -> float: ...
    @staticmethod
    def Value(arg0: float) -> float: ...
    @staticmethod
    def Zero() -> float: ...
    @staticmethod
    def size_bytes() -> int: ...

class I32:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def One() -> int: ...
    @staticmethod
    def Value(arg0: int) -> int: ...
    @staticmethod
    def Zero() -> int: ...
    @staticmethod
    def size_bytes() -> int: ...

class I64:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def One() -> int: ...
    @staticmethod
    def Value(arg0: int) -> int: ...
    @staticmethod
    def Zero() -> int: ...
    @staticmethod
    def size_bytes() -> int: ...

class IndexT:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def One() -> int: ...
    @staticmethod
    def Value(arg0: int) -> int: ...
    @staticmethod
    def Zero() -> int: ...
    @staticmethod
    def size_bytes() -> int: ...

class Logger:
    class Level:
        __members__: ClassVar[dict] = ...  # read-only
        Critical: ClassVar[Logger.Level] = ...
        Debug: ClassVar[Logger.Level] = ...
        Error: ClassVar[Logger.Level] = ...
        Info: ClassVar[Logger.Level] = ...
        Trace: ClassVar[Logger.Level] = ...
        Warn: ClassVar[Logger.Level] = ...
        __entries: ClassVar[dict] = ...
        def __init__(self, value: int) -> None: ...
        def __eq__(self, other: object) -> bool: ...
        def __hash__(self) -> int: ...
        def __index__(self) -> int: ...
        def __int__(self) -> int: ...
        def __ne__(self, other: object) -> bool: ...
        @property
        def name(self) -> str: ...
        @property
        def value(self) -> int: ...
    Critical: ClassVar[Logger.Level] = ...
    Debug: ClassVar[Logger.Level] = ...
    Error: ClassVar[Logger.Level] = ...
    Info: ClassVar[Logger.Level] = ...
    Trace: ClassVar[Logger.Level] = ...
    Warn: ClassVar[Logger.Level] = ...
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def set_level(arg0: Logger.Level) -> None: ...

class Matrix12x12:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Matrix2x2:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Matrix3x3:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Matrix4x4:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Matrix6x6:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Matrix9x9:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class SizeT:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def One() -> int: ...
    @staticmethod
    def Value(arg0: int) -> int: ...
    @staticmethod
    def Zero() -> int: ...
    @staticmethod
    def size_bytes() -> int: ...

class Transform:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> Transform: ...
    @staticmethod
    def Rotation(arg0: AngleAxis) -> Transform: ...
    @staticmethod
    def Scaling(arg0: numpy.ndarray[numpy.float64]) -> Transform: ...
    @staticmethod
    def Translation(arg0: numpy.ndarray[numpy.float64]) -> Transform: ...
    def apply_to(self, arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    def inverse(self, arg0) -> Transform: ...
    def matrix(self) -> numpy.ndarray[numpy.float64]: ...
    def prerotate(self, arg0: AngleAxis) -> Transform: ...
    def prescale(self, arg0: numpy.ndarray[numpy.float64]) -> Transform: ...
    def pretranslate(self, arg0: numpy.ndarray[numpy.float64]) -> Transform: ...
    def rotate(self, arg0: AngleAxis) -> Transform: ...
    def scale(self, arg0: numpy.ndarray[numpy.float64]) -> Transform: ...
    def translate(self, arg0: numpy.ndarray[numpy.float64]) -> Transform: ...
    @overload
    def __mul__(self, arg0: Transform) -> Transform: ...
    @overload
    def __mul__(self, arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...

class U32:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def One() -> int: ...
    @staticmethod
    def Value(arg0: int) -> int: ...
    @staticmethod
    def Zero() -> int: ...
    @staticmethod
    def size_bytes() -> int: ...

class U64:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def One() -> int: ...
    @staticmethod
    def Value(arg0: int) -> int: ...
    @staticmethod
    def Zero() -> int: ...
    @staticmethod
    def size_bytes() -> int: ...

class Vector12:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: int) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: float) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Unit(arg0: int) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitW() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitX() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitY() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitZ() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Vector2:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: int) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: float) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Unit(arg0: int) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitX() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitY() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Vector3:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: int) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: float) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Unit(arg0: int) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitX() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitY() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitZ() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Vector4:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: int) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: float) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Unit(arg0: int) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitW() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitX() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitY() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitZ() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Vector6:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: int) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: float) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Unit(arg0: int) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitW() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitX() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitY() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitZ() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

class Vector9:
    def __init__(self, *args, **kwargs) -> None: ...
    @staticmethod
    def Identity() -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: int) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float) -> numpy.ndarray[numpy.float64]: ...
    @overload
    @staticmethod
    def LinSpaced(arg0: float, arg1: float, arg2: float) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Ones() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Random() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Unit(arg0: int) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitW() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitX() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitY() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def UnitZ() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Values(arg0: numpy.ndarray[numpy.float64]) -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def Zero() -> numpy.ndarray[numpy.float64]: ...
    @staticmethod
    def shape() -> tuple[int, int]: ...

def config() -> json: ...
def default_config() -> json: ...
def init(arg0: json) -> None: ...
