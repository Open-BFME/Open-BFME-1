# AIUpdateInterface::getCurrentStateID COMDAT ownership

Investigation base: 4d92da13a150e0287b5595d826c0aad09608b897.
Exact name: `?getCurrentStateID@AIUpdateInterface@@QBEIXZ`.

Retail RVA 0x000C3D90 is 20 bytes, reached through ILT 0x0002FAEA
from the matched AIAttackApproachTargetState::updateInternal. Its existing
owner is AIUpdate/AIUpdateInterfaceGetCurrentStateID.cpp. It reads the
state-machine pointer at +0x30, the state pointer at machine+0x1c, and
the ID at state+4, with INVALID_STATE_ID (999999) for a null state.
There are no relocations in this body.

The competing copies in AIStates.cpp and AIUpdate.cpp are select-any
COMDATs (COFF selection 2), with identical 20-byte code:
`8b412c8b401c85c074048b4008c3b83f420f00c3`.
They instead read interface+0x2c and state+8.
The origin is two copied ZH headers: sweep/GameLogic/Module/AIUpdate.h
and aiupdatelayout/GameLogic/Module/AIUpdate.h. The latter shadows the
former for AIUpdate.cpp. The shared State accessor also carries the +8
load. This is not repaired by modifying only the sweep header.

Declaration-only accessors in both headers prevent emission of the
non-retail definitions. Existing calls resolve to the established retail
owner without changing class sizes, field order, or the ledger order.
COFF inspection of both trial objects shows an undefined external for the
exact name and no defining COMDAT.

The 2026-10-28 12:38 census at ea2916a82d reports 12,675 affected authored
bytes and 847 bytes conditionally blocked by this family alone. These are
diagnostic figures, not a measured post-repair LINKED gain.

Validation before final census:

- The original retail owner passes its 20-byte body and relocation checks.
- Affected-header analysis selects 98 sources, with 3,331 matched rows.
  The broad byte check passed 3,329 rows. The two failures were stale
  TurretStateMachine cleanup labels; the unwind-state oracle also found four
  identical-byte twins whose old labels now denoted the wrong state.
- `eh_state_pins.py --fix` rebound those six TurretAI labels and one AIUpdate
  label using retail FuncInfo and state indices. The subsequent 106-row
  TurretAI/AIUpdate gate passed, including relocations and body guard.
- Across all 3,331 rows: 311 string literals plus 15 empty strings, 189 float
  constants, three local readonly loads, and body guard passed.
- Six DIR32 references in AIStates/Locomotor failed on pristine HEAD too.
  `g_rva01075350` already has a matched data row at VA 0x01075350, and its
  provider passed the data byte gate. Historical DIR32 spellings at the same
  address hid that ownership because the guard rejected aliases before
  considering data rows. The repair recognizes an existing data owner at the
  exact address, continues rejecting unowned aliases, and additionally refuses
  a known data owner at any other address even when its spelling fits. No
  record or baseline additions are needed. All 2,290 affected DIR32 refs pass.
- Focused data-address/record/ownership tests: 111 passed, one skipped.
  Operator-correction tests: 17 passed in isolation. Running the record and
  operator suites together has three pre-existing order-dependent failures;
  the identical combined command fails on pristine HEAD as well.
- The normal full commit gate passed all 3,331 matched rows across 98 TUs,
  including relocation, data-reference and body checks. Final-link measurement
  remains separate; these checks alone do not establish a LINKED-byte gain.

Related repaired family: StateMachine::getCurrentStateID at RVA 0x0009FF60.
The same census identifies eight wrong emitters with the same digest and
19,084 affected bytes. Its retail owner reads state+4; the sweep header
composes the state+8 accessor. The separate repair and dependent-body gate
are documented in `0009fee0-state-accessor-comdat.md`.

PlayerInfo is a separate layout issue: the retail 0x004F1120 copy owns
three AsciiStrings and ten dwords (52 bytes); both the ZH header and
peerdefs shim declare only two strings. Replacing the AsciiString view
alone cannot repair the record layout. Do not bind a 36-byte ZH record to
the 52-byte retail copy constructor merely to remove a linker blocker.

Accepted fresh census results for the combined AI/State repairs are in
[final results](0009fee0-state-comdat-results.md): +1,038 authored linked
bytes, three existing consumer TUs unlocked, no newly unlinked source.
