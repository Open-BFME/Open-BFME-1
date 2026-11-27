# Private B1 compiler-vtable owner-locator tooling patch

**Sicher:** the private candidate locates the actual current SpawnUnit constructor
source without a compiler, source comment, data row, baseline edit or mocked
current-object verdict. **Sicher:** 97/97 focused tests pass (34 new, 63 existing).
The unchanged tool fails five of the new tests and passes the other29. This
package is a tooling prerequisite, **0 new C++ bodies / 0 byte credit**.

## Production scope and restricted policy

Proposed files only:

* `tools/repair_queue.py`
* new `tools/tests/test_repair_queue_vtable_owner.py`

The tool adds one helper and one call from `locate_source`, plus a hashlib
import. Existing matched data-owner and function-owner resolution retains
precedence and its existing ambiguity/path policy. Ordinary non-vtable names
retain the old literal Git search. The new branch is **BFME1-only**, for exact
names starting `??_7` that have no existing matched data/code owner. It does not
change BFME2 behavior.

The compiler-name branch has no literal-search fallback. It requires all of:

1. The existing native local census index has valid native table shapes, the
   same checkout root and a complete object inventory.
2. `link_check.changed_since(census_commit)` proves no changed path under
   **`link_census.CENSUS_INPUTS`**. Documentation/census-output-only commits may
   differ. Any source/header/ownership/provider-tool change makes the definer
   set unknown and refuses this route until a fresh census. This is deliberately
   stricter than a speculative selected-object preview.
3. Exactly one indexed object defines the exact name, and exactly one census
   source maps to that object. Strong and COMDAT inventories are deduplicated by
   the same object; no first-copy choice is made between owners.
4. The source is a tracked, existing `game/` C/C++ file, with no traversal or
   alternate separator, and resolves inside this checkout. The existing native
   `build.obj_path` must equal the actual inventoried object path.
5. The actual object SHA256 equals the census inventory, and the native
   **`build.compile_is_current`** command/source/header/search-directory receipt
   accepts it. A fresh-preprocessor receipt fallback is intentionally not used.
6. Native COFF validation/parser find exactly one actual EXTERNAL2 data
   definition of the exact name in initialized storage. Undefined and weak
   symbols are not owners; a same-name function is not accepted as data.
7. Object bytes, the native reusable compile receipt, and census-input currency
   still agree at the end of the bounded read.

Missing, corrupt or unavailable evidence returns None. No fetch, refresh,
compiler, preprocessor, new trust stamp, source override or alternate identity is
introduced. A source only provable through a fresh preprocessor receipt remains
unavailable to this read-only locator. The helper locates an owner for the real
gate; it proves no table size, slot ABI, data relocation, linked image or runtime.

## Actual current-input control

`ACTUAL-READONLY-LOCATOR.json` records the private candidate applied to the
unmodified real checkout. It returns:

```
??_7SpawnUnitBehaviorModuleData@@6B@
 -> game/GameEngine/Source/GameLogic/Object/Behavior/SpawnUnitBehaviorModuleDataConstructor.cpp
```

The actual existing COFF and normal receipt are used. No compiler result,
dependency result, index, source, object, ledger or gate was mocked for this
control. Production tool and all original Spawn input hashes are checked again
in `FINAL-CURRENCY.json`.

The separate Spawn diagnosis remains valid: its current ownership predicate is
already None, while the emitted table has4B and the original live family has17
slots. This patch changes neither fact. Do not describe successful debt removal
as reconstruction of the full class/interface.

## Regression evidence

`green.log` and `green-result.json`: **97 passed** in14.62s. This includes the
unmodified existing63 queue tests, including both project layouts, recorded
data/function owners, refusal of unsafe/ambiguous owners, interrupted builds,
stdin hook behavior and mixed-baseline-line-ending preservation.

`red.log` and `red-result.json`: the frozen original tool with exactly the34
new tests produces **5 failed / 29 passed**. The five expected failures are the
two valid compiler-owner lookups, the two real-child pass-test orchestration
cases, and refusal to return to a literal Git search after a census refusal.

New controls include missing/corrupt/stale/foreign census, missing inventory or
object/receipt, object digest change, source/header/command/inventory receipt
mismatch, source/dependency/new-source changes since census, undefined/weak/
different/duplicate/function definitions, multiple source/object owners, unsafe
or missing/untracked/non-C++ source paths, wrong object/source association,
and both gate success/failure with exact baseline bytes preserved.

Test fixtures contain structurally complete actual i386 COFF bytes and normal
native dependency sidecars in private fixture Git repositories. Pure command
discovery is deterministic for portability; cache verdicts, file hashes,
dependency inventories, COFF validation and owner metadata parsing are not
mocked true. The pass-test orchestration fixture executes a separate real Python
child that records its argument and observes the already-removed baseline; it
is explicitly not a C++-compiler or retail-verification result.

An initial diagnostic run mixed the private and production module during
`importlib.reload` after another native module prepended its tool path. Its
`candidate-first.log` is invalid as a candidate-suite result and is not used.
The final runner installs an exact-module import finder, binding every reload
to the chosen immutable baseline or candidate. Both final receipts record that
path and digest. No production import/source file was changed to do this.

## Root integration sequence

1. Reserve/review the two tool/test paths centrally. Apply
   `repair-owner-locator.patch` only if production baseline hashes still agree.
2. Run the normal current-tree Python tests:
   `python3 -m pytest -q tools/tests/test_repair_queue.py tools/tests/test_repair_queue_vtable_owner.py`.
   Review `AST-SCOPE.json`: only existing `locate_source` changed; all other
   existing top-level function/class segments, including `pass_test` and
   `verify_removed`, remain byte-for-byte identical as source text.
3. Bank this tool/test change in its **own normal Verifier-Change commit**, with
   normal hooks and suitable concise tracked evidence. Do not stage a runtime
   source, data row or baseline with this tool commit.
4. Only after that commit, Root can invoke the exact already-served normal
   `repair_queue.py pass-test '<Spawn baseline line>'`. It must remove that one
   exemption before running the original source gate and restore every byte on
   failure. `pass_test` is completely unchanged. The real native constructor
   gate (two existing rows/144B) is still required and has not been executed here.
5. If normal admission refuses, preserve the refusal; there is no direct
   baseline edit, fallback datum, pointer surrogate, alias or source-name anchor.
   The existing data-size/Weak105/full-interface limits remain separate.

## Scope limits

No normal source build, fresh census, actual Spawn pass-test, data admission,
final link or runtime was run by this child. Root remains sole writer of
production, Git, claims and publication. No PC shutdown is requested or performed.
Ephemeral private pytest fixture repositories stay outside the tracked review
package; the manifest hashes only the immutable patch, review sources and result
receipts/logs needed to reproduce and assess this change.
