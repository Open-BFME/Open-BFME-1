# TheTerrainRenderObject provider and texture-matrix binding

## Native identity and ownership

The native datum is `BaseHeightMapRenderObjClass *TheTerrainRenderObject`.
The existing definition is `game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp:158`; the existing canonical declaration is in `inputs/reference/shims/bfmeheightmap/W3DDevice/GameClient/BaseHeightMap.h:345`.
This repair registers that existing definition rather than defining a second pointer.

Its retail home is VA `0x012F7FE0` (RVA `0x00EF7FE0`), four loader-zero bytes in `.data`. The official data-row verifier independently compiles `sizeof(::TheTerrainRenderObject)` as four bytes, equal to the COFF allocation extent. The canonical DIR32 map already places the same decorated name at this home.

The separately matched constructor `BaseHeightMapRenderObjClass::BaseHeightMapRenderObjClass`, RVA `0x006CFAE0`, 1307 bytes, declares this canonical pointer and assigns `this` to it. Actual retail instruction RVA `0x006CFC9A` is `mov [0x012F7FE0], esi`. This constructor corroborates the datum identity independently of the caller repaired here.

## Caller and offsets

The existing 281-byte body at RVA `0x007DCF00` retains its address-derived method and opaque matrix ABI. Its executable boundary ends in `ret 0x0C` at RVA `0x007DD016` (next RVA `0x007DD019`). No method identity or original matrix argument type is newly claimed.

Actual retail instructions establish:

| Instruction RVA | Read |
| --- | --- |
| `0x007DCF00` | pointer at VA `0x012F7FE0` |
| `0x007DCF05` | byte at receiver `+0x306C` |
| `0x007DCF1B` | map pointer at receiver `+0x2FF4` |
| `0x007DCF21` | map border at `+0x10` |
| `0x007DCF24` | map width at `+0x08` |
| `0x007DCF27` | map height at `+0x0C` |

The meaning and original type of the byte at `+0x306C` are unproven. It remains an explicit byte read, with no invented member, padding, or layout. The existing opaque map view retains independently witnessed width, height and border offsets; its border volatility is an emission constraint, not a native type claim.

The caller adopts the existing canonical header and removes the wrong `g_bfmeG1059` declaration and its terrain facade. Native SDK declarations provided by the included headers replace the local D3DX declarations; the opaque matrix storage is cast only at those existing SDK edges. No shared header, fake import slot, global alias, symbol pin, or baseline is added.

## Verification and impact

The independent probe compiles the edited source: 281 bytes, 11 real relocation fields, exact outside those fields. The ordinary scoped gate covers the caller, its existing native data owner, and the independent matched constructor.

The old caller's sole unresolved name in the saved accepted census preview is `?g_bfmeG1059@@3PAVBfmeG1059@@A`. Source gain is measured from fresh objects against the frozen accepted index and labelled as a per-file preview. The body was already authored C++; this repair adds no newly recovered function bytes. The only new data ownership is four bytes at the existing native datum.

Strict native binding controls link successfully with the repaired caller's actual DIR32 operand pointing to the selected four-byte native datum. All five calls bind to the three native SDK public providers, their actual fast-table fields and native initializer bodies; all five constant operands retain the physical retail values. Missing datum and legacy alias controls both fail with exit 96. No symbol stubs were needed. This sliced fixture proves these native edges and initial data, not whole-image or runtime closure.

The fixture links the full native SDK math member with genuine CRT libraries. Its PE imports include 14 retail imports and genuine C++ allocation/deallocation exports absent from retail. This is another reason its result is limited to the datum and SDK edges above.
