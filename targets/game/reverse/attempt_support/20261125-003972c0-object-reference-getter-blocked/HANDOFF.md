# BLOCKED: exact caller correction cannot pass current provider policy

Current native refresh checked all 22,997 current objects and 1,888 data rows,
but still returned selected=getAllIDs wrong and LINKED 0 -> 0. No SourceTask,
new body, coverage or successful link is claimed. The candidate is banked;
the actual source is restored and rebuilt normally, with its own lease then
released before independent work continues. No tool, index, baseline, pin,
template identity or compiler-profile workaround was made.

The sole named getter owner itself is selected: AIGroup_getAllIDs.cpp,
object66f3076e3641d2aa04ce2b454ab57bbe56b9eaf1f5b31bedbebcd9bbdbbb3b6d,
136B COMDAT digest054f9cd871d2/NODUPLICATES. Nonrelocation bytes all match.
Native RetailTruth rejects its sole REL32 at +116: original10B8B ->1523D0,
whereas its ObjectID-overflow name has a functions.csv claim at33DAC ->36B490.
The existing10B8B pin is deliberately subordinate to that named ledger claim.
Native ILT oracle confirms the ObjectID name at10B8B (p_false4.57e-4) and
contradicts it at33DAC. This does not establish the replacement C++ identity
of33DAC or allow reordering pins.

There is also an independent actual helper mismatch: this getter TU emits a
332B ObjectID-overflow COMDAT; original1523D0 is282B, currently represented by
a ScienceType gen-alias in ParsePrerequisiteScienceThunk.cpp. Original33DAC
instead targets the265B generated struct/POD helper36B490. Existing old
attempt51245 already records this template-identity/family blocker; later
enum-adoption63530 explicitly supplied no link proof. A complete fix needs
independent original template/ABI ownership and a supported migration of these
existing rows, plus verified whole-TU helper code. No such fix is demonstrated
here, and no unchanged template/profile trial was repeated.

The following analysis records why the smaller caller correction was plausible
and exact. Its proposed source is useful only after those provider repairs.

# Object-reference getter binding, 0x003972C0 / 29 B

The existing caller names a nonexistent `BfmeObjectReference::getObjectIdSlot`.
Original code instead calls ILT 0x00017436 -> 0x00154AD0, the independently
rowed 136 B `AIGroup::getAllIDs() const`. The existing verified provider contract
returns a const reference to canonical STLport `vector<ObjectID, allocator<ObjectID> >`;
the original instructions independently establish the vector-address return.
They do not independently encode C++ const qualification. The caller reads
the returned vector's start pointer and its first four-byte ID, then calls
ILT 0x0001F253 -> `GameLogic::findObjectByID(int)` at 0x0009A510 / 82 B.

The source repair declares that existing real getter API, includes the existing
canonical ObjectID header, and preserves the previous prefix structures and
two original loads. Canonical allocator/vector types are only forward declared;
no new AIGroup storage, size, bases or virtual interface is asserted. The
outer BfmeObjectReference placeholder remains because its complete original
class identity has not been established. Null-receiver and empty-vector
behavior are unchanged. No new function, data row, pin, layout header, compiler
flag or boundary is introduced.

## Independent target facts and donor contribution

The complete original 29 B body witnesses the unchanged ECX receiver, both
calls and the two dependent loads. The complete original 136 B getter gathers
Object IDs from +0x74, returns its own vector at +0x34, and is already owned
by AIGroup_getAllIDs.cpp. Canonical STLport `_Vector_base` begins with
`_M_start`; its vector subclass adds no earlier storage. No BFME2 +0x30 group
offset is transferred to BFME1.

Historical donor e2e99959950e6eebfe1ced5663aa05de320afc52 is read-only.
`Code/GameEngine/Include/GameLogic/AIGroup.h:91` supplies the same API spelling,
and `Code/GameEngine/Source/Common/RTS/PlayerSetCurrentlySelectedAIGroup.cpp:71`
demonstrates the typed vector-reference call followed by prefix access. Relevant
authored history: 1fd625fa156b652a6e69be40dbbeb010e9195899 and
f7a489d96b1724239870a056f19329b1cbc043cc. BFME1 target calls and the real owned
provider establish the particular identity and receiver; donor similarity alone
does not. Native scan/cache input receipts were freshly validated without an
unnecessary rescan.

## Two bounded private forms

The first private control used the provider's real STLport/static profile and
direct `ids.front()`. It failed the original instruction ordering, moved the
global DIR32 relocation from +16 to +15, and emitted two three-byte accessors.
It was discarded; its source, objects, raw difference and command remain in
the private diagnostic directory. No score, coverage or pass was inferred.

The second form uses the already existing prefix-access pattern and the exact
original caller profile. It strictly preserves all 29 bytes and three relocation
positions. The only complete runtime/FPO graph difference is the external REL32
name at +5, from the nonexistent getter to the independently owned getter.
There are no additional code/data/EH/FPO/COMDAT/weak/CRT/defaultlib/vtable
emissions. The normal production object independently confirms the same graph.

## Normal verification

Caller plus both provider source files: four of four rows, seven DIR32 checks,
BodyGuard zero; both actual provider source and object hashes stay unchanged.
The sibling 527 B SelectionTable::invoke row was also checked. FDU passes.
The native Before preview reports the old unresolved getter and 0 -> 0 B.
The native After preview and any necessary current-provider refresh are
documented in the final receipt; a frozen old census is not current-provider
proof. These previews are scoped link-policy evidence, not a full image link
or a runtime test.

This is one source/link repair of retained existing C++. New exact-body bytes,
new exact .text union, and new functions are all zero. The native session
progress delta is zero. The historical +10,237 C++ exact bytes against master
predate this task and must not be credited again.

## Reproduction and immutable artifacts

Use the normal environment and build all three sources with tools/build.py:
`game/GameEngine/Source/GameLogic/Object/BfmeObjectReferenceResolve.cpp`,
`game/GameEngine/Source/GameLogic/AI/AIGroup_getAllIDs.cpp`, and
`game/GameEngine/Source/GameClient/GUI/Palantir/SelectionAll00595230.cpp`.
Run normal tools/link_check.py on the caller; where the frozen census lacks
the newer real provider, use its documented `--refresh --refresh-compile`.
Never replace native name resolution, change an index by hand, or inject a
private object into the normal cache.

Private diagnostics: W:/OpenBFME/diagnostics/one-per-project-20261125-190319/bfme1.
The final compact manifest hashes the original/private/normal objects, native
logs and reproducible read-only proof scripts without copying whole inventories
into the repository. This blocked candidate was restored and its one lease released unlanded
using fresh remote owner/lease/token-CAS fences; no source is being published. The parked Node13
branch at 0485927757533b40c3ce34412ae871bcb70f85c9 is preserved. PC stays on.

Tracked evidence text uses LF for review. Exact raw original/candidate source and native output files remain private, with their independent hashes; source_sha256 fields bind those original input bytes, while tracked_artifacts binds each LF transcription. No game source or build receipt was normalized.
