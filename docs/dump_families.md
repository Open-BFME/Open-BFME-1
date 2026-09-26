# Shared-global family recipes

This note is the handoff for the 2026-09-16 family sweep.  It records only
addresses and layouts supported by retail bytes, landed source, or the Zero
Hour twin.  An anonymous dump remains anonymous until a caller, slot, string,
or other independent witness proves its identity.

## Family 13: `0x012F7FE0` / `TheTerrainRenderObject`

The explicit session list contains 31 bodies (the live `dump_families.py`
scan also reports 31, 66,570 bytes).  Every member loads VA `0x012F7FE0`.
The existing aliases in `targets/game/reverse/symbols.csv` store the same location as RVA
`0x00EF7FE0`; `0x012F7FE0 = 0x00400000 + 0x00EF7FE0`.  `TerrainTextureMatrix.cpp`
and the canonical `inputs/reference/shims/bfmeheightmap/.../BaseHeightMap.h` provide
the owner witness: this is `TheTerrainRenderObject`, a
`BaseHeightMapRenderObjClass`-compatible object.  The opaque pin
`?g_bfmeA1087@@3PAVBfmeA1087@@A` is an address alias, not a reason to invent a
new class name.

The field-access union across the 31 retail bodies is:

| offset | supported meaning | bodies that use it |
| --- | --- | --- |
| `+0x2FF4` | height-map pointer (`m_map`) | `0x00743520`, `0x007171F0`, `0x00763620`, `0x0071BBC0`, `0x00727E00`, `0x006EB500`, `0x007C3FD0`, `0x007CCF50`, `0x0071EEC0`, `0x007C5690`, `0x007CE290`, `0x007C7FD0` |
| `+0x3009` | byte flag; exact semantic name not proven | `0x007446A0` |
| `+0x301C` | maximum-height field (`m_maxHeight`) | `0x007171F0`, `0x0073E050` |
| `+0x30B8` | shroud pointer (`m_shroud`) | `0x0071A680`, `0x006C23B0`, `0x0071A680`, `0x00742920`, `0x006DA2D0`, `0x006EB500`, `0x007C3FD0`, `0x007A7240`, `0x007A37B0`, `0x007CCF50`, `0x0071EEC0`, `0x007C5690`, `0x007CE290`, `0x007C7FD0` |
| `+0x30BC` | adjacent taint/shroud field; semantic name not promoted here | `0x006EB500`, `0x007C5690`, `0x007C7FD0` |
| virtual slot `+0xEC` | virtual call on the same owner | `0x00743180`, `0x00746420`, `0x007446A0` |
| virtual slots `+0x208/+0x20C`, `+0x228`, `+0x21C/+0x234` | virtual calls on the same owner | `0x0007E9B0`, `0x006E2540`, `0x007446A0` |

The `+0x120E0`/`+0x10` accesses in `0x0071BBC0` are on the pointed-to
height map, not additional fields of the global owner.  The shared
declaration belongs with the existing BaseHeightMap/height-map shim; do not
add a second `BfmeA1087` header or a TU-local copy of `BaseHeightMap`.

The smallest clean candidate, `0x0071A680` (140 bytes), was compiled through
the existing `W3DShroud::getShroudTexture`/texture-handle shape.  The best
source is banked at `targets/game/reverse/attempts/0x0071a680.cpp`, score 0.95: it is
139 bytes versus retail 140, with the remaining difference in the hidden
handle return-slot register and temporary-handle store/destructor schedule.
The second short candidate, `0x006EBC30` (192 bytes), is the ZH
`W3DDisplay::setTimeOfDay` shape.  Its global prefix and both calls to the
already exact `updateLights` helper were reproduced; the remaining clean
probe difference is the ambient-vector register/temporary schedule and the
verified `j_00040bc9` tail.  Neither is claimed as a source match.

Recipe for an anonymous seat:

1. Start from `BaseHeightMap.h` and the landed local layouts in
   `W3DShaderManager.cpp`, `W3DDisplaySetBorderShroudLevel.cpp`, and
   `W3DTerrainLogicRva006BE890.cpp`.
2. Run `python3 tools/callees.py <rva> <size>` and use only those callee
   declarations.  The `TheTerrainRenderObject` global is the existing pin;
   no new pin is needed merely because the dump spells it `g_bfmeA1087`.
