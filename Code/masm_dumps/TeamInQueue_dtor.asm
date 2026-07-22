.386
.model flat
; ??1TeamInQueue@@MAE@XZ
; Exact 112B @ 0x00160ED0. Identity: vtable 0x1096940 precedes "TeamInQueue" string;
; scalar-deleting dtor 0x161260 -> ILT 0x2C1B5 -> this body; m_team@+0x1c matches
; disband@0x161A60; tears down work-order list, inlines Team::setActive, clears m_workOrders.
_TEXT SEGMENT
public ??1TeamInQueue@@MAE@XZ
??1TeamInQueue@@MAE@XZ PROC
    db 6Ah,0FFh,68h,0D8h,53h,00h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,53h,56h,8Bh,0F1h,89h,74h,24h,08h,0C7h,06h
    db 40h,69h,09h,01h,8Bh,4Eh,14h,33h,0DBh,3Bh,0CBh,89h,5Ch,24h,14h,74h
    db 11h,57h,8Bh,01h,8Bh,79h,0Ch,6Ah,01h,0FFh,10h,3Bh,0FBh,8Bh,0CFh,75h
    db 0F1h,5Fh,8Bh,46h,1Ch,3Bh,0C3h,74h,0Dh,38h,58h,31h,75h,08h,0C6h,40h
    db 32h,01h,0C6h,40h,31h,01h,8Bh,4Ch,24h,0Ch,89h,5Eh,14h,0C7h,06h,44h
    db 37h,07h,01h,5Eh,5Bh,64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h,10h,0C3h
??1TeamInQueue@@MAE@XZ ENDP
_TEXT ENDS
END
