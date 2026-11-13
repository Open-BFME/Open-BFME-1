# AICommandParmsStorage wrong-provider retirement — 2026-11-13

Baseline: `72cdedeab4bda93ec099f6454b92cc568a8e7b96`. Runtime:
`openai/gpt-6.1-sol:high`. This is an **already-source provider repair, zero
source-byte gain/loss**, not new byte coverage or a complete closure result.
Cached queue rank 8's 1949 bytes are not current measured credit.

## Target facts and minimal repair

The sole ledger owner of `?doXfer@AICommandParmsStorage@@QAEXPAVXfer@@@Z`
is `game/GameEngine/Source/GameLogic/AI/AICommandParmsStorageXfer.cpp`,
RVA `0x00187860`, 805 bytes, 21 relocation records, thiscall `ret 4`.
Retail ILT `0x00002DEC` jumps to this body. The native calls and full normal
gate establish the BFME version block and second team-name transfer.
`S3VersionBlocks.cpp` has two real REL32 calls to this provider and no
competing definition. Its private view and calls are unchanged.

`game/GameEngine/Source/GameLogic/AI/AIStates.cpp` separately emitted a
968-byte NODUP COMDAT with the same public name from an explicitly
`present-unmatched` Zero Hour implementation. That implementation lacks
BFME's version/team-owner transfer and uses the older storage layout. Only
this wrong definition is removed; the declaration, correct provider, callers,
headers, types, pins, data, aliases and verifier rules are untouched.

Removing source lines changes `__LINE__` arguments in five unrelated runtime
bodies. Parent specifically approved one filename-free `#line 297` reset at
the original following line, preserving their existing `__FILE__/__LINE__`
behavior. Before-source SHA256:
`5cf43017d2d83e3cdc5b796167a5fcc7945af3a5c11957538fa08252eb7140aa`;
after: `6378006538e2f3927aac1f08a93b72768a7985cc7c636a62bae26a6281bb176a`.
Both proof objects compile at the same official source path using normal
compiler command construction under the external lane guard.

## Complete bounded object evidence

`test_aistates_retirement.py` has seven read-only checks. All retained runtime
sections compare exactly in bytes, relocation order/type/addend/target,
symbol/type/storage/value, COMDAT selection/association, section flags,
COMMON, weak-external bindings and directives. Only COFF section/symbol indices
and compiler-private EH label ordinals are represented by their actual graph
identities, never by raw numbering. The SafeSEH table is decoded to its handler
symbols; its raw checksum is independently recalculated. The only lost table
entry is the removed function's handler.

Seven sections disappear: the wrong 968-byte function, its associated EH code
and data, and four exclusively emitted inline helpers. **1778 retained runtime
sections** (plus the decoded SafeSEH table) are unchanged. All 103 AIStates-owned
matched symbols remain. Normal provider and consumer objects are current and
graph-equal to their independently compiled private inputs.

| Removed incidental helper | Bounded remaining use / existing provider |
| --- | --- |
| `CommandButton::getName` const-reference getter, 4B | No old/new local inbound relocations; unchanged canonical transfer TU naturally emits its own 4B `lea eax,[ecx+0xC]; ret` provider. No ledger row. |
| `Path::operator new(size,PathMagicEnum)`, 14B | No old/new local inbound relocations; no ledger row. Correct transfer uses global operator new and the real Path constructor, not this pool allocator. |
| `Path::operator delete(ptr,PathMagicEnum)`, 12B | Only old wrong-function EH had an inbound relocation; none retained. Ledger owner remains `Common/RTS/RtsPoolGlueDeletes.cpp`, unchanged. |
| `PolygonTrigger::getTriggerName` by-value getter, 37B | Only wrong doXfer had an inbound call; none retained. No ledger row. Canonical transfer uses its evidenced inline const-reference accessor, not a new alias/provider for this by-value ABI. |

These are bounded object facts, not a complete census of external consumers.
Exact helper records and ledger owners are in `helper-ownership.json`.

## Native pair: useful negative evidence, NOT closure

`native_pair.py` links the complete genuine AIStates, canonical transfer and
S3 consumer objects with shipped MSVC CRT/Kernel32 import libraries. Same
boundary/options at bases `0x10000000` and `0x20000000`; real doXfer API root;
`/NODEFAULTLIB /OPT:REF /OPT:NOICF`; no stubs, synthetic data, manual archive
index/import DEF, aliases, `/FORCE`, object rewriting or image execution.

All four links return **96**: BEFORE has one LNK2005 for doXfer; AFTER has
zero. Both sides still have the same **244 genuine unresolved externals**,
including real Path, StringBase, global-manager and other AIStates/S3
providers. No valid linked image or selected-provider/descriptor/ILT/IAT
closure proof is claimed. Both whole-program and bounded-family closed-byte
deltas are **NULL**, not 1949 or zero. Local `link_check` preview is UNKNOWN:
`build/link_census/link_index.pkl` is absent. No cold census or remote CI ran.

## Validation and receipts

Run all project scripts/normal builds through
`/home/pispike/qa/bfme-spike3-20261113/integration.sh` before imports.

- Normal BEFORE and AFTER gates on AIStates + canonical provider + S3:
  **121/121**, 12 literals, 8 float constants, 37 DIR32 references, zero
  baselines/skips/unverified. AFTER recompiles AIStates and validates the two
  current dependency-cache objects normally.
- `test_aistates_retirement.py --before BEFORE.obj --after AFTER.obj
  --provider CANONICAL.obj --consumer S3.obj --receipt RECEIPT.json`: **7/7**.
- Negative control flips one retained FindPositionOptions constructor byte in
  a private copy; proof fails with exit 1 in both graph-equality checks.
- `check_csv.py`: PASS; `git diff --check`: PASS.

Tracked `proof.json` is the actual graph-delta receipt; `native_pair.py`
reproduces the deliberately unsuccessful bounded link test from the preserved
private input paths. Raw objects, exact source edit/commands, native link
commands/logs and helper checks are under
`build/spike3/aicommand-feasibility/`. Top-level logs:
`build/spike3/{aicommand-normal-before,aicommand-normal-after,aicommand-proof-tests,
aicommand-negative-tests,aicommand-native-pair,s3-link-before}.log`.
The negative-control exit and normal-gate exits are retained alongside logs.

## Donor evidence and limits

Pinned BFME2 revision `76f0baefa6f285d54bc1ca922397674312a5913f`:
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva0026AFDAMemberDoXfer.cpp`
and its AIUpdate/DeployStyle callers reviewed. Its 680-byte, 0xC4 storage
layout differs; it is a semantic comparison, not BFME1 layout/name proof or
an imported repair. BFME1's actual provider/callers establish this removal.
No donor file/gitlink was changed. No original laptop private evidence was
assumed available. Publication remains HOLD until independent immutable-range
review and explicit parent approval.
