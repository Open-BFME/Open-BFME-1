# GiantBird constructor suppression with state-proven cleanup bindings

Task started2026-11-10 23:10:48 UTC, local November11. Base609ed09f40. Follow-up to20261110-giantbird-guard-ctor-emission.md.

## Repair

The machine constructor at0x2C05C0 is429 bytes. Its inline return-state construction also emitted a64-byte `??0GiantBirdGuardReturnState@@QAE@PAX@Z` COMDAT. That name is pinned at ILT0x1C292, which actually reaches this429-byte machine constructor; the64-byte copy is not that body. Suppress the unused standalone emission with the existing imported force-inline constructor recipe, retaining the complete native inlined construction. No new pin, alias, global or identity claim.

The earlier attempt stopped because four11-byte cleanup rows had stale compiler labels and the byte matcher could not choose among equal bodies. The approved `eh_state_pins.py --source game/.../GiantBirdGuardMachineCtor.cpp --fix --model gpt-6.1-sol` resolves them by native unwind state indices1..4, uniquely:

| Native action | Old label | New label | State |
|---|---|---|---|
|0xC13A08|$L677|$L669|1|
|0xC13A13|$L678|$L670|2|
|0xC13A1E|$L679|$L671|3|
|0xC13A29|$L680|$L672|4|

Only that tool writes the four ledger bindings. Its post-check reports four proven/twin-proven actions. No manual label choice, byte-only ambiguity exception or gate bypass.

## Independent verification

- Normal source gate5/5, including the429B parent and all four11B actions; caller factory1/1. All string/constant/DIR32/body guards pass.
- Original source compiled to a private build/queue-retry/giantbird/original.obj. The quoted stringinline include was rewritten only to resolve the same local header from that private directory; original flags retained. The private baseline and normal repaired object have identical429-byte parent instructions outside relocation fields and identical symbolic call/data relocations.
- Compiler unwind maps have the identical predecessor sequence[-1,0,0,0,0]. All five action byte and relocation signatures are identical; labels alone change.
- Original object defines the64B wrong constructor; repaired object has neither that definition nor ANY __imp_ reference. No new dynamic import is introduced.
- The existing pin is confirmed to reach0x2C05C0 by pin_consistency and native five-byte thunk decoding. It is not changed; the machine source now contributes no competing definition under it.
- Census-only link check before: COMDAT wrong/selected wrong,0B. After: LINKS, preview0 ->426B (three padding bytes excluded). Current dependency check: PREVIEW UNKNOWN because the complete changed object set is unavailable. No current linked-byte total claimed.

BFME2 pinned2bac16a6 and fetched officialcfe11f2c reviewed: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardMachine.cpp (unchanged across those snapshots) has distinct constructor ABI/layout and cannot be copied directly. The local constructor/state-map/native evidence determines this repair; no donor address, source or flag is imported.

The prior claim that EH label ambiguity itself blocked this suppression is superseded: the repository's state-map tool proves the exact bindings.
