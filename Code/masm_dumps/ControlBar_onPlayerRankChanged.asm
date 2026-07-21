.386
.model flat

; ?onPlayerRankChanged@ControlBar@@QAEXPBVPlayer@@@Z
; Exact 111 retail bytes @ RVA 0x0049DC90
; Drift queue had wrong RVA 0x00C6C40A (epilogue/padding); real body is string-anchored
; on "ControlBarArrow" (twin: onPlayerSciencePurchasePointsChanged @ 0x0049DD20).
_TEXT SEGMENT
public ?onPlayerRankChanged@ControlBar@@QAEXPBVPlayer@@@Z
?onPlayerRankChanged@ControlBar@@QAEXPBVPlayer@@@Z PROC
    db 56h,8Bh,0F1h,8Bh,4Ch,24h,08h,0E8h,0DBh,5Bh,0B7h,0FFh,84h,0C0h,74h,5Bh
    db 0A1h,48h,0D7h,2Eh,01h,8Bh,40h,0Ch,8Bh,80h,64h,02h,00h,00h,39h,86h
    db 0CCh,02h,00h,00h,7Fh,3Ah,0A1h,30h,33h,2Fh,01h,85h,0C0h,74h,31h,0A1h
    db 8Ch,14h,2Fh,01h,8Ah,48h,0Dh,84h,0C9h,74h,25h,8Ah,48h,0Eh,84h,0C9h
    db 74h,1Eh,6Ah,00h,51h,89h,64h,24h,10h,8Bh,0CCh,68h,0B4h,0B8h,0Fh,01h
    db 0E8h,0DBh,0AEh,3Eh,00h,8Bh,0Dh,30h,33h,2Fh,01h,0E8h,38h,7Fh,0BAh,0FFh
    db 0B0h,01h,88h,86h,0C8h,02h,00h,00h,88h,46h,24h,5Eh,0C2h,04h,00h
?onPlayerRankChanged@ControlBar@@QAEXPBVPlayer@@@Z ENDP
_TEXT ENDS
END
