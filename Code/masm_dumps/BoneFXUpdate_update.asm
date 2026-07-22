.386
.model flat

; ?update@BoneFXUpdate@@UAE?AW4UpdateSleepTime@@XZ
; Exact 467 retail bytes @ 0x00289580; queue RVA was off-by-one (0x289581); body after int3 pad.
; Identity: calls matched initTimes@BoneFXUpdate@0x2F775; three FX/OCL/PS bone loops; ret UpdateSleepTime=1.
_TEXT SEGMENT
public ?update@BoneFXUpdate@@UAE?AW4UpdateSleepTime@@XZ
?update@BoneFXUpdate@@UAE?AW4UpdateSleepTime@@XZ PROC
    db 83h, 0ECh, 08h, 0A1h, 98h, 08h, 2Fh, 01h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 48h, 3Ch
    db 8Ah, 86h, 24h, 06h, 00h, 00h, 84h, 0C0h, 8Bh, 6Eh, 0F4h, 57h, 89h, 4Ch, 24h, 10h
    db 75h, 0Fh, 8Dh, 4Eh, 0F0h, 0E8h, 0CBh, 61h, 0DAh, 0FFh, 0C6h, 86h, 24h, 06h, 00h, 00h
    db 01h, 33h, 0DBh, 8Bh, 96h, 1Ch, 06h, 00h, 00h, 8Dh, 04h, 0D3h, 8Bh, 4Ch, 86h, 1Ch
    db 83h, 0F9h, 0FFh, 74h, 65h, 3Bh, 4Ch, 24h, 10h, 7Fh, 5Fh, 8Dh, 0Ch, 40h, 8Dh, 94h
    db 8Eh, 9Ch, 01h, 00h, 00h, 8Dh, 04h, 0C0h, 8Bh, 4Ch, 85h, 2Ch, 52h, 51h, 8Dh, 4Eh
    db 0F0h, 0E8h, 88h, 59h, 0DAh, 0FFh, 8Bh, 96h, 1Ch, 06h, 00h, 00h, 8Dh, 3Ch, 0D3h, 8Dh
    db 04h, 0FFh, 8Ah, 4Ch, 85h, 28h, 84h, 0C9h, 8Dh, 44h, 85h, 0Ch, 74h, 0Ah, 0C7h, 44h
    db 0BEh, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0EBh, 22h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h
    db 3Ch, 8Dh, 48h, 10h, 89h, 54h, 24h, 14h, 0E8h, 0AFh, 0F2h, 0D8h, 0FFh, 0E8h, 16h, 0D8h
    db 76h, 00h, 03h, 44h, 24h, 14h, 89h, 44h, 0BEh, 1Ch, 8Bh, 86h, 1Ch, 06h, 00h, 00h
    db 8Dh, 04h, 0C3h, 8Bh, 8Ch, 86h, 9Ch, 00h, 00h, 00h, 83h, 0F9h, 0FFh, 74h, 74h, 3Bh
    db 4Ch, 24h, 10h, 7Fh, 6Eh, 8Dh, 0Ch, 40h, 8Dh, 94h, 8Eh, 1Ch, 03h, 00h, 00h, 8Dh
    db 04h, 0C0h, 8Bh, 8Ch, 85h, 0B0h, 04h, 00h, 00h, 52h, 51h, 8Dh, 4Eh, 0F0h, 0E8h, 90h
    db 1Bh, 0D9h, 0FFh, 8Bh, 96h, 1Ch, 06h, 00h, 00h, 8Dh, 3Ch, 0D3h, 8Dh, 04h, 0FFh, 8Ah
    db 8Ch, 85h, 0ACh, 04h, 00h, 00h, 84h, 0C9h, 8Dh, 84h, 85h, 90h, 04h, 00h, 00h, 74h
    db 0Dh, 0C7h, 84h, 0BEh, 9Ch, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0EBh, 25h, 8Bh, 0Dh
    db 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 8Dh, 48h, 10h, 89h, 54h, 24h, 14h, 0E8h, 29h
    db 0F2h, 0D8h, 0FFh, 0E8h, 90h, 0D7h, 76h, 00h, 03h, 44h, 24h, 14h, 89h, 84h, 0BEh, 9Ch
    db 00h, 00h, 00h, 8Bh, 86h, 1Ch, 06h, 00h, 00h, 8Dh, 04h, 0C3h, 8Bh, 8Ch, 86h, 1Ch
    db 01h, 00h, 00h, 83h, 0F9h, 0FFh, 74h, 74h, 3Bh, 4Ch, 24h, 10h, 7Fh, 6Eh, 8Dh, 0Ch
    db 40h, 8Dh, 94h, 8Eh, 9Ch, 04h, 00h, 00h, 8Dh, 04h, 0C0h, 8Bh, 8Ch, 85h, 34h, 09h
    db 00h, 00h, 52h, 51h, 8Dh, 4Eh, 0F0h, 0E8h, 34h, 0FDh, 0D8h, 0FFh, 8Bh, 96h, 1Ch, 06h
    db 00h, 00h, 8Dh, 3Ch, 0D3h, 8Dh, 04h, 0FFh, 8Ah, 8Ch, 85h, 30h, 09h, 00h, 00h, 84h
    db 0C9h, 8Dh, 84h, 85h, 14h, 09h, 00h, 00h, 74h, 0Dh, 0C7h, 84h, 0BEh, 1Ch, 01h, 00h
    db 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0EBh, 25h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch
    db 8Dh, 48h, 04h, 89h, 54h, 24h, 14h, 0E8h, 89h, 40h, 0D8h, 0FFh, 0E8h, 07h, 0D7h, 76h
    db 00h, 03h, 44h, 24h, 14h, 89h, 84h, 0BEh, 1Ch, 01h, 00h, 00h, 43h, 83h, 0FBh, 08h
    db 0Fh, 8Ch, 6Dh, 0FEh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 83h
    db 0C4h, 08h, 0C3h
?update@BoneFXUpdate@@UAE?AW4UpdateSleepTime@@XZ ENDP
_TEXT ENDS
END
