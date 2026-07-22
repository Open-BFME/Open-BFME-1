.386
.model flat

; ?evaluateSoloNexus@InGameUI@@IAEXPAVDrawable@@@Z
; Exact 213 retail bytes @ RVA 0x00444340; true body (queue 0x007B54F9 was mid-fn float noise)
; Callers: selectDrawable@0x4463EC / deselectDrawable@0x4464F1 via ILT thunk 0x35968
; Solo field m_soloNexusSelectedDrawableID @ this+0x13A4; getter @ 0x44B370
_TEXT SEGMENT
public ?evaluateSoloNexus@InGameUI@@IAEXPAVDrawable@@@Z
?evaluateSoloNexus@InGameUI@@IAEXPAVDrawable@@@Z PROC
    db 8Bh,44h,24h,04h,55h,56h,57h,33h,0FFh,3Bh,0C7h,8Bh,0E9h,89h,0BDh,0A4h
    db 13h,00h,00h,74h,28h,8Bh,0B0h,0FCh,00h,00h,00h,3Bh,0F7h,74h,1Eh,6Ah
    db 2Eh,8Bh,0CEh,0E8h,0B7h,0E1h,0BEh,0FFh,84h,0C0h,75h,11h,6Ah,2Fh,8Bh,0CEh
    db 0E8h,0AAh,0E1h,0BEh,0FFh,84h,0C0h,0Fh,84h,92h,00h,00h,00h,8Bh,45h,18h
    db 53h,8Bh,18h,3Bh,0D8h,89h,7Ch,24h,14h,0Fh,84h,7Fh,00h,00h,00h,90h
    db 8Bh,7Bh,08h,8Bh,0B7h,0FCh,00h,00h,00h,85h,0F6h,74h,59h,8Bh,46h,04h
    db 85h,0C0h,74h,0Ch,8Bh,48h,04h,85h,0C9h,74h,05h,0E8h,0Bh,0DFh,0BBh,0FFh
    db 8Bh,88h,0CCh,00h,00h,00h,0F6h,0C5h,40h,74h,1Eh,8Bh,44h,24h,14h,40h
    db 66h,3Dh,01h,00h,89h,44h,24h,14h,75h,3Ah,8Bh,0CFh,0E8h,30h,57h,0BCh
    db 0FFh,89h,85h,0A4h,13h,00h,00h,0EBh,1Dh,8Bh,46h,04h,85h,0C0h,74h,0Ch
    db 8Bh,48h,04h,85h,0C9h,74h,05h,0E8h,0CFh,0DEh,0BBh,0FFh,8Bh,88h,0CCh,00h
    db 00h,00h,84h,0EDh,79h,0Eh,8Bh,1Bh,3Bh,5Dh,18h,75h,93h,5Bh,5Fh,5Eh
    db 5Dh,0C2h,04h,00h,0C7h,85h,0A4h,13h,00h,00h,00h,00h,00h,00h,5Bh,5Fh
    db 5Eh,5Dh,0C2h,04h,00h
?evaluateSoloNexus@InGameUI@@IAEXPAVDrawable@@@Z ENDP
_TEXT ENDS
END
