# Placement: getting sources into the directory their class lives in

## The problem, in numbers

| | this tree | the original (ZH reference) |
|---|---|---|
| `.cpp` under `game/` | **14,841** | 1,421 |
| `.h` under `game/` | **533** | 1,471 |
| median functions per `.cpp` | **1** (76% hold exactly one) | — |
| files directly in `game/GameEngine/Source/Common/` | **6,892** | — |

The conversion lane writes one new TU per recovered function, wherever it happens
to be standing, which is usually the flat root of `Common/`. AI state machines,
W3D drawable modules and script-engine bodies all end up there. Nothing inside
those files — no rename, no comment — makes the tree navigable while that is true.

`tools/readability_metric.py` measures it as `Local` (functions sharing a file,
26) and `SSoT` (types resolved through a header, 20). Both have been falling all
month while `Body` rises: the tree is getting larger at constant legibility.

## Two lanes, and only one of them works

**MERGING** fragments into one TU per class is the obvious answer and is mostly
blocked. Measured over every (directory, owning class) group with two or more
files -- not just the ones carrying a `readable body of ...: <dest>` marker, which
is how this was first counted and is why an earlier version of this document said
the lane reached nine files:

| | groups | files |
|---|---|---|
| groups of 2+ files owned by one class | 961 | — |
| blocked: donors disagree on their `// cl:` line | 463 | — |
| blocked: two donors declare the SAME type | 235 | — |
| blocked: holds a `__declspec(naked)`/`__emit` donor | 232 | — |
| **mergeable** | **13** | **26** |

**All 13 were then tried, and all 13 failed to compile.** The lane's real reach
is ZERO; do not plan around it. `merge_cluster --list --ready` reports 52 marker
clusters and every one has donors that disagree on their flags.

The number in this document has been wrong twice, each time because the check was
weaker than the compiler. It said 261 groups when it tested only the `// cl:`
line and naked donors; 13 once it also tested whether two donors declare the same
type; zero once the groups were actually built. The last blocker is the one a
static check cannot see: a donor's shim collides with a type the DESTINATION's
includes already define. `RankInfo.cpp` includes ZH's `RankInfo.h`, which defines
`RankInfo` and `RankInfoStore`; `RankInfoParse.cpp` declares its own. Each
compiles alone, and concatenated they give `error C2011: type redefinition`.

Treat `tools/mergeable_groups.py` as an upper bound and the compiler as the
oracle. Adopting headers (`docs/header_adoption.md`) is the prerequisite for this
lane, not a parallel one.

The three reasons a merge is refused, each paid for once:

* Folding a byte spray into a readable file is the lift AGENTS.md bans -- it
  byte-matches by construction, scores +0, and destroys the destination's
  readable statement of that function.
* The `// cl:` line is the TU's entire compile environment, flags *and* include
  search path. `BezierSegmentEvaluation.cpp` builds against
  `game/GameEngine/Include` and `BezierSegment.cpp` against the ZH reference
  tree; folding the first into the second resolved different headers and gave
  `FAIL 1/68` from byte-identical source text.
* Two TUs that each declare their own shim for the same type cannot simply be
  concatenated. `docs/header_adoption.md` is the prerequisite, not a parallel
  lane.

**MOVING** has none of those constraints and is the lane that works:

* the `// cl:` line travels with the file, so the compile environment is unchanged
* 14,615 of 14,734 sources (99%) carry no relative include, so nothing resolves
  differently afterwards
* nothing has to be reconciled against a sibling

Measured over 103 landed moves, a move is byte-neutral.

## The tools

    python3 tools/placement_queue.py --by-dir     # rebuild targets/game/reverse/placement_queue.tsv
    python3 tools/placement_batch.py --count 80   # move + byte-gate, land nothing
    python3 tools/placement_batch.py --count 80 --commit

`placement_queue.py` queues a file only when it declares exactly ONE owning class
and the evidence names a different home for it. Three sources, strongest first:

