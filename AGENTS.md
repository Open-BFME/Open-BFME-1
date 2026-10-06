# Contributing

Many agents push to `origin/master` all day. Keep each change small, verified
and easy to rebase. `docs/matching.md` covers byte matching and
`docs/structural.md` manual reverse engineering.

## Verifier upgrade in progress

Gate checks land shortly (jump tables, extent tails, local statics,
`gen-alias` tokens, data RVAs, thunk-table names). Until then, edit
`tools/build.py`, `.githooks/` or baselines only to fix a verifier bug; add no
`gen-alias` notes, data pins, alias rows or `__emit` lifts; pause bulk renames.
Flagged rows will be queued.

## Setup

- `git pull --rebase origin master`. Once per host:
  `python3 -m pip install -r tools/requirements.txt`.
- On Windows use `.\build.cmd` (same arguments as `./build.sh`) and
  `tools\fleet\launch_fleet.cmd`; run other scripts as `bash tools/<name>.sh`, never
  directly from PowerShell or cmd. Python is `py -3` in PowerShell.
- `python3 tools/check_csv.py` must pass before other work.

## Work selection

An explicit request or assigned lane overrides the queue. WorldBuilder work
uses `python3 tools/worldbuilder.py next` and `docs/worldbuilder.md`, with its
own ledger and verification.

1. **Linking first.** `tools/link_check.py next` claims the name
   alone blocking the most unlinked bytes; `near` lists files linking once
   calls use the pinned row's name (never `/alternatename`). Fix it minimally:
   keep the retail-proven copy, remove a wrong definition nothing
   verified needs, define one datum (`tools/add_data_match.py`), or map an
   import to retail's. Gate, push with its `Claim-Lease:` trailer and
   `link_check.py <file>` before/after in the
   message, then `claims.py release --landed <sha>`. STLport, string and
   `The*` names have one owner each (`next --family F`).
   Never reorder `functions.csv` rows for COMDAT selection.
2. `python3 tools/next_work.py` is the byte-matching default and explains its
   tiers. Its `finish` tier serves a banked attempt scoring 0.90+: start from
   that stash, even after a later `blocked`.
3. Most remaining work is anonymous `?d_` bodies; the brief's evidence pack
   is the lead. A proven identity gets its real name, evidence cited. An
   unproven one gets an opaque name that keeps the address
   (`RvaXXXXXXXX::method`, `?dup_XXXXXXXX`). Never ship a plausible
   guessed name: no gate can see it. `docs/carving.md` and
   `tools/carve_unclaimed.py` serve bodies found by boundary evidence.
4. Named `__emit` lifts are dumps too; `python3 tools/lift_lane.py` lists them.
   Names are often wrong; follow the brief's EXTENT and IDENTITY CHECK
   lines. Write the real body in the TU its `// readable body of` comment
   names, land it with `add_match --replace-existing` at the proven extent,
   delete the naked function.
5. When `next_work.py` is dry, `python3 tools/list_naked_candidates.py game`
   serves `game/gen_asm/` dumps with proven boundaries.
6. Replacing generator-written C++ scores +0; take it last. Only
   `gen-tgrid`/`gen-shim` rows have source to write.
7. **EA renames.** `python3 tools/ea_queue.py next` serves one rename to EA's
   own name and every file it touches.
8. **Names.** `python3 tools/name_lane.py next --model <your model>` serves one
   file's placeholder names. A name lands only when another vendor's model
   proposes it too; never rename placeholders by hand.

`tools/eligibility.py` alone decides whether a body is open work; never
re-derive it.

**Claim a body first:** `python3 tools/claims.py claim 0xRVA` (if held, take
another; claims expire after 4 h). After pushing, `claims.py release --landed`
frees what landed; `release 0xRVA` frees a banked, blocked or abandoned body.

**Before writing a body**, run `python3 tools/callees.py <rva> <size>` and use
the callee names it prints. A link failure against a real retail body usually
means a callee is named wrong, not a missing pin; never pin on a seat's say-so.
For a callee with no signature it prints `inferred ABI:`; declare it that way
before blaming your body.

**Small dependency repairs travel with the body.** If the scoped gate fails only
on an unresolved callee the body really calls, prove that callee's identity and
ABI independently, add one pin, run `tools/pin_consistency.py --check` and
rerun the gate, all in the same commit; use an address-derived name if its
meaning is unproven. Switch bodies when the evidence is ambiguous or the repair
spreads.

Finish or revert each body before the next. After several failed shapes or
about 30 minutes without byte progress take a fresh candidate; never leave a non-matching
reconstruction in `game/`.

## Work the file

`next_work.py` lists the other queued bodies in the same file; work them
together, since siblings share layout, offsets and callee pins. A shared header
edit costs a full gate: edit every dependent body and pay once.

## Convert, verify, commit, push

1. Make the smallest source and ledger change for one function. Sub-100-byte
   recoveries following one established pattern may share a commit; verify
   each function and its identity separately.
