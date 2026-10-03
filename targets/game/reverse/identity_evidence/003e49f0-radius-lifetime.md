# RVA 003E49F0: radius output lifetime

Retail begins after INT3 at RVA 003E49F0 and ends with RET12 at 003E4CDE
(+2EE), followed by INT3 at 003E4CE1. The complete extent is 753 bytes.
Matched Pathfinder::isAttackViewBlockedByObstacle at 003EA570 passes the
Object pointer, position pointer and output ID array through ILT 00005484.
That proves the owner and ABI; its synthetic bfmeCheckAttackViewHelper
spelling supplies no EA method-name witness. The new method retains its RVA.
The original partial is archived byte-for-byte in 003e49f0-original-bank.cpp.txt.

Starting from the preferred bank and its canonical-header history, exposing
the authentic 297-byte getRadiusAndCenter body (003DEE30) reduces the residue
from 25 to 23 bytes. Replacing the artificial two-integer radius array with a
single scalar then permits the radius slot to be reused by the floor
conversion and loop bound. All 753 caller bytes now probe exact. The visible
radius helper also passes a strict selected-row verification at its complete
297-byte extent, including its one float constant and six DIR32 references. This follows
the independently matched PathfinderRva003DF250 and removeGoal003E3D20
precedents. Object and Coord3D use existing headers; no shared header changes.
The two-instruction fld/fistp helper is the established x87 rounding blocker,
not a lifted instruction body. No volatile qualifiers or padding are added.

The strict caller gate initially failed only on rva003FBB20. That callee was
independently decoded, not inferred from the failed call:

- ILT 00009A89 is E9 to 003FBB20. The body is preceded by INT3 and ends with
  RET8 at 003FBB72, followed by INT3 at 003FBB75 (85 bytes total).
- ECX is a layer receiver; two stack integers are coordinates. The caller
  computes that receiver as Pathfinder + 85C + 44*layer, the established
  layer array and stride from matched Pathfinder implementations.
- The body reads row pointers at +4, width/height +8/+C, origins +10/+14,
  checks coordinates, and returns a 16-byte cell pointer unless type bits
  at cell+C equal 5. Ghidra and retail disassembly agree.
- Although all 85 bytes equal 003FBAB0, retail has separate bodies. No semantic
  getCell identity is transferred. The new pin is the opaque
  PathfindLayer::rva003FBB20 at the actual body, not an ILT routing alias.

The snapshot-bound name corrections cover the historical bank comparison:
its unsupported helper spelling and duplicate getCell declaration become
address-qualified methods. No established production identity is renamed;
the replaced row is only the generated d_003e49f0 placeholder.
