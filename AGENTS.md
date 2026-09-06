# Contributing

Several agents push to `origin/master` continuously. Keep each change small,
verified and easy to rebase. `docs/matching.md` covers byte matching,
`docs/structural.md` manual RE. Prose trimmed from these docs lives in git
history, one `git show` away.

## Work selection

An explicit request or assigned lane overrides the queue:

1. `git pull --rebase origin master`
2. `python3 tools/check_csv.py` — repair ledger errors before other work
3. `python3 tools/list_naked_candidates.py Code` serves a byte-true dump from
   `Code/gen_asm/`, boundary already proven. **Converting dumps to real C++ is
   the default work.**
4. `python3 tools/next_work.py` for identity/structural work; it explains its
   own tiers.

A tier reporting zero candidates is exhausted, not broken. Regenerate with
`tools/drift_classify.py`, `tools/anchor_unclaimed.py`, `./build.sh`.

Finish or revert each body before the next.

## Work the file, not the row

`next_work.py` lists every other queued candidate in the same source file.
**That file is your unit of work** — drain it first. Measured land rate: 19.5%
solo, 46.5% with ten or more siblings landed together, because the layout,
offsets and callee pins from the first body are what the next one needs. A
shared header edit costs a full gate: edit every dependent body, pay once.

## Convert, verify, commit, push — per body

1. Make the smallest source and ledger change for one function.
2. `./build.sh <file-or-symbol>`. If a command returns a process or session ID,
   poll it; never launch a duplicate build.
3. Stage explicit paths only: `git add <specific-paths>`, never `git add .`.
   Check every new ledger source is tracked.
3b. **A green byte-match says nothing about the NAME.** A pin on the wrong
   function still compiles to retail's bytes, so no other check can see that
   class of defect. Four detectors find it, and the commit hook now runs the two
   fast ones through `tools/identity_guard.py`, baselined in
   `reverse/identity_baseline.txt`; the slow one runs in the full gate. Those
   counts only go DOWN — raising one to go green is the ORPHAN_BASELINE move, and
   lowering one belongs in the same commit as the fix. Run them by hand when a
   row's identity is in doubt: `tools/multi_name.py` (one address, several names),
   `tools/null_reloc.py` (our vftable store where retail wrote a literal zero;
   ~70s), `tools/size_outlier.py` (a body far smaller than its family), and
   `tools/find_emitter.py` (which TU could own an orphaned row). None proves
   identity on its own — **a matched caller naming the symbol outranks all four.**

3a. **Never `git stash pop` bare, and prefer not to stash at all.** Separate
   worktrees isolate the working tree and the index; they do NOT isolate the
   stash stack, which is one shared `refs/stash` for the whole repository. A
   bare pop applied another lane's stash — one explicitly labelled HOLD — into
   the wrong tree and dropped its ref. Read `git stash list` and pop an explicit
   `stash@{N}`; better, park work in a patch file or a temp branch, which no
   other lane can consume. Same class as `git add .`: a bare command silently
   taking something that is not yours.
4. Commit normally. **Never bypass hooks.**
5. `git pull --rebase origin master`, `git push`, then pull --rebase again. On
   rejection: rebase, recheck the ledger, retry, final pull.

Header, vendored-reference and shared-shim edits — and a resolved merge —
trigger the full gate in the hook; poll it, don't relaunch, and never filter a
gate through a pipeline that hides its exit code.

Before pushing, `python3 tools/progress.py origin/master` prints what your
session added. `+0.00 pp` is the common outcome — do not stop there; take
another body from the file you were served, and if it is exhausted say so with
the figure and reason.

## Anti-lift policy

Clean C++ is preferred; MASM or inline asm only for a proven codegen blocker
(compiler machinery, x87 shape, SEH). Lifting a dump into a
`__declspec(naked)`/`__emit` .cpp is **not** a conversion: it byte-matches by
construction, scores +0, and deletes the body the next converter needed. The
naked body must be **gone**, replaced by real C++. `tools/conversion_gate.py`
enforces this in both hooks, and the push hook scans your whole outgoing range
— a blocked push may name a historical lift, not yours. Never `--no-verify`.

