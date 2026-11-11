# Native Object-pointer list-base destructor and node contract

Input16b521b3ea, retail SHA256
1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.
Proposed sole identity at RVA000CEBD0 is
`??1?$_List_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ`.
Old row tg_000cebd0 describes a list<int> duplicate and borrows its object
symbol in HordeContainDestructors.cpp. Equal66-byte bodies do not justify that
identity, nor two identities at this address; retail has no ICF.

## Independently rechecked native pointer chains

These are raw native observations, not acceptance of the banked parent sources
in001d88c0/002382d0 evidence. Complete helper disassembly and actual route
bytes are preserved in build/object-list-native-chains.txt,
object-list-raw-parent.txt and object-list-deallocator-full.txt.

1. Native parent001D88C0 copies the list at001D900B through thunk385F5 ->
   complete111B copy001CB160. That copy allocates12-byte sentinel storage,
   self-links offsets0/4, then calls thunk4FFC -> complete66B range insertion
   001C53B0. Insertion allocates12 bytes through82E540, copies ONE dword from
   source node+8 to destination+8 and links next/previous at0/4. The parent's
   loop at001D9022 loads that payload as a pointer and dispatches through its
   virtual interface; it destroys this SAME list at001D904F through E68D.
2. Complete413B population00237FB0 independently copies payload+8 through
   the same12-byte allocation/link pattern. Its hash lookup at00238074 reads
   the returned pointer from hash-node+8 and stores it at list-node+8. Its
   complete final cleanup00238133 calls E68D. Thus these values are pointers,
   not integer IDs selected merely because both have four-byte size.
3. Complete225B consumer0023FDB0 loads list-node+8 into ESI at0023FE00, then
   dereferences its+204 AI pointer at0023FE03 and+210 ExperienceTracker pointer
   at0023FE28. These agree with the existing evidenced canonical Object layout
   in game/GameEngine/Source/GameLogic/Object/object.h; the matched consumer
   includes that header. This is the concrete Object relationship, not a
   destructor spelling inferred from allocation size. Source-only partial
   parent sketches are not byte acceptance or additional name proof.
4. Native cleanup routes18949 ->D0020 ->E68D ->CEBD0, and direct E68D calls
   above, reach the complete66B destructor. It walks next links, saves the
   successor before freeing each node, then frees the sentinel; payloads are
   NOT deleted. Both deallocation calls pass pointer + size12 to82E5F0.
   Complete85B deallocator82E5F0 reads those cdecl arguments and selects its
   bucket by(size-1)>>3 at0130B1C0, with its existing lock/unlock calls.
   This is NOT a raw free/new allocator contract.

The existing Object* pin at E68D and ILT-name confirmation p_false=7.18e-04
corroborate the typed native chains. The old int decoration is contradicted.
Neither oracle nor66B equality substitutes for the observations above.
The66-byte extent ends in RET followed by padding; the complete decoder checks
instruction endpoints. No alias/pin/body-boundary expansion is proposed.

## Coherent physical class repair

The generic vendor node has next0/previous4/payload8. Its TU-wide
BFME_PARTICLE_LIST_NODE_TAIL adds32bytes to EVERY payload, including Object*.
Exactly3 game TUs define it: InGameUI.cpp, InGameUI_selectNextIdleWorker.cpp,
ParticleSys.cpp. All3 now have the literally identical Object*-specific
specialization, before instantiation, using the existing base/data/trivial
members. Only this already-evidenced pointer payload loses the artificial tail.
The other Superweapon/particle/animation payload contracts are untouched.
No shared/vendor header is changed; do not infer other payload widths from
Object's size. Primary non-tail and all3 specialized views independently
compile to size12/alignment4/next0/prev4/payload8. Private explicit-output
measurement: build/object-list-layout-proof.py/.json, seven actual probe COFF
arrays including TransportContainOnRemoving.cpp. The initial aggregate7 probe
FAILED because the relocated private seventh source could not resolve its
original relative Coord3D.h include. The six successful contexts were retained;
the seventh was separately recompiled to an explicit private output after
mapping that original relative include to its existing BFME1 Wine-absolute
header path. It returned12/4/0/4/8. Failed aggregate logs and the separate
corrected seventh-success log are preserved; no fallback header or shared
verified object was substituted. This corroborates, rather than replaces, the
native chains.

TunnelTracker's global static-STL flag was REJECTED despite row matches: it
introduced542 additional COMDATs. A donor-backed declaration-only specialization
of the Object* base destructor suppresses only the wrong imported copy while
retaining the original allocator/consumer context and no new COMDATs. The
existing correct unchanged OpenContain emitter supplies the native body.
HordeContainCreatePayload uses static STL and removes _STLP_USE_NEWALLOC:
static alone changed the wrong68B imported variant into a still-wrong62B
raw-delete variant; the real bucket allocator restores66B. No handwritten helpers,
imports, aliases or pins are added. Compiler-emission additions/removals are
reported explicitly in the footprint below. Keep these allocator edits separable from
the3-TU layout repair.

## Provider/consumer verification and limits

