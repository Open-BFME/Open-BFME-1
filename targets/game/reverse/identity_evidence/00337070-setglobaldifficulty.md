# 0x00337070 is ScriptEngine::setGlobalDifficulty

Claim: `?setGlobalDifficulty@ScriptEngine@@QAEXW4GameDifficulty@@@Z` at RVA
0x00337070 (13 bytes), retiring the address-derived placeholder
`?dup_00337070@@YAXXZ` (gen-alias, same extent).

## Boundary (retail evidence)

- 13-byte thiscall setter: `mov eax,[esp+4]; mov [ecx+0x17620],eax; ret 4`.
- ILT slot 0x000126BB is a 5-byte `jmp` landing here; the same extent is
  already claimed by the gen-alias row, whose emission byte-matches.

## Identity (independent retail + upstream evidence)

1. Member offset: ZH `ScriptEngine.h` places `m_gameDifficulty` (a
   `GameDifficulty` dword) immediately before `m_freezeByScript`. BFME's
   ScriptEngine carries a proven +0x6868 run ahead of `m_freezeByScript`
   (shim `scriptenginelayout/GameLogic/ScriptEngine.h`, two independent
   pins), so BFME+0x17620 is exactly ZH+0x10DB8: `m_gameDifficulty`. ZH
   declares the setter out-of-line: `void setGlobalDifficulty(GameDifficulty)`
   (`ScriptEngine.h:336`), with the enum spelled `GameDifficulty`
   (`GameCommon.h:141`), giving the claimed decoration.
2. Oracle: `ilt_oracle.check` CONFIRMS the enum-spelled name at 0x00337070
   (p_false 2.6e-4) and CONTRADICTS both the bool spelling
   `?setObjectsShouldReceiveDifficultyBonus@ScriptEngine@@QAEX_N@Z` and the
   int spelling `?setObjectsShouldReceiveDifficultyBonus@ScriptEngine@@QAEXH@Z`
   there. The bool method genuinely lives at 0x002ED530 (byte store at
   +0x17634, oracle-confirmed there, row untouched).
3. Callers: three named retail bodies call ILT 0x000126BB, each pushing a
   dword in a difficulty context: `?prepareNewGame@GameLogic@@QAEXHW4GameDifficulty@@H@Z`
   (0x00397190, pushes 1), `?DifficultySelectSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z`
   (0x004C72C0, pushes the `s_AIDiff` difficulty), `?bfmeShutdownAAV@@YAXXZ`
   (0x004D1B00, pushes `g_bfmeArgAAV`). A matched caller naming the symbol is
   the strongest evidence; all three TUs now spell this name.

## Retired claim

`?dup_00337070@@YAXXZ` was an address-derived placeholder whose gen-alias
object-symbol guessed the bool difficulty-bonus method. That guess is refuted:
the bool method is the byte-store body at 0x002ED530 (different offset,
different width, oracle-confirmed there), while this dword body, its slot
window, its member offset and its three callers all identify
`setGlobalDifficulty`.

## Reconciled conflicting pin

The bool setter row at 0x002ED530 is independently oracle-CONFIRMED
(p_false=7.83e-4). Its old candidate pin at ILT 0x126BB instead reached
0x00337070 and caused pin_delta to reject the newly named dword setter.
Correct the bool pin to its proven 0x002ED530 body; the three dword callers
now name setGlobalDifficulty and no longer depend on that false bool pin.
