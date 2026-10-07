# 0x0026F0E0 is AIUpdateInterface::friend_startingMove

## Stub proof

`symbols.csv` pins `?friend_startingMove@AIUpdateInterface@@QAEXXZ` at the ILT
stub 0x0001246D (`pin_consistency.py --symbol` verdict: consistent). Ledger row
`?j_0001246d@@YAXXZ` records `target=FUN_0066f0e0`, i.e. RVA 0x0026F0E0, and
`callees.py 0x178BC0 88` prints `0x1246d -> 0x26f0e0`.

## Caller proof

The matched computePath bodies 0x00178BC0, 0x00178D90 and 0x00178E30 call the
stub on their AIUpdateInterface after requestPath, exactly where ZH
AIInternalMoveToState::computePath calls `ai->friend_startingMove()`.

## Body proof

The 28-byte body stores, in order: +0x323 = 0, +0x324 = 1, +0x16C = 0,
+0x326 = 0. ZH friend_startingMove assigns m_movementComplete = FALSE,
m_isMoving = TRUE, m_blockedFrames = 0, m_isBlockedAndStuck = FALSE in that
order. `name_oracle.py --class AIUpdateInterface` independently witnesses
+0x16C m_blockedFrames and +0x326 m_isBlockedAndStuck (layout_witness, 1.00).

The previous name `?reset@Rva0026F0E0@@QAEXXZ` was an opaque placeholder
("identity not recovered").
