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

## Making a player lose on demand

Selecting the citadel fills the palantir ring, and the pale icon at its lower
left is **Demolish — "Destroys your Citadel"**. No confirmation prompt. This is
what makes a win/loss matrix affordable: it defeats a player instantly, with
`leave=0`, so the record is a genuine loss rather than a quit — and every
multiplayer loss measured before it came from someone quitting, which is a
different row entirely.

Caveat, unconfirmed: it destroys only the citadel. In one run the player was
defeated instantly; in another they kept playing with no citadel, and the
difference looked like other structures having been built by then (command cap
400 vs 200). Demolish alone is not a guaranteed defeat once a base exists.

Two things that make a matrix cheap to run once discovered:

* **After the score screen every client lands back in the network lobby.** The
  host creates a new game and the others rejoin — no main-menu walk. A reseat
  is ~2 minutes instead of ~40.
* **The game list has to have populated before the join click.** Straight after
  a match it has not; clicking a row that is not there yet silently does
  nothing, and the join reports success anyway.

## Read the error string before diagnosing the error

A host plus three joiners was reliable; the fourth was refused, and the refusal
survived every environmental fix — distinct CD keys, network namespaces, port
availability, resolution, renderer, load, join ordering, and a fresh client
restart. All of that was aimed at the wrong target, because the error had been
identified by eye rather than by lookup.

The dialog reads **"Game has already started"**. The obvious key, and the one
this was chased against for a long time, is `LAN:ErrorGameStarted`. That key's
text is **"Sorry, this game has already started."** — different string. The one
that matches the dialog exactly is `LAN:ErrorGameGone`.

Those two mean opposite things. *Game started* is a refusal on state: the match
is under way, do not admit anyone. *Game gone* is a refusal on identity: the
game you asked to join is not in the host's list any more. A LAN client joins
the row it has, and the host's advertisement changes as players take slots — so
a row selected before an earlier player was seated is stale by the time it is
clicked, and the host answers "gone". The failure was never about the fourth
seat; it was about the age of the row.

Two things follow for anyone testing this. Select the row again on every
attempt, from a fresh broadcast — re-clicking JOIN on a row already on screen
re-sends the same stale identity and fails identically forever. And decode the
string table rather than reading the screen: strings live bit-inverted in
`lang/english.big` -> `lang\english\lotr.csf`, so grep finds nothing and the
temptation is to guess from the English. `LAN:ErrorGameFull`,
`LAN:ErrorDuplicateName`, and `LAN:ErrorGameExists` are all similarly easy to
confuse by sight.

The client-side table that maps an error code to one of these keys is at RVA
`0x00688B50`, dispatching through a jump table at `0x00688C58` (code 2 GameFull,
3 DuplicateName, 6 GameStarted, 8 GameGone). Worth knowing before building on
it: that function has no rel32 callers and no dword references anywhere in the
13MB of `.text` — it is unreferenced, like the ladder-results path. Whatever
raises the dialog in a running game reaches it some other way.

## Four real clients, one 2v2, four agreeing records

A 2v2 between four real clients on one machine plays to a result, and all four
machines write records that agree. Four things were needed, and each hid the
next.

**One address per client.** Separate WINEPREFIXes carry two clients. Past that,
joiners are admitted and then dropped as "player was not responding" -- which
reads as a performance problem and is not one. The source says why: the host
tracks each slot's liveness by address (`getPlayerLastHeard`, weeding lobby
players at `s_resendDelta*2` = 20s), and `LANAPI.cpp` assigns every slot the
same port with the comment *"LAN game, everyone has a unique IP, so it's ok to
use the same port"*. Behind one address the announcements all attribute to one
slot and the rest age out. `lan4-netns.sh` gives each client its own stack
inside an unprivileged user namespace -- no root, nothing touched on the host,
gone when the run ends.

**A hostname that resolves to that address.** The game picks the address it
binds its game transport to with `gethostname()` + `gethostbyname()`
(IPEnumeration.cpp). In a namespace that answers `::1`, which the namespace does
not have. Each namespace gets its own UTS namespace and a matching `/etc/hosts`
entry -- and `nsswitch.conf` must be overridden too, because the stock order
puts `resolve [!UNAVAIL=return]` ahead of `files`, so systemd-resolved answers
first and `/etc/hosts` is never read.

