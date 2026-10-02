# ScriptEngine::getSkirmishEnemyPlayer at 0x0034C430 (identity only)

The 69-byte body at 0x0034C430 is still the generated dump `?d_0034c430@@YAXXZ`.
A 68/69-byte bank exists at `targets/game/reverse/attempts/0x0034c430.cpp`,
under the invented name `BfmeHostAAT::bfmeFindAAT`. Earlier sessions blocked
the body on codegen (long-form global loads) and on an unproven owner. This note
settles the owner and the method. No ledger row changes.

## Facts from retail 1.03 (`lotrbfme.exe`, image base 0x400000)

- ILT 0x00006E6F jumps to 0x0034C430. Its VA 0x00406E6F appears once in data:
  at 0x010E7A78, slot 18 (+0x48) of the table at VA 0x010E7A30. No direct call
  reaches the body or its ILT.
- 0x010E7A30 is ScriptEngine's SubsystemInterface table. Slot 5 is
  `?update@ScriptEngine@@UAEXXZ` (0x0034B9A0) and slot 9 is
  `?newMap@ScriptEngine@@UAEXXZ` (0x00342E40). Slots 19-23 are
  `getCurrentPlayer`, `getObjectTypes`, `doObjectTypeListMaintenance`,
  `getQualifiedTriggerAreaByName` and `evaluateConditions`, all already
  `@ScriptEngine` in the ledger.
- Zero Hour's ScriptEngine declares, in order: `newMap`, `getActionTemplate`,
  `getConditionTemplate`, `startEndGameTimer`, `startQuickEndGameTimer`,
  `startCloseWindowTimer`, `runScript`, `runObjectScript`, `getTeamNamed`,
  **`getSkirmishEnemyPlayer`**, `getCurrentPlayer`, `getPlayerFromAsciiString`,
  .... With newMap at slot 9 and getCurrentPlayer at slot 19, the slot before
  getCurrentPlayer is getSkirmishEnemyPlayer. Slot 17 (0x0034F160) compares its
  argument with the literal "<This Team>" (0x010E1FD0), Zero Hour's
  `THIS_TEAM` test in `getTeamNamed`. That is the ZH order.
- The body matches Zero Hour's `ScriptEngine::getSkirmishEnemyPlayer` statement
  for statement, without ZH's later Generals-Challenge filter:
  - `mov ecx,[ecx+0x170AC]; test; je -> return 0`. `getCurrentPlayer`
    (0x0033DA70) returns the same field `[esi+0x170AC]`, so it is
    `m_currentPlayer`.
  - `call ILT 0x00015438` -> 0x000C9420, `mov eax,[ecx+0x220]; ...`: the
    current-enemy accessor (`m_currentPlayer->getCurrentEnemy()`); a non-null
    result is returned.
  - Otherwise it loops `i < ThePlayerList->getPlayerCount()` (global 0x012ED748,
    count at +0x10), calls `PlayerList::getNthPlayer` (ILT 0x00044F30 ->
    0x000DF240) and tests the player's type field at +0x2C (ZH
    `getPlayerType() == PLAYER_HUMAN`). It returns the first match, otherwise 0.
  - Plain `ret` (no stack arguments), result in EAX: `Player *(void)`.

## Conclusion

0x0034C430 is `ScriptEngine::getSkirmishEnemyPlayer()`, mangled
`?getSkirmishEnemyPlayer@ScriptEngine@@UAEPAVPlayer@@XZ` (public virtual, as in
ZH). The banked body only needs this name and ScriptEngine's real field name
`m_currentPlayer` (+0x170AC). The remaining blocker is codegen: retail uses
long-form `mov ecx,[ThePlayerList]` / `mov edx,[ecx+0x10]` where MSVC emits the
short accumulator form.
