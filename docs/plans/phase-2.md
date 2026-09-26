# Phase 2: Land proven naming improvements

## Objective

Use elapsed 0:30–3:00 to deliver verified naming improvements and measure the
team's actual edit-to-push throughput.

## Implementation

- Naming worker starts with
  game/GameEngine/Source/GameLogic/Object/WeaponTemplate_CopyAssign.cpp:
  field_names.csv maps +0x14 to m_attackRange and +0x18 to
  m_minimumAttackRange. Confirm ownership/offsets and rename proven identifiers
  throughout the TU, preserving existing types, offsets and expression order.
- Placement worker reviews TimedOperationNode constructor/destructor filenames
  Bfme5TimedOpNodeCtor.cpp and Bfme5TimedOpNodeDtor.cpp under Common. Use existing
  class vocabulary and rename_addressed_sources.py for small eligible proposals;
  inspect source provenance and update ledger paths in the same unit.
- Evidence worker reviews and prepares the next independent owner, beginning
  with GameNetwork/Y2FeslAddressFormat.cpp parameter/local names. Formatting and
  parsing prove octet/buffer vocabulary; do not infer that m_extra is a port or
  rename its unknown owning class. Preserve all public symbol identities.
- Keep function/class renames requiring mangled-symbol changes for phase 4's
  evidence standard. Coordinate any move and body edit of the same file under
  one owner. Publish continuously under the common runbook.
- At hours 1, 2 and 3, review landed samples, identify one measurable bottleneck
  and apply/evaluate the hourly experiment. Use observed throughput to forecast
  the remaining time without setting an artificial rename quota.

## Verification

- `./build.sh <every-affected-surviving-source>` passes before and after integration.
- `python3 tools/check_csv.py` and normal commit/push hooks pass; confirm renamed
  sources are tracked and narrow `rg` searches find no stale active references to
  replaced identifiers or paths. Do not remove historical evidence references.
- `python3 tools/readability_metric.py --staged` is recorded alongside reviewed
  rename counts, including legitimate zero metric movement.
- An independent reviewer can trace each semantic field/local name to concrete
  evidence. Each published SHA is confirmed in origin/master. Hourly checkpoints
  contain observed times, review findings and experiment results.
