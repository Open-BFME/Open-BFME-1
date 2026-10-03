# Physics coordinate-array cleanup at RVA 00C121A0

The retail 0029A150 parent has its EH prefix at 0029A160. The handler
immediate at 0029A163 selects C121BB, whose FuncInfo is E01630. Its unwind
map E01620 has state 0 -> -1 / C121A0 and state 1 -> 0 / C121B3.
This establishes ownership independently of neighboring code and names.

C121A0 pushes callback VA0041364C, count4, stride12 and EBP-6C, calls the
native EH vector destructor iterator at 009F6D76, and returns at C121B2.
The next action begins C121B3; the complete extent is19 bytes, with no
padding included. ILT1364C reaches the established Coord3D destructor5BC40.
Normal-path construction/destruction in the parent uses the same four
12-byte points. Ghidra's raw read agrees with the baseline PE.

The unchanged production TU already matches the930-byte parent and owns
four nontrivial Coord3D elements. Its established native array lifetime
emits this cleanup; no new facade, callback alias, wrapper or pin is added.
The ordinary strict build checks its known constructor/destructor and
Bezier calls, including all8 floating-point reference operands.

A separate header-adoption experiment reproduced both parent and action
using coord3d.h, bezier_segment.h and the real inline assignment bodies.
The required TU include_alias triggered a full gate, which waited on a
host build lock; that optional source change was withdrawn before any
commit. It is not part of this conversion or a claimed full-gate pass.
The proposal is preserved in local build/b2_physics_header_proposal.patch.

Final unchanged-source COFF: parent handler in section20 references
FuncInfo $T6597 in section24, whose map $T6608 selects predecessor -1 /
$L6539 for state0 and predecessor0 / $L6540 for state1. The action at
section20 offset0 is exactly19 bytes. The state1 ledger row is unchanged.
