.386
.model flat
; ?Get_DX8_Texture_Filter_Name@DX8Wrapper@@
; Exact 71B @ 0x00902EC0; Open-BFME4
_TEXT SEGMENT
public ?Get_DX8_Texture_Filter_Name@DX8Wrapper@@
?Get_DX8_Texture_Filter_Name@DX8Wrapper@@ PROC
    db 8Bh, 44h, 24h, 04h, 48h, 83h, 0F8h, 07h, 77h, 37h, 0FFh, 24h, 85h, 08h, 2Fh, 0D0h
    db 00h, 0B8h, 80h, 9Eh, 13h, 01h, 0C3h, 0B8h, 6Ch, 9Eh, 13h, 01h, 0C3h, 0B8h, 54h, 9Eh
    db 13h, 01h, 0C3h, 0B8h, 3Ch, 9Eh, 13h, 01h, 0C3h, 0B8h, 24h, 9Eh, 13h, 01h, 0C3h, 0B8h
    db 10h, 9Eh, 13h, 01h, 0C3h, 0B8h, 0FCh, 9Dh, 13h, 01h, 0C3h, 0B8h, 0E8h, 9Dh, 13h, 01h
    db 0C3h, 0B8h, 34h, 02h, 08h, 01h, 0C3h
?Get_DX8_Texture_Filter_Name@DX8Wrapper@@ ENDP
_TEXT ENDS
END
