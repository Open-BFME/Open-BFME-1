# One physical BuffLogic pointer owner

Round baseline: `44a491c1cede3e516e44a5b9bbea49cfeb8812d7`.
The preserving merge `55f514cce7` adds only upstream progress displays/history.

## Original datum and actual consumers

VA `0x012EF4F0` / RVA `0x00EEF4F0` is one four-byte pointer cell in
the original `.data` virtual tail. The normal data verifier's native
`reloc_ledger.Image.read` supplies its loader-initialized four zero bytes.
The raw code/file-offset reader is unsuitable for this virtual tail; its
different raw-file bytes are preserved as a diagnostic, not treated as
loaded data or used to change expected values.

Nine actual DIR32 operands across six whole consumer sources independently
store/load that exact address. GameLogic::init stores its slot-11 result,
initializes the SubsystemInterface prefix at +4, and names it `TheBuffLogic`.
Reset reads the same pointer and dispatches through that prefix; destruction
and the TBuff unregister path read the root pointer. The two Buff entry
consumers load the same pointer into ECX before the existing 337-byte
BuffLogic::addBuff provider (ILT `0x000397FC` -> RVA `0x001B0E90`).
Its existing two-stack-argument, value-returning member contract is retained.

Both recorded spellings previously had no physical provider and no data row:
`?g_012EF4F0@@3PAVManager012EF4F0@@A` and
`?Effects0040A260@@3PAUEffectFactory0040A260@@A`. The proposed owner uses
the first existing spelling and its existing pointer declaration. No new
global name or complete pointee layout is inferred. Existing per-TU lifecycle
views remain partial; this task does not claim to reconcile their hierarchy.

## Smallest coherent source change

Define the existing Manager pointer as zero in GameLogicInit.cpp. In only
BuffTransfer0040A260.cpp and BuffEntryTransition00409610.cpp, replace the
never-defined opaque Effects forward declaration/global reference with the
same existing Manager pointer name. Keep their explicit BuffLogic receiver
conversions, all function contracts, bodies, headers, flags and emitters.
No new class member, macro, alias, pin, virtual slot, or helper is introduced.
No corresponding canonical Buff/Manager header exists in game or the shims.

The existing source-index retirement policy independently excludes obsolete
Effects references confined to dead `?d_00405e80@@YAXXZ` in a multi-PROC
generated ASM file. That file still builds a different live 195-byte PROC;
it is not described as an entirely unused file. The dead original entry is
already covered by an authored PathfindZoneManager row. No dump is edited,
no exemption is added, and the actual normal retirement guard must decide.

Historical attempt 68229 assumed a complete EA-global rename was needed.
The narrower existing-name/data-owner route avoids that unsupported rename.
Only normal `add_data_match.py` may admit the new owner, and only normal
`dir32_record.py retire` may remove the old Effects record after sources and
the owner are staged. A refusal is preserved; no manual record edit is used.

## Donor and measured control boundary

Historical donor `e2e99959950e6eebfe1ced5663aa05de320afc52` owns
TheBuffLogic in GameLogicInit.cpp and uses a type-punning g_012EF4F0 macro
in Common/System/TBuff.cpp. Its macro, names, addresses, class layout and
compiler settings are not ported. BFME1's own original operands establish
this physical-cell convergence; the broader EA name remains deferred.

Normal unchanged controls pass 12/12 rows in seven TUs, four existing data
rows, 87 DIR32 references and 11 literals, with zero body baselines. All
seven objects are ordinary-current. Three stale labels in the unchanged
GameLogicDestructorThunk source are accepted by the native byte re-finder;
they remain preexisting metadata debt, not a claimed clean global EH audit.

The frozen scope has 11 existing consumer rows in six sources plus the
unchanged addBuff provider. Pointer size/bytes, preservation of existing data
owners, paired object graphs, native retirement and actual before/after
results are recorded below and in the sibling receipt. No new C++ body,
full-image link, memory/crash, or
runtime improvement follows from this source/data repair alone.

## Actual admission, object delta and link boundary

The normal data writer admits exactly four zero-filled bytes with
`sizeof(::g_012EF4F0) = 4` under the existing profile and allocation extent 4.
Normal staged retirement accepts the old Effects record for this real data
owner. No other record byte, function row, pin or hatch baseline changes.
Post-retirement verification passes 12/12 functions, five data rows and all
87 DIR32 references; FDU reports all definitions already matched.

The actual paired-object proof covers 181 runtime sections in the six
consumers plus all 32 sections of the unchanged addBuff provider. The owner
BSS grows from 12 to 16 bytes: new g occupies +8, existing LargeGroupAudio
moves from +8 to +12 within the COFF BSS only. Its original data-row VA does
not move. Four owner relocation-binding fields account for those definitions.
The two other changed objects differ only in three Effects-to-g DIR32 names.
Five of six SafeSEH index words change because they are COFF symbol-table
indices; all six ordered handler names, code sections, offsets, types and
storage classes are independently identical. No numeric-index blanket
normalization is used. All remaining code/data/FPO/EH/COMDAT/CRT/weak/directive
payloads and edges are exact; no new function, helper or initializer appears.
An independent read-only review confirms the same actual objects and limits.

Normal scoped legacy-census previews: BEFORE 0/6 LINKS, 0 -> 0, 442.0 s;
AFTER 0/6 LINKS, 0 -> 0, 427.8 s. Every old g/Effects missing-name entry is
removed. Reset's 614-byte physical row (613-byte CC-filtered display) remains
UNKNOWN because the selection receipt for __stl_delete is stale. Init and
the destructor retain additional old stale selections; the destructor also
retains existing duplicate/vtable/alias debt. TBuff, transfer and transition
retain their other counter/unregister/factory/GameLogic-name prerequisites.
No index, provider, header, alias, pin or verifier is changed to hide them.

Thus the demonstrated gain is one real four-byte static-data owner with
three coherent source edits and a supported old-name retirement. New C++
bytes, new function rows and demonstrated LINKED gain are zero. The legacy
preview at `42237e2367` is not a fresh full-image census or runtime result.
