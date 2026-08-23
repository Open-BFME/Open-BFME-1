# Plan: measure the core matrix, close the zero-record gap

Delete this file before opening the PR.

## Architecture

```
overlay/features/020-gameresult/src/payload.asm      the mod (x86, code cave)
   │  built by tools/modbuild.py ── uses ──> tools/cave.py   (PE section + detour)
   ▼
overlay/dist/lotrbfme.exe                            the shipped modded exe
   │  run by
   ▼
tools/gametest/lan4-netns.sh ─> lan4-netns-inner.sh
   │      unprivileged user+net+uts namespace per client; holds the bridge up
   ├─> gpu-displays.sh    headless sway, GPU-backed X, display detected not assumed
   ├─> launch-mod.sh      wine, one WINEPREFIX + one CD key per client
   └─> run_lan4.py        seats N, sets teams per-client, settles, starts
          └─ uses driver.py    resolution-independent screenshot/click
   │  produces  %APPDATA%\...\GameResult.jsonl  ×N
   ▼
reverse/game_end/measured/<row>/P*.jsonl             committed fixtures
   ▼
tools/tests/test_game_records.py                     property tests (NEW)
```

Currently only the **end** record exists, written from a detour on
`VictoryConditions::update`. Machines that quit or die before game end write
nothing; the design covers that with a **start** record plus every survivor
carrying all slots' `PlayerLeaveStatus`. That fails only when no machine
survives to game end.

## What ships

### 1. Exit-mode primitives  (`tools/gametest/exits.py`)
`quit(d)` ESC→Exit→confirm · `demolish(d)` select citadel → Demolish ·
`kill(prefix)` SIGKILL · `freeze(prefix)` SIGSTOP.
Kill/freeze signal the client by matching `WINEPREFIX` in `/proc/*/environ`,
the same rule `kill-mine.sh` already uses.

Demolish needs per-client citadel targeting: each camera sits differently, and
the button only responds within ~2px of centre.

### 2. Row runner  (`tools/gametest/run_row.py`, rows declared in `rows.py`)
A row declares shape, ordered per-player exit modes, expected file-presence
pattern and expected winner. The runner seats via `run_lan4.py`, applies the
exits in order, waits for the score screen, and copies each client's JSONL into
`reverse/game_end/measured/<row>/`.

### 3. The eleven rows
Core ten: **3, 4, 7, 8** (what crash and freeze look like in a record — every
other row containing K or F is uninterpretable until these land), **2, 5, 6**
(quit and host-loss), **27, 30, 32** (winning team lost a member).
Plus **row 9** (1v1, both quit), which is the red-green test for the fix below.

### 4. Leave-record detour — closes the zero-record gap
`Network::quitGame` is pinned: vtable VA `0x0111A968` slot `+0x78`, body
`0x006822E0`. Detour it to append a `"leave"` record carrying the local slot,
frame, and the same slot table the end record writes.

That makes row 9 recoverable: both machines state who left and when, which is
the complete and correct answer for a match nobody won. It does **not** help
kill or freeze — no code runs — and the plan does not pretend otherwise.

### 5. `docs/game-quitting.md` (written)
Under 500 words: where the file lands, the JSONL format, and the quit path.
Survives the pr.md cleanup as-is — it is the doc a future reader needs.

While writing it, one defect surfaced: `getenv("APPDATA")` is not null-checked,
so an unset `APPDATA` formats `(null)` into the path and the record is silently
dropped. Nothing sets `APPDATA` in the harness so it has never fired. One-line
fix in `open_file`, worth folding in with the `quitGame` detour since both
touch the same payload.

### 6. Cleanup required by pr.md
Delete `run_lan.py`, `run_skirmish.py`, `run_probe.py`, `run_crash.py`
(superseded by the generalised `run_lan4.py`), `netns-setup.sh` and
`netns-launch.sh` (superseded by the unprivileged rig; both need sudo),
`sniff.py` and its `BFME_SNIFF` block (diagnostic; its finding is in the docs),
and `ref/` if nothing at 1024x768 remains. Slim `docs/overlay.md` 444 → ~110
lines. Fold `docs/test-matrix.md` into the measured results. Keep
`docs/game-quitting.md`.

## Red-green

The fix has a real red state, and it is measured, not asserted:

1. Run row 9 **before** the detour. Both clients quit a 1v1. Expect **zero**
   end records. `test_game_records.py::test_row_9` asserts the outcome is
   recoverable → **fails**.
2. Add the `quitGame` detour, rebuild `overlay/dist/lotrbfme.exe`.
3. Run row 9 again. Two `leave` records → **passes**.

Both fixture sets are kept (`row09-pre-fix/`, `row09/`) so the red state stays
reproducible without reverting the exe.

## Testing

`tools/tests/test_game_records.py`, parametrized over every directory in
`reverse/game_end/measured/`. No game needed — the fixtures are committed, so
this is permanent regression cover for any future payload change:

* every surviving machine agrees on `frame`, the `teamWon` vector, and each
  slot's `leave` / `leaveFrame` / `defeatFrame`
* file presence matches the row's declared pattern (a quitter writes no end
  record; a killed client writes nothing at all)
* exactly one team carries `teamWon=1`, or none if nobody won
* the union of records names every player who was in the lobby
* `desync == 0` and `observer == 0` on every record

`tools/tests/test_overlay_build.py` gains: the second detour installs, both
stolen prologues relocate correctly, and the two detours do not overlap. Each
assertion is confirmed by reintroducing the bug and watching it fail — the rule
already used for the five toolchain bugs this repo has shipped.

## Proof

* four score screens from one 2v2, all listing four players
* the record table showing all four machines agreeing
* `pytest tools/tests/test_game_records.py` green
* row 9 before/after: zero records → two leave records

PR body is a single composed PNG (pr.md: new feature = image only, title ≤ 10
words). Branch off `origin/master` carrying the 22 existing commits plus this
work.

## Risks

* **Kill and freeze leave-codes are unmeasured.** Rows 3/4/7/8 exist to settle
  them; every K/F row after that depends on the answer.
* **`quitGame` is a vtable slot, not a rel32 call.** The detour must patch the
  body at `0x006822E0`, and the payload must preserve thiscall `ecx`.
* **Shared machine.** Four clients need ~4GB during load; this box has been at
  3.8GB available with 25GB of swap in use. Rows will need re-running when it
  is busy, and a row that cannot be run gets reported as not-run, never
  inferred.
