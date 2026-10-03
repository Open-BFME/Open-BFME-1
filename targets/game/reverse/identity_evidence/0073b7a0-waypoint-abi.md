# RVA 0073B7A0: opaque traversal body

The source retains the address in `Rva0073B7A0`; it does not claim an original
function or class name. No source twin, named caller or constructor-proven
vtable entry identifies the original owner.

## Boundary and ABI

The retail unpacked executable at RVA 0073B7A0 starts by loading TheTerrainLogic
from VA 012EF4CC. Its ILT entry RVA 00024E6F jumps here. Ghidra creation yields
179 bytes, corroborated independently by Capstone: RET at RVA 0073B852, INT3
at 0073B853. ECX is overwritten before use, no stack argument is read, and
RET has no immediate. An ordinary zero-argument function represents that ABI.

## Distinct native layout views

Existing TerrainLogic and View headers are included, not redeclared. The
address-qualified views describe only native reads and calls; they do not
replace the donor types or change any shared header.

* Terrain singleton virtual offset 0x78 returns a node pointer.
* Node coordinate words are at 0x0C/0x10/0x14. There is a four-byte gap at
  0x18 before the next pointer at 0x1C. Eight indexed pointer slots begin
  at 0x20; the native range guard rejects indices below zero or at least eight.
* A separate signed count is read at 0x4C, after twelve opaque bytes at 0x40.
  The count can exceed eight, but invalid indices skip drawing.
* TheTacticalView at VA 012F1600 is dispatched through virtual offset 0x2C.
  Both calls push two coordinate pointers, a 32-bit color and zero. The view
  declaration uses bool for the final zero, without claiming the virtual name.
* The first call uses the node coordinate and a temporary whose Z is raised
  by native float 10.0 (VA 01075C74), color FFFFFF00. Each valid nonnull link
  uses its coordinate and color FF646400. These are the literal native values.

The body has no direct callee pins. The existing canonical TerrainLogic* and
View* global spellings resolve to the two native global operands. Verify those
DIR32 relocations and the 10.0 constant as well as masked instruction bytes.

## Source shape

The coordinate temporary must live outside the outer loop. Declaring it
inside yielded 179 bytes but 44 differing bytes from reordered loads/stores.
Hoisting it reproduced the native scheduling. Scalar component copies retain
the canonical Coord3D type. Compile-time offset checks cover all node reads.

`add_match.py --replace-rva` ran the scoped build successfully: 1/1 functions,
all 179 bytes exact; constant verification checked the one float and DIR32
verification checked all four absolute references. Independent retail reads
confirm ILT bytes `e9 2c 69 71 00` and 10.0 bytes `00 00 20 41`.
