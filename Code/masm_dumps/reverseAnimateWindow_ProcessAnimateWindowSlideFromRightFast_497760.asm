.386
.model flat

; ?reverseAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z
; Exact 260 retail bytes @ 0x00497760
; Identity: SlideFromRightFast ctor @0x4973C0 stores vtbl 0x10FA2E0; slot4 ILT 0x27D40 -> this body.
; Semantics: reverse x-slide (startTime/timeGetTime, getVel, curPos.x+=vel.x, clamp to startPos.x,
;   winSetPosition, speedUp/maxVel clamp, setVel). Queue 0x4AB1E9 is mid-function junk (fadd/fmul),
;   not a function ENTRY. C++ near-match blocked (246B vs 260B): frame 0x14 vs 0x18 + x87 shape.
_TEXT SEGMENT
public ?reverseAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z
?reverseAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z PROC
    db 83h,0ECh,18h,56h,8Bh,74h,24h,20h,85h,0F6h,89h,4Ch,24h,04h,74h,07h
    db 8Ah,46h,41h,84h,0C0h,74h,09h,0B0h,01h,5Eh,83h,0C4h,18h,0C2h,04h,00h
    db 57h,8Bh,7Eh,34h,0E8h,5Bh,0Ah,0BBh,0FFh,3Bh,0C7h,73h,0Ah,5Fh,32h,0C0h
    db 5Eh,83h,0C4h,18h,0C2h,04h,00h,55h,8Bh,6Eh,28h,85h,0EDh,75h,0Bh,5Dh
    db 5Fh,0B0h,01h,5Eh,83h,0C4h,18h,0C2h,04h,00h,8Bh,4Eh,0Ch,8Bh,46h,08h
    db 8Bh,7Eh,18h,53h,8Bh,5Eh,1Ch,8Dh,54h,24h,18h,89h,4Ch,24h,24h,52h
    db 8Bh,0CEh,89h,44h,24h,24h,0E8h,7Dh,6Dh,0B7h,0FFh,0D9h,44h,24h,18h,0E8h
    db 64h,0F6h,55h,00h,03h,0F8h,8Bh,44h,24h,20h,3Bh,0F8h,8Bh,0CDh,53h,7Eh
    db 16h,50h,0C6h,46h,41h,01h,0E8h,0B2h,1Ch,0B8h,0FFh,5Bh,5Dh,5Fh,0B0h,01h
    db 5Eh,83h,0C4h,18h,0C2h,04h,00h,57h,0E8h,0A0h,1Ch,0B8h,0FFh,8Bh,46h,10h
    db 8Bh,4Eh,14h,89h,7Eh,18h,2Bh,0F8h,8Bh,44h,24h,10h,89h,5Eh,1Ch,89h
    db 4Ch,24h,24h,3Bh,78h,0Ch,7Fh,09h,0D9h,44h,24h,18h,0D8h,48h,14h,0EBh
    db 05h,0D9h,40h,04h,0D9h,0E0h,0D9h,40h,04h,0D9h,0E0h,0D9h,5Ch,24h,2Ch,0D8h
    db 54h,24h,2Ch,0DFh,0E0h,0F6h,0C4h,41h,75h,06h,0DDh,0D8h,0D9h,44h,24h,2Ch
    db 8Bh,54h,24h,1Ch,0D9h,5Ch,24h,10h,8Bh,44h,24h,10h,5Bh,5Dh,8Bh,0CAh
    db 89h,46h,2Ch,5Fh,89h,4Eh,30h,89h,54h,24h,08h,32h,0C0h,5Eh,83h,0C4h
    db 18h,0C2h,04h,00h
?reverseAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z ENDP
_TEXT ENDS
END
