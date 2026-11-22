# Object-AI loop: call the existing predicate owner

Native `link_check.py near --packet` served the complete one-row source
`game/GameEngine/Source/GameLogic/AI/RunReadyObjectAI.cpp`:68B at003D55C0,
with no owned data rows. Its only link blocker was the undefined legacy
`BfmeReadyGate::bfmeReady()` spelling. The actual59B authored provider is
`Rva003FD060Owner::anyBlocked() const`, in
`game/GameEngine/Source/Common/SmallGaps/Rva003FD060AnyBlocked.cpp`.

The original caller's complete68B body calls ILT2E8ED ->3FD060 with the
unchanged pointer from its existing AI view's+140 field in ECX, no pushed
arguments, and tests AL. The complete59B target traverses its+4 chain,
tests the stored id against INT_MAX, queries the existing terrain vslot32,
and returns AL0/1 with plain RET. Its actual current normal object independently
passes all59 original bytes. The provider's existing const member model is
retained; machine code alone does not recover its original constness or class
identity. The caller uses only an opaque method view and a pointer-sized field;
no pointee storage layout, new semantic API or original EA name is claimed.

Replace that declaration/field pointer and call by the already-owned provider
name. The loop, condition polarity, action call, object offsets, globals and
compiler profile remain unchanged. There is no header/provider/pin/alias/data
change and no new function or added escape hatch. The source's summary comment
describes the actual predicate test without inferring a new gameplay role.

Normal whole-source gate:1/1, all68 original bytes,1DIR32 reference, no body-guard
findings. `find_declared_unmatched.py` passes. Both real normal objects have
identical raw code, complete runtime section bytes/flags/sizes/definitions,
default libraries, weak externals, COMDAT selection and FPO metadata except
the single independently proven REL32-name correction at+40. No verifier or
resolver mapping was changed to compare them.

Before, the ordinary current link preview reported only the absent predicate
and `LINKED0 ->0`. After, it reports `LINKS`, `LINKED0 ->68 bytes`,1/1 clean.
This per-file current prediction uses census index42237e2367; it is not a fresh
whole-image link or game-runtime result. Existing68B C++ and59B provider code
are retained; no new exact/code-coverage bytes are claimed.

BFME2 donor1e864b34e05f68568db539537b6959d94d104f57 was inspected within this
target: `Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp`, its canonical
`Code/GameEngine/Include/GameLogic/AIPathfind.h`, and
`PathfinderIsViewBlockedByObstacle.cpp`. Those support different cell/geometry
interfaces and layouts, not the identity of this opaque chain predicate. No
RunReadyObjectAI/AnyBlocked counterpart or existing-name binding was found;
no donor name, offsets, virtual interface or flags were copied. Zero Hour's
AIPathfind global-object classification loop also does not establish this
predicate/action identity. BFME1's original ILT/receiver/AL use and existing
authored provider are the authority for the repair. The proposed AIPathfind
TU-map hint is not treated as approval for a file move.

Full source/object/control/ABI/graph evidence, normal before/after logs and
the closed hash manifest are in
`W:/OpenBFME/diagnostics/one-per-project-20261122-followup/bfme1/`.
The earlier AI2067 blocker was only inspected with no claim or compiler trial;
the completed Value81 and parked Node13 branch remain untouched.
This task's lease is003D55C0=70baa7509e0d47b4933891993781e8d3.
