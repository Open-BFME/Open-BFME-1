.386
.model flat

; ??0AIMoveAndEvacuateState@@QAE@PAVStateMachine@@@Z
; Exact 57B @ 0x0017FD10. Drift 0x00186048 was mid-instruction inside
; AIStateMachine ctor (inlined newInstance sequence after operator new).
; True body is string-anchored on "AIMoveAndEvacuateState" and builds the
; debug-name via StringBase/AsciiString(char*) @ 0x888BC0, then
; AIInternalMoveToState(StateMachine*, AsciiString) @ 0x32182, stores
; vtable @ 0x109AA60, and zeros m_origin (Coord3D) at this+0x50/54/58.
; Sibling pattern: AIMoveAndDeleteState_ctor.asm / AIBusyState_ctor.asm.
_TEXT SEGMENT
public ??0AIMoveAndEvacuateState@@QAE@PAVStateMachine@@@Z
??0AIMoveAndEvacuateState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,0B8h,0AAh,09h,01h
    db 0E8h,9Bh,8Eh,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,51h,24h,0EBh
    db 0FFh,33h,0C0h,0C7h,06h,60h,0AAh,09h,01h,89h,46h,50h,89h,46h,54h,89h
    db 46h,58h,8Bh,0C6h,5Eh,59h,0C2h,04h,00h
??0AIMoveAndEvacuateState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
