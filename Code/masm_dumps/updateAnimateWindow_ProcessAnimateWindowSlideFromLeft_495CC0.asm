.386
.model flat

; ?updateAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
; Exact 230 retail bytes @ 0x00495CC0
; Identity: SlideFromLeft ctor @0x495AC0 stores vtbl 0x10FA270; slot3 ILT 0x2C1DD -> this body.
; Semantics: timeGetTime vs startTime, win null, getVel, slide x toward endPos,
; slowDownThreshold*ratio, clamp vel.x>=1.0f via fcom pool, setCurPos/setVel/winSetPosition.
; Queue 0x9DE7CE was mid-fn rdtsc (misplaced); C++ blocked stack frame 0x10 vs 0xc +
; win spill + x87 fcom-mem clamp (same residual as SlideFromTop update attempt).
_TEXT SEGMENT
public ?updateAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
?updateAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z PROC
    db 83h,0ECh,10h,56h,8Bh,74h,24h,18h,85h,0F6h,89h,4Ch,24h,04h,74h,07h
    db 8Ah,46h,41h,84h,0C0h,74h,09h,0B0h,01h,5Eh,83h,0C4h,10h,0C2h,04h,00h
    db 57h,8Bh,7Eh,34h,0E8h,0FBh,24h,0BBh,0FFh,3Bh,0C7h,73h,0Ah,5Fh,32h,0C0h
    db 5Eh,83h,0C4h,10h,0C2h,04h,00h,8Bh,46h,28h,85h,0C0h,89h,44h,24h,1Ch
    db 75h,0Ah,5Fh,0B0h,01h,5Eh,83h,0C4h,10h,0C2h,04h,00h,8Bh,46h,14h,8Bh
    db 7Eh,18h,53h,8Bh,5Eh,10h,55h,8Bh,6Eh,1Ch,8Dh,4Ch,24h,18h,51h,8Bh
    db 0CEh,89h,44h,24h,20h,0E8h,1Eh,88h,0B7h,0FFh,0D9h,44h,24h,18h,0E8h,05h
    db 11h,56h,00h,03h,0F8h,3Bh,0FBh,7Eh,0Fh,5Dh,5Bh,0B0h,01h,5Fh,88h,46h
    db 41h,5Eh,83h,0C4h,10h,0C2h,04h,00h,8Bh,4Ch,24h,24h,55h,57h,0E8h,4Ah
    db 37h,0B8h,0FFh,0D9h,44h,24h,18h,8Bh,44h,24h,10h,89h,7Eh,18h,89h,6Eh
    db 1Ch,8Bh,48h,0Ch,2Bh,0DFh,3Bh,0D9h,7Fh,03h,0D8h,48h,10h,0D8h,15h,34h
    db 53h,07h,01h,0DFh,0E0h,0F6h,0C4h,05h,7Ah,08h,0DDh,0D8h,0D9h,05h,34h,53h
    db 07h,01h,8Bh,54h,24h,1Ch,0D9h,5Ch,24h,10h,8Bh,44h,24h,10h,5Dh,5Bh
    db 8Bh,0CAh,89h,46h,2Ch,5Fh,89h,4Eh,30h,89h,54h,24h,08h,32h,0C0h,5Eh
    db 83h,0C4h,10h,0C2h,04h,00h
?updateAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z ENDP
_TEXT ENDS
END
