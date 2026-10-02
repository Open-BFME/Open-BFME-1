# AIAttackMeleeApproachState::computePath at 0x00176A50 (identity only)

The 1041-byte body at 0x00176A50 is still the generated dump
`?d_00176a50@@YAXXZ`. Earlier sessions called it "an anonymous EH-framed AI
computePath-style routine" with "no matched caller, vtable slot, or source
declaration". The slot exists. No ledger row changes.

## Facts from retail 1.03 (`lotrbfme.exe`, image base 0x400000)

- ILT 0x000179EA jumps to 0x00176A50. Its VA 0x004179EA is slot 17 (+0x44) of
  the table at VA 0x0109A6C0.
- 0x0109A6C0 is AIAttackMeleeApproachState's table. Slot 0 is the matched
  `??_GAIAttackMeleeApproachState@@MAEPAXI@Z` (0x00185450). Slot 2 is
  0x0017F850, `mov eax, 0x0109A718; ret`, the literal "AIAttackMeleeApproachState".
  The same literal is the State name its constructor passes to
  `AIInternalMoveToState::AIInternalMoveToState(StateMachine*, AsciiString)`.
  That constructor is 0x0017F7F0 (`??0BfmeStateBB@@QAE@PAX@Z`, noted in the
  ledger as the AIAttackMeleeApproachState constructor); it then stores
  0x0109A6C0 at +0. AttackMeleeStateMachine's constructor (0x00180EE0) builds the
  same state inline (0x00180F51-0x00180F63). Those three places are the only
  references to the table and to the literal.
- Slot 17 in the AIInternalMoveToState family: 27 tables keep
  `?computePath@AIInternalMoveToState@@MAE_NXZ` (0x001725B0) there. A few
  states override it with their own address-named `computePath` rows
  (0x00178D90, 0x00178E30, 0x00173680). This table overrides it with 0x00176A50.
- ABI: every exit of the 1041-byte extent is a plain `ret` (no stack
  arguments), matching `Bool computePath()`.

## Conclusion

0x00176A50 is `AIAttackMeleeApproachState::computePath`, mangled like the base
row: `?computePath@AIAttackMeleeApproachState@@MAE_NXZ`. Its constructor
0x0017F7F0 still carries the placeholder `BfmeStateBB` name, which this note
does not change.