1. **ZH has a `.cpp` of that class's name** — its directory.
2. **A ZH header declares that class** — the mirrored `Source/` directory, *when
   that directory exists in ZH*. Worth files the first rule cannot see: ZH
   declares 1,264 classes across its headers and most never got a file of their
   own name.
3. **The class already keeps two or more bodies in one other directory** — that
   directory. One sibling elsewhere is as likely to be the misplaced file, and
   two alternative directories are an ambiguity rather than a plurality vote.
   MSVC scalar/vector deleting destructors corroborate a conflicting home but do
   not nominate one: ignoring them hid an exact destructor family split across
   two directories and let a stale identity-corrected TU nominate a third.

The queue also excludes `targets/game/reverse/placement_blocked.tsv`: those sources already
failed the placement gate at the proposed path and remain blocked until the
underlying source-claim, compile, or byte-match defect is repaired and its row is
removed. Serving them again only repeats a known failure that `placement_batch.py`
would refuse anyway.

And three destinations are always refused: the flat `Common/` root (a class whose
bodies mostly sit in the dumping ground is not evidence that the dumping ground is
where they belong), a directory that does not exist, and **any ancestor of where
the file already is** — a file inside the destination subtree is already home.

The regenerated `targets/game/reverse/placement_queue.tsv` and the tool's printed skip summary
are the authoritative current state; counts become stale as other workers land
moves and evidence guards. An empty queue means this evidence-backed lane is
exhausted, not broken. Sources skipped because no evidence names a destination —
primarily BFME-specific classes and free functions with no ZH twin — remain
blocked on identification rather than on placement tooling.

## Weak evidence must never outrank strong

The queue's worst defect was silent, and the byte gate could never have caught it:
a move that is byte-neutral is still a move to the wrong place.

`AssaultTransportAIUpdate.cpp` sits in `GameLogic/Object/Update/AIUpdate/` —
exactly where ZH has it. The queue wanted it in `GameLogic/AI`. Rule 1 looked up
ZH, found *this* directory, saw `candidate == here`, and **fell through** to rule
3, which answered on two siblings that were themselves misplaced. ZH saying "this
file is already home" has to end the search, not be skipped as a non-answer.

Two more of the same family:

* An inline method emitted from an included header does not make that class the
  TU's owner. `PopupHostGame.cpp` emitted `GameInfo::setUseStats`, but both ZH
  trees keep the exact source under the GUI menus tree. An exact ZH source path
  now stops the move before an inferred owner can pull the file elsewhere.
* Sibling counts cannot split a module from its colocated `<Class>ModuleData`
  partner. Three DominateEnemy sources were repeatedly volleyed between
  `Object/SpecialPower` and `Common/Thing`; the votes in `Common/Thing` were a
  consequence of those moves, while the independently recovered module-data
  constructor has its sole ledger home in `Object/SpecialPower` and positively
  anchors the family there.
* A destination that is an **ancestor** of the current directory was accepted, so
  324 files were bound to leave `GameLogic/AI` for `GameLogic`. ZH's header tree
  is coarser than our source tree in places; answering with the parent throws away
  a subdirectory that already names the file. The same applies when the file is
  elsewhere but two or more bodies already establish the class in a descendant:
  `ControlBar.h` only proves `GameClient`, while CommandSet's bodies establish
  `GameClient/GUI/ControlBar`. The queue refines a coarse mirror to that deeper
  directory only when it is the class's sole established descendant; multiple
  descendants are ambiguous even when one has more bodies, so the queue refuses
  to rank them.
* `Include/<Area>/<Sub>` was mirrored onto `Source/<Area>/<Sub>` without checking
  the mirror **exists in ZH**. It does not for `Module`: ZH keeps those bodies
  under `Object/Update` and `Object/Behavior`. 606 files were bound for an
  invented directory and 195 of them were leaving the right one to get there.

