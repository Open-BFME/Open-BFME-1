# The overlay: modding without decompiling

Everything here was measured against retail `lotrbfme.exe` 1.03
(sha256 `c1a907c4…`) or read out of a running game. Nothing is inferred.

## The mechanism

A mod needs somewhere to put code that does not fit, and a way to reach a
function without owning its source. `tools/cave.py` appends a `.bfmemod`
section and installs a 5-byte `jmp rel32` at a target, relocating the
displaced instructions into the cave and returning. **A feature needs only an
address and a struct layout — the target does not have to be converted.**
That is what puts the ~65% of `.text` still held as raw retail bytes in reach:
decompilation stops being a prerequisite for modding and becomes a
prerequisite only for *rewriting*.

The image cooperates unusually well:

| property | value | why it matters |
|---|---|---|
| `SizeOfHeaders` | `0x1000`, table ends `0x3B8` | room for 81 more section headers |
| trailing bytes after last raw section | **0** | appending is a pure append |
| `SectionAlignment` = `FileAlignment` | `0x1000` | no padding arithmetic |
| `DllCharacteristics` | `0x0000` | no ASLR, no NX — absolute addressing in the cave is safe |
| `0xCC` padding inside `.text` | 3,347,683 B | in-place growth room before you even need the cave |

The first feature detours `VictoryConditions::update` (`0x0035F920`) — which is
still an `__emit` byte-lift with no source to edit — and writes a JSONL record
of how the match went. **No new imports were needed:** `fopen`, `fprintf`,
`fputs`, `fflush`, `fclose`, `getenv` and `time` are already in the IAT.

The overlay never touches `Code/` or `reverse/` and never participates in the
byte-exact rebuild. That separation is the point: a mod must not be able to
influence the byte gate.

## Codebase discoveries

**Retail has exactly 12 live command-line switches.** One table at
`0x012A6F40`: `-noshellmap -mod -noaudio -xres -yres -win -scriptDebug2
-scriptDebugLite -fullVersion -preferLocalFiles -Watchdog -noWatchdog`.
Zero Hour's whole determinism suite (`-deepCRC`, `-debugCRCFromFrame`,
`-verifyClientCRC`, `-noDraw`, the `-x*CRC` toggles) survives *as strings* in a
help blob but **nothing in the image references their addresses** — they are
dead text, not parseable switches. A `strings` grep will happily convince you
otherwise; check for a pointer to the string before believing it.

**BFME drives the mouse through `DirectInputMouse`, not `Win32Mouse`.** The
engine ships both; retail picked DirectInput, and the ledger confirms it
(`??0DirectInputMouse@@QAE@XZ` at `0x006BB7F0`). This is the single fact that
decides whether synthetic input works — see Testing below.

**`d3d9.dll` is not statically imported.** It is `LoadLibrary("D3D9.DLL")` +
`GetProcAddress("Direct3DCreate9")` at one site, RVA `0x90AD09`, inside the
594-byte function at `0x0090AB60` (still an unconverted `gen_asm` dump). The
W3D renderer funnels every device call through the `DX8CALL()` macro — **34
distinct D3D entry points across all of WW3D2** in the Zero Hour reference tree,
which is the closest measurable proxy for BFME's DX9 fork of the same code.
A Vulkan backend is a bounded interface, not a rewrite — though DXVK already translates D3D9→Vulkan for free,
so the only reason to go native is the submission *pattern*, which DXVK cannot
fix.

**918,841 bytes across 1,189 files are `__emit` byte-lifts.** They sit inside
the "converted" number but carry no semantics, and `AGENTS.md`'s anti-lift
policy forbids them. Judging a file by its path is not enough — `grep -l
__emit` before assuming a body is editable.

**`PlayerLeaveStatus` is at `TheGameLogic+0x1B0`, stride `0x1C`:**

```
+0x00 leave status   1 = graceful quit, 2 = voted out, 0 = never left
+0x04 leave frame
+0x08 defeat frame
+0x0C victory frame  (see "Fields that lie")
+0x10 empty flag     0 for an occupied slot, 1 for an empty one
+0x14 slot index     255 when unassigned
+0x18 AsciiString    one pointer; characters at +8
```

`reverse/game_end/FINDINGS.md` says "then a present byte and an AsciiString",
which reads as `+0x10` and `+0x14`. **The name is at `+0x18`.** Found by
dumping all seven dwords of a live record rather than guessing a second time.

**The ladder packet's `seed` field is not a seed.** Disassembling
`generateLadderGameResultsPacket` (`0x00639190`) contiguously from its entry,
the first vararg resolves to `byte [TheGameLogic+0x6C]` — the same value as its
fourth. It sits in a path 1.03 never executes (`populatePlayerInfo`'s only
callers run from a `.wnd` layout the image does not contain). Do not build a
match key on it.