**Each player sets their own team.** The host's team dropdowns for other players
are inert. They fail silently, and the game starts as a free-for-all while the
script reports success.

**Let the lobby settle, then keep the wire in.** Clicking PLAY GAME a second
after the last team change leaves the host in the match and the joiners in the
lobby; twelve seconds is enough. And the harness must not exit: `br0` lives in
the outer namespace with every client's veth plugged into it, so when the
seating script returned the bridge was destroyed and all four clients lost the
network mid-match. That looked exactly like the in-game mesh failing to form and
was written up that way for a while. A raw-socket capture inside a namespace
settled it -- traffic from both peers right up to `PLAY GAME + 8s`, then
`recv: Network is down`.

Two smaller things worth keeping. The LAN lobby is broadcast-only: announcements
go to 255.255.255.255 sprayed across ports 8086-8091, which is why clients
holding different ports still see each other, and why no unicast appears until a
match forms. And BFME already ships generous in-game timeouts -- patch 2.22 sets
`NetworkDisconnectTime=15000`, `NetworkPlayerTimeoutTime=100000`,
`NetworkKeepAliveDelay=360` -- all INI-settable through `TheGlobalData`, so a
slower machine can be accommodated without touching the exe.

### What the four records say

Demolishing a citadel defeats that player instantly with `leave=0`, so the
record is a genuine loss rather than a quit. The button is tiny: it is the pale
icon at the lower left of the palantir ring, and it only responds within a pixel
or two of its centre -- a click four pixels high produces no tooltip and no
effect, silently.

    machine   result    frame   players (defeated/teamWon)
    P1_T1     victory    3757   P1:d0/w1  P2:d0/w1  P3:d1/w0  P4:d1/w0
    P2_T1     victory    3757   P1:d0/w1  P2:d0/w1  P3:d1/w0  P4:d1/w0
    P3_T2     defeat     3757   P1:d0/w1  P2:d0/w1  P3:d1/w0  P4:d1/w0
    P4_T2     defeat     3757   P1:d0/w1  P2:d0/w1  P3:d1/w0  P4:d1/w0

All four agree on the end frame, on both defeat frames (P3 at 2583, P4 at 3757),
and on `teamWon`, with `leave=0` for everyone and `desync=0`. A reconciler
keying on `teamWon` gets the same answer from any of the four.

## Two harness bugs that manufactured evidence

Both produced confident, wrong results for a long time, and both are the same
mistake: believing a check that was never watched failing.

The retry loop around joining ended with an unconditional `break`, so three
attempts were one attempt. Every "the fourth seat is refused" conclusion rested
on a single try.

The seated check compared the button strip along the bottom of the screen. A
JOIN FAILED dialog *dims* that strip, so the strip differs, so the check read
"not on the lobby any more" and reported the join as successful. It now matches
the "CUSTOM GAME LOBBY" sub-header, which sits above anything a modal covers.

## An accidental measurement for the game_end track

`reverse/game_end/FINDINGS.md` lists three machines that can wait at game end
and says of the quit freeze: "Which one the quit freeze is" is open, pending a
LAN test. One got measured here by accident.

In a three-human match (P1 hosting, P2 and P3 on the other team), P2 quit and
then **P1 — the host, and therefore the packet router — quit**. FINDINGS
predicts what follows: "the survivors of a router that quit... hold a request
the router never answers and fall through to the DisconnectManager's timeout
path." Observed: the surviving client keeps simulating (the screen keeps
changing, resources keep accruing) but never reaches `m_endFrame`, so it never
records a result. Still stalled 6+ minutes after the router left, against the
10 000 ms in `hasLeaveRequestTimedOut` and the 30 000 ms in `Connection::doSend`
— so neither of those is what a router-quit survivor is waiting on.

Practical consequence for anyone testing game end over LAN: **do not let the
host be the player who quits.** Keep the router alive and quit from a joiner,
or the match never resolves and the test measures nothing. This was a
test-design mistake here, and it cost a full seating cycle.

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
