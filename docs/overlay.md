# The overlay: modding without decompiling

Measured against `lotrbfme.exe` 1.03 or a running game.

## The mechanism

`tools/cave.py` appends a `.bfmemod` section and installs a 5-byte `jmp rel32`
at a target, relocating the displaced instructions into the cave and returning.
**A feature needs only an address and a struct layout — the target need not be
converted**, which puts the ~65% of `.text` still held as raw retail bytes in
reach. `DllCharacteristics` is `0x0000`, so absolute addressing is safe.

**A feature is one `.cpp`; no hand-written machine code survives.**
`tools/modbuild.py` compiles it with the game's own MSVC 7.1, relocates the
linked image into the cave, and reaches each entry through a shim `cave.py`
*generates* (`pushad/pushfd/cld/push ecx/call`). There is no loader and no CRT,
so the link is naked and fails on any unresolved external.

The one feature detours `VictoryConditions::update` (`0x0035F920`) and
`ConnectionManager::sendPlayerLeaveCommands` (`0x00665C10`), writing the JSONL
of `docs/game-quitting.md`. Both targets are `__declspec(naked)` `__asm` lifts
in the ledger — no semantics to edit — which is the only reason a detour is
needed; convert one properly and its detour disappears. The overlay never
touches `Code/` and never joins the byte-exact rebuild: a mod must not move the
byte gate.

## Addresses worth keeping

**`PlayerLeaveStatus` at `TheGameLogic+0x1B0`, stride `0x1C`** — full layout in
`reverse/game_end/FINDINGS.md`, but note the AsciiString is at `+0x18` with its
chars at `+8`, not at `+0x14` as FINDINGS reads.

**`d3d9.dll` is not statically imported**: `LoadLibrary`/`GetProcAddress` at RVA
`0x90AD09`, every device call funnelling through `DX8CALL()` — 34 entry points,
so a Vulkan backend is a bounded interface. **The mouse is `DirectInputMouse`**
(`0x006BB7F0`), which decides whether synthetic input works.

**Strings live bit-inverted** in `lang/english.big` → `lotr.csf`, so grep finds
nothing and you guess from the English. "Game has already started" is
`LAN:ErrorGameGone` — your row is stale — *not* `LAN:ErrorGameStarted`. Opposite
meanings.

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
2. Resolve a blob's landing address before emitting it. Built for one address
   and placed at another, every relative operand in it points at nothing.
3. There is no CRT. A local over a page, 64-bit arithmetic or a float compile
   to `__chkstk`/`__alldiv`/`__ftol2`, which nothing can resolve.
4. `fputs(str, FILE*)` takes the string first; `fprintf` does not.
5. Gate on state that is false *after* the match: the leave entry fires when a
   player leaves a finished one too. Anything that only says "a match was in
   progress" appends a spurious `leave` to every completed game.
6. A flag with no assertion behind it looks like a working one: `--probe`
   passed doing nothing after a rewrite dropped its guard.
7. `link.exe` stamps the export directory with the clock. Left in, the
   committed artifact is a different file on every rebuild.

## Building

```bash
python3 tools/modbuild.py --dist    # -> overlay/dist/lotrbfme.exe (needs wine)
```

Tests, and what producing `measured.jsonl` costs: `docs/lan-testing.md`.
