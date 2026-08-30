# mods/: the cave mechanism, and what it costs to get wrong

## The rules

**Mods always stack.** There is no mix-and-match and no per-feature build:
`python3 tools/modbuild.py --dist` produces exactly one executable at
`mods/dist/lotrbfme.exe`, and two features claiming the same address is a hard
build error, never a last-writer-wins merge. `--dist` refuses `--only` for the
same reason — a partial build silently replaced the shipped artifact once.

**No mod is part of the byte-exact decomp.** A feature never touches `Code/` or
`reverse/`, so `./build.sh` and both git hooks are unaffected. That separation
is what keeps the byte gate meaningful, and why `mods/` sits outside `Code/`.

**`tools/modbuild.py` is the authority on which features exist**, and no
document lists them. One used to — a `features = [...]` array in a `.toml`
nothing parsed — and it was already wrong before anyone noticed. A feature
directory's numeric prefix is its application order, not decoration. `010` is
deliberately unused: it was reserved for a test-harness feature (`-noDraw` plus
per-frame logic CRC) that proved unnecessary, since driving the real game with
synthetic clicks and asserting on screenshots covers the journey, and a
feature's own output file covers the outcome.

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
`mods/features/020-gameresult/README.md`. Both targets are `__declspec(naked)` `__asm` lifts — no
semantics to edit — which is the only reason a detour is needed; convert one and
its detour disappears. A mod never joins the byte-exact rebuild: it
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

All covered by `test_cave.py`/`test_mods_build.py`, each watched failing
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

## Instruments are not features

`FEATURES` ships; `INSTRUMENTS` measures. `030-netlatprobe` writes tens of lines a
second, so it is selected only by name and `--dist` refuses to carry one —
`mods/dist` is what every ladder player runs. See `docs/measuring.md`.

A hook that needs the target's own argument uses `detour_call(..., args=("ecx",
"stack:0"))`: a thiscall's `this` arrives in ecx and its arguments do not, and
the shim lifts one off the target's frame. That is only meaningful at a
function's **entry**, before the body has pushed anything.

## Building

```bash
python3 tools/modbuild.py --dist    # -> mods/dist/lotrbfme.exe (needs wine)
```

Tests, and what producing `measured.jsonl` costs: `docs/measuring.md`.
