.386
.model flat
; ?doPhaseStuff@SlowDeathBehavior@@IAEXW4SlowDeathPhaseType@@@Z
; Exact 504B @ 0x002080B0; true body via beginSlowDeath@0x20A000 + update@0x208E1E/0x208E33
; thunk 0x3BD0E; SEH; BFME 4 phase effect vecs (fx/ocl/weapon/sound); file SlowDeathBehavior.cpp
; queue 0x20A315 is INSIDE update() after beginSlowDeath
_TEXT SEGMENT
public ?doPhaseStuff@SlowDeathBehavior@@IAEXW4SlowDeathPhaseType@@@Z
?doPhaseStuff@SlowDeathBehavior@@IAEXW4SlowDeathPhaseType@@@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh,68h,0E0h,0BFh,00h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,74h,55h,8Bh,0E9h,8Bh,4Dh,04h,8Ah,81h
    db 0A4h,01h,00h,00h,84h,0C0h,0Fh,84h,0B7h,01h,00h,00h,8Bh,84h,24h,88h
    db 00h,00h,00h,8Dh,04h,40h,56h,8Dh,34h,81h,8Bh,46h,5Ch,57h,2Bh,46h
    db 58h,0C1h,0F8h,02h,85h,0C0h,7Eh,3Ah,53h,68h,17h,02h,00h,00h,68h,0E8h
    db 66h,0Ah,01h,48h,50h,6Ah,00h,0E8h,0A0h,0F9h,0E1h,0FFh,8Bh,4Eh,58h,8Bh
    db 3Ch,81h,8Bh,5Dh,08h,83h,0C4h,10h,85h,0FFh,74h,15h,8Bh,0CFh,0E8h,54h
    db 9Eh,0E0h,0FFh,84h,0C0h,75h,0Ah,6Ah,00h,53h,8Bh,0CFh,0E8h,89h,0AAh,0E1h
    db 0FFh,5Bh,8Bh,86h,8Ch,00h,00h,00h,2Bh,86h,88h,00h,00h,00h,0C1h,0F8h
    db 02h,85h,0C0h,7Eh,30h,68h,21h,02h,00h,00h,68h,0E8h,66h,0Ah,01h,48h
    db 50h,6Ah,00h,0E8h,56h,9Ah,0DFh,0FFh,8Bh,8Eh,88h,00h,00h,00h,8Bh,0Ch
    db 81h,8Bh,45h,08h,83h,0C4h,10h,85h,0C9h,74h,0Ah,6Ah,00h,6Ah,00h,50h
    db 0E8h,5Ch,0DFh,0E0h,0FFh,8Bh,86h,0BCh,00h,00h,00h,2Bh,86h,0B8h,00h,00h
    db 00h,0C1h,0F8h,02h,85h,0C0h,7Eh,37h,68h,2Bh,02h,00h,00h,68h,0E8h,66h
    db 0Ah,01h,48h,50h,6Ah,00h,0E8h,13h,9Ah,0DFh,0FFh,8Bh,8Eh,0B8h,00h,00h
    db 00h,8Bh,04h,81h,83h,0C4h,10h,85h,0C0h,74h,14h,8Bh,4Dh,08h,8Dh,51h
    db 38h,52h,51h,8Bh,0Dh,38h,0F7h,2Eh,01h,50h,0E8h,9Fh,0DCh,0E2h,0FFh,8Bh
    db 86h,0ECh,00h,00h,00h,2Bh,86h,0E8h,00h,00h,00h,0C1h,0F8h,02h,85h,0C0h
    db 0Fh,8Eh,0BBh,00h,00h,00h,68h,38h,02h,00h,00h,68h,0E8h,66h,0Ah,01h
    db 48h,50h,6Ah,00h,0E8h,0C3h,0F8h,0E1h,0FFh,8Bh,0B6h,0E8h,00h,00h,00h,8Bh
    db 04h,86h,83h,0C4h,10h,85h,0C0h,89h,44h,24h,0Ch,74h,0Eh,83h,0C0h,04h
    db 50h,0FFh,15h,5Ch,8Eh,35h,01h,8Bh,44h,24h,0Ch,85h,0C0h,0C7h,84h,24h
    db 88h,00h,00h,00h,00h,00h,00h,00h,74h,4Ch,8Bh,0Dh,68h,0D6h,2Eh,01h
    db 85h,0C9h,74h,42h,8Bh,45h,08h,8Bh,40h,74h,50h,8Dh,44h,24h,10h,50h
    db 8Dh,4Ch,24h,18h,0E8h,4Dh,0Ch,0E0h,0FFh,8Bh,0Dh,68h,0D6h,2Eh,01h,8Bh
    db 11h,8Dh,44h,24h,10h,50h,0C6h,84h,24h,8Ch,00h,00h,00h,01h,0FFh,52h
    db 44h,8Dh,4Ch,24h,10h,0C6h,84h,24h,88h,00h,00h,00h,00h,0E8h,0D3h,0ECh
    db 0E1h,0FFh,8Bh,44h,24h,0Ch,85h,0C0h,0C7h,84h,24h,88h,00h,00h,00h,0FFh
    db 0FFh,0FFh,0FFh,74h,1Ch,8Bh,0F0h,83h,0C0h,04h,50h,0FFh,15h,54h,8Eh,35h
    db 01h,85h,0C0h,7Fh,0Ch,85h,0F6h,74h,08h,8Bh,16h,6Ah,01h,8Bh,0CEh,0FFh
    db 12h,5Fh,5Eh,8Bh,4Ch,24h,78h,5Dh,64h,89h,0Dh,00h,00h,00h,00h,81h
    db 0C4h,80h,00h,00h,00h,0C2h,04h,00h
?doPhaseStuff@SlowDeathBehavior@@IAEXW4SlowDeathPhaseType@@@Z ENDP
_TEXT ENDS
END
