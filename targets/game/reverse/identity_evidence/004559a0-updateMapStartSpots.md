# 0x004559A0 is ?updateMapStartSpots@@YAXPAVGameInfo@@QAPAVGameWindow@@_N@Z, not ?write@SkirmishPreferences@@

The 2026-08-11 Open-BFME5 `*Thunk.cpp` lift
`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishPreferences_write_Thunk.cpp`
holds a naked `__emit` copy of the 838 bytes at 0x004559A0 under the ledger name
`?write@SkirmishPreferences@@`. That name is wrong. The bytes are the free
`__cdecl` function `updateMapStartSpots`, and the same bytes now byte-verify from
real C++ in
`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/UpdateMapStartSpotsBFME.cpp`.

## The name the pin already carried

`targets/game/reverse/symbols.csv:87482` pins the real identity on this address:

```
?updateMapStartSpots@@YAXPAVGameInfo@@QAPAVGameWindow@@_N@Z,0x004559A0,Generals source signature and WOLDisplayGameOptions aligned three-argument call prove direct BFME body
```

`functions.csv` had no row under that name, so the lift claimed the address
instead and the pin had nothing to bind.

## Three MATCHED callers name the symbol

`python3 tools/callers_of.py 0x004559A0` reports the retail call sites, and every
one of them sits inside a ledger row that is already `matched` with real source:

| retail call site | matched row | source | call in that source |
|---|---|---|---|
| 0x00492400 | `?init@MultiPlayerLoadScreen@@` 0x00492400/1688B (functions.csv:59863) | `game/GameEngine/Source/GameClient/GUI/LoadScreenInit.cpp` | `updateMapStartSpots( game, m_buttonMapStartPosition, TRUE )` (line 639) |
| 0x00493120 | `?init@GameSpyLoadScreen@@` 0x00493120/2717B (functions.csv:59847) | `game/GameEngine/Source/GameClient/GUI/LoadScreenInit.cpp` | `updateMapStartSpots( game, m_buttonMapStartPosition, TRUE )` (line 938) |
| 0x004F1C20 | `?WOLDisplayGameOptions@@YAXXZ` 0x004F1C20/392B (functions.csv:23597) | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp` | `updateMapStartSpots( ... )` (line 2282) |

A matched caller naming the symbol outranks every identity detector the repo
runs (AGENTS.md, "a matched caller naming the symbol outranks all five"). The
call sites land inside those bodies, not at their edges.

## The body is a three-argument free function, not a member write()

`python3 tools/dis_retail.py 0x004559A0 838` reads, in body order:

* `mov ecx,[esp+0x124]` then `call` the `GameInfo::getMap` ILT 0x0002F28E
  (`?getMap@GameInfo@@QBE?AVAsciiString@@XZ`) -- argument 1, a `GameInfo *`;
* `mov edi,[esp+0x138]` / `mov ebp,[esp+0x138]` -- argument 2, the
  `GameWindow *buttonMapStartPositions[]` array, indexed `[edi + esi*4]` and
  `[ebp + eax*4]`;
* `cmp byte ptr [esp+0x13c],bl` with `bl == 0` -- argument 3 read as ONE BYTE,
  which is the `bool` in `_N` and not the four-byte `Int` a `Bool` member would
  leave in the frame;
* the epilogue is `add esp,0x120; ret` (no `ret 4`), so the callee pops its own
  three arguments: `__cdecl`, not the `__thiscall` a
  `SkirmishPreferences::write` member would be;
* the frame holds no `this`-relative store at all -- every `mov [esi+...]` is
  through the `GameSlot *` returned by `getSlot`.

`Bool SkirmishPreferences::write(void)` also does none of what the body does. The
Zero Hour twin (`SkirmishGameOptionsMenu.cpp:342`) writes `"Color"`,
`"PlayerTemplate"`, `"Map"`, `"UserName"`, `setStartingCash`,
`setSuperweaponRestricted`, `setSlotList` and `setInt("FPS")` into the preference
map, then tail-calls `UserPreferences::write` -- which is itself a landed row at
0x000A9F60 (`?write@UserPreferences@@UAE_NXZ`, functions.csv:134634). This body
calls none of those and reaches no `OptionPreferences`/`PreferenceMap` member: it
loops eight buttons, calls `GameWindow::winHide` (ILT 0x00027F2A),
`GadgetRadioSetText` (ILT 0x000424F1) and `GameWindow::winSetTooltip` (ILT
0x00003328) against `TheGameText` and `TheMapCache` (0x012F1594).

## The ledger name is not even a complete decoration

`?write@SkirmishPreferences@@` carries no signature. A `Bool write(void)` member
decorates as `?write@SkirmishPreferences@@UAE_NXZ` -- the same shape as the landed
`?write@SkirmishBattleHonors@@UAE_NXZ` (0x0009EA10) and
`?write@UserPreferences@@UAE_NXZ` (0x000A9F60). So the lift's name was never a
resolvable symbol; the lift file's own header comment already pointed at the
right home:

```
// readable body of ?write@SkirmishPreferences@@: game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp
```

`SkirmishGameOptionsMenu.cpp` is exactly the translation unit that carries the
Zero Hour `updateMapStartSpots` (it is still there, next to
`positionStartSpots`), and the 2026-08-11 lift of `SkirmishPreferences::write` was
taken from the same file. The name came from the sibling function, not from the
bytes.

## Extent

`targets/game/reverse/lift_extents.csv:27` already carries the proven
correction for this lift: 830 -> 838, "end 0x00455CE6 meets int3 padding before a
16-aligned start". The 830-byte ledger row stopped inside the final
`add esp,0x120; ret`; `tools/probe.py` reports "MATCHES PAST THE SIZE: ours equals
retail over all 838 bytes".

## The conversion

`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/UpdateMapStartSpotsBFME.cpp`
is a self-contained minimal-shim TU in the style of
`GameInfo_getMapIsOfficial_BFME.cpp`, `CustomMatchPreferences_getPreferredMap_Thunk.cpp`
and `Rva000C1E50MapCacheDefinition.cpp`. Its one real lever is the StringInline
string shape (docs/shape_levers.md row 2): with the Zero Hour `AsciiString` /
`UnicodeString`, which spell their own copy constructor and destructor, MSVC 7.1
emits `mov ecx,esp` BEFORE the EH `mov [esp+N],esp` at all five by-value string
temporaries in this body (30 bytes across +0xC1, +0x16F, +0x21B, +0x24C, +0x2B5).
With `class AsciiString : private StringBase<char>` carrying INLINE FORWARDERS to
the base that owns the out-of-line bodies, retail's order comes out. The second
lever, naming `MapCache *cache = TheMapCache` so the global is loaded once into
esi, is the one `GameInfo_getMapIsOfficial_BFME.cpp` already uses.