3. Use `/DNDEBUG /MD /EHsc` and the normal WWMath/WWLib include roots.  Probe
   one body at a time with `tools/probe.py`; the one lever that matters for
   the lighting body is the volatile global-pointer load plus preservation of
   the helper's VC7.1 internal EAX/EBX convention.
4. Land an exact C++ body with `tools/add_match.py --replace-rva`; otherwise
   bank the best clean body with `re_log.py record ... partial --stash ...
   --score ...` and include all tried source shapes in one evidence line.

## Families 14 and 15: DX8 state and `0x0134ECC8`

The user-supplied family-14 and family-15 lists are subsets/overlaps of the
live DX8 family scan.  Their shared character operand is VA `0x0134ECC8`.
The ledger pin is correctly written as RVA `0x00F4ECC8`; do not “fix” it to a
VA in `targets/game/reverse/symbols.csv`.  The bytes and `symbols.csv` therefore agree.
The value is one character of storage (`g_bfmeCh1035`), not a class layout.

The shared DX8 declarations belong to
`inputs/reference/shims/dx8state/DX8State.h` and the canonical WW3D2 headers.  The
existing matched helper
`DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name` at `0x00906FE0`, plus
`BoxSetTexture` at `0x00905AC0`, `StringClass::Get_String` at `0x009DB890`,
`StringClass::Free_String` at `0x009DB7A0`, and
`TextureClass::Release_Ref` at `0x009EB7A0`, are the reusable callee
contracts.  `0x01340534`, `0x01340568`, and `0x01340594` retain their
canonical DX8/scorch declarations.  `0x012D9124` remains opaque.

For these families the smallest useful recipe is the already matched
`Gen_0071B1F0_ShaderStageReset.cpp` pattern: use the shared DX8 state shim,
retain the `BoxSetTexture` handle ABI, and let the state-name helper run only
under the snapshot/diagnostic branch.  Compile each candidate against its
own byte range; sharing a call list does not prove its owner or method name.
Do not use the old local `DX8Wrapper`/`StringClass` stand-ins, and do not
promote `0x013F...` state bytes to names without a pin or field witness.

No new DX8 pin or header edit was required by the VA/RVA audit.  The listed
family bodies are consequently unlocked for the anonymous lane, while the
pre-existing partial attempts remain the evidence for bodies that have
already been explored.

## Current next-family scan

The live `python3 tools/dump_families.py --top 40` reports family 16 as
45 bodies / 65,283 bytes, anchored on
`UnicodeString::format` at `0x00889190`, with a 23-body overlap on the
`StringBase<wchar_t>` constructor at `0x00888DE0`.  It is not a DX8Wrapper
family and is the next shared-call lane after the three explicit W3D
families.  Its smallest members are `0x005867D0` (185), `0x00591A60` (195),
and `0x002184D0` (263); use `tools/callers_of.py`, the exact string headers,
and `tools/callees.py` before naming any owner.  Families 17 onward should
be skipped only when their anchor is a DX8Wrapper state/helper that belongs
to the W3D lane.

## Family 16: Unicode/StringBase formatting contract

The live family-16 scan is 45 bodies / 65,283 bytes.  This is a shared call
contract rather than one newly proven global owner: the anchor is
`UnicodeString::format` at RVA `0x00889190`, and 23 members also call the wide
`StringBase<wchar_t>` constructor at RVA `0x00888DE0`.  The common cleanup
callee is `StringBase<wchar_t>::releaseBuffer` at `0x008881D0`; narrow-string
members use the corresponding canonical `StringBase<char>`/`AsciiString`
declarations.  These are existing ledger identities, not new speculative
pins.

The declaration belongs in
`inputs/reference/shims/stringbaseunicode/Common/UnicodeString.h` and its canonical
`StringBase` include path.  A candidate that also needs narrow strings must
use the existing ASCII shim selected by that source; do not add a local
UnicodeString, StringBase, or GameSpy text-object stand-in.  The working
compile contract is `/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
/D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC` with the relevant
`inputs/reference/shims/stringbaseunicode` and
`inputs/reference/shims/asciistring_downloadmanager` include roots.  Run
`tools/callees.py` on each body first and pin only a callee whose identity is
independently established.

