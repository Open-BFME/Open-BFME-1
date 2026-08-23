# The overlay: modding without decompiling

Everything here was measured against retail `lotrbfme.exe` 1.03
(sha256 `c1a907c4…`) or read out of a running game. Nothing is inferred.

## The mechanism

`tools/cave.py` appends a `.bfmemod` section and installs a 5-byte `jmp rel32`
at a target, relocating the displaced instructions into the cave and returning.
**A feature needs only an address and a struct layout — the target does not have
to be converted**, which puts the ~65% of `.text` still held as raw retail bytes
in reach: decompilation stops being a prerequisite for modding.

| property | value | why it matters |
|---|---|---|
| `SizeOfHeaders` | `0x1000`, table ends `0x3B8` | room for 81 more section headers |
| trailing bytes after last raw section | **0** | appending is a pure append |
| `SectionAlignment` = `FileAlignment` | `0x1000` | no padding arithmetic |
| `DllCharacteristics` | `0x0000` | no ASLR, no NX — absolute addressing is safe |
| `0xCC` padding inside `.text` | 3,347,683 B | growth room before the cave is needed |

The first feature detours `VictoryConditions::update` (`0x0035F920`) and
`ConnectionManager::sendPlayerLeaveCommands` (`0x00665C10`) — both still
`__emit` byte-lifts with no source to edit — and writes a JSONL record of how
the match went (`docs/game-quitting.md`). **No new imports were needed:**
`fopen`, `fprintf`, `fputs`, `fflush`, `fclose`, `getenv` and `time` are already
in the IAT. The overlay never touches `Code/` or `reverse/` and never
participates in the byte-exact rebuild — a mod must not be able to move the
byte gate.

## Addresses and layouts worth keeping

**`PlayerLeaveStatus` at `TheGameLogic+0x1B0`, stride `0x1C`:** `+0x00` leave
status (1 quit, 2 stopped answering, 0 never left), `+0x04` leave frame, `+0x08`
defeat frame, `+0x0C` victory frame (lies — below), `+0x10` empty flag, `+0x14`
slot index (255 unassigned), `+0x18` AsciiString, characters at `+8`.
`reverse/game_end/FINDINGS.md` reads as if the name were at `+0x14`; it is not.

**Retail has 12 live command-line switches**, one table at `0x012A6F40`
(`-noshellmap -mod -noaudio -xres -yres -win -scriptDebug2 -scriptDebugLite
-fullVersion -preferLocalFiles -Watchdog -noWatchdog`). Zero Hour's determinism
suite (`-deepCRC`, `-verifyClientCRC`, `-noDraw`, the `-x*CRC` toggles) survives
as *strings* with nothing referencing their addresses: check for a pointer to a
string before believing `strings`.

**The mouse is `DirectInputMouse`, not `Win32Mouse`** (`??0DirectInputMouse@@QAE@XZ`
at `0x006BB7F0`) — the fact that decides whether synthetic input works at all.
**`d3d9.dll` is not statically imported**: `LoadLibrary("D3D9.DLL")` +
`GetProcAddress("Direct3DCreate9")` at RVA `0x90AD09`, inside the unconverted
594-byte function at `0x0090AB60`, and every device call funnels through
`DX8CALL()` — 34 distinct D3D entry points across WW3D2, so a Vulkan backend is
a bounded interface rather than a rewrite.

**LAN error codes** map to string keys at `0x00688B50` via a jump table at
`0x00688C58` (2 GameFull, 3 DuplicateName, 6 GameStarted, 8 GameGone) — a
function with no callers and no dword references in `.text`, so whatever raises
the dialog reaches it some other way. Strings live bit-inverted in
`lang/english.big` → `lang\english\lotr.csf`, so grep finds nothing and the
temptation is to guess from the English. **"Game has already started" is
`LAN:ErrorGameGone`** — the row you clicked is stale — *not*
`LAN:ErrorGameStarted` ("Sorry, this game has already started."). Opposite
meanings; chasing the wrong one costs days.

## Fields that lie

Each was caught by measuring two machines instead of one. `victoryFrame` and
`defeatCount` (`VictoryConditions+0xC0`) are **removed** from the record:
the first is machine-local (a survivor recorded `203` for a slot whose own
machine recorded `0`) and skirmish never writes it; the second counts true
returns of `hasSinglePlayerBeenDefeated` over 32 slots, so it read 2 on one
machine and 8 on the other for one match. The ladder packet's `seed` is not a
seed either — in `generateLadderGameResultsPacket` (`0x00639190`) it resolves to
`byte [TheGameLogic+0x6C]`, on a path 1.03 never executes.