Normal unified eight-source gate (six changed + unchanged OpenContain and old
ledger-owning HordeContainDestructors):250/250 functions,2data rows,
6literals+1empty,21floats,138DIR32, no unverified refs or baselined findings. One InGameUI funclet is repinned ONLY through eh_state_pins: native
parent addWorldAnimation ->state0 ->actionC22DD0 uniquely selects $L109546;
final independent check is proven/unique, exit0. Equal-byte auto-recovery alone
was not used as ownership proof. Normal sole-writer verification preserves all
row bytes. Logs: build/object-list-unified-final.log and object-list-eh-final/.

Strict target-copy proof changes InGameUI wrong66B and two wrong68B copies to
native66B digest20caad36d6dd (Tunnel now uses the retained external provider).
All current available cached emitters are surveyed, not unavailable/future
objects. The initial pin-only home misleadingly classified an old5B
TransportContainOnRemoving.cpp implementation as retail by matching the ILT.
Once the real66B body row is present it correctly becomes WRONG; the failed
assertion/report is retained. Parent explicitly admitted this single sixth-TU
prerequisite: remove ONLY that handwritten union-call dtor trampoline and its
unused j declaration; use declaration-only canonical binding. No alternative
wrapper/alias/pin or constructor/flag/layout change. Full987B onRemoving passes
normal byte verification. Paired597 retained sections preserve body/flag/
definition/relocation meaning after the sole j_E68D-to-canonical-member
substitution and SafeSEH symbol-index renumbering; the fake5B body disappears.
The complete section-aux/association audit checks all597 retained sections.
EXACT EXCEPTION: .sxdata raw symbol-index payload1927->1922 and its non-COMDAT
(selection0) checksum1975621639->1109354549 change while resolving to the SAME
onRemoving EH handler. Both checksums recompute exactly from their raw payloads
(CRC32 init0/no final xor). Other aux fields and association-owner graph are
unchanged. This is semantic SafeSEH/selection metadata equivalence, NOT raw-all-
aux equality. See build/object-list-transport-sectionaux-final.json. The native handlerC0D7C8/FuncInfoDFC490 has exactly
state0->-1/actionC0D7C0,8B `lea ecx,[ebp+4];jmp list-dtor`. Before/after COFF
maps retain this action and public-list-dtor reference; native route is
18949->D0020->E68D->CEBD0. See build/object-list-sixth-proof.json and
object-list-sixth-native-eh.txt. Equal-byte auto-label inference is not proof.

After this bounded removal all43 remaining available Object*base-dtor copies
are complete66B/native, no5B exception. Complete added/removed/changed
COMDAT/definition/undefined footprint is in build/object-list-footprint.json;
all non-Object list payload copies in the3tail TUs are unchanged. Tunnel removes
5Object-related copies/adds none; Horde adds4 compiler allocator leaves and
changes7 copies (including previously wrong copy-constructor now unplaced/
unknown), explicitly NOT all claimed native matches. Its2old imported allocator
externals disappear in favor of the existing native bucket/new/delete symbols.
No handwritten helper is added. Transport removes1bad copy, changes only the
expected public-list wrapper/caller binding and adds the canonical undefined
member. No hidden44B Object* native counterexample is in the inspected corpus;
do not claim a full census or universal linking gain.
Historical842B queue preview is a lead only. Current linking is UNKNOWN;
no actual current linkwinner, census gain or family-closure credit is claimed.
Other unplaced helper verdicts/selection limitations remain in the full report;
this is not permission to chase additional TUs or force a name/placement.

Four present-unmatched ParticleSys methods also have REAL immediate-code
changes, not merely hash/local-symbol renames: computeParticleVelocity4,
updateWindMotion7, computeParticlePosition15 and computePointOnUnitSphere3
PUSH __LINE__ arguments each increase10 after the inserted10 source lines.
All other bytes and relocation meaning are identical; local jump-table labels
renumber at unchanged offsets. The complete native69B GetGameClientRandomValueReal
at00096E80 ignores file/line arguments and reads only ESP+4/+8, so this changes
no RNG/algorithm behavior. Those four methods are NOT newly byte-matched.
Read-only detail: build/object-list-particlesys-four-meaning.json; the native
callee behavior and complete unchanged remainder were independently reviewed.

## Reference provenance

Pinned donor76f0baefa6f285d54bc1ca922397674312a5913f,
Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp has declaration-only
_List_base<Object*> suppression. This supplies an emission lead, NOT BFME1
identity/layout. Its _STLP_USE_MALLOC and ::free allocator specializations are
INAPPLICABLE: BFME1 independently calls82E5F0 with size12. No donor flags,
headers, addresses or free-based body are copied. Code maps to game; local
canonical provider is unchanged OpenContain.cpp. Zero Hour's actual Object
list declarations corroborate pointer containers but do not establish the
BFME1 target's offsets or allocator. Compiler MSVC7.1 13.10.3077, original
/O2 /MD/EHsc contexts and approved private WoW64 prefix/BUILD_POOL=2.

Parent independently APPROVED exact9892fd1a59 code/ledger/retirement/sole-writer
EH repair for normal publication, with the evidence-only clarifications above.
Root proof/hash packet:
/home/wacket/Projects/Open-BFME/build/sol12h-20261111-171921/object-list-parent-review.json.
No additional TU/header/pin/alias expansion is approved. If a retained44B Object*
contract or wider required change appears, bank/revert rather than force a name,
add a data alias, or weaken a baseline.
