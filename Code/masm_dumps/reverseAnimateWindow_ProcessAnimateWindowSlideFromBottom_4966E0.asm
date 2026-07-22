.386
.model flat

; ?reverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z
; Exact 263 retail bytes @ 0x004966E0
; Identity: SlideFromBottom ctor @0x4963B0 stores vtbl VA 0x10FA2A8 (RVA 0xCFA2A8);
;   slot3=update@0x4965B0, slot4=reverse@0x4966E0 (this body). Queue 0x4965B0 was update.
; Semantics: delay gate, win null, curPos.y+=vel.y, finish if curPos.y>startPos.y,
;   else set pos/cur, speedUp or -m_maxVel.y, clamp vel.y to -m_maxVel.y.
; C++ blocked: startPos y-then-x spill before getVel + fcom-mem clamp + setVel y/x store order
;   (compiled 249B, first 0x4A bytes match then diverge).
_TEXT SEGMENT
public ?reverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z
?reverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z PROC
    db 83h,0ECh,14h,56h,8Bh,74h,24h,1Ch,85h,0F6h,89h,4Ch,24h,04h,74h,07h
    db 8Ah,46h,41h,84h,0C0h,74h,09h,0B0h,01h,5Eh,83h,0C4h,14h,0C2h,04h,00h
    db 57h,8Bh,7Eh,34h,0E8h,0DBh,1Ah,0BBh,0FFh,3Bh,0C7h,73h,0Ah,5Fh,32h,0C0h
    db 5Eh,83h,0C4h,14h,0C2h,04h,00h,55h,8Bh,6Eh,28h,85h,0EDh,75h,0Bh,5Dh
    db 5Fh,0B0h,01h,5Eh,83h,0C4h,14h,0C2h,04h,00h,8Bh,4Eh,0Ch,8Bh,46h,08h
    db 8Bh,7Eh,1Ch,53h,8Bh,5Eh,18h,8Dh,54h,24h,14h,89h,4Ch,24h,20h,52h
    db 8Bh,0CEh,89h,44h,24h,20h,0E8h,0FDh,7Dh,0B7h,0FFh,0D9h,44h,24h,18h,0E8h
    db 0E4h,06h,56h,00h,03h,0F8h,8Bh,44h,24h,20h,3Bh,0F8h,8Bh,0CDh,7Eh,17h
    db 50h,53h,0C6h,46h,41h,01h,0E8h,32h,2Dh,0B8h,0FFh,5Bh,5Dh,5Fh,0B0h,01h
    db 5Eh,83h,0C4h,14h,0C2h,04h,00h,57h,53h,0E8h,1Fh,2Dh,0B8h,0FFh,8Bh,46h
    db 10h,8Bh,56h,14h,89h,44h,24h,1Ch,8Bh,44h,24h,10h,89h,7Eh,1Ch,89h
    db 5Eh,18h,8Bh,48h,0Ch,2Bh,0FAh,3Bh,0F9h,7Fh,09h,0D9h,44h,24h,18h,0D8h
    db 48h,14h,0EBh,05h,0D9h,40h,08h,0D9h,0E0h,0D9h,40h,08h,0D9h,0E0h,0D9h,5Ch
    db 24h,28h,0D8h,54h,24h,28h,0DFh,0E0h,0F6h,0C4h,41h,75h,06h,0DDh,0D8h,0D9h
    db 44h,24h,28h,8Bh,4Ch,24h,14h,0D9h,5Ch,24h,18h,8Bh,44h,24h,18h,5Bh
    db 5Dh,8Bh,0D1h,89h,46h,30h,5Fh,89h,56h,2Ch,89h,4Ch,24h,08h,32h,0C0h
    db 5Eh,83h,0C4h,14h,0C2h,04h,00h
?reverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z ENDP
_TEXT ENDS
END
