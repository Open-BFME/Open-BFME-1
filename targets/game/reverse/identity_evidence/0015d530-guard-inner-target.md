# AIGuardMachine::lookForInnerTarget: complete BFME reconstruction

Retail RVA `0015D530` has a complete **2,514-byte** body ending at `0015DF02`.
This remains a nonmatching evidence bank, with **zero new native bytes**.
The executable SHA256 is
`c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9`.
The independently authored AIGuardOuterState::update caller, the existing named
pin, and the distinctive Zero Hour AIGuard.cpp guard-target/filter flow establish
the identity. The older bank was only a 1,716-byte prefix despite its estimated
0.55 score; it omitted most iterator cleanup and the second scan. Fresh
read-only Ghidra plus complete raw disassembly supplied the BFME behavior.
Decompiler types and normalized shape were not treated as byte proof.

## Complete behavior and independent contracts

The source preserves the goal-object and team-target early returns, Object/Team
scan position, linked relationship/attack/map/kind filters, scan timing, optional
polygon/flying/sight filters, collected-ID fallback, closest-object fallback,
contained-target resolution, area-cell floor conversions, second scan and all
iterator/collector cleanup paths. It uses the canonical Object and Coord3D
headers. AIGuard_getGuardScanPos.cpp independently witnesses guard fields at
10/44/48/4C/50/5C/68; retail proves the nemesis/mode/scan fields at6C/70/74.
No assertion about the runtime value of an INI-configurable constant is made.

- PartitionManager iterator wrapper `009F2960` is57 bytes, thiscall with a
  hidden four-byte return and five explicit arguments, RET18. It loads the
  grid at receiver+C, forwards the arguments plus a middle zero to009F63D0,
  and returns the hidden result pointer. Native Rva002113A0NearbyObjects and
  Rva00265150FilteredTargets independently supply the holder layout: a native
  vector of8-byte entries, cursor+C, reference count+10. Cleanup decrements
  that count and deletes the native vector/holder at zero. Independent agent B
  decoded the whole wrapper and confirmed these contracts.
- PartitionFilter::link `009F2AE0` is46 bytes, one stack argument, RET4. It
  retains this as EAX, walks next pointers at+4, and appends at the tail. B
  independently confirmed both returns. The closest-object wrapper is009F26A0.
- The visible PartitionFilterAcceptByKindOf constructor at000C3DD0 emits
  **102/102 exact bytes modulo its vtable relocation**. Its two24-byte masks,
  +4 null link and vtable store agree with the independent existing native
  owner; slot1 reaches the matched two-mask Object predicate. The one-bit clear
  mask is a real temporary for bit129. Ending that temporary at the constructor
  statement and exposing the real constructor body recovers retail frame144.
- Visible Overridable::getFinalOverride at00087A80 independently emits
  **26/26 exact bytes**. The call is made on the next override at template+4,
  as in the original recursive implementation, rather than recursively passing
  the unadvanced template. Both helpers already have native owners and carry
  **no new coverage or ownership claim**.
- The building filter constructor001DCE00 is126 bytes. The map-status filter
  has existing address-derived identity Rva0025ED50ObjectFilter. The attack,
  flying, sight and collector filter views retain their vtable address tokens
  C956C4/C95FBC/C95FCC/C9608C; the attack table is not the different existing
  PartitionFilterPossibleToAttack table. Collector0015C4B0 is the existing
  105-byte destructor of an8-byte polymorphic member followed by a12-byte
  vector of IDs, not a fake pointer-only destructor.
- GateOpenAndCloseBehavior is the actual retail NameKey literal. FindModule
  001BEE60 returns a secondary interface, so the code checks it before
  subtracting4 and invoking virtual slot18. The explicit isKindOf call takes
  bit136 (0x88). Contained-target helper001C70C0 receives target as this,
  `(owner,true)` as its two stack arguments, RET8. Distance helper0015BE50
  receives each candidate as this and the scan position pointer; unordered
  comparisons do not replace the current best candidate.
- The second scan deliberately links its new local map/relationship chain but
  appends sight2 to and passes the ORIGINAL relationship head to iterate.
  Agent B independently audited stack-relative LEAs: retail +0748/+0777 use
  original-SP+3C (new map2); +07EC/+07FB use original-SP+50 (original head).
  This surprising behavior was preserved rather than repaired.
- The area position is three floats. Retail calls imported MSVCR71 floor three
  times, rounds the returned double to float, then performs the native float
  to integer conversion. The source uses floor plus the existing canonical
  fast_float2long_round primitive; no assembly was added. The older atan2
  declaration and /QIfist qword conversion were rejected as wrong behavior.

## Measured result and bounded residue

Final formatted complete source: **2,545 /2,514 bytes**, frame **144 /144**,
94 relocations, **1,319 differing masked positions**. There are **1,195 equal aligned positions**. The extent-aware positional score is
**1 - (1,319 + 31) / max(2,545,2,514) =1,195 /2,545 =0.46954813359528486**. The separate normalized instruction similarity
is **0.961**, with32 structural alignment differences. This is not a96.1%
byte match. The extra31 bytes remain a size failure.

The complete retail inventory contains30 distinct direct targets plus three
floor IAT calls. A strict main-body verification attempt stops at the guarded
floor DIR32 import because the drifting relocation site currently lies over a
non-import retail operand. This is a layout failure, not evidence for a new
floor pin. No all-callees-resolved or full-gate success is claimed for the main
body. The future exact pass must verify every chosen route after alignment.
No function ledger, pin, shared header or baseline was changed.

The bounded pass tried authentic temporary mask lifetime, a visible exact
accept-filter constructor, canonical Object/Coord3D adoption, a witnessed
AIGuard layout, native iterator/vector cleanup, scalar versus Coord3D area
positions and the visible exact recursive override reader. The last reader
improved normalized shape from0.944/40 structural differences to0.961/32,
while positional differences improved by only one byte. The residue is broad
stack-local allocation, query argument scheduling and control-flow placement;
further generic spelling sweeps are not justified without fresh evidence.

The bank tool retains the prior preferred source because its historical0.55
estimate exceeds this measured extent-aware positional score. The complete new source is
preserved as immutable alternative `a40def5f82323c033e994c8995554a885f3b6699d816f6382d6a112a4f2be24b.json` and is the recommended starting point;
the old estimate must not be interpreted as measured byte agreement.
Session approximately30 minutes, model=gpt-6. New headline progress: **zero**.

The first unpublished measurement archive used1195/2514 and omitted the31-byte
extent penalty. It is retained immutably as historical evidence; the final
verdict and recommended alternative use1195/2545. This corrects arithmetic,
not an additional matching attempt.
