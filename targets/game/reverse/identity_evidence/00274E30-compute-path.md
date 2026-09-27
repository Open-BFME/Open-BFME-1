# AIUpdateInterface::computePath, RVA 0x00274E30 / 3472 bytes

This is a measured bank improvement, not a native landing. The current
preferred source emits3416 bytes,227 relocations,1488 differing masked
positions and56 missing bytes:1928/3472 equal positions,
score0.5552995391705069. Normalized instruction agreement is0.946 with46
structural differences; this is not byte coverage. There are144 relocation
layout mismatches. No game source, function row, symbol pin or helper
ownership was changed.

## Identity and proven source corrections

The independently native AIUpdateInterface::doPathfind caller in AIUpdate.cpp
calls this through ILT0x00023209. It supplies the PathfindServicesInterface*
and writable Coord3D* arguments; RET8 and the byte return agree. The Zero
Hour computePath twin in AIUpdate.cpp:1675 establishes the method family;
BFME adds the path-portal early return, debug tracing and movement policy.

The old bank defined Region3D::isInRegionNoZ using inclusive comparisons
and forced both calls inline. Canonical basetype.h:445 and the independent
66-byte native helper at0x000FBA20 prove strict lo<query<hi bounds. Retail
+0x2E7..+0x31B contains the strict inline test, while+0x345 calls that helper
for the copied current position. Removing forceinline and restoring the
actual condition improves normalized instruction agreement0.873→0.946.
The default branch and NaN behavior now follow the shipped helper.

The bank now includes canonical ascii_string.h/string_base.h and the real
StringBase<char>::str body. The coordinate copy constructor remains the
existing witnessed member-wise form. A separate canonical basetype.h POD
variant was measured at3419 bytes/score0.39746543778801846 and archived;
it changes coordinate copy scheduling and does not fix the frame.

The 36-byte Path output record is independently established by native
Locomotor_rva001B7200.cpp:43: float at+0,Coord3D at+4,three floats at+0x10,
layer at+0x1C and the integer tested here at+0x20. The old bank placed the
layer at+0x10; the overall size and tested final offset were already right.

At retail+0x60F, isLinePassable's result is consumed through AL. Its full
native131-byte body at0x003EE7A0 returns0/1; its older recovered view uses
int, but the original Bool interface and this caller support the bool view.
The bank uses bool. No new pin was added: this and other inherited callee
aliases require strict resolution before a future landing.

## Bounded helper and lifetime experiments

Before writing, callees.py inventoried all21 distinct direct targets.
Independent review confirms the strict-region logic and the movement policy:
template+0x4B1 OR KindOf124 enables moving allies, and KindOf138 disables it.
The apparent missing KindOf124 region in the shape alignment is a diff
alignment artifact, not missing source behavior.

The real setter at0x0016A6D0 copies three words to+0x180 AND clears the byte
at+0x31D. Both effects were retained in the visible noinline alternative;
the emitted helper independently matches all38 bytes. Its caller becomes
3414 bytes/score0.5544354838709677. The helper is already represented by
Rva0016A6D0::set, so it contributes zero newly recovered bytes. An earlier
copy-only experiment was incomplete and was discarded, not banked.

The complete existing CRCParameterCheck logger body was also tried visibly
out-of-line, alongside its declaration-only form; caller code is identical.
The logger helper itself emits156 rather than215 bytes under this probe's
flags, so no helper match is claimed for that experiment. Other measured
levers were inline/noinline authentic Overridable traversal, canonical
coordinate/string headers, object-ID and logger capture, split coordinate
initialization, bool/int low-byte call views, and boolean local spelling.
No volatile, dummy locals, padding, barriers or assembly was introduced.

Remaining differences begin with frame0x5C versus retail0x64 and logger
pointer in EDX versus EBX. Retail spills the initial object ID and path
result, preserves the movement decision in stack byte+0x13, and merges
several trace paths differently. Capturing the object and logger restores
the first branch boundary but does not reproduce whole-body allocation.
The original source had3448 bytes,2085 differences,24 missing bytes,
score0.39256912442396313. Its0.56 header was an author estimate. Exact
original bytes were archived before correcting that metadata.

Original archive: targets/game/reverse/attempt_history/0x00274e30/bd865bee2186fb750ba523c2e975f8bcf225e67216940e69b3c31c44fad6a53b.json

Alternatives:

- canonical: targets/game/reverse/attempt_history/0x00274e30/53215294f511de6d3142153293779913f4e6a6efac20dcc8e5fc3aa4ca8cd986.json
- typed-setfinal: targets/game/reverse/attempt_history/0x00274e30/01f3dc489d9b72eec259cf1152c66d9c39fcb8a9fd246e787769a5f1228ef177.json
- typed-entry: targets/game/reverse/attempt_history/0x00274e30/ffe62c841f01038910bb2dacc9bda8b133beb2413844b7d7245a52db6514345c.json
