# Reset caller bindings at 0x003C1A50

Base: ec0bc05646da7375bfd04153879619c53c7138a8 (2026-10-30). The linking
near packet served the already matched 84-byte caller with five stale names.
The body remains Rva003C1A50::run; no original owner name is inferred.

## Target identity and ABI

The complete native caller passes its unchanged ECX through these ILTs:

| Caller site | ILT -> existing body | Existing owner |
| --- | --- | --- |
| 003C1A53 | 000214E0 -> 003C0EF0 | Gen_003C0EF0::bfmeClear |
| 003C1A5A | 0001B333 -> 003C0F70 | Gen_003C0F70::bfmeClear |
| 003C1A8F | 00024875 -> 003C0DB0 | Gen_003C0DB0::bfmeClear |

At 003C1A82/003C1A98 it instead loads ECX from the unchanged VA 012F706C
global, whose data-row owner is TheLivingWorldManager. Call 003C1A88 reaches
ILT 0001F7DF -> BfmeThingBLE::bfmeGoBLE at 00610050. The final JMP 003C1A9F
reaches ILT 00015834 -> Rva0060FFC0Owner::resetUiState at 0060FFC0.
Full native bodies of all five providers were decoded and their existing
sources read. They consume the same receiver with no explicit arguments;
their plain-return/tail forms do not add a receiver adjustment or stack input.

Declare the existing row owners and cast only the receiver at each call.
Remove the old declaration-only methods and unused g_bfmeGameCW view macro;
the existing global is referenced directly. The caller's fields and stores,
compiler flags, row name, boundary and all provider sources remain unchanged.
No pin, alias, header, new global or ledger edit is introduced.

## Donor and related-source review

Reviewed BFME 2 reference b5a7b8290a0c4c20b03a3664609d434904e228eb,
the corresponding Common/provider-name searches, and
Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldManagerCleanup.cpp
with its row and history. Its 112-byte 0021427A cleanup already binds existing
row owners, but its optional objects at +264/+268 and flag +2C0, five local
calls and separate singleton guards do not establish a counterpart to this
84-byte BFME 1 caller. No donor body, layout or semantic name is imported.
An equal +28C offset in AptMessengerOnline describes a vector, not this
provider's optional pointer; it is explicitly not mapping evidence.

The related-source sweep finds Glo012F706CType used by other lookup methods
and OptionalReset. Those have different signatures and targets, so no blanket
class rename or unsupported same-name edit is applied. The other blocker
families below remain separate prerequisites.

## Verification and remaining scope

- Six-source normal gate passes 8/8 rows and nine DIR32 references.
- All 84 raw caller bytes are identical (SHA256
  299ad104334e7a6a7c6952182134e110c041779be54dd59bcf00b96b915f731f).
  Exactly five REL32 referents change; the global references and all other
  relocation records are identical. Defined-unmatched checking passes.
- Paired frozen-index preview at 1d5131d3f1 (2026-10-30 12:21) changes the
  caller 0 -> 83 authored bytes and the six-source cohort 233 -> 316, 3/6
  to 4/6 LINKS. This is a prediction, not a measured census gain.
- Bfme5ClearsWithTails and Bfme5SingletonClear retain their pre-existing
  import/element-destructor/notify/stop/remove/swap name blockers. Their
  bytes pass, but provider-unit closure is not claimed. The other three
  provider units retain 170, 25 and 38 preview bytes respectively.
- Ordinary current-object preview is UNKNOWN: 22,717 current ledger objects
  cannot be read for selection verification. A stale-index prediction cannot
  clear those dependencies or establish a complete engine link/runtime result.

## Exact-snapshot name pairing correction

The first commit gate pairs the removed Glo012F706CType::go declaration with
the newly declared Gen_003C0EF0::bfmeClear and calls this a name regression.
They are different native methods: 003C1A88/ILT 0001F7DF reaches 00610050,
while 003C1A53/ILT 000214E0 reaches 003C0EF0. The former call retains the
existing bfmeGoBLE row name in the new source; it is not renamed to bfmeClear.
Both paths independently retain their original receiver and destination.

docs/naming_evidence.md, Keeping names, explicitly permits an exact-snapshot
name_corrections.json entry for a false pairing of removed/new declarations.
The entry records the reported go/bfmeClear pair with both exact source hashes
and this native evidence. It does not assert those methods have one identity
or allow a general descriptive-name downgrade. No checker or threshold is
changed, and the normal name/history and commit/push gates remain active.

Qwen2.5-Coder-7B Q4_K_M reviewed only the supplied five-entry ABI mapping.
It found no contradiction and correctly required host byte/relocation/link
verification. This was a constrained consistency check of supplied facts,
not independent ABI discovery or a naming vote. It wrote no game code.
It ran on four low-priority CPU threads and stopped after the request.

Local raw evidence: build/continuation-qwen-20261030-201608/; helper input and
output: W:/OpenBFME/diagnostics/continuation-qwen-20261030-201608/ and the
corresponding .tools/qwen-helper/requests/ packet. Full consumer/current-census
confirmation remains open; do not repeat the completed five-binding repair.
