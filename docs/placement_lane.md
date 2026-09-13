# Placement: getting sources into the directory their class lives in

## The problem, in numbers

| | this tree | the original (ZH reference) |
|---|---|---|
| `.cpp` under `Code/` | **14,841** | 1,421 |
| `.h` under `Code/` | **533** | 1,471 |
| median functions per `.cpp` | **1** (76% hold exactly one) | — |
| files directly in `Code/GameEngine/Source/Common/` | **6,892** | — |

The conversion lane writes one new TU per recovered function, wherever it happens
to be standing, which is usually the flat root of `Common/`. AI state machines,
W3D drawable modules and script-engine bodies all end up there. Nothing inside
those files — no rename, no comment — makes the tree navigable while that is true.

`tools/readability_metric.py` measures it as `Local` (functions sharing a file,
26) and `SSoT` (types resolved through a header, 20). Both have been falling all
month while `Body` rises: the tree is getting larger at constant legibility.

## Two lanes, and only one of them works

**MERGING** fragments into one TU per class is the obvious answer and is mostly
blocked. `tools/merge_cluster.py --list --ready` prints the split:

* 146 clusters covering 704 files carry a `readable body of ...: <dest>` marker
* **95 of them (531 files) hold a `__declspec(naked)`/`__emit` donor.** Folding a
  byte spray into a readable file is the lift AGENTS.md bans — it byte-matches by
  construction, scores +0, and destroys the destination's readable statement of
  that function. Those clusters need the conversion lane first.
* Of the 51 that remain, **only 6 have donors that agree on their `// cl:` line.**
  That line is the TU's entire compile environment, flags *and* include search
  path. `BezierSegmentEvaluation.cpp` builds against `Code/GameEngine/Include`
  and `BezierSegment.cpp` against the ZH reference tree; folding the first into
  the second resolved different headers and gave `FAIL 1/68` from byte-identical
  source text. Only 19% of directories are flag-homogeneous, so this is the
  common case.

Total reach of the merge lane: **9 files.** Do not plan around it.

**MOVING** has none of those constraints and is the lane that works:

* the `// cl:` line travels with the file, so the compile environment is unchanged
* 14,615 of 14,734 sources (99%) carry no relative include, so nothing resolves
  differently afterwards
* nothing has to be reconciled against a sibling

Measured over 103 landed moves, a move is byte-neutral.

## The tools

    python3 tools/placement_queue.py --by-dir     # rebuild reverse/placement_queue.tsv
    python3 tools/placement_batch.py --count 80   # move + byte-gate, land nothing
    python3 tools/placement_batch.py --count 80 --commit

`placement_queue.py` queues a file only when it declares exactly ONE owning class
and that class demonstrably lives elsewhere — the ZH reference has a file for it,
or the class already keeps two or more bodies in another existing directory. The
destination is never invented, and never the flat `Common/` root: a class whose
bodies mostly sit in the dumping ground is not evidence that the dumping ground is
where they belong.

Current queue: **1,368 files.** 7,556 are skipped because no evidence names a
destination — those are BFME-specific classes and free functions with no ZH twin,
and they are blocked on identification, not on this lane.

## State

103 files moved and landed. `Common/` 6,965 → 6,892.

**The lane is currently blocked repo-wide.** `tools/identity_guard.py` fails on a
completely clean checkout:

    identity_guard: FAIL — a row that byte-matches now names the wrong function
        multi_name.different: 0 -> 1

`tools/multi_name.py` names it: `0x002978A0`, 105 bytes, *DIFFERENT BODIES —
cannot share an address*. Until somebody settles that row, the commit hook rejects
every change under `Code/`, including byte-neutral moves. Settle it, or establish
it is an artifact, before resuming.

## Traps this lane has already paid for

**An empty file list is the full gate.** `./build.sh $MOVED` with an empty `MOVED`
expands to `./build.sh` with no arguments, which verifies the whole tree under a
host-wide lock. A batch whose files were all returned as red did exactly that,
held the lock for twenty-one minutes, blocked every other agent, and verified a
half-moved tree whose answer meant nothing. `placement_batch.py` raises rather
than build an empty set.

**A file red at its original path is red after the move**, and the failure names
the moved path, so it reads like the move's fault. Return it, do not diagnose it.
About 1 file in 80.

**`git add -A Code/` is `git add .` by another door.** It swept a file outside the
batch into a commit and the hook rejected the whole thing. Stage the batch's own
paths only.

**`git mv` and the ledger repoint are two halves of one change.** Committing one
without the other leaves `reverse/functions.csv` pointing at an untracked path;
`check_csv` catches it, but only if you run it. And `git add -A <old-path>` fails
once the old path is gone, which will take an `&&` chain down with it and produce
a half-commit.

**The ledger is bytes.** `reverse/functions.csv` carries mixed line terminators
and a `csv` round-trip flattens them, which `check_csv` rejects. Repoint the
source column by byte replacement, anchored on the surrounding commas so a path
that is a prefix of another cannot be hit.

**Some files cannot be committed anywhere.** `GameMessage_destructor.cpp` defines
`GameMessageArgument::deleteInstance` and `AIGuardReturnState_onEnter_Bfme.cpp`
defines `AIGuardReturnState::onEnter`; neither is declared in the ledger, so the
hook rejects them wherever they sit. That predates this lane and needs a ledger
row, not a move.

## What this lane cannot fix

At ~80 files an hour the queue is roughly 17 hours, and `Common/` still ends
around 5,500. Moving files makes the tree *browsable* — it does not reduce the
file count, and it does not touch the header problem, which is the deeper reason
nothing is findable: 533 headers against 1,471 means types have no home, so every
TU redeclares them. `AsciiString` is declared TU-locally **1,375** times, `Object`
1,317. That is a separate campaign with a different cost model, because any staged
`.h` forces the full gate.
