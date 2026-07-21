.386
.model flat

; ??0AIAttackFireWeaponState@@QAE@PAVStateMachine@@PAVNotifyWeaponFiredInterface@@@Z
; Exact 57B @ 0x001712C0. Drift 0x0018DD06 was mid-insn inside a parent StateMachine
; ctor (inlined newInstance after operator new: add ebp,4 / jmp / xor ebp). True body
; is string-anchored on unique "AIAttackFireWeaponState" @ 0x1097e14 and builds the
; State debug-name via StringBase/AsciiString(char*) @ 0x888BC0; then State base,
; vtable 0x1097dc0, m_att@+0x24, byte@+0x28=0. Sibling: AIDeadState/AIBusyState MASM.
_TEXT SEGMENT
public ??0AIAttackFireWeaponState@@QAE@PAVStateMachine@@PAVNotifyWeaponFiredInterface@@@Z
??0AIAttackFireWeaponState@@QAE@PAVStateMachine@@PAVNotifyWeaponFiredInterface@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,14h,7Eh,09h,01h
    db 0E8h,0EBh,78h,71h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,0D1h,22h,0E9h
    db 0FFh,8Bh,4Ch,24h,10h,0C7h,06h,0C0h,7Dh,09h,01h,89h,4Eh,24h,0C6h,46h
    db 28h,00h,8Bh,0C6h,5Eh,59h,0C2h,08h,00h
??0AIAttackFireWeaponState@@QAE@PAVStateMachine@@PAVNotifyWeaponFiredInterface@@@Z ENDP
_TEXT ENDS
END