**A quitter usually writes NO end record — and a 1v1 will tell you otherwise.**
FINDINGS says the leaver "does not wait: it posts `MSG_CLEAR_GAME_DATA` and is
on the score screen a tick later". In a measured LAN 1v1 the quitter *did* write
a full end record, which looked like FINDINGS being pessimistic. It was not: the
game there ended one frame after the quit (leave 287, end 288), so the leaving
machine's last `update` still saw `m_endFrame` set. In a measured 2v2 the quit
happened at frame 355 and the match ran to 1849 — the quitter wrote a start
record and nothing else.

So a leaver's file is normally the same shape as a crashed machine's: `start`
with no `end`. **Distinguish them from a survivor's file, not the leaver's** —
`slots[N].leave == 1` means that player quit, `leave == 0` with no `defeatFrame`
means they vanished. This is the single strongest argument for every record
carrying all eight slots rather than the local verdict: in that 2v2 the quitter's
fate *and its team's win* exist only in the survivor's file.

## Fields that lie

The most useful thing this work produced is a short list of data you should
*not* trust, each caught by measuring two machines instead of one.

**`victoryFrame` — removed.** It is machine-local: in a LAN 1v1 the survivor
recorded `203` for slot 0 while the quitter, having left at frame 287, recorded
`0` for the same slot. It is also never written at all in skirmish — an AI that
demonstrably won one still showed `0`. Everything it could convey is carried by
`teamWon`/`defeated`/`leave`/`leaveFrame`/`defeatFrame`, all of which agreed
byte for byte across both machines.

**`defeatCount` (`VictoryConditions+0xC0`) — removed.** It reported 2 on one
machine and 8 on the other for the same match. It is a running counter over 32
slots incremented by every true return of `hasSinglePlayerBeenDefeated`, not a
player count.

**`teamWon` — keep, and key on this one.** From `hasAchievedVictory(p)`: *"one
alliance remains and some undefeated player is p **or p's ally**"*. It was
identical on both machines in the 1v1 (the only match where both produced an end
record), and a 2v2 shows it doing the job it exists for:

```
2v2, Team 1 = joiner + Easy Army, Team 2 = host + Hard Army; host quits
  slot[1] 'host'  leave=1 leaveFrame=355 defeatFrame=356
  player[1]       defeated=1  teamWon=1     <- quit at 355, team won at 1849
  player[3]       defeated=0  teamWon=1     <- the ally that actually won it
  player[0]/[2]   defeated=1  teamWon=0     <- the losing side
```

A player who quit 1,500 frames before the win still reads `teamWon=1`. Nothing
else in the record says that.

The general rule: **emit the raw value next to the decoded one.** When the name
lookup read the wrong offset it produced `namePtr: 255, name: ""` — visibly
wrong data instead of a plausible empty string. That one habit turned a silent
misread into a five-minute fix.

## Testing a 2005 game with nobody at the keyboard

**A wine virtual desktop is load-bearing.** On bare Xvfb every synthetic click
is silently dropped — the pointer moves, `xdotool getwindowfocus` names the
game window, and nothing happens. There is no window manager, so nothing is
ever *foreground* in the Windows sense and DirectInput never acquires. Run the
game inside `wine explorer /desktop=bfme,WxH` and input works immediately.
`ydotool` (kernel uinput) is the fallback and was never needed.

**Pixel stability is not a readiness signal.** The loading splash is a static
image, so "nothing is moving" is true long before the menu exists. Two runs
clicked the splash, then landed the *next* click on whatever button occupied
that coordinate on the screen that finally drew — both times ending up in
Options while believing they had started a skirmish. Assert *which screen you
are on* before every click; `driver.py` matches a 60-pixel button strip against
a reference, which discriminates every menu tested (min off-diagonal score
13.9, tolerance 8).

**Two clients need two `WINEPREFIX`es, and nothing more.** The single-instance
mutex is per wineserver, so separate prefixes let two full clients run at once,
and LAN discovery and a full match work between them on the host network with
no network namespaces. Symptom of getting the prefix wrong: the second client
exits instantly with no error.

**Seating more than two clients needs BOTH a distinct CD key per prefix AND a
network namespace per client. Neither alone is enough — measured.**

Never clone a wine prefix for a multi-client test: the CD key comes with it.
Two clients always worked; a third was refused every time, and the message
depended on the network setup:

| network setup | what the third client was told |
|---|---|
| all clients on the host stack | "Game has already started" |
| each client in its own netns | **"Your serial is already in use"** |

The real cause was never the network. `wine3` and `wine4` were made with
`cp -a wine1`, so all three carried the same serial at
`HKLM\Software\Wow6432Node\Electronic Arts\EA Games\The Battle for
Middle-earth\ergc`. `wine1` and `wine2` had been created independently with
sequential keys (`…ED06`, `…ED07`), which is exactly why two clients were always
fine and the third never was. Give every prefix its own `ergc` value.

Fixing the serial raised the ceiling from two clients to three, and then the
real wall showed itself: **clients that seat successfully get dropped again**,
which is the "player was not responding" message the host prints. This was
mistaken for a join limit for a long time because the symptom looks identical
from the joiner's side.

