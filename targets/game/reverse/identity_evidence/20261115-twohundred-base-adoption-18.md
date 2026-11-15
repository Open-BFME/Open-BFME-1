# Canonical StringBase adoption: tasks 158-164 of 200

Baseline `eef8200f0665fead40b21bf931c52bf0978349fe`.
Replace only the local StringBase template with the existing native string_base.h.
No source-level local AsciiString body is present in this family. Existing
UnicodeString views remain unchanged. One source adoption is one task; dependent
cleanup locator repairs are not counted again. This is reconciliation of existing
code, not new function reconstruction or authored-byte progress.

## ABI, compiler and object proof

The native BFME1 string_base.h describes the settled four-byte buffer-pointer
object and narrow/wide method identities. Per-source CodeView requires every
original concrete StringBase instantiation to remain present, with sizeof4,
one pointer field at offset0, no bases, no virtual pointer or slots. Companion
UnicodeString size, direct fields, base identities/offsets and virtual state
must remain exactly equal between controls. A size1 empty incomplete facade is
admitted only with exact complete runtime inventory identity and no other concrete
object layout containing or deriving from it. The settled native header and
verified providers independently establish its real4B pointer ABI; no size1
retail-type claim is made. No size-dependent caller code may change.
Private controls use the same physical input path and original include context.
The independent normal-before/normal-after comparison retains all ordinary
runtime bytes, section flags and relocation sites/kinds/targets. Local EH graph
roles, action offsets and resolved SafeSEH handlers remain equal. A strict full
ordered inventory can additionally prove disconnected local tables without
guessing a mapping. Weak external contracts remain identical.

New or changed callable COMDATs require an existing matched ledger identity
and native full-byte/relocation-target RetailTruth proof. Removed definitions
must be canonical copies independently proven wrong. No unknown new body is accepted.
The only additional data exception recognizes the original narrow/wide
StringBase::str TheNullChr exports from exports.csv: exact original RVA,
scalar1/2B size, readonly non-executable section, no relocations, exact zero
initializer read at that original address. This is not callable proof from a pin.
Only the three compiler aliases already emitted by unchanged verified providers
can be duplicated; any newly duplicated alias remains unused by the consumer.
No source alias, pin, header, compiler flag, verifier or baseline changes.

## Reference context

The read-only BFME2 revision f6c3838e7b58025531e09913bc42b810f1a01216 and its
Code/Libraries/Source/WWVegas/WWLib/string_base.h inform the common-owner pattern.
Native BFME1 evidence and existing headers determine the buffer layout, ABI,
addresses, method bodies and exception ordering. No donor address or flag is copied.
The BFME2 binary-source sweep was refreshed earlier in this round; unchanged
Zero Hour inputs and previously refuted link blockers are not rescanned per unit.

| Task | Source | Retained RVAs | New / corrected retail implementation copies |
|---|---|---|---|
| 158 | `game/Libraries/Source/string/StringBaseLessNoCase.cpp` | `0x00887920` | 0 / 0 |
| 159 | `game/GameEngine/Source/GameClient/PopupMessageData.cpp` | `0x0043F460`, `0x0043F4B0`, `0x0043F480` | 0 / 0 |
| 160 | `game/GameEngine/Source/GameClient/GUI/InGameChatAddEntry.cpp` | `0x00512170` | 1 / 0 |
| 161 | `game/GameEngine/Source/Common/FormatLadderRankText.cpp` | `0x00C313D0`, `0x00539020` | 1 / 0 |
| 162 | `game/GameEngine/Source/Common/OnlineHomeRankText.cpp` | `0x005462E0`, `0x00C32430` | 1 / 0 |
| 163 | `game/GameEngine/Source/Common/Rva0052DEB0RankText.cpp` | `0x0052DEB0`, `0x00C309E0` | 1 / 0 |
| 164 | `game/GameEngine/Source/GameClient/GUI/OnlineLoginTextGetters.cpp` | `0x00C32A70`, `0x00C32AB0`, `0x0054D250`, `0x0054D180`, `0x0054D360`, `0x00C32A30` | 1 / 0 |

## Ordinary gates and link prediction

17 retained rows preserve 1500B.
Combined normal gate: 191/191 functions across
11 sources, 348 DIR32 references, body guard OK,
including the four unchanged canonical provider sources.
6 cleanup locators are corrected only by eh_state_pins.py --fix.
Frozen before: 6/7 LINKS, 1286B.
Frozen after: 6/7 LINKS, 1286B.
No formerly linkable file is lost. Staged current-provider preview: 7/7 UNKNOWN, 0/7 LINKS, 0/7 blocked. Unknown results authorize no LINKED claim.
The complete earlier census43711614660 separately confirms the preceding450B
and total3,088,824 LINKED B; it predates these adoptions. No new full-link, runtime,
memory improvement or crash-fix claim. Reservations, row-specific prior attempts,
snapshots, layout controls and complete private/native proofs remain in this
round's batch diagnostics. Failed trials are neither applied nor counted.

Native state-proven cleanup locators:
- `0x00C309E0`: `$L408` -> `$L683`.
- `0x00C32A70`: `$L373` -> `$L660`.
- `0x00C32AB0`: `$L445` -> `$L780`.
- `0x00C313D0`: `$L408` -> `$L683`.
- `0x00C32430`: `$L408` -> `$L683`.
- `0x00C32A30`: `$L431` -> `$L722`.
