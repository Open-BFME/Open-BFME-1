.386
.model flat

; ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ
; Exact 95B @ 0x007AEA90; true body (drift 0xC4D39D was int3 pad+COMDAT thunks)
; BFME rewrite: mark node+4=1, next@+0xD4, list heads this+0xC/+4/+8
_TEXT SEGMENT
public ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ
?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ PROC
    db 08Bh,041h,00Ch,033h,0D2h,03Bh,0C2h,053h,089h,051h,00Ch,0B3h,001h,074h,00Eh,090h
    db 088h,058h,004h,08Bh,080h,0D4h,000h,000h,000h,03Bh,0C2h,075h,0F3h,08Bh,041h,004h
    db 03Bh,0C2h,089h,051h,004h,074h,016h,0EBh,007h,08Dh,0A4h,024h,000h,000h,000h,000h
    db 088h,058h,004h,08Bh,080h,0D4h,000h,000h,000h,03Bh,0C2h,075h,0F3h,08Bh,041h,008h
    db 03Bh,0C2h,089h,051h,008h,074h,016h,0EBh,007h,08Dh,0A4h,024h,000h,000h,000h,000h
    db 088h,058h,004h,08Bh,080h,0D4h,000h,000h,000h,03Bh,0C2h,075h,0F3h,05Bh,0C3h
?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ ENDP
_TEXT ENDS
END
