# SinglePlayerSkirmishGameInfo::xfer at 0x0061FDA0

The 901-byte body at 0x0061FDA0 was matched as
`?xfer@Rva0061FDA0Owner@@MAEXPAVXfer@@@Z`. An earlier session showed it is a
byte twin of `?xfer@SkirmishGameInfo@@MAEXPAVXfer@@@Z` (0x0061F930) in a
different class, and left the owner unnamed. The owner's Snapshot table names
the class: SinglePlayerSkirmishGameInfo.

## Facts from retail 1.03 (`lotrbfme.exe`, image base 0x400000)

Two 134-byte constructors build the two twin classes. Both call the GameInfo
base constructor, store the base Snapshot table 0x01073744 at +0x58, then
their own tables:

| ctor | primary table | Snapshot table (+0x58) | Snapshot slot 2 | slot 3 | `new` result stored to |
|---|---|---|---|---|---|
| 0x00075C10 | 0x01075E90 | 0x01075E7C | 0x00075CF0: `B8 D4 5E 07 01 C3` -> "SkirmishGameInfo" (VA 0x01075ED4) | ILT 0x00014E5C -> 0x0061F930 `SkirmishGameInfo::xfer` | 0x012F7094 (at 0x0057BEA7, after `new(0x27C)`) |
| 0x00619720 | 0x011171DC | 0x011171C8 | 0x00619820: `B8 20 72 11 01 C3` -> "SinglePlayerSkirmishGameInfo" (VA 0x01117220) | ILT 0x0000EB6F -> 0x0061FDA0 (this body) | 0x012F7090 (at 0x0061B58B, after `new(0x27C)`) |

Constructor store bytes: 0x0061976E `C7 46 58 C8 71 11 01`; 0x00075C5E
`C7 46 58 7C 5E 07 01`.

The string "SinglePlayerSkirmishGameInfo" occurs once in the image (the
"SkirmishGameInfo" at 0x0111722C is its suffix). Its only code reference is the
getter 0x00619820.

## Why slot 2 names the class

In BFME's Snapshot tables, slot 1 is `loadPostProcess`, slot 2 is a
`mov eax, offset literal; ret` getter, and slot 3 is `xfer`. A survey of the
ledger's literal name getters (`?name@Rva........Named@@QBEPBDXZ`) placed 281
of 282 table references at slot 2, and wherever the owner is named
independently the literal is the owner's class name:

- Squad: slot 1 `?loadPostProcess@Squad@@MAEXXZ`, slot 2 -> "Squad", slot 3 `?xfer@Squad@@MAEXPAVXfer@@@Z`
- ScoreKeeper: slot 1 `loadPostProcess@ScoreKeeper`, slot 2 -> "ScoreKeeper", slot 3 `xfer@ScoreKeeper`
- Money, Player, TeamTemplateInfo: slot 1 `loadPostProcess@<C>`, slot 2 -> "<C>"
- the twin itself: slot 2 -> "SkirmishGameInfo", slot 3 `SkirmishGameInfo::xfer`

So the table 0x011171C8 belongs to SinglePlayerSkirmishGameInfo, and its slot-3
override is `SinglePlayerSkirmishGameInfo::xfer`. The mangled form copies the
twin's: `?xfer@SinglePlayerSkirmishGameInfo@@MAEXPAVXfer@@@Z`.

## Related rows this note does not change

The constructor at 0x00619720 is currently `??0SkirmishGameInfo@@QAE@XZ` and the
one at 0x00075C10 is `??0Open2SlotOwner75C10@@QAE@XZ`. By the table above these
names are swapped: 0x00075C10 builds SkirmishGameInfo (its `new` lands in
0x012F7094, the global that `SkirmishBattleHonors::write`'s pin note calls
TheSkirmishGameInfo) and 0x00619720 builds SinglePlayerSkirmishGameInfo. The
dir32 rows `??_7SkirmishGameInfo@@6BSnapshot@@@ -> 0x011171C8` and
`??_7Open2SlotOwner75C10@@6BSnapshot@@@ -> 0x01075E7C` inherit the same swap.
Correcting them is a separate change.
