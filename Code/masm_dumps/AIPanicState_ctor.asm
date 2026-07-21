.386
.model flat

; ??0AIPanicState@@QAE@PAVStateMachine@@@Z
; Exact 82B @ 0x0017FBE0. Drift 0x00183CA7 was mid-prologue inside the already-
; matched AIAttackFollowWaypointPathState ctor (201B @ 0x00183C90; string
; "AIFollowWaypointPathState"). True body sits immediately before the
; getNameKey-style mov eax,"AIPanicState";ret @ 0x17FC50 and stores vtable
; 0x109A988 (string "AIPanicState" at vtbl+0x58). Inlines AIInternalMoveToState
; via StringBase/AsciiString(char*) @ 0x888BC0 + AIInternalMoveToState @ 0x32182
; with asGroup=false, zeros FollowWaypoint fields + m_waitFrames/m_timer at
; this+0x6c/0x70 (BFME zeros them even though ZH only does that for AIWanderState).
; Sibling pattern: AIWanderState cluster @ 0x17FB00 / AIMoveAndDeleteState_ctor.
_TEXT SEGMENT
public ??0AIPanicState@@QAE@PAVStateMachine@@@Z
??0AIPanicState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,08h,0A8h,09h,01h
    db 0E8h,0CBh,8Fh,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,81h,25h,0EBh
    db 0FFh,33h,0C0h,89h,46h,50h,89h,46h,54h,89h,46h,58h,89h,46h,5Ch,89h
    db 46h,60h,89h,46h,64h,88h,46h,68h,88h,46h,69h,89h,46h,6Ch,89h,46h
    db 70h,0C6h,46h,6Ah,01h,0C7h,06h,88h,0A9h,09h,01h,8Bh,0C6h,5Eh,59h,0C2h
    db 04h,00h
??0AIPanicState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
