# The overlay: modding without decompiling

## The mechanism

`tools/cave.py` appends a `.bfmemod` section and installs a 5-byte `jmp rel32`
at a target, relocating the displaced instructions into the cave. **A feature
needs only an address and a struct layout — the target need not be converted**,
which puts the ~65% of `.text` still held as raw retail bytes in reach.
`DllCharacteristics` is `0x0000`, so absolute addressing is safe.

**A feature is one `.cpp`; no hand-written machine code survives.**
`modbuild.py` compiles it with the game's own MSVC 7.1, relocates the linked
image into the cave, and reaches each entry through a shim `cave.py` *generates*
(`pushad/pushfd/cld/push ecx/call`). No loader, no CRT: the link is naked and
fails on any unresolved external. MSVC 7.1 rejects `__thiscall`, so the engine's
virtuals are called `__fastcall` with an unused `edx`.

The feature detours `VictoryConditions::update` (`0x0035F920`) and
`sendPlayerLeaveCommands` (`0x00665C10`), writing the JSONL of
`docs/game-quitting.md`. Both targets are `__declspec(naked)` `__asm` lifts — no
semantics to edit — which is the only reason a detour is needed; convert one and
its detour disappears. The overlay never joins the byte-exact rebuild: a mod
must not move the byte gate.

## Addresses worth keeping

**`PlayerLeaveStatus` at `TheGameLogic+0x1B0`, stride `0x1C`** — layout in
`reverse/game_end/FINDINGS.md`, except the AsciiString is at `+0x18`, chars at
`+8`, not `+0x14` as FINDINGS reads.

**Strings live bit-inverted** in `lang/english.big` → `lotr.csf`, so grep finds
nothing and you guess from the English. "Game has already started" is
`LAN:ErrorGameGone` — the row is stale — *not* `LAN:ErrorGameStarted`.

## Fields that lie

`victoryFrame` and `defeatCount` (`VictoryConditions+0xC0`) are **removed**: the
first is machine-local, the second read 2 on one machine and 8 on another for
one match.

**Key on `teamWon`** — one alliance remains and some undefeated player is p *or
p's ally*, so a player who quit long before the win still reads `teamWon=1`.
Emit the raw value beside the decoded one: a wrong offset gave `namePtr: 255`,
visibly wrong rather than plausibly empty.

## Gotchas that shipped into a binary

All covered by `test_cave.py`/`test_overlay_build.py`, each watched failing
with its bug restored.

1. Section `Characteristics` belong at `+0x24`; one field late they read `0`.
2. Resolve a blob's landing address before emitting it, or every relative
   operand points at nothing.
3. No CRT: a local over a page, 64-bit arithmetic or a float compiles to
   `__chkstk`/`__alldiv`/`__ftol2`, which nothing resolves.
4. `fputs(str, FILE*)` takes the string first; `fprintf` does not.
5. Gate on state false *after* the match. The leave entry fires when a player
   leaves a finished one too, so anything meaning "a match was in progress"
   appends a spurious `leave` to every completed game.
6. A flag with no assertion behind it looks like a working one: `--probe`
   passed doing nothing after a rewrite dropped its guard.
7. `link.exe` stamps the export directory with the clock, making the committed
   artifact a different file on every rebuild.

## Building

```bash
python3 tools/modbuild.py --dist    # -> overlay/dist/lotrbfme.exe (needs wine)
```

Tests, and what producing `measured.jsonl` costs: `docs/lan-testing.md`.