The wall is environment capacity, not the game and not the mod. Xvfb renders
through `llvmpipe`, so each client burns ~200% CPU rasterising while the box's
two real GPUs (`/dev/dri/card1`, `card2`) sit idle; load reaches ~40 and clients
cannot service the lobby heartbeat. Measured progression:

| serials | network | outcome |
|---|---|---|
| duplicate | shared stack | 2 seat, 3rd refused — "Game has already started" |
| duplicate | namespace each | 3rd refused — **"Your serial is already in use"** |
| distinct | shared stack | **3 seat**, then one drops |

**Dropping to `-xres 640 -yres 480` fixes it.** Quartering the pixels quarters
what llvmpipe has to do: CPU per client falls from ~200% to ~140%, and all four
clients seat — including the third, which had never once succeeded at 1024x768
in any serial or namespace configuration. Three then stay stable indefinitely;
the fourth still drops sometimes, so a 4-human match wants GPU rendering, but
three humans on teams is reliable.

Two consequences for the harness, both now in `driver.py`:

* **Coordinates are fractions of the detected client area, never screen pixels.**
  `client_rect()` reads the window and `at()`/`tap()` map a named UI point onto
  it, so changing resolution costs nothing. Re-deriving fifteen constants by
  hand is how a harness rots.
* **Interior widgets do not scale like the button strip.** The nickname field
  and the game-list rows sit at different fractions at 640x480 than at
  1024x768; the game reflows them. Only the bottom button strip is
  proportional. And `BACK` is not in a fixed column at all — it moves with the
  number of buttons on the screen, and assuming otherwise walked a run into the
  LOAD screen and stranded it there.
* **Park the pointer before matching a screen.** A button under the cursor
  draws highlighted, and the button strip is exactly what the match reads —
  leaving the pointer on it adds ~9 to every score and fails a screen that is
  in fact correct.

Before reaching that, these were eliminated, each by its own run: a 2-player map
(it was Black Gate, "Number of Players: 4"); the host having started the game
(`PLAY GAME` never clicked); a stale game list (refreshed to `2/4` first);
joiners browsing before the game existed (host created first); port collision
(each client takes its own from `8086`–`8089`, `ss -uln`); duplicate nicknames;
and CPU starvation (`taskset -c` per quarter took load from ~53 to ~30, worth
doing regardless, but it changed nothing).

**A fresh prefix has no skirmish profile** and opens a modal "Create Profile"
over the setup screen, dimming the button strip so a screen match fails with no
explanation. `driver.py:dismiss_profile_prompt` handles it.

**Hold the display per instance, never in a module global.** `driver.py` read
`DISPLAY` at import time; every "host" action in a scripted two-client run was
silently going to the joiner's screen, screenshots included.

## Gotchas that cost a build

Each of these shipped into a binary and was caught only by disassembling the
result. All five are now covered by `tools/tests/test_cave.py` and
`test_overlay_build.py`, and each test was watched to fail with its bug
reintroduced before being kept.

1. **Section `Characteristics` belong at `+0x24`.** Packed one field late they
   read `0` — a section the loader faults on the moment it is entered.
2. **yasm `-f bin` aligns its output section.** An `org` at a non-4-aligned
   address emits leading pad bytes, and the trampoline lands short of the
   payload's first instruction. Align every cave allocation.
3. **Resolve the landing address before emitting, not after.** A detour that
   reads a raw `cave_used` instead of `next_rva()` is correct only while the
   cave is empty — which is exactly the case a naive test covers and the real
   builder never hits.
4. **The relocated prologue is appended after the *whole* blob.** A payload
   with helper functions after its exit must *jump* past them; falling off the
   end of its own code runs the helpers with a live return address.
5. **`fputs(str, FILE*)` takes the string first; `fprintf(FILE*, fmt, …)` does
   not.** Reusing fprintf's push order hands the `FILE*` over as the string.
   The game raised `EXCEPTION_INVALID_HANDLE` mid-match and helpfully named an
   address inside the cave in its own stack trace.

A sixth was a *test* that reported success while doing nothing: `--probe`
depended on an `%ifndef PROBE` block that a later rewrite replaced. A
diagnostic flag with no assertion behind it is indistinguishable from a working
one.

## Building it

```bash
python3 tools/modbuild.py --dist        # -> overlay/dist/lotrbfme.exe + manifest.json
python3 -m pytest tools/tests/test_cave.py tools/tests/test_overlay_build.py
tools/gametest/run_skirmish.py :78 ~/.wine lotrbfme.exe 'C:/r.jsonl' ~/.wine/drive_c/r.jsonl out
```

`tools/gametest/` also holds `run_lan.py` (two clients, one quits),
`run_crash.py` (SIGKILL mid-match) and `run_probe.py` (drops the end-of-game
gate so struct layouts can be read off a live game in minutes instead of
playing a match to its finish).
