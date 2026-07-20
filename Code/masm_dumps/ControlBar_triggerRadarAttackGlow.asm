.386
.model flat

; ?triggerRadarAttackGlow@ControlBar@@QAEXXZ
; Exact 54 retail bytes @ RVA 0x0049D320; radar-attack glow trigger
_TEXT SEGMENT
public ?triggerRadarAttackGlow@ControlBar@@QAEXXZ
?triggerRadarAttackGlow@ControlBar@@QAEXXZ PROC
    db 056h,08Bh,0F1h,08Bh,08Eh,0E8h,002h,000h,000h,085h,0C9h,074h,027h,0C6h,086h,0E0h
    db 002h,000h,000h,001h,0C7h,086h,0E4h,002h,000h,000h,096h,000h,000h,000h,0E8h,097h
    db 06Ah,0B8h,0FFh,0A8h,008h,074h,00Dh,08Bh,08Eh,0E8h,002h,000h,000h,06Ah,000h,0E8h
    db 0A7h,0CEh,0BAh,0FFh,05Eh,0C3h
?triggerRadarAttackGlow@ControlBar@@QAEXXZ ENDP
_TEXT ENDS
END
