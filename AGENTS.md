# Contributing

Many agents push to `origin/master` all day. Keep each change small, verified
and easy to rebase. `docs/matching.md` covers byte matching and
`docs/structural.md` manual reverse engineering.

## Setup

- `git pull --rebase origin master`. Once per host:
  `python3 -m pip install -r tools/requirements.txt` (the hooks need `pefile`
  and `capstone`).
- On Windows use `.\build.cmd` (same arguments as `./build.sh`) and
  `tools\fleet\launch_fleet.cmd`; run other scripts as `bash tools/<name>.sh`, never
  directly from PowerShell or cmd. Python is `py -3` in PowerShell.
- `python3 tools/check_csv.py` must pass before other work.

## Work selection

An explicit request or assigned lane overrides the queue. WorldBuilder work
uses `python3 tools/worldbuilder.py next` and `docs/worldbuilder.md`; its
ledger and verification are separate from the game's.

1. `python3 tools/next_work.py` is the default work, and it explains its own
   tiers. The first, `finish`, serves a body whose banked attempt already
   scores 0.90+: start from that stash, and do not rewrite it because a later
   session recorded `blocked`.
2. Most remaining work is anonymous `?d_` bodies, and the brief's evidence
   pack is the lead. A proven identity gets its real name with
   the evidence cited. An unproven one gets an opaque name that keeps the
   address (`RvaXXXXXXXX::method`, `?dup_XXXXXXXX`). Never ship a plausible
   guessed name: no gate can see it. `docs/carving.md` and
   `tools/carve_unclaimed.py` serve bodies found by boundary evidence.
3. Named `__emit` lifts are dumps too; `python3 tools/lift_lane.py` lists them.
   Their names are often wrong, so follow the brief's EXTENT and IDENTITY CHECK
   lines. Convert one by writing the real body in the TU its
   `// readable body of` comment names, landing it with
   `add_match --replace-existing` at the proven extent, and deleting the naked
   function.
4. When `next_work.py` is dry, `python3 tools/list_naked_candidates.py game`
   serves byte-true dumps from `game/gen_asm/` whose boundaries are proven.
5. Replacing generator-written C++ with hand-written C++ is deferred: it scores
   +0. Take it only when the lanes above are dry, and say so.
6. **Linked build.** Nothing has linked the tree yet.
   `python3 tools/link_debt.py --report` lists literal image addresses: replace
   each with a named extern (`dir32_addresses.csv`, else `g_XXXXXXXX`) without
   changing a byte. `tools/link_census.py`, after a full `BUILD_POOL=12
   ./build.sh`, lists the rest.

Whether a body is open work is decided in one place, `tools/eligibility.py`;
never re-derive it in a new tool.

**Claim a body before you start it:** `python3 tools/claims.py claim 0xRVA`. If
someone else holds it, take another. Claims expire after 4 h. `add_match`
releases yours when you land; run `python3 tools/claims.py release 0xRVA` if you
bank, block or abandon the body.

**Before writing a body**, run `python3 tools/callees.py <rva> <size>` and use
the callee names it prints. A link failure against a real retail body almost
always means a callee is named wrong, not that it needs a pin; never add a pin
on a seat's say-so. For a callee with no signature it prints `inferred ABI:`;
declare the callee that way before blaming your body.

**Small dependency repairs travel with the body.** If the scoped gate fails only
on an unresolved callee the body really calls, prove that callee's identity and
ABI independently, add one pin, run `tools/pin_consistency.py --check` and
rerun the gate, all in the same commit; use an address-derived name if its
meaning is unproven. Switch bodies when the evidence is ambiguous or the repair
spreads.

Finish or revert each body before the next. After several failed shapes or
about 30 minutes without byte progress, take a fresh candidate; never leave a
non-matching reconstruction in `game/`.

## Work the file

`next_work.py` lists the other queued bodies in the same source file. That file
is your unit of work: siblings share the layout, offsets and callee pins the
first body needed. A shared header edit costs a full gate, so edit every
dependent body and pay once.

## Convert, verify, commit, push

1. Make the smallest source and ledger change for one function. Several
   sub-100-byte recoveries that follow one established pattern may share a
   commit; verify each function and its identity separately.
2. `./build.sh <file-or-symbol>`. If a command returns a process or session ID,
   poll it; never launch a duplicate build.
3. Stage explicit paths only (`git add <paths>`, never `git add .`), and check
   that every new ledger source is tracked.
4. Commit normally; never bypass hooks or use `--no-verify`. A commit that
   stages a header or shim runs the full gate (40-60 minutes): poll it, never
   relaunch it, and never pipe it through anything that hides its exit code.
   Baselines may only shrink; never add a line to one to go green.
5. `git pull --rebase origin master`, `git push`, then pull again. On rejection,
   rebase, recheck the ledger and retry.
6. Before pushing, `python3 tools/progress.py origin/master` shows what your
   session added.

Never `git stash pop` bare: worktrees share one stash stack. Park work in a
patch file or a temp branch.

## Verdicts and near misses

Convert to clean C++. Use MASM or inline asm only for a proven codegen blocker
(compiler machinery, x87 shape, SEH). A `__declspec(naked)`/`__emit` lift is
not a conversion, and the hooks refuse it. Ghidra boundaries, xrefs and vtables
are identity evidence; decompiled C is not byte-match proof.

Record each session's outcome with
`python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence>`, never
by editing `re_attempts.log`: cite the real boundary, `t=<minutes>`, `model=`
and, for a `partial` or long `blocked`, `blocker=<family>` (`tools/blockers.py`).
Pass `--model` to `add_match.py`; fleet workers get it from `BFME_MODEL`.

Close but not exact? Bank it:
`partial '<what is wrong>' --stash <your .cpp> --score <0..1>`, so the next
agent starts from your body. No body, no `partial`: record `blocked`. For a
0.9+ near miss, run `tools/probe.py` and check `docs/shape_levers.md` first.

## File placement

- The game baseline is `inputs/baselines/bfme1/retail-1.03-unpacked` (since
  2026-09-27; older verdicts that blame the baseline predate it). Its
  `no_ground_truth` addresses are retired. Mods still build from the workshop
  exe.
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
- Before quoting a `GlobalData` constant as behaviour, read the shipped value
  with `tools/ini_value.py <Key>`: `ini.big` and `_patch222.big` override many
  compiled defaults.

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
