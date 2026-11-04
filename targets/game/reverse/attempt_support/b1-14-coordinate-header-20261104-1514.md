# Adopt canonical Coord3D in LuaObjectBindings002E6650

Replace one private data-only Coord3D definition with the registered existing
header `game/Libraries/Include/Lib/Coord3D.h` at a source-relative include. The native compiler's
CodeView layout proves struct/size12, fields [[0, 'x', 'float', 4], [4, 'y', 'float', 4], [8, 'z', 'float', 4]], with no bases,
vptr, methods or static members. This agrees with BFME1's current canonical
class contract. Keep every body, field spelling, ABI/compiler option and all
other definitions; no shared-header, ledger, pin, alias or baseline change.

Native normal/frozen/header-acceptance gates pass for 2 existing
function/EH rows. All 6 external code definitions/relocations,
named local code and all non-debug object sections remain identical. The only
new resolved dependency is the adopted header; every old header path and hash
remains. No generated code recovery, native-byte, runtime, memory or crash gain
is claimed. The private copy count is lower by one; a full linking result is
not established by this source-local byte preservation.
