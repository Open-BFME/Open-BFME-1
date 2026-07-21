.386
.model flat

; ??0AIIdleState@@QAE@PAVStateMachine@@W4AIIdleTargetingType@0@@Z
; Exact 71B @ 0x00180320. Drift 0x186B04 was mid-insn inside AIStateMachine
; ctor (inlined newInstance: c6 44 24 20 39 ...). True body is string-anchored
; on "AIIdleState" @ VA 0x1098604 (standalone ENTRY after int3 pad). Builds the
; State debug-name via StringBase/AsciiString(char*) @ 0x888BC0, base State@0x35B2,
; stores vtable 0x109AD20 (same as AIStateMachine inlined AI_IDLE path), then
; m_inited=0 @+0x27, byte@+0x2c=0, byte@+0x26=1, m_initialSleepOffset=-1 @+0x24,
; and raw AIIdleTargetingType enum @+0x28. ret 8 (machine + targeting). Sibling:
; AIBusyState_ctor.asm / AIDeadState_ctor.asm / FailureState_ctor.asm.
_TEXT SEGMENT
public ??0AIIdleState@@QAE@PAVStateMachine@@W4AIIdleTargetingType@0@@Z
??0AIIdleState@@QAE@PAVStateMachine@@W4AIIdleTargetingType@0@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,04h,86h,09h,01h
    db 0E8h,8Bh,88h,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,71h,32h,0E8h
    db 0FFh,8Bh,4Ch,24h,10h,32h,0C0h,88h,46h,27h,88h,46h,2Ch,0C6h,46h,26h
    db 01h,66h,0C7h,46h,24h,0FFh,0FFh,0C7h,06h,20h,0ADh,09h,01h,89h,4Eh,28h
    db 8Bh,0C6h,5Eh,59h,0C2h,08h,00h
??0AIIdleState@@QAE@PAVStateMachine@@W4AIIdleTargetingType@0@@Z ENDP
_TEXT ENDS
END
