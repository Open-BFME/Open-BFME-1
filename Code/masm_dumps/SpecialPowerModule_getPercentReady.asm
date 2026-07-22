.386
.model flat
; ?getPercentReady@SpecialPowerModule@@UBEMXZ
; Exact 210B @ 0x00268A90; queue 0x002A98AF was INSIDE FUN_006a9850 (9219B)
; Identity: interface-this [esi-0xc] like getRequiredScience@0x268A30;
; isReady vcall [eax+4]; pausedCount+8/pausedPercent+10; isSharedNSync@0x268920;
; percent = 1.0 - (readyFrame-frame)/reloadTime; +0x14 BFME flag returns 0.0
_TEXT SEGMENT
public ?getPercentReady@SpecialPowerModule@@UBEMXZ
?getPercentReady@SpecialPowerModule@@UBEMXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 8Ah, 46h, 14h, 84h, 0C0h, 74h, 0Bh, 0D9h, 05h, 50h
    db 53h, 07h, 01h, 5Eh, 83h, 0C4h, 08h, 0C3h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 04h, 84h
    db 0C0h, 74h, 0Bh, 0D9h, 05h, 34h, 53h, 07h, 01h, 5Eh, 83h, 0C4h, 08h, 0C3h, 8Bh, 46h
    db 08h, 85h, 0C0h, 7Eh, 08h, 0D9h, 46h, 10h, 5Eh, 83h, 0C4h, 08h, 0C3h, 55h, 8Bh, 6Eh
    db 0F4h, 8Bh, 45h, 08h, 85h, 0C0h, 75h, 0Ch, 0D9h, 05h, 50h, 53h, 07h, 01h, 5Dh, 5Eh
    db 83h, 0C4h, 08h, 0C3h, 8Bh, 4Eh, 0F8h, 85h, 0C9h, 57h, 8Bh, 7Eh, 04h, 74h, 2Ah, 53h
    db 0E8h, 2Fh, 7Dh, 0DBh, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 74h, 1Dh, 8Bh, 4Dh, 08h, 0E8h, 0ABh
    db 0BDh, 0D9h, 0FFh, 84h, 0C0h, 74h, 11h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 18h, 50h, 8Bh
    db 0CBh, 0E8h, 19h, 0A5h, 0DAh, 0FFh, 8Bh, 0F8h, 5Bh, 0A1h, 98h, 08h, 2Fh, 01h, 2Bh, 78h
    db 3Ch, 85h, 0FFh, 89h, 7Ch, 24h, 0Ch, 0DBh, 44h, 24h, 0Ch, 7Dh, 06h, 0D8h, 05h, 58h
    db 53h, 07h, 01h, 8Bh, 4Dh, 08h, 0D9h, 5Ch, 24h, 0Ch, 0E8h, 4Ah, 0B8h, 0DBh, 0FFh, 85h
    db 0C0h, 89h, 44h, 24h, 10h, 0DBh, 44h, 24h, 10h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h
    db 01h, 0D8h, 7Ch, 24h, 0Ch, 5Fh, 5Dh, 5Eh, 0D8h, 2Dh, 34h, 53h, 07h, 01h, 83h, 0C4h
    db 08h, 0C3h
?getPercentReady@SpecialPowerModule@@UBEMXZ ENDP
_TEXT ENDS
END
