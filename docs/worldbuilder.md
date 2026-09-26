# WorldBuilder recovery

WorldBuilder lives in this repository with its own binary, ledger, evidence,
compiler profiles and work queue. Start with `python3 tools/worldbuilder.py next`.
The ordinary game commands still operate on BFME1.

The initial three-worker pilot recovered five additional editor functions
(250 bytes) across two source files. The third file's two brush-feedback
handlers reached an unexported-data blocker; their source is banked with the
unproved operands excluded from the recorded scores. Together with the seed
set, ten functions account for 490 verified bytes. The assertion-enabled
`Coord2D::Negate` calibration is also banked, outside that total.

A clean checkout reproduced the seed matches, the unchanged retail image,
the compact inventory and a pinned BFME2 donor fetch without an existing
Ghidra database or installed MFC runtime. Live claim collision and failed-worker
cleanup checks passed. Start with two editor workers on distinct files and one
dependency/tooling lane; the next shared blocker is support for independently
witnessed unexported data and callees. These results establish a recovery lane,
not a fully rebuilt or runnable editor.

## Target and source ownership

The baseline manifest at `inputs/baselines/bfme1/workshop-vanilla-1.03/manifest.json`
records the WorldBuilder image and its SHA-256. The verifier checks that image
before comparing bytes. The target ledger is
`targets/worldbuilder/reverse/functions.csv`; generated runs live under ignored
`build/worldbuilder/`.

Editor sources belong in `worldbuilder/src/`. Independently verified
engine implementations can reuse existing `game/` sources. When WorldBuilder
needs a different implementation, put it at the corresponding path beneath
`worldbuilder/`. A game claim never implies a WorldBuilder claim.
Edits to a source claimed by both targets trigger both verification paths.

The initial compiler profiles use the existing MSVC 7.1 toolchain
(13.10.3077), running through Wine on Linux. `engine-size` and `editor-size`
use size optimization; editor sources use real MFC headers and the DLL ABI.
These are calibrated profiles, not proof of one compiler setting for the entire
editor. In particular, some engine functions retain assertion paths absent from
the game's implementation.

## Recover and verify

```sh
python3 tools/worldbuilder.py check
python3 tools/worldbuilder.py next
python3 tools/worldbuilder.py show CWorldBuilderView::OnShowGrid
python3 tools/worldbuilder.py verify
python3 tools/worldbuilder.py progress --ref origin/master
```

Packets contain the exact image hash, body extent, source family, compiler
profile, identity chain, callees and donor provenance. Work the source family.
`next` prefers untouched candidates and includes all siblings in the selected
file; explicit selections can retry a banked or blocked candidate.
Use the packet's decorated name, RVA, size, profile and evidence in
`worldbuilder.py probe` or `land`:

```sh
python3 tools/worldbuilder.py probe \
  --name '<decorated name>' --rva '<RVA>' --size '<bytes>' \
  --source '<source.cpp>' --profile editor-size --evidence '<packet evidence>'
```

`land` takes the same arguments plus `--model`. It verifies the complete source
family and appends only after successful byte comparison. Compilation uses a
fresh run directory. Relocations require independent named exports, imports,
verified target functions or witnessed literal data; unknown references stop
verification. There is no masked-relocation success mode. Each successful run
retains its command, compiler output, comparison receipt and an unchanged copy
of the retail executable demonstrating the accepted replacements.

Export identities and independently decoded MFC runtime-class/message-map
chains are supported. A guessed name or Ghidra function label is insufficient.
Count each accepted byte range once; WorldBuilder's general linker/ICF behavior
has not been established. Naked bodies and emitted-byte lifts are rejected.

For an incomplete attempt, keep the useful source outside the production roots:

```sh
python3 tools/worldbuilder.py record '<candidate ID>' partial \
  --model '<model>' --evidence '<observations; t=minutes>' \
  --blocker '<specific unresolved reference or byte difference>' \
  --stash build/worldbuilder/attempt.cpp --score 0.95
```

Both `--stash` and `--score` are required for a partial. Use `blocked` without
those flags when no useful body exists. Banked sources are evidence, not
coverage. Restore the production source to its verified state before publishing.

## References and inventory

`worldbuilder_inventory.py --check` regenerates the compact PE/MFC evidence and
checks it against the tracked inventory. Named exports, resource labels, class
records and message-map chains provide independent identity evidence. Source
paths and assertion strings provide leads; they do not establish a function
boundary by themselves.

The optional whole-image analysis is reproducible with
`python3 tools/worldbuilder_analysis.py --analyze --ghidra <installation>`.
It writes function ranges, call sites and string references under ignored
`build/worldbuilder-inventory/`; the tracked `targets/worldbuilder/reverse/analysis.json`
records tool versions, hashes and boundary samples. Ordinary recovery does not
require a Ghidra database. Ghidra can miss metadata-proven function starts, and
its owned-address count can describe noncontiguous ranges; neither is an
accepted body size.

The donor index pins exact BFME1 and BFME2 revisions and source hashes. Search
offline, then explicitly fetch a small selected source into the ignored cache:

```sh
python3 tools/worldbuilder_donors.py Region3D --reference bfme2
python3 tools/worldbuilder_donors.py '<decorated name>' --exact --reference bfme2 --show
```

Same-name donor correspondences are recovery leads, not byte matches. Zero Hour
editor references include the vendoring revision and normalized file hashes;
the original upstream revision is not known.

MFC ordinal evidence and acquisition commands are documented in
[`targets/worldbuilder/dependencies/README.md`](../targets/worldbuilder/dependencies/README.md).
The small verified map is sufficient for normal compilation/verification;
large dependency downloads are explicit. Unproven ordinals remain unsupported.

## Bounded workers and publication

`worldbuilder_fleet.py` claims whole editor source files. The initial lane permits
only WorldBuilder-exclusive source edits; shared engine work is coordinated
manually. `run` supplies the binary binding and packet path to a worker command,
records its output and exit status, and releases the file after it stops:

```sh
python3 tools/worldbuilder_fleet.py run '<candidate ID>' --run-id '<unique ID>' -- <worker command>
python3 tools/worldbuilder_fleet.py claims
```

For agents managed outside a child process, use `claim` and `release --reason`.
Keep the lease until the agent has stopped writing. A killed coordinator can
leave a lease intentionally: inspect its run and stop the worker before explicit
release from its owning worktree. Claims live under Git's common directory, so
worktrees of the same clone share ownership. Independent clones need a single
dispatch coordinator. `run` requires POSIX process groups; Windows workers use
externally supervised `claim`/`release`. Workers do not share Git staging or publication operations; one
coordinator commits the verified results using explicit paths and normal hooks.

Before publishing, run target verification and progress, commit normally, rebase
on `origin/master`, and push. Hooks verify the actual staged/outgoing inputs and
reject dirty dependencies. Do not bypass a hook or increase a baseline to make
it pass. The game ledger remains independently checked.
