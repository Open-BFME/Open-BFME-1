# 0x003006B0 ScriptActions::doCreateReinforcements (2445 B), 2026-11-12 handoff

Bank: `targets/game/reverse/attempts/0x003006b0.cpp` (meant for the new split TU
`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doCreateReinforcements.cpp`,
`// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline`, stlport).
Probe: 2444 B against retail's 2445 B, 76 relocs, normalized shape 0.969, 24 structural diffs,
frame 0xC0 against retail's 0xB4. t=~75 min, model=claude-opus-5-5.

## Identity (BFME 1 evidence)
- `ilt_oracle.oracle().check()` gives these verdicts at 0x003006B0:
  - `?doCreateReinforcements@ScriptActions@@IAEXABVAsciiString@@0_N@Z` is CONFIRMED (exact, p=8.5e-4).
  - The old 2-argument ledger/stash name `...@0@Z` is CONTRADICTED.
- The retail body ends with `ret 0xC`, and the executeAction arms push three stack words.
- The third argument is a Bool. When it is set, the body places the reinforcements on a named unit
  (ScriptEngine slot 27, `+0x6C`, AsciiString by value) instead of a waypoint
  (TerrainLogic slot 31, `+0x7C`, by value). It also sets adjust-to-pathable when that unit
  `isKindOf(7)` is true.
- This was found with the present-unmatched oracle join. The script is in build/w1r4/oracle_join.py
  in the w1 worktree. It takes ZH present-unmatched tokens under GameLogic/, finds full names in
  the BFME 1 and BFME 2 ledgers, and oracle-checks them against open rows near the class's matched rows.

## Donor
Open-BFME-2 76f0baefa6 `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsReinforcements.cpp`
(BFME 2 0x003C7BBB, 1839 B at /O1, same mangled name). BFME 1 differs from it in three ways:
- No rank/upgrade calls on the units.
- A four-field packet for the group move, sent through the pinned `Rva0015A190Owner::applyPacket`
  (ILT 0x48C43).
- No `_ReadWriteBarrier`.

The partition section copies the matched `ScriptActions_doLoadAllTransports.cpp` (0x003014C0).

## Layout read from retail
- **TeamPrototype:** +0x10 owner, +0x14 name, TeamTemplateInfo at +0x12C.
- **TeamTemplateInfo:**
  - unitsInfo[7] {min,max,name} at +4
  - count at +0x58
  - transport type at +0xAC
  - start waypoint at +0xB0
  - startsFull at +0xB4
  - transportsExit at +0xB5
- **Object:** +0x38 position, +0x74 id, +0xBC major radius, +0x1A4 disabled (bit 3 = held),
  +0x1FC contain, +0x204 ai, +0x214 containedBy. The PMF DLINK skeleton has its vbptr at +0x68.
- **Team:** head at +0xC; setActive writes +0x32 then +0x31.
- **Other:** the AI pathfinder is at +0xC; the unit LocomotorSet is at ai+0x1A8; updateGoal's
  file/line are the `"F:\bfme\...\ScriptActions.cpp"` literal and 0x3B3.

## Levers measured
- Raw masked test for the held-disabled bit (`m_disabledMask & 8`, no `!= 0`) took shape from
  0.955 to 0.959.
- `memset` in the BitFlags<86> mask constructor took shape from 0.959 to 0.969. Retail zeroes
  each newObject mask temp with a fresh `xor ecx,ecx` between the argument pushes. A zeroing loop
  used the zero register instead, and explicit stores were worse (2495 B).

## Remaining residue
1. **Frame is 12 bytes too large (0xC0 against 0xB4).** The /FAsc slot tables, in retail esp coordinates:
   - **Retail:**
     - j 0x20, transport 0x24, origin 0x28, theTeam 0x34
     - transportTemplate 0x38, also holding the by-value-arg saved-esp temp
     - shared 12-byte slot at 0x3C: newObject mask, vecOfUnits, contain-loop pos
     - destination 0x48, proto 0x54, transportCount 0x58
     - shared 24-byte slot at 0x5C: iterator with its PMF at 0x64..0x6C, unitInfo pointer, pair temps, group packet
     - shared slot at 0x74: i, pair, solution
     - transport mask alone at 0x80, partition 0x8C
     - shared slot at 0x14: unit-loop pos, vecOfTransports, contain-loop mask
   - **Ours:**
     - j 0x14, transport 0x18, theTeam 0x1C, transportTemplate 0x20, origin 0x24, destination 0x30
     - iterators (24 B), pos and vecOfTransports at 0x3C
     - proto 0x54, pos2/vecOfUnits 0x58, solution 0x64, transportCount 0x70, i 0x74
     - packet alone at 0x7C, mask temp at 0x8C, partition 0x98
   - The packet and the iterators do not share retail's 0x5C slot. Most of the 1578 byte diffs
     follow from this slot drift.
2. **Small structural items.**
   - In the two template comparisons, retail's OVERRIDE null branch is `jne` / `xor; jmp`; ours is `je`.
   - The two bools are stored as an immediate 0 in retail and through a zero byte register in ours.
   - transportCount is incremented through a register in retail; ours does `inc dword [mem]`.
   - The solution-vector size is reloaded, and the group packet's stores are in a different order.

## Dependencies
- The callees are all ledger-named except 0x003E9720 and 0x00159AD0. Both are reached through
  existing pins: `?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@W4PathfindLayerEnum@@PBDH@Z`
  and `?applyPacket@Rva0015A190Owner@@...` at ILT 0x48C43.
- Landing needs a functions.csv rename of the `?d_003006b0` gen-dump row to the 3-argument name
  (`add_match --replace-rva`). It also needs the present-unmatched 2-argument ZH body in
  ScriptActions.cpp reconciled with that name.
