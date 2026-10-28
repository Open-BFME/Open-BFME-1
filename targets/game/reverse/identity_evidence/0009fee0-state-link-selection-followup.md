# State getter ownership: final-link follow-up

The fresh census at 4094737c79 exposed a dependency that local byte checks
cannot see. Rehoming the real State accessors to their existing emitters
moves AITNGuard/TurretAI earlier in the object sequence. No ledger rows were
reordered, and restoring the old order is not a repair.

Compared with 4e2915d862, the three intended consumers gained 1,042 linked
bytes, but 13 previously linked constructor/deleting-destructor sources
lost 474 bytes to `??_7State@@6B@`. With the getter ownership accounting
(-8 bytes from the old tiny-body TU, +4 from the preserved opaque getter),
the measured intermediate net gain was only 564 bytes. The source repairs
were not published with that regression.

## State vtable emission

TurretAI's private turretai_constructor StateMachine.h view emits a 48-byte
State vtable. Retail State constructor 000A19E0 installs 01080770, a 17-slot
(68-byte) table. In the private view, onEnter is at +8; retail has it at
+0x10. Its destructor/access spelling and pool/snapshot slots also differ.
The previously selected four-byte StateConstructor copy was unproven,
not proof of a complete retail vtable. The newly earlier TurretAI copy is
proven wrong. This distinction matters: restoring the prior classification
does not reconstruct the full State vtable.

Mark the partial constructor view `__declspec(novtable)` so its empty inline
base destructor cannot emit this wrong table. The real constructor and
destructor owners remain separate. COFF inspection confirms TurretAI no
longer defines `??_7State@@6B@`. Matched parent bodies remain exact; six
cleanup labels were rebound by retail FuncInfo unwind-state identity.

## Two non-retail method definitions

The same order change exposed these already-present wrong definitions:

- `??0TurretAI@@QAE@PAVObject@@PBVTurretAIData@@W4WhichTurretType@@@Z`:
  delete the present-unmatched ZH constructor in TurretAI.cpp. Its existing
  retail owner is TurretAI_ctor_Thunk.cpp, 0018DED0/383 bytes, identified by
  the matched AIUpdateInterface caller and TurretAI family evidence.
- `?onEnter@AITNGuardIdleState@@UAE?AW4StateReturnType@@XZ`: delete the
  present-unmatched ZH body in AITNGuard.cpp. AITNGuardIdleStateOnEnter.cpp
  owns the retail 00189C90/74-byte body with BFME machine/owner/AI offsets.
  AITNGuard now has an undefined external for this exact symbol.

The removed TurretAI constructor was the only use forcing the existing
12-byte placement-delete COMDAT at 007EFFF0. An address-taking emission
anchor retains that already-matched helper, following RankInfo.cpp's
existing pattern. The anchor is explicitly absent from retail and is not
a new match or symbol alias.

Verification: 60/60 matched rows across TurretAI, AITNGuard and the two
retail provider TUs; 11 strings, two constants, 29 DIR32 references and body
guard pass. Follow-up census validation remains required.

## Remaining vtable evidence

`??_7AIAttackFireWeaponState@@6B@` is also selected from TurretAI after the
getter ownership change. Its private 12-slot ZH view disagrees with the
17-slot table at 01097DC0 installed by the exact retail constructor
001712C0. The matched TurretStateMachine constructor inlines that vptr
store, so suppressing it or changing the constructor call shape would
change a matched parent. This needs a complete, independently supported
BFME virtual view; do not guess the remaining slot identities or move the
ledger to select another incomplete copy. It caused no additional loss of
a previously linked source in the intermediate census and remains a
reported blocker, not a claimed fix.
