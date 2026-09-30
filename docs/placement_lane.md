# Placement: getting sources into the directory their class lives in

The conversion lane writes one TU per recovered function wherever it is standing,
usually the flat root of `game/GameEngine/Source/Common/`. This lane moves each
source into its class's directory. That makes the tree browsable; it does not
reduce the file count or fix redeclared types (`docs/header_adoption.md`).

## Move, don't merge

Merging fragments into one TU per class failed: every group that passed the
static checks failed to compile. Treat
`tools/mergeable_groups.py` as an upper bound and the compiler as the oracle. A
merge is blocked when:

- a donor is a `__declspec(naked)`/`__emit` lift; folding it in is a lift, which
  the hooks refuse.
- donors disagree on their `// cl:` line. That line is the TU's whole compile
  environment, flags and include path, so the same text can resolve different
  headers.
- two donors, or a donor and the destination's includes, declare the same type
  (`error C2011`). Header adoption has to come first.

Moving avoids all three: the `// cl:` line travels with the file, almost no
source has a relative include, and a move is byte-neutral.

## The tools

    python3 tools/placement_queue.py --by-dir     # rebuild targets/game/reverse/placement_queue.tsv
    python3 tools/placement_batch.py --count 80   # move + byte-gate, land nothing
    python3 tools/placement_batch.py --count 80 --commit

`placement_batch.py` repoints the ledger, returns files that are red, and records
sources the hook refuses in `targets/game/reverse/placement_blocked.tsv`, which the
queue then skips. An empty regenerated queue means the lane is exhausted, not
broken.

## Where a file belongs

A file is queued only when the evidence names a different home. Strongest first:

1. EA's own source path for every row the file owns (`ea_evidence.csv`, routes
   `wb1`/`zh`; `targets/game/reverse/analysis/worldbuilder_evidence.md`): its
   directory. The only rule that reaches BFME-only classes, free functions and
   address-named shims.
2. The file's one owning class has a ZH `.cpp`: its directory.
3. A ZH header declares the class: the mirrored `Source/` directory, only if that
   directory exists in ZH.
4. The class keeps two or more bodies in one other directory. One sibling
   elsewhere is as likely to be misplaced; two candidates are ambiguous.

A byte-neutral move to the wrong place passes every gate, so these rules carry the
lane:

- When a rule says the file is already home (its directory or an ancestor), stop.
  Never fall through to weaker evidence.
- An exact ZH source path for the file beats an inferred owner. An inline method
  emitted from an included header does not make its class the TU's owner.
- Never move into an ancestor of the current directory, or into the flat
  `Common/` root unless EA or ZH keeps the file there. Only EA's path may create
  a directory.
- Refine a coarse ZH header mirror to a deeper directory only when that is the
  class's one established descendant. Several descendants are ambiguous.
- Sibling counts cannot split a module from its `<Class>ModuleData` partner. The
  partner's independently recovered home anchors the family.
- MSVC deleting destructors can corroborate a contested home, never nominate one.

These were measured and rejected; do not retry them. Reach is not evidence.

- The file's own `#include` set: mostly wrong.
- The classes a file references: wrong in every spot check.
- The `/I` paths on its `// cl:` line, and the ZH directory of its base class.
- Run-filled EA paths (`wb1-run`, `retail-run`): they give an inline body the TU
  that emitted it.

## Traps

- `./build.sh $MOVED` with an empty `MOVED` runs the full gate under a host-wide
  lock. Never build an empty list.
- A file red at its old path is red after the move, and the error names the new
  path. Return it; do not debug it as the move's fault. A source refused at every
  path needs its source-claim, compile or byte defect fixed first; remove its
  `placement_blocked.tsv` row only after that.
- Stage the batch's own paths only. `git add -A game/` is `git add .` by another
  door.
- `git mv` already stages both sides of a rename. `git add -u <old paths>` then
  fails with exit 128 and throws the batch away.
- Commit each `git mv` with its ledger repoint.
- `functions.csv` has mixed line endings, and a `csv` round-trip flattens them.
  Repoint the source column by byte replacement, anchored on the surrounding
  commas, so a path that prefixes another is not hit.
- If `identity_guard` fails with `multi_name.different` after many compiles, read
  its verdict: `-> DIRTY` means stale objects. Rebuild the sources it names and
  re-run. Never edit the ledger to go green.
