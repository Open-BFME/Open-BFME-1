# 0x000D77B0 Player::becomingLocalPlayer (748 B)

Source: `game/GameEngine/Source/Common/RTS/PlayerBecomingLocal.cpp`, replacing the
naked `__emit` lift `Player_becomingLocalPlayerMethodThunk.cpp`.

## Identity (BFME 1 target evidence)

- `ilt_oracle.Oracle().check('?becomingLocalPlayer@Player@@QAEX_N@Z', 0xD77B0)`:
  CONFIRMED, exact, p_false 0.00026 (ILT slot 19491 = thunk 0x00018CB4).
  `becomingTeamMember`, `PlayerList::setLocalPlayer` and `garrisonAllUnits`
  spellings are CONTRADICTED at the same target.
- The matched `PlayerList::setLocalPlayer` (0x000DF3C0) calls ILT 0x00018CB4
  (`jmp 0x004D77B0`) twice, with ECX = a Player and one bool argument.
- Boundary: SEH prologue at 0x000D77B0, `ret 4` at 0x000D7A99, int3 padding from
  0x000D7A9C (748 B).

## Layout (read from the retail body)

Player colour +0x1C4, night colour +0x1C8, observer +0x296, dead +0x680
(the matched `Player::isPlayerActive` 0x000C9D10 reads the same two flags).
Object: template +0x04, contain +0x1FC (vslot 16 recalcApparentControllingPlayer),
team +0x23C, disguiser bit 0x800 of +0x130, drawable at vslot 10. Template bit
0x800000 of +0xD0. StealthUpdate player index +0x34, disguised flag +0x38.
GlobalData time of day +0x218. The partition result is a one-word refcounted
handle (`[h]+0x04` end, `+0x0C` cursor, `+0x10` references), the same
`BfmeResultA` view as the matched `Player::garrisonAllUnits` (0x000D8E30).

## Donor (carried, not BFME 1 proof)

Open BFME 2 `Code/GameEngine/Source/Common/RTS/PlayerBecomingLocal.cpp` at
76f0baefa6: cached GameClient pointer, one-word partition result,
SpecialDisguiseUpdate notification before the disguise-colour pass, no
ControlBar dirty call. All four hold in BFME 1 retail.

## Callee spelling: `bfmeForwardResultA`, not `iterateAllObjects`

The 0.45 bank called `ThePartitionManager->iterateAllObjects()`, Zero Hour's
`ObjectIterator *` API. Retail instead passes a hidden return pointer to
0x009F2A20, which the ledger matches as
`?bfmeForwardResultA@BfmeResultForwardA@@QAE?AUBfmeResultA@@XZ`
(BfmeResultForwardA.cpp, a 32-byte forwarder through the member at +0x0C).
The body must call that ledger name to link to retail's bytes. The ZH name has
a different ABI, so it cannot be kept. The forwarder's own EA name is still
unproven and is not renamed here.
