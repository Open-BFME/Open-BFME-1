# Formation member update, RVA 0x00241050

The existing 1540-byte extent ends at RET +0x603; INT3 begins at +0x604.
The matched `BfmeAODHordeContainOwner::updateAODFormation` at 0x00230AE0
calls `updateFormationMembers` through ILT 0x00010D6B. Its existing source
and this direct caller establish the retained owner/method spelling. Unknown
records and virtual interfaces retain address-qualified names.

The saved score-1.0 reconstruction is the starting source. It uses the existing
Object and Coord3D headers and the authentic visible GameLogic lookup. Its
1540 bytes probe exactly with 41 relocation sites. No assembly or shared-header
change is needed.

## Delay tree lookup

The call at caller +0x447 encodes ILT 0x000416AA, which jumps to 0x00235BA0.
The preceding LEA selects receiver+0x144 and the two arguments are a hidden
iterator result address and a reference to the member ObjectID. The body
loads the tree header from receiver+0, descends left/right through node+8/+12,
and compares signed integer keys at node+0x10. Both exits store a node into
the result address, return that address in EAX, and pop eight stack bytes.
The complete body is 71 bytes, ending with RET 8 at +0x44, then INT3.
Ghidra and direct retail decoding agree on this ABI and search algorithm.

The caller reads mapped storage at node+0x14: three coordinate words followed
by a countdown at +0x0c. `Delay00241050` therefore retains its address-based
identity. The native `_Rb_tree<int,pair<const int,Delay00241050> >::find<int>`
emission independently matches all 71 bytes with **zero relocations**.
The new binding pins that emission to the body, not to the ILT. The existing
`dup_235ba0` ledger provider remains unchanged: its GameSpy template is a
byte-identical donor, not evidence that this caller owns a GameSpy map.

## Thing angle helper

The caller's two encoded call sites reach ILT 0x00049413, then the already
matched 214-byte `Thing::bfmeRelativeAngleTo` body at 0x00150510. Additional
source calls share these tails. The callee reads the pointed coordinate's X/Y
at +0/+4, subtracts receiver position +0x38/+0x3c, normalizes, gets the unit
direction, clamps the dot product, calls ACos, and chooses the sign by the
2D cross product. It returns in ST0 and pops one four-byte argument.
Ghidra independently recovers these operations; the existing matched source
provides the same contract.

The canonical coordinate header declares `class Coord3D : Coord3DBase`, with
three contiguous float fields and no vptr. The helper's older TU declares the
same pointer payload as `struct Coord3D`. MSVC decorates these declarations
with PBV and PBU respectively. The new PBV pin is an ABI-compatible class-key
view of that same established method, not a second function identity. It pins
the real body at 0x00150510; no alternate-name linker mapping or route exemption
is used. The PBU provider and its existing users remain unchanged.