The smallest anonymous bodies `0x005867D0` (185) and `0x00591A60` (195) are
not safe source owners: both have a live-in ESI contract, no named caller,
and no clean emitter.  The first ordinary candidate, `0x002184D0`, is proven
as `SalvageCrateCollide::executeCrateBehavior` by its vtable slot, caller, and
callee set.  Its clean C++ bank is size-exact (263/263, 15 relocation sites)
with six non-relocation bytes remaining: MSVC chooses EBP where retail uses
EBX for the module-data pointer, and emits EH state 0 where retail emits 5.
Local-order, pointer-type, declaration, and compiler-flag probes did not
move those bytes.  This is a banked near miss, not a landed body.

Recipe for the swarm: include the canonical Unicode/StringBase headers, use
the exact by-value temporary and `format` call shape witnessed by the retail
body, compile with the flags above, and compare the full range with the byte
gate.  The first useful lever is preserving the canonical temporary lifetime
through `releaseBuffer`; do not replace it with a helper or a guessed global.
The family has a verdict for every member and is unlocked in
`targets/game/reverse/unlocked.txt` with the `fam16` tag.  Family 17 shares the wide-string
constructor and can reuse this recipe, but still needs its own per-body
identity and byte verdict.

## Family 24: TerrainLogic layer-query pathfinding

Families 18 through 23 in the live top-40 ranking are DX8Wrapper/render-state
clusters and remain outside this lane.  Family 24 is the next eligible
family: 44 bodies / 57,484 bytes share
`TerrainLogic::getLayerForDestination` at RVA `0x001C675`.  The additional
features include the BFME ESF check, computer-controlled query, Pathfinder
query, terrain-step, and AI frame-state helpers.  This is a shared pathfinding
call surface, not proof that all 44 rows have one owner.

Use the existing Pathfinder/TerrainLogic declarations and the Zero Hour AI
pathfinding headers only where the caller and vtable evidence agree.  The
normal source flags remain `/DNDEBUG /MD /EHsc` plus the repository's standard
include roots; run `tools/callees.py` for each body and prove every non-opaque
callee before adding a pin.  The first three small rows (`0x0026F460` 213B,
`0x001C86B0` 302B, and `0x003F5C70` 335B) have no safe standalone owner.  The
named rows such as `Pathfinder::findGroundPath` and
`Pathfinder::internalFindPath` have semantic evidence but remain banked
near-misses where their clean C++ output is not byte-exact.  The family has a
verdict for all 44 members and is unlocked with `fam24`; no generated dump
was edited.

## Family 28: APT allocator and pooled-object contract

Families 25 through 27 remain DX8/D3DX or render-state families and are
skipped here.  Family 28 is the next non-DX8 cluster: 47 bodies / 55,537
bytes all read the APT allocator function pointer at data `0x01337828`
(`Rva008C5D70Alloc`).  Thirty also share the idle-pool object at
`0x01337810`; the smaller subsets expose the existing APT string truncation,
pooled-object constructor, and node-list contracts.  The allocator global is
already declared by the canonical APT sources, including
`Rva008CF3C0ParseAppend.cpp` and the APT primitive creators.

This family has no single owner layout.  Use the existing EA APT headers and
the exact pooled-object declaration for the selected body, with the normal
`/DNDEBUG /MD /EHsc` project flags.  `tools/callees.py` must be run per body;
the allocator pointer is not a reason to add a pin.  The smallest rows are
anonymous APT bodies with separate owners, while the largest `0x008BF100`
has no caller or built emitter and is recorded blocked.  All 47 members have
verdicts and are unlocked with `fam28`; no generated body was edited.

## Family 29: GameSpyInfo owner contract

Family 29 is the next non-DX8 global family: 44 bodies / 54,205 bytes read
`TheGameSpyInfo` at data `0x012F7194`.  The shared secondary witnesses are
`TheGameSpyPeerMessageQueue`, `TheGameSpyGame`, the canonical Unicode/StringBase
constructors, and the GameSpy message constructors/destructors.  Sixteen
members overlap the already unlocked family-16/17 rows; those addresses stay
listed once under their earlier tag.

