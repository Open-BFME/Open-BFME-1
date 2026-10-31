# Patch-check consumers: match the existing byte flag owners

Base after the first task: `b7fe1fbda`. Claimed native StartPatchCheck at
`006304A0` (218 bytes) and HTTPThinkWrapper at `00630450` (62 bytes).
The census queue serves StartPatchCheck's unresolved bool-typed DNS flag.

## Native identity and existing owners

`MainMenuUtils.cpp` and its existing data rows define unsigned-char
`s_asyncDNSLookupInProgress` at VA `012F717A` and `cantConnectBeforeOnline`
at `012F716D`. Each row owns one zero byte. The native HTTP pump loads the
DNS byte at `00630450` and stores byte 1 to the failure flag at `00630473`.
StartPatchCheck stores the DNS byte at `00630536`. The cancellation function
at `0062F760` already declares its Bool as unsigned char and clears the same
DNS byte at `0062F76A`; it needs no edit.

The pre-edit four-source gate passes all 12 function bodies and eight data
rows but refuses exactly three DIR32 references under bool-typed spellings:
StartPatchCheck +152 and HTTPThinkWrapper +1/+37. The actual variables are
already recorded under their unsigned-char COFF names. This is a stale
consumer declaration, not a new data object or missing allocation.

Change only the three extern declarations in the two consumers to unsigned
char. Their complete 218/62-byte bodies are unchanged. The three relocations
now name the existing owners; every other code byte and relocation stays
identical. All three other external code definitions in StartPatchCheck's
object are identical, and neither object gains or loses a code definition.
The normal four-source gate now passes 12/12 functions, eight data rows,
55 DIR32 references, 22 literals plus six empty-string references and the
body guards. Frozen-definition checks pass for both edited files.

No owner, data row, pin, alias, class layout, shared header or flag is edited.
The separate TU-local scheduling flags and other legacy global-alias debt
are not retired. The related cancellation declaration was already correct;
the provider and cancellation bodies are verified unchanged with the consumers.

## Donor context and limits

Reviewed BFME 2 pin `b5a7b8290a0c4c20b03a3664609d434904e228eb`,
`Code/GameEngine/Source/GameNetwork/GameSpy/MainMenuUtils_hasWriteAccess.cpp`:
its file-static DNS/failure flags and HTTP state-machine family are shared
context. Its Bool declarations and different addresses are not imported;
BFME 1's native byte accesses and its existing data rows decide these
external bindings. The strict automatic global-rewrite proposal found no
unambiguous typed change for the old bool spelling; the explicit target
and owner evidence above supports this manual declaration repair.

With official frozen index `afbe8bafb6` (2026-10-31 12:37), the two changed
consumers preview LINKS/217 + 62 authored bytes, previously zero. The
unchanged cancellation and provider units keep unrelated string/QueuedDownload
and other binding blockers. The four-source preview is 0 -> 279, not a full
current-selection or new census gain. The previously observed missing local
ledger-object set remains incomplete; no unchanged whole-cache scan or runtime
test is performed or claimed.

Native disassembly, pre-edit DIR32 refusal, byte/data gates and both object
relocation comparisons are retained under ignored
`build/two-each-no-qwen-20261031-1559` and the matching create-only diagnostic
package. Qwen and other local inference stayed off; the shared ten-worker
limit remains in effect.