The 103 moves that had already landed were audited against ZH afterwards: none of
them went against a ZH location.

## State

181 files moved and landed. The `0x002978A0` row that was blocking every `game/`
commit is settled, and `identity_guard` is green.

If `identity_guard` fails again with `multi_name.different: 0 -> N`, read its own
verdict before believing it: it compares THIS TREE'S compiled objects, prints
`-> DIRTY`, and names the source whose object no longer matches. Rebuild that one
source and re-run. Compiling a few hundred TUs is enough to surface it. It is an
artifact, not a ledger defect, and it must never be settled by editing the ledger.

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

**`git add -A game/` is `git add .` by another door.** It swept a file outside the
batch into a commit and the hook rejected the whole thing. Stage the batch's own
paths only.

**`git mv` and the ledger repoint are two halves of one change.** Committing one
without the other leaves `targets/game/reverse/functions.csv` pointing at an untracked path;
`check_csv` catches it, but only if you run it.

**`git mv` already stages both halves of the rename.** Naming the old paths again
— `git add -u <old>` — aborts the whole command with exit 128 as soon as one of
them is gone from the working tree, which is all of them. A batch moved 80 files,
byte-verified them, and threw the result away on that line.

**The ledger is bytes.** `targets/game/reverse/functions.csv` carries mixed line terminators
and a `csv` round-trip flattens them, which `check_csv` rejects. Repoint the
source column by byte replacement, anchored on the surrounding commas so a path
that is a prefix of another cannot be hit.

**A red source cannot be fixed by moving it.** If the hook rejects a file at
every path, repair its underlying source-claim, compile, or byte-match defect
before serving it again. The blocker register prevents the placement lane from
repeating the same failed move in the meantime.

## What this lane cannot fix

At ~80 files an hour the queue is roughly 17 hours, and `Common/` still ends
around 5,500. Moving files makes the tree *browsable* — it does not reduce the
file count, and it does not touch the header problem, which is the deeper reason
nothing is findable: 533 headers against 1,471 means types have no home, so every
TU redeclares them. `AsciiString` is declared TU-locally **1,375** times, `Object`
1,317. That is a separate campaign with a different cost model, because any staged
`.h` forces the full gate.


## Four more evidence sources, measured and rejected

The 8,909 files skipped for "no destination the evidence supports" are the bulk of
the flat `Common/` directory, so it is worth knowing what has already been tried.
All four were measured, not argued:

| idea | reach | spot checks | verdict |
|---|---|---|---|
| classify by the file's own `#include` set | 67 files | **3 of 5 WRONG** | no |
| classify by the classes the file REFERENCES | **1,275 files (30.7%)** | **0 of 10 correct** | no |
| the `/I` paths on its `// cl:` line | 0 files | — | no |
| ZH's directory for the class's BASE class | 0 files | — | no |

**The second one is the cautionary tale.** It reaches nearly a third of the
directory, which is by far the best reach anything has ever shown here, and it is
wrong every single time. A file that defines its own class still references
classes from whichever area dominates the tree, so
`AnimationSoundClientBehaviorGlobal_unregister.cpp` -- a GameClient file by its
name and its headers -- infers GameLogic. Implementing it would have moved 1,275
files to the wrong place, and **every one of those moves would have been
byte-neutral**, so no gate in this repo could have caught it. Reach is not
evidence.

The other two reach zero for structural reasons: most of these files carry no `/I`
paths at all or several areas' worth, and most are constructor/destructor thunks
with no base class written in the source -- the hierarchy lives in the ledger and
the binary, not the text.

**Conclusion: the lane is evidence-limited, not tooling-limited.** The 8,909 are
BFME-specific classes with no ZH twin, free functions, and synthetic shims
(`Rva*`, `Gen_*`, `Bfme*`). They are blocked on identification, which is the
conversion lane's work. Adopting headers (`docs/header_adoption.md`) is the
prerequisite that would make them tractable, not a smarter placement heuristic.
