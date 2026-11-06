# 0x00519150 BfmeAptScreenLanLobby update (884 B) - EXACT

Symbol: `?rva00519150@BfmeAptScreenLanLobby@@QAEHXZ` (vtable 0x01105A78 slot 5,
int return; RET +0x34B, jump table +0x34C..+0x373, INT3 +0x374).
Best source: `build/wf/00519150/best.cpp`, cl line unchanged from the bank
(`/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`, probe defaults otherwise).
probe: 884/884 B, 62 relocs, `result EXACT (modulo relocation slots)`.
The same TU also emits `?getGameInfoRva00516850@BfmeAptScreenLanLobby@@QAE_NHPAPAX@Z`
EXACT at 0x00516850/239 B.

## Baseline (bank reproduced as logged)

`targets/game/reverse/attempts/0x00519150.cpp`: 884 B, 13 non-reloc bytes.
Retail frame (0x14 of locals, offsets from body esp): case-7 selected 0xC,
case-7 game 0x10, tail selected 0x14, BfmeNetAddress 0x18..0x1F, and the tail
game shares 0x10 with case 7's game. The `$T` UnicodeString-argument pointers
also sit on 0x10/0xC. The bank kept `games[1]` at function scope (0xC), so
case 7's selected moved to 0x10. Every block-scoped spelling (logged before as
b1) put the tail game on its own slot (frame 0x18, 14 B).

## Fix: callee visibility (family d)

Define the landed body of 0x00516850 (`getGameInfoRva00516850`, copied
verbatim from
`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenLanLobby_getGameInfoRva00516850.cpp`,
same flags) in the same TU. Use block scopes: case 7 has `int selected` in the
case block and `GameInfo *game` in an inner `{}` that ends before the
GSKickedGameFull path; the tail `if (m_customGamesList)` block declares its own
`selected` and `game`. Placing the definition before or after the caller gives
the same result.

Measured:
- visible real callee + b1 scopes: EXACT
- visible real callee + bank's fn-scope `games[1]`: 9 B
- trivial visible stub (`*game = GetItemData(...); return *game != 0;`): 136 B
  (the stub tells the caller too much, see shape_levers "Callees must share the TU")
- b1 scopes with the callee only declared: 14 B (frame 0x18)

Hypothesis (unverified beyond this body): with the callee's body visible,
`&game` no longer escapes, so VC7.1 packs the two disjoint game locals onto one
slot. `selected` still escapes into the opaque `GadgetListBoxGetSelected`, so
the two selected locals keep separate slots. This fits the existing
shape_levers entries on visible callees and escaped locals.

## Ruled out this session (each 14 B, frame 0x18, unless noted)

- force-inlined helper owning `game` in both case 7 and the tail (inlined
  locals do not share). A non-forced helper is not inlined in case 7 (836 B).
- inline wrapper taking `game` by value (`&param` as a temporary)
- tail game declared before selected (888 B); tail game in a nested block
- case-7 game flat in the case block: 19 B, because the GSKickedGameFull `$T` loses slot 0x10
- function-scope `int selected` used only by the tail, with case 7 shadowing it

## Landing (2026-11-06)

- Both bodies now live in
  `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenLanLobby_getGameInfoRva00516850.cpp`,
  the existing home of the 0x00516850 row, so no rehome was needed. Its cl line
  (`/O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`) is kept, and both probe EXACT.
  The 0x00519150 row was repointed from the gen_asm dump with `--replace-rva`.
- Callee bindings, checked by the add_match gate (2/2 rows, 7 literals, 22 DIR32,
  11 jump-table entries):
  - `flushPendingUpdates` is ILT 0x0000AD21 -> 0x0052AD00, which the ledger
    matches as `SkirmishScreenState::flushPendingUpdates`. The +0x25C state
    object's other two calls are ledgered as MpGameSetup methods (0x00527930,
    0x005280A0), so the MpGameSetup view forwards through an inline cast. The
    two placeholder class names for one object are left for a naming pass.
  - The 0x012F4998 lobby global uses the data ledger's `g_rva012F4998LanLobby`
    (typed BfmeAptScreenLanLobby*). The 0x012F19E8 receiver for the
    0x00465B80 call uses the TU's recorded `g_bfmeR1078`, replacing the
    bank's unrecorded `g_bfme935GlobC` / `g_bfmeManager`.