The owner declaration belongs in the canonical GameSpy peer definitions,
`inputs/reference/shims/peerdefs/GameNetwork/GameSpy/PeerDefs.h` and
`PeerDefsImplementation.h`, with any TU-local ABI view justified by an
independent vtable slot or named caller.  Use `/DNDEBUG /MD /EHsc` and the
existing string/GameSpy include roots.  Do not name an anonymous body merely
because it reads `TheGameSpyInfo`; prove its method, callee ABI, and complete
retail boundary first.  The smallest family-only rows are still
address-derived GameSpy/Apt bodies; all 44 members now have verdicts, and the
28 rows not already unlocked by family 16/17 are tagged `fam29`.

## Family 17: wide-string constructor overlap

The next non-DX8 family in the live top-40 scan is 40 bodies / 61,958 bytes,
anchored on `StringBase<wchar_t>` construction at RVA `0x00888DE0`.  Twenty-
three bodies overlap family 16 and retain the `UnicodeString::format` recipe;
the other 17 are the family-17-only rows listed with the `fam17` tag in
`targets/game/reverse/unlocked.txt`.  The additional shared witnesses are
`StringBaseWideAP::bfmeConcatAP` at `0x00888600`,
`BfmeStrWVUY::bfmeTranslateVUY` at `0x008891F0`, and the existing
`GameSpyInfo`/`MapCache` globals.  They identify the reusable string ABI, not
a common C++ owner for every body.

Use the same canonical header and compile flags as family 16.  The first
lever is the visible wide temporary lifetime: keep the constructor,
format/concat operation, and `releaseBuffer` teardown in the source so the
EH state and by-value string ABI remain available to MSVC.  Run
`tools/callees.py` per body; do not pin the address-derived helpers merely
because they occur in this family.  All 40 members now have recorded
verdicts; no family-17 body was byte-exactly landed in this pass, and the
17 newly unlocked rows remain available for a worker with a proven owner.

## Families 33-35: scalar constants already witnessed

The next audited non-DX8 groups are scalar-global families rather than
unmodelled object layouts.  Family 33 has 49 bodies around the VA
`0x01075C74` direction-weight constant; the source witnesses in
`W3DTerrainLogicRva006BE890.cpp` and `PathfindSnapLineCellCallback.cpp` are
already present.  Family 34 has 36 bodies around VA `0x0107FAC4`, the same
`g_bfmeScaleBC` symbol whose ledger pin is the corresponding RVA
`0x00C7FAC4`; the VA/RVA distinction is intentional.  Family 35 has 45
bodies around VA `0x01075C70` (`g_bfmeScaleBK`), also already used by the
terrain and AI sources.  Families 30-32 were skipped as DX8/render-heavy
clusters despite their non-DX8-looking secondary anchors.

All members of families 33-35 now have verdict evidence, including the
newly recorded anonymous blockers at `0x003F82C0` and `0x007C2490`; the
already matched MASM bodies remain exact but are not clean-C++ landings.  No
new unlock rows are added for these groups because their shared constants
already have source witnesses and their bodies overlap the earlier handoff
rows.  Future work should replace only an identity-proven body, using the
existing scalar declarations and the ordinary project flags; do not move or
rename the VA/RVA pins.

## Family 39: UnicodeString empty-string global

Family 39 is the remaining eligible top-40 cluster after the render-heavy
groups: 33 bodies / 45,891 bytes share the canonical
`UnicodeString::TheEmptyString` object at VA `0x01336E54`.  Secondary
witnesses include the existing GadgetTextEntry, MapCache, GameSpyInfo, and
wide-string translation contracts.  This is another shared string-global
surface, not one common owner layout.

Use `inputs/reference/shims/stringbaseunicode/Common/UnicodeString.h` and the
existing GameSpy/GUI declarations, preserving the by-value string ABI and
temporary cleanup.  The normal flags are `/DNDEBUG /MD /EHsc`; use
`tools/callees.py` and named caller/vtable evidence before claiming a real
method or adding a pin.  All 33 members have verdicts, including the newly
recorded blocked `0x006AF840`; the 22 rows not already handed off under
families 16, 17, 24, 28, or 29 are tagged `fam39`.  Families 36-38 and 40
remain skipped because their shared feature sets are DX8/render-owned.
