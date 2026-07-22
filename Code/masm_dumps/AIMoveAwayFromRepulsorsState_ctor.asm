.386
.model flat

; ??0AIMoveAwayFromRepulsorsState@@QAE@PAVStateMachine@@@Z
; Exact 54B @ 0x0017F450. Drift 0x185C69 was mid-instruction (bytes 64 24 18
; are the tail of prior insn inside AIStateMachine inlined newInstance/SEH).
; True body string-anchored on "AIMoveAwayFromRepulsors" @ VA 0x109a3c0
; (push at 0x17F45C), builds State debug-name via StringBase/AsciiString(char*)
; @ 0x888BC0, then base AIMoveAndTightenState(machine,name) via ILT 0x32182
; (->0x14F280), zeros m_okToRepathTimes@+0x50 + m_checkForPath@+0x54, stores
; own vtable VA 0x109a368 (slot4 thunk -> onEnter@0x173D50 already matched).
; Sibling: AIDockState_ctor.asm / AIAttackAreaState_ctor.asm.
_TEXT SEGMENT
public ??0AIMoveAwayFromRepulsorsState@@QAE@PAVStateMachine@@@Z
??0AIMoveAwayFromRepulsorsState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,0C0h,0A3h,09h,01h
    db 0E8h,5Bh,97h,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,11h,2Dh,0EBh
    db 0FFh,33h,0C0h,88h,46h,54h,89h,46h,50h,0C7h,06h,68h,0A3h,09h,01h,8Bh
    db 0C6h,5Eh,59h,0C2h,04h,00h
??0AIMoveAwayFromRepulsorsState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
