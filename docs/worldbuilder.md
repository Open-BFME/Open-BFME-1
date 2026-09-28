# WorldBuilder recovery

WorldBuilder is a separate target; the ordinary game commands still operate
on BFME1. Start with `python3 tools/worldbuilder.py next`. Staff the lane with
two editor workers on distinct files and one dependency/tooling lane, whose
next target is support for independently witnessed unexported data and
callees.

## Target and source ownership

- `inputs/baselines/bfme1/workshop-vanilla-1.03/manifest.json` records the
  WorldBuilder image and SHA-256; the verifier checks it before comparing.
- Ledger: `targets/worldbuilder/reverse/functions.csv`; runs go to the
  ignored `build/worldbuilder/`.
- Editor sources go in `worldbuilder/`. An independently verified engine
  implementation may reuse its `game/` source; a divergent one goes at the
  matching `worldbuilder/` path.
- A game claim never implies a WorldBuilder claim. Editing a source both
  targets claim runs both verifications.
- Profiles `engine-size` and `editor-size`: MSVC 7.1 (13.10.3077) under Wine,
  size-optimized; editor sources use the real MFC headers and DLL ABI. They
  are calibrated, not proven editor-wide: some engine functions keep
  assertion paths the game lacks.

## Recover and verify

```sh
python3 tools/worldbuilder.py check
python3 tools/worldbuilder.py next
python3 tools/worldbuilder.py show CWorldBuilderView::OnShowGrid
python3 tools/worldbuilder.py verify
python3 tools/worldbuilder.py progress --ref origin/master
```

Work the source family: `next` prefers untouched candidates and lists every
sibling in the file; an explicit selection can retry a banked or blocked
candidate. Feed the packet's values to `probe` or `land`:

```sh
python3 tools/worldbuilder.py probe \
  --name '<decorated name>' --rva '<RVA>' --size '<bytes>' \
  --source '<source.cpp>' --profile editor-size --evidence '<packet evidence>'
```

`land` adds `--model` and appends only after the whole source family
byte-compares in a fresh run directory.

- Each relocation needs an independent named export, import, verified target
  function or witnessed literal data. An unknown reference stops
  verification; there is no masked-relocation success mode.
- Identity comes from named exports, resource labels, class records or
  independently decoded MFC runtime-class/message-map chains, never a guessed
  name or Ghidra label. Source paths and assertion strings are leads, never a
  function boundary.
- Count each accepted byte range once; WorldBuilder's linker/ICF behavior is
  unknown.
- Naked bodies and emitted-byte lifts are rejected.

Bank an incomplete attempt outside production roots:

```sh
python3 tools/worldbuilder.py record '<candidate ID>' partial \
  --model '<model>' --evidence '<observations; t=minutes>' \
  --blocker '<specific unresolved reference or byte difference>' \
  --stash build/worldbuilder/attempt.cpp --score 0.95
```

`partial` needs both `--stash` and `--score`; with no useful body, record
`blocked` without them. Banked sources are evidence, not coverage. Restore the
production source to its verified state before publishing.

## References and inventory

- `python3 tools/worldbuilder_inventory.py --check` regenerates the compact
  PE/MFC evidence and checks it against the tracked inventory.
- Ghidra is optional. `python3 tools/worldbuilder_analysis.py --analyze
  --ghidra <installation>` writes ranges, call sites and string references to
  the ignored `build/worldbuilder-inventory/`; the tracked
  `targets/worldbuilder/reverse/analysis.json` audits it. Ghidra can miss
  metadata-proven starts, and its owned-address counts are never body sizes.
- The donor index pins exact BFME1 and BFME2 revisions and hashes. Search
  offline; `--fetch` pulls a small selected source into the ignored cache
  (`--show` also prints it). A same-name donor is a lead, not a byte match.

  ```sh
  python3 tools/worldbuilder_donors.py Region3D --reference bfme2
  python3 tools/worldbuilder_donors.py '<decorated name>' --exact --reference bfme2 --show
  ```

- MFC ordinal evidence and acquisition commands:
  [`targets/worldbuilder/dependencies/README.md`](../targets/worldbuilder/dependencies/README.md).
  The small verified map suffices; large downloads are explicit. Unproven
  ordinals stay unsupported.

## Bounded workers and publication

`worldbuilder_fleet.py` claims whole editor source files. Workers edit only
WorldBuilder-exclusive sources; coordinate shared engine work manually. `run`
gives the worker its binary binding and packet path, records output and exit
status, and releases the file when it stops:

```sh
python3 tools/worldbuilder_fleet.py run '<candidate ID>' --run-id '<unique ID>' -- <worker command>
python3 tools/worldbuilder_fleet.py claims
```

- Outside a child process, use `claim '<candidate ID>'` and `release '<run
  ID>' --reason '<why>'`; hold the lease until the agent stops writing.
- A killed coordinator may leave its lease on purpose: inspect its run and
  stop the worker, then release from the owning worktree.
- Claims live in Git's common directory, shared by a clone's worktrees.
  Independent clones need one dispatch coordinator.
- `run` needs POSIX process groups; Windows workers use externally
  supervised `claim`/`release`.
- Workers do not stage or publish; one coordinator commits verified results
  with explicit paths.

To publish: run `verify` and `progress`, commit normally, rebase on
`origin/master`, push. Never bypass a hook or raise a baseline to pass one.
