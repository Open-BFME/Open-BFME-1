# 0x00271DB0 AIUpdateInterface::DoXfer (2099 B): BFME 2 donor recipe (landed s548)

Session a1 s548 (2026-11-03), model claude-opus-5-5. Identity is in
`identity_evidence/00271db0-aiupdateinterface-xfer.md` (ILT check:
`?DoXfer@AIUpdateInterface@@MAEXAAVXfer@@@Z` CONFIRMED exact at 0x271DB0, the
`?xfer@...@@MAEXPAVXfer@@@Z` spelling CONTRADICTED; the body takes the Xfer in a
stack slot, so check which spelling the landing needs). The ledger row is still a
naked destructor lift, plus two more destructor over-claims on the same extent.

## Reproduce (about 5 minutes)

1. Donor: `inputs/reference/open-bfme-2/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateXfer.cpp`
   (open-bfme-2 45afcff3). Inline its quoted includes (search order: the file's
   directory, `reference/shims/bfme2_ascii`, `reference/shims/moduledata`,
   `Code/GameEngine/Include`; 9 headers) into one scratch .cpp and set the
   `// cl:` line to BFME 1's `/DNDEBUG /MD /EHsc` (the donor's `/O1 /G7 /arch:SSE`
   is wrong here).
   As is: 2069/2099 B, shape 0.912.
2. Xfer vtable: BFME 2 has one extra `operator==` overload. Deleting any one unused
   overload (PooledString was used) moves `==(unsigned int&)` +0x78 -> +0x74 and
   `==(bool&)` +0x90 -> +0x8C, as retail. Snapshot (+0x30) and Version (+0x28) do not move.
3. `Xfer::Version version(1, 6)` (retail stores 6, the donor 5).
4. AIUpdateInterface vtable: delete 16 `gapNNN` virtuals before `makeStateMachine`
   (retail calls it at +0x218, the donor at +0x258).
5. Wrap the tertiary state machine block in `if (version.m_minimum >= 5) { ... }`
   (retail `cmp byte [esp+0x15],5; jb`).
   Result: 2076/2099 B, shape 0.915, first structural difference at +0x1D6.

## Remaining

- Member layout: the donor's offsets are BFME 2. BFME 1's bools sit 0x92 lower
  (m_isAiDead +0x32B, not +0x3BD; m_isRecruitable +0x32C). The BitFlags members
  are smaller in BFME 1. Re-derive every offset from the retail listing.
  `m_areaToGuard`'s name is at +0x08 in BFME 1 (+0x40 in the donor view).
- Starting at +0x1D6, retail's trigger-area block is different: it copy-constructs
  the AsciiString (0x615DB0), calls TheTerrainLogic (VA 0x012EF4CC) slot +0x90 and
  stores the result to +0x6C before the attack-info block. The donor
  goes straight to the attack name.
- The frame differs: gotsecondary sits at [esp+0x12] in retail and [esp+0x11] here.

## Outcome

Landed exact in the same session as
game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceDoXfer.cpp. Steps after the above:
- re-derive offsets by aligning normalised instruction streams (difflib on retail vs ours)
- rewrite the tail from the retail listing
- TerrainLogic slots +0x80/+0x90 (three fewer)
- trigger name by value; attack name via `getName()` (ILT 0x47AFF pin)
- `Snapshot *m_turretAI[2]` loop
- no `m_extra3DC` transfer
- `BFME_SNAPSHOT_CAPITALIZED_SLOTS` + `BFME_SNAPSHOT_REFERENCE_XFER` so `DoXfer(Xfer &)`
  overrides slot 3
- an inline 16-bit length test instead of the out-of-line `isEmpty`
- Path is 0x24 bytes
- callees with only address-derived names go through `?j_` ILT rows