Ghidra boundaries, xrefs and vtables are identity evidence; decompiled C is
not byte-match proof. After several failed shapes or ~30 minutes without byte
progress take a fresh candidate, never leaving a nonmatching reconstruction in
`Code/`. Record the verdict:
`python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence>`
(never hand-edit `reverse/re_attempts.log`); cite the real boundary and
include `t=<minutes>` and your model.

**Close, not exact? Bank the body.**
`partial '<what is wrong>' --stash <your .cpp> --score <0..1>` keeps the
candidate servable and starts the next agent from your body, not cold. Both
flags are required: over 95 rows, a `partial` describing the near miss without
banking it landed 5.1% against 7.5% for silence. No body, no `partial` —
record `blocked`.

## Placement and integrity

- Game source under `Code/`; MASM dumps in `Code/masm_dumps/`; scratch
  untracked under `build/`. Banked attempts (`reverse/attempts/<rva>.cpp`) are
  evidence, never progress: nothing compiles them, `add_match` deletes one on
  landing, `check_csv` flags leftovers.
- Prefer TU-scoped shims over shared-header edits.
- Progress = `matched` `reverse/functions.csv` rows backed by real source and
  byte verification. Markers and prose are not.
- **Landing a `reverse/symbols.csv` pin?** It is an ADDITIVE candidate list:
  the resolver keeps the first pinned address that reproduces retail, so a pin
  naming the *wrong* function still byte-matches and a green gate proves
  nothing about it. Run `tools/pin_consistency.py --symbol <name>` before you
  pin and `--check` after. `reverse/pin_consistency_baseline.csv` is the
  known-bad backlog and may only shrink — never add a line to get green. See
  `docs/lessons.md`, "A `pinharvest` row is a candidate, not an address".
  Pinning an address calls ENCODE but the function does not LIVE at (an import
  thunk, a jump stub) needs a `route=<target>` note: `--routes` re-derives every
  one from the retail image and refuses anything else, so it exempts that row
  from one-name-one-body without exempting an identity.
  Near-miss (0.9+) bodies: run `tools/probe.py` (compile + retail diff + symptom/lever) and check `docs/shape_levers.md` before banking.
- **Quoting a `GlobalData` constant as behaviour?** The compiled `imm32` is not
  what the game runs on. 378 GlobalData fields are INI-parseable, and a value
  can be changed by `ini.big` OR by `_patch222.big` on top of it, so read the
  shipped value with `tools/ini_value.py <Key>` first. Six of the nine
  `Network*` fields differ from their compiled defaults, the largest by 120x,
  and two wrong numbers have already been published from the disassembly. The
  compiled constant identifies the field; the archive says what it does.
- No fallback paths; they conceal mismatches.
- Never load `reverse/functions.csv`, `ghidra_functions.csv` or `exports.csv`
  wholesale; use `rg` or narrow filters.
- Preserve unrelated dirty-tree work; revert only your own attempt.

## Generated claims

`gen-*` rows (`Code/gen_small/`, `Code/gen_asm/`) are byte-true placeholders,
not progress. Recovering a real identity means writing clean C++ at its proper
`Code/` path and repointing the row:
`tools/add_match.py <real-name> <rva> <size> <source> --replace-rva <rva>` for
`gen_asm` dumps (`--replace-existing` when the name is unchanged). `check_csv`
rejects a gen-* row sharing a range with a real-name row; the placeholder
yields.

**Never edit a file under `Code/gen_asm/`**: repoint the row and leave the
orphaned `PROC`, which keeps converters conflict-free there.
`Code/gen_small/uw_gen_*.cpp` is owned end to end by `tools/gen_uw.py land` —
never hand-edit it, and never infer a funclet's `parent=` from adjacency; a
guessed parent is invented identity.

After landing a batch, sweep your own rows: one body per address. A duplicate
range among them is an over-claim, not an ICF alias.

## Vendored third-party claims

`vendored=<lib>-<ver>` rows carry the upstream's real identities, never `gen-`
prefixes; the header comment names the exact release. Library sources live at
their official BFME paths, and pristine C TUs compile against
`reference/shims/gamespy/`, never a real Platform SDK.
