# 0x00267D80 SpecialDisguiseUpdate::triggerAbilityEffect (433 B)

Identity correction: the row was the naked `__emit` lift
`rva_00267d80_SpecialDisguiseUpdate_slot15` (object symbol
`_bfme_StealthUpdateChangeVisualDisguise_267D80`) in
`SpecialDisguiseUpdateSlot15Rva00267D80Thunk.cpp` (deleted). The body is
`?triggerAbilityEffect@SpecialDisguiseUpdate@@MAEXXZ`.

## BFME 1 target evidence
- The SpecialDisguiseUpdate constructor 0x00267820 installs vtable 0x010B7708;
  slot 15 reaches this body through ILT 0x0003DD43 (earlier verdicts in
  re_attempts.log).
- `ilt_oracle.py check ?triggerAbilityEffect@SpecialDisguiseUpdate@@MAEXXZ 0x00267D80`:
  CONFIRMED (p_false 6.52e-04, exact); the `UAE` and `EAE` spellings are
  CONTRADICTED.
- The body's first call (ILT 0x0003FA30) is 0x002A9850, confirmed as
  SpecialAbilityUpdate::triggerAbilityEffect by the landed
  ToggleMountedSpecialAbilityUpdate::triggerAbilityEffect override
  (0026c9e0-togglemounted-triggerabilityeffect.md), which makes the same call
  first. It is called by its defined row name
  `??1WeaponSetSpecialAbilityUpdate@@UAE@XZ`, as that override does.
- Boundary: SEH prologue after INT3 padding, final RET at +0x1B0; 433 bytes.
- Retail literal 0x010B77C4 is `DisguiseStarted`, passed to Drawable's
  per-unit sound lookup (ILT 0x0000FD44) and copied into a 0x70-byte
  AudioEventRTS (ILT 0x00047B27), given the owner id (+0x74) and played
  through TheAudio slot 17.

## Donor evidence (BFME 2, 59e3f8f825)
- `Code/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdate.cpp`
  `?triggerAbilityEffect@SpecialDisguiseUpdate@@UAEXXZ` (BFME 2 0x004B0653,
  431 B, matched there): same statement sequence (base call; idle-AI and
  state-1 gates; clear an active disguise and swap back; else empty the
  contain module, fade the drawable 2/0.2/0.7/2.0, set the condition, swap by
  local-player ownership, play `DisguiseStarted`).
- Differences adapted from BFME 1 retail: the disguise test is the inline
  condition-word test at Object+0x130 bit 0x800 (BFME 2 calls an isKindOf
  helper first), the AI is at +0x204 (slot 96 isIdle), contain at +0x1FC
  (slots 64/37), the local player at ThePlayerList+0x0C, and the sound lookup
  returns an AudioEventRTS pointer (BFME 2 returns a record by value).

## Structural inference
- The visual swap 0x00267B10 (ret 4, one byte) is still a dump row; it is
  called through its ILT 0x00020847 exactly as the matched Rva00267D00.cpp
  does. The sound lookup 0x00416FE0 is likewise a dump row, called through ILT
  0x0000FD44 as TurretAIOwnerAndMachine.cpp does.
