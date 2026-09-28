# mods/: the cave mechanism

## Rules

- **Mods always stack.** `python3 tools/modbuild.py --dist` builds exactly one
  executable, `mods/dist/lotrbfme.exe` (needs Wine). There is no per-feature
  build: two features claiming the same address is a build error, and `--dist`
  refuses `--only`.
- **No mod is part of the byte-exact decomp.** A feature never touches `game/`
  or `targets/game/reverse/`, so `./build.sh` and the git hooks never see it.
- **`tools/modbuild.py` is the only list of features.** `FEATURES` is the
  distributable set. `UNSHIPPED` holds opt-in experiments and diagnostics,
  built only by name and refused by `--dist`. Arena deployment is a separate
  choice.
- Test a feature by driving the real game (synthetic clicks, screenshot
  assertions) and checking its own output file.

## Mechanism

`tools/cave.py` appends a `.bfmemod` section and installs a 5-byte `jmp rel32`
at a target, moving the displaced instructions into the cave. A feature needs
only an address and a struct layout; the target need not be converted.
`DllCharacteristics` is `0x0000`, so absolute addressing is safe.

A feature is one `.cpp`, with no hand-written machine code. `modbuild.py`
compiles it with the game's own MSVC 7.1, relocates the linked image into the
cave, and reaches each entry through a shim that `cave.py` generates
(`pushad/pushfd/cld/push ecx/call`). No loader, no CRT: the link is naked and
fails on any unresolved external. MSVC 7.1 rejects `__thiscall`, so call the
engine's virtuals as `__fastcall` with an unused `edx`.

A hook that needs the target's own argument uses `detour_call(..., args=("ecx",
"stack:0"))`: a thiscall's `this` arrives in ecx but its arguments do not, and
the shim lifts one off the target's frame. It works only at a function's
**entry**, before the body has pushed anything.

## Mod bus

Features link separately, so they share state only through fixed addresses:
the first `0x40` bytes of the cave, VA `0x01416000` (`MOD_BUS_VA` in
`modbuild.py`), zeroed and never given to a payload. Append fields; never
reorder them, because every feature compiles the offsets in.

| Offset | Field | Users |
|---|---|---|
| `+0x0` | magic `0x4D46424F` ('OBFM'); without it every flag reads as on | 043 reads, 047 writes |
| `+0x4` | `BUS_ROTATE` (byte) | 043 reads, 047 toggles |
| `+0x5` | `BUS_TILT` (byte) | 043 reads, 047 toggles |
| `+0x6` | `BUS_ZOOM` (byte) | 043 reads, 047 toggles |

## Shipping data

`modbuild.DATA` names, per feature, the archives it rebuilds and the module in
its directory that rebuilds them. 048's button and panel text live in
`Options.apt`, so:

    DATA = {"048-advancedgfx": [("apt/options.big", "apt_panel")]}

`--dist` writes `mods/dist/apt/options.big` beside the exe and records its
sha256 and source baseline in the manifest; two consecutive `--dist` runs give
identical hashes. The source is the tracked
`inputs/baselines/bfme1/workshop-vanilla-1.03/files/apt/options.big`, never a
local install. A missing baseline fails the build with the path it wanted; a
non-dist build prints what it would have written.

## 020-gameresult: addresses and fields

The feature detours `VictoryConditions::update` (`0x0035F920`) and
`sendPlayerLeaveCommands` (`0x00665C10`), writing the JSONL of
`mods/features/020-gameresult/README.md`.

- **`PlayerLeaveStatus` at `TheGameLogic+0x1B0`, stride `0x1C`**: layout in
  `targets/game/reverse/game_end/FINDINGS.md`, except the AsciiString is at
  `+0x18`, chars at `+8`, not `+0x14` as FINDINGS reads.
- **Strings live bit-inverted** in `lang/english.big` → `lotr.csf`, so grep
  finds nothing and you guess from the English. "Game has already started" is
  `LAN:ErrorGameGone` (that row is stale), *not* `LAN:ErrorGameStarted`.
- `victoryFrame` and `defeatCount` (`VictoryConditions+0xC0`) are **removed**:
  the first is machine-local, and the second read differently on two machines
  for one match.
- **Key on `teamWon`**: it means one alliance remains and some undefeated
  player is p *or p's ally*, so a player who quit long before the win still
  reads `teamWon=1`.
- Emit the raw value beside the decoded one. A wrong offset then shows as
  visibly wrong (`namePtr: 255`) rather than plausibly empty.

## Traps

`tools/tests/test_cave.py` and `tools/tests/test_mods_build.py` cover each one.

1. Section `Characteristics` belong at `+0x24`; one field late they read `0`.
2. Resolve a blob's landing address before emitting it, or every relative
   operand points at nothing.
3. No CRT: a local over a page, 64-bit arithmetic or a float compiles to
   `__chkstk`/`__alldiv`/`__ftol2`, which nothing resolves.
4. `fputs(str, FILE*)` takes the string first; `fprintf` does not.
5. Gate on a state that is false *after* the match. The leave entry also
   fires when a player leaves a finished match, so a check meaning "a match
   was in progress" appends a spurious `leave` to every completed game.
6. Back every flag with an assertion: `--probe` once passed while doing
   nothing.
7. `link.exe` stamps the export directory with the clock, making the committed
   artifact a different file on every rebuild.