**Key on `teamWon`.** From `hasAchievedVictory(p)`: one alliance remains and
some undefeated player is p *or p's ally*, so a player who quit 1,500 frames
before the win still reads `teamWon=1`. And **emit the raw value next to the
decoded one**: a wrong offset produced `namePtr: 255, name: ""` — visibly wrong
instead of plausibly empty.

## Testing a 2005 game with nobody at the keyboard

The rig is `tools/gametest/`; each script carries the reasoning for its own
shape. The facts that live nowhere else:

* **A wine virtual desktop is load-bearing.** On bare Xvfb every synthetic click
  is silently dropped — no window manager means nothing is ever *foreground* in
  the Windows sense and DirectInput never acquires. Run under
  `wine explorer /desktop=bfme,WxH`.
* **Pixel stability is not readiness.** The splash is a static image, so
  "nothing is moving" is true long before the menu exists. Assert *which screen
  you are on* before every click, pointer parked — a button under the cursor
  draws highlighted and adds ~9 to a screen match that is otherwise correct.
* **Four clients need a distinct CD key per prefix AND a network stack each.**
  Never `cp -a` a prefix: the serial at `HKLM\…\EA Games\The Battle for
  Middle-earth\ergc` comes with it. The host tracks slot liveness by address
  (`getPlayerLastHeard`, 20 s) while `LANAPI.cpp` gives every slot the same
  port, so behind one address the announcements attribute to one slot and the
  rest age out as "player was not responding".
* **A namespace needs a hostname resolving to its own address** — the transport
  bind address comes from `gethostname()` + `gethostbyname()` — **and**
  `nsswitch.conf` forced to `hosts: files`, or systemd-resolved answers `::1`
  and the in-game mesh never forms while the broadcast lobby hides it.
* **Each player sets their own team.** The host's dropdowns for other players
  are inert and fail silently into a free-for-all.
* **Render on the GPU.** llvmpipe costs ~200% CPU per client; four of them drop
  each other's heartbeats. 640x480 halves it again.
* **Demolish is how a player loses on demand** — the pale icon at the lower left
  of the citadel's palantir ring, no confirmation, answering only within a pixel
  or two of its centre. It defeats instantly with `leave=0`, so the record is a
  genuine loss and not a quit.

## Gotchas that cost a build

Each shipped into a binary and was caught only by disassembling the result. All
are covered by `tools/tests/test_cave.py` and `test_overlay_build.py`, each test
watched failing with its bug reintroduced.

1. **Section `Characteristics` belong at `+0x24`.** One field late they read
   `0` — a section the loader faults on the moment it is entered.
2. **yasm `-f bin` aligns its output section.** An `org` at a non-4-aligned
   address emits leading pad bytes and the trampoline lands short of the
   payload's first instruction. Align every cave allocation.
3. **Resolve the landing address before emitting, not after.** A detour reading
   a raw `cave_used` instead of `next_rva()` is correct only while the cave is
   empty — the one case a naive test covers.
4. **The relocated prologue is appended after the *whole* blob.** A payload with
   helpers after its exit must *jump* past them.
5. **`fputs(str, FILE*)` takes the string first; `fprintf(FILE*, fmt, …)` does
   not.** Reusing fprintf's push order hands the `FILE*` over as the string and
   raises `EXCEPTION_INVALID_HANDLE` mid-match.
6. **Gate on state that is false after the match, not merely "in progress".**
   The leave payload's entry fires when a player leaves a *finished* match too;
   a `d_started` latch or the network status (still 1 on the score screen)
   appends a spurious `leave` to every finished game.

A seventh was a *test* that reported success while doing nothing: `--probe`
depended on an `%ifndef PROBE` block a later rewrite had removed. A diagnostic
flag with no assertion behind it is indistinguishable from a working one.

## Building and running it

```bash
python3 tools/modbuild.py --dist    # -> overlay/dist/lotrbfme.exe + manifest.json
python3 -m pytest tools/tests/test_cave.py tools/tests/test_overlay_build.py \
                 tools/tests/test_game_records.py
tools/gametest/gpu-displays.sh 4 800x600     # write the numbers into .env
python3 tools/gametest/run_row.py row30      # seat, play and land one matrix row
```

Seating installs `overlay/dist/lotrbfme.exe` into the game directory, so a
measured row is always a measurement of the shipped artifact. Rows are declared
in `tools/gametest/rows.py` before they are run; results land in
`reverse/game_end/measured/` (see its README).
