# Canonical StringBase adoption: tasks 193-196 of 200

Baseline `7d551300edb3ce100a7188295f9ab171b477946e`.
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
| 193 | `game/GameEngine/Source/GameLogic/Object/Die/RefundDieOnDie.cpp` | `0x00255BE0` | 0 / 0 |
| 194 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenOnlineChatInitGadgets.cpp` | `0x00534A60` | 2 / 1 |
| 195 | `game/GameEngine/Source/GameClient/GUI/LoadScreenUpdates.cpp` | `0x00490570`, `0x00491F30`, `0x004914C0`, `0x0050FF30`, `0x00491EB0`, `0x00491550` | 2 / 1 |
| 196 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenLanLobby_getGameInfoRva00516850.cpp` | `0x00516850`, `0x00519150` | 2 / 1 |

## Ordinary gates and link prediction

10 retained rows preserve 2942B.
Combined normal gate: 184/184 functions across
8 sources, 398 DIR32 references, body guard OK,
including the four unchanged canonical provider sources.
0 cleanup locators are corrected only by eh_state_pins.py --fix.
Frozen before: 0/4 LINKS, 0B.
Frozen after: 0/4 LINKS, 0B.
No formerly linkable file is lost. Staged current-provider preview: 4/4 UNKNOWN, 0/4 LINKS, 0/4 blocked. Unknown results authorize no LINKED claim.
The complete earlier census43711614660 separately confirms the preceding450B
and total3,088,824 LINKED B; it predates these adoptions. No new full-link, runtime,
memory improvement or crash-fix claim. Reservations, row-specific prior attempts,
snapshots, layout controls and complete private/native proofs remain in this
round's batch diagnostics. Failed trials are neither applied nor counted.
