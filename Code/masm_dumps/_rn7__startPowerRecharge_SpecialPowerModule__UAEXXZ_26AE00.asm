.386
.model flat
; ?startPowerRecharge@SpecialPowerModule@@UAEXXZ
; Exact 112B @ 0x26AE00; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?startPowerRecharge@SpecialPowerModule@@UAEXXZ
?startPowerRecharge@SpecialPowerModule@@UAEXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 0E0h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 5Fh, 8Bh, 4Fh
    db 0E4h, 85h, 0C9h, 74h, 58h, 53h, 0E8h, 09h, 5Ah, 0DBh, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 74h
    db 4Bh, 8Bh, 76h, 08h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Eh, 8Bh, 48h, 04h, 85h, 0C9h
    db 74h, 09h, 0E8h, 2Ah, 0DEh, 0DDh, 0FFh, 0EBh, 02h, 8Bh, 0C6h, 8Ah, 88h, 15h, 01h, 00h
    db 00h, 84h, 0C9h, 74h, 0Ch, 56h, 8Bh, 0CBh, 0E8h, 1Ah, 0C0h, 0DCh, 0FFh, 5Bh, 5Fh, 5Eh
    db 0C3h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 17h, 8Bh, 70h, 3Ch, 8Bh, 0CFh, 0FFh, 52h, 18h
    db 8Bh, 0C8h, 0E8h, 22h, 95h, 0DBh, 0FFh, 03h, 0C6h, 89h, 47h, 04h, 5Bh, 5Fh, 5Eh, 0C3h
?startPowerRecharge@SpecialPowerModule@@UAEXXZ ENDP
_TEXT ENDS
END