2. `./build.sh <file-or-symbol>`. Poll any returned process or session ID;
   never launch a duplicate build.
3. Stage explicit paths only (never `git add .`); check every new ledger source
   is tracked.
4. Commit normally; never bypass hooks (`--no-verify`). A commit that stages a
   header or shim runs the full gate (40-60 minutes): poll it; never relaunch it
   or pipe it through anything that hides its exit code.
   Baselines may only shrink; never add a line to one to go green.
5. `git pull --rebase origin master`, `git push`, then pull again; on rejection,
   rebase, recheck the ledger, retry.
6. `python3 tools/progress.py origin/master` shows what your session added.

Never bare `git stash pop` (worktrees share one stash); park work in a patch
or temp branch.

## Verdicts and near misses

Convert to clean C++. Use MASM or inline asm only for a proven codegen blocker
(compiler machinery, x87 shape, SEH). A `__declspec(naked)`/`__emit` lift is
not a conversion, and the hooks refuse it. Ghidra boundaries, xrefs and vtables
are identity evidence; decompiled C is not byte-match proof.

Record each session's outcome with
`python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence>`, never
by editing `re_attempts.log`: cite the real boundary, `t=<minutes>`, `model=`
and, for a `partial` or long `blocked`, `blocker=<family>` (`tools/blockers.py`).
Pass `--model` to `add_match.py` (fleet workers: `BFME_MODEL`).

Bank a near miss for the next agent:
`partial '<what is wrong>' --stash <your .cpp> --score <0..1>`; with no body,
record `blocked`. For 0.9+, run `tools/probe.py` and read
`docs/shape_levers.md` first.

## File placement

- The game baseline is `inputs/baselines/bfme1/retail-1.03-unpacked` (since
  2026-09-27; older verdicts blaming the baseline predate it); its
  `no_ground_truth` addresses are retired. Mods build from the workshop exe.
- Game source lives under `game/` at its official BFME path, MASM dumps in
  `game/masm_dumps/`, and scratch in untracked `build/`. Banked attempts
  (`targets/game/reverse/attempts/`) are evidence, never progress.
- Progress is `matched` rows in `targets/game/reverse/functions.csv` backed by
  real source and byte verification.
- Prefer TU-scoped shims to editing a shared header, but never redeclare a type
  a header already covers: `#include` it. `tools/adopt_header.py --fix-staged`
  does the swap; see `docs/header_adoption.md`.
- Never load `functions.csv`, `ghidra_functions.csv` or `exports.csv` whole; use
  `rg` or narrow filters.
- Preserve unrelated dirty-tree work; revert only your own attempt. No fallback
  paths: they hide mismatches.

## Names and identity

- A green byte-match says nothing about a name: a wrong name compiles to the
  same bytes. A matched caller naming the symbol is the strongest evidence.
- Ask before you invent a member, type or file name:
  `tools/name_oracle.py --class <C> --offset <N>`, and `docs/naming_evidence.md`
  for the rules. An address-derived name is honest; drop the address only for a
  name the evidence supports.
- `symbols.csv` pins are candidates: the resolver keeps the first address that
  reproduces retail, so a wrong pin still matches. Run
  `tools/pin_consistency.py --symbol <name>` before pinning and `--check` after.
  A `pinharvest` row proposes a name and proves nothing. A pin at an address
  that is only called through (an import thunk, a jump stub) needs a
  `route=<target>` note.
- Retail was linked without identical-COMDAT folding, so each body has exactly
  one identity. A second real name on an address is an over-claim to retire;
  `python3 tools/one_identity.py` shows the evidence.
- `?j_XXXXXXXX@@YAXXZ` is a 5-byte ILT thunk claimed by address;
  `?dup_XXXXXXXX@@YAXXZ` is a real body whose identity is unknown or disputed.
  Re-home a mis-anchored row to whichever fits its size. Never infer a
  funclet's `parent=` from adjacency.
- Read shipped `GlobalData` values with `tools/ini_value.py <Key>` before
  quoting them: `ini.big` and `_patch222.big` override compiled defaults.

## Generated and vendored claims

`gen-*` rows (`game/gen_small/`, `game/gen_asm/`) are byte-true placeholders,
not progress, and no generator remains to rebuild them. Recover the identity in
clean C++ at the proper `game/` path and repoint the row with
`tools/add_match.py <real-name> <rva> <size> <source> --replace-rva <rva>`
(`--replace-existing` when the name is unchanged). Never edit files under
`game/gen_asm/` or `game/gen_small/`: a hand edit there is permanent and
unchecked. After landing a batch, check your own rows: one body per address.

`vendored=<lib>-<ver>` rows carry the upstream's real identities, and the header
comment names the exact release. Library sources live at their official BFME
paths; pristine C TUs compile against `inputs/reference/shims/gamespy/`, never a
real Platform SDK.
