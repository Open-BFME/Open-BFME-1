.386
.model flat
; ?Get_DX8_Render_State_Name@DX8Wrapper@@SAPBDK@Z
; Exact 673B @ 0x00873DA0; Open-BFME4
_TEXT SEGMENT
public ?Get_DX8_Render_State_Name@DX8Wrapper@@SAPBDK@Z
?Get_DX8_Render_State_Name@DX8Wrapper@@SAPBDK@Z PROC
    db 55h, 8Bh, 0ECh, 83h, 0E4h, 0F8h, 83h, 0ECh, 34h, 53h, 56h, 8Bh, 35h, 70h, 8Dh, 35h
    db 01h, 57h, 0FFh, 0D6h, 50h, 0FFh, 15h, 0D4h, 8Dh, 35h, 01h, 8Bh, 3Dh, 78h, 8Dh, 35h
    db 01h, 89h, 44h, 24h, 10h, 0FFh, 0D7h, 50h, 0FFh, 15h, 08h, 8Eh, 35h, 01h, 68h, 80h
    db 00h, 00h, 00h, 89h, 44h, 24h, 10h, 0FFh, 0D6h, 50h, 0FFh, 15h, 1Ch, 8Fh, 35h, 01h
    db 6Ah, 02h, 0FFh, 0D7h, 50h, 0FFh, 15h, 20h, 8Fh, 35h, 01h, 0DDh, 05h, 40h, 0C6h, 07h
    db 01h, 0BBh, 01h, 00h, 00h, 00h, 0DDh, 5Ch, 24h, 20h, 0DDh, 05h, 40h, 0C6h, 07h, 01h
    db 33h, 0C0h, 0DDh, 5Ch, 24h, 28h, 0B9h, 0AFh, 1Fh, 00h, 00h, 0DDh, 05h, 40h, 0C6h, 07h
    db 01h, 0C7h, 05h, 0B0h, 62h, 35h, 01h, 3Ch, 00h, 00h, 00h, 0DDh, 5Ch, 24h, 30h, 89h
    db 1Dh, 4Ch, 65h, 35h, 01h, 0A3h, 24h, 66h, 35h, 01h, 0A3h, 58h, 63h, 35h, 01h, 0C7h
    db 05h, 3Ch, 63h, 35h, 01h, 08h, 00h, 00h, 00h, 0A3h, 78h, 63h, 35h, 01h, 0A3h, 40h
    db 64h, 35h, 01h, 89h, 1Dh, 20h, 65h, 35h, 01h, 89h, 1Dh, 24h, 65h, 35h, 01h, 89h
    db 1Dh, 28h, 65h, 35h, 01h, 89h, 1Dh, 2Ch, 65h, 35h, 01h, 89h, 1Dh, 30h, 65h, 35h
    db 01h, 89h, 1Dh, 34h, 65h, 35h, 01h, 89h, 1Dh, 38h, 65h, 35h, 01h, 89h, 1Dh, 3Ch
    db 65h, 35h, 01h, 89h, 1Dh, 40h, 65h, 35h, 01h, 89h, 1Dh, 44h, 65h, 35h, 01h, 89h
    db 1Dh, 0C4h, 64h, 35h, 01h, 89h, 1Dh, 0A4h, 64h, 35h, 01h, 89h, 1Dh, 64h, 63h, 35h
    db 01h, 89h, 1Dh, 64h, 65h, 35h, 01h, 89h, 1Dh, 84h, 63h, 35h, 01h, 89h, 1Dh, 84h
    db 64h, 35h, 01h, 89h, 1Dh, 44h, 63h, 35h, 01h, 89h, 1Dh, 64h, 64h, 35h, 01h, 89h
    db 1Dh, 04h, 65h, 35h, 01h, 89h, 1Dh, 0E4h, 64h, 35h, 01h, 0A3h, 0C0h, 64h, 35h, 01h
    db 89h, 0Dh, 0D4h, 64h, 35h, 01h, 0A3h, 0A0h, 64h, 35h, 01h, 89h, 0Dh, 0B4h, 64h, 35h
    db 01h, 0A3h, 60h, 63h, 35h, 01h, 0C7h, 05h, 74h, 63h, 35h, 01h, 00h, 80h, 00h, 00h
    db 0A3h, 60h, 65h, 35h, 01h, 0C7h, 05h, 68h, 65h, 35h, 01h, 0B8h, 0Bh, 00h, 00h, 0A3h
    db 80h, 63h, 35h, 01h, 0A3h, 80h, 64h, 35h, 01h, 0A3h, 40h, 63h, 35h, 01h, 0C7h, 05h
    db 48h, 63h, 35h, 01h, 0A0h, 0Fh, 00h, 00h, 0A3h, 60h, 64h, 35h, 01h, 0C7h, 05h, 68h
    db 64h, 35h, 01h, 88h, 13h, 00h, 00h, 0A3h, 00h, 65h, 35h, 01h, 0A3h, 0E0h, 64h, 35h
    db 01h, 33h, 0FFh, 39h, 04h, 0BDh, 20h, 65h, 35h, 01h, 0Fh, 84h, 96h, 00h, 00h, 00h
    db 8Dh, 44h, 24h, 38h, 50h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Dh, 74h, 24h, 1Ch, 0E8h, 0ADh
    db 0FDh, 0FFh, 0FFh, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 1Bh, 8Bh, 35h, 0A8h, 8Eh, 35h, 01h
    db 68h, 80h, 17h, 13h, 01h, 0FFh, 0D6h, 68h, 38h, 17h, 13h, 01h, 0FFh, 0D6h, 68h, 20h
    db 17h, 13h, 01h, 0FFh, 0D6h, 83h, 0FFh, 04h, 74h, 47h, 83h, 0FFh, 08h, 74h, 42h, 83h
    db 0FFh, 09h, 74h, 3Dh, 85h, 0FFh, 74h, 24h, 83h, 0FFh, 03h, 74h, 1Fh, 83h, 0FFh, 06h
    db 74h, 1Ah, 83h, 0FFh, 07h, 74h, 15h, 0DDh, 44h, 24h, 18h, 0DCh, 34h, 0FDh, 48h, 4Bh
    db 2Dh, 01h, 0DCh, 4Ch, 24h, 20h, 0DDh, 5Ch, 24h, 20h, 0EBh, 28h, 0DDh, 44h, 24h, 18h
    db 0DCh, 34h, 0FDh, 48h, 4Bh, 2Dh, 01h, 0DCh, 4Ch, 24h, 28h, 0DDh, 5Ch, 24h, 28h, 0EBh
    db 13h, 0DDh, 44h, 24h, 18h, 0DCh, 34h, 0FDh, 48h, 4Bh, 2Dh, 01h, 0DCh, 4Ch, 24h, 30h
    db 0DDh, 5Ch, 24h, 30h, 33h, 0C0h, 47h, 83h, 0FFh, 0Ah, 0Fh, 8Ch, 53h, 0FFh, 0FFh, 0FFh
    db 39h, 05h, 58h, 63h, 35h, 01h, 75h, 3Ch, 0DDh, 44h, 24h, 20h, 0DDh, 05h, 18h, 17h
    db 13h, 01h, 0E8h, 0CBh, 2Fh, 18h, 00h, 8Bh, 55h, 18h, 0D9h, 1Ah, 0DDh, 44h, 24h, 28h
    db 0DDh, 05h, 88h, 4Ah, 09h, 01h, 0E8h, 0B7h, 2Fh, 18h, 00h, 8Bh, 45h, 14h, 0D9h, 18h
    db 0DDh, 44h, 24h, 30h, 0DDh, 05h, 18h, 17h, 13h, 01h, 0E8h, 0A3h, 2Fh, 18h, 00h, 8Bh
    db 4Dh, 10h, 0D9h, 19h, 8Bh, 54h, 24h, 0Ch, 52h, 0FFh, 15h, 78h, 8Dh, 35h, 01h, 50h
    db 0FFh, 15h, 20h, 8Fh, 35h, 01h, 8Bh, 44h, 24h, 10h, 50h, 0FFh, 15h, 70h, 8Dh, 35h
    db 01h, 50h, 0FFh, 15h, 1Ch, 8Fh, 35h, 01h, 5Fh, 5Eh, 8Bh, 0C3h, 5Bh, 8Bh, 0E5h, 5Dh
    db 0C3h
?Get_DX8_Render_State_Name@DX8Wrapper@@SAPBDK@Z ENDP
_TEXT ENDS
END
