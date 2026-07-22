.386
.model flat

; ??1StringInfo@@QAE@XZ
; Exact 76 retail bytes @ RVA 0x004368F0.
; Queue 0x009DB087/148 was mid-function (not a prologue). True body via deinit
; m_stringInfo ehvec_dtor (elem size 8, dtor ILT 0x1510E -> 0x4368F0):
; destroys UnicodeString@+4 then AsciiString@+0 (BFME StringInfo is 8B, no speech).
_TEXT SEGMENT
public ??1StringInfo@@QAE@XZ
??1StringInfo@@QAE@XZ PROC
    db 6Ah,0FFh,68h,0A8h,21h,02h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh,0F1h,89h,74h,24h,04h,8Dh,4Eh,04h
    db 0C7h,44h,24h,10h,00h,00h,00h,00h,0E8h,0B3h,18h,45h,00h,8Bh,0CEh,0C7h
    db 44h,24h,10h,0FFh,0FFh,0FFh,0FFh,0E8h,14h,10h,45h,00h,8Bh,4Ch,24h,08h
    db 5Eh,64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h,10h,0C3h
??1StringInfo@@QAE@XZ ENDP
_TEXT ENDS
END
