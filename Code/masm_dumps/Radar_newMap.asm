.386
.model flat

; ?newMap@Radar@@UAEXPAVTerrainLogic@@@Z
; Exact 323 retail bytes @ 0x001078B0. Queue 0x0079CEFC was MOTD/replay pad
; (misplaced). Identity: calls LeftHUD helper thunk 0x1827D -> 0x107340
; (ControlBar.wnd:LeftHUD string), then reset vcall [this+4]+0x10, TerrainLogic
; getExtent [vtbl+0x24] into m_mapExtent@+0x143c, 128x128 sample with 1/128
; (0xC888F4), averages m_terrainAverageZ/m_waterAverageZ @ +0x18/+0x1c.
_TEXT SEGMENT
public ?newMap@Radar@@UAEXPAVTerrainLogic@@@Z
?newMap@Radar@@UAEXPAVTerrainLogic@@@Z PROC
    db 55h, 8Bh, 0ECh, 83h, 0E4h, 0F8h, 83h, 0ECh, 2Ch, 53h, 56h, 57h, 8Bh, 0F1h, 0E8h, 0BAh
    db 09h, 0F1h, 0FFh, 8Bh, 46h, 04h, 8Dh, 4Eh, 04h, 0FFh, 50h, 10h, 8Bh, 7Dh, 08h, 8Bh
    db 17h, 8Dh, 9Eh, 3Ch, 14h, 00h, 00h, 53h, 8Bh, 0CFh, 0FFh, 52h, 24h, 0D9h, 43h, 0Ch
    db 0D8h, 23h, 33h, 0C0h, 89h, 44h, 24h, 0Ch, 89h, 44h, 24h, 10h, 0D8h, 0Dh, 0F4h, 88h
    db 08h, 01h, 89h, 44h, 24h, 18h, 0D9h, 5Eh, 20h, 0D9h, 43h, 10h, 0D8h, 63h, 04h, 89h
    db 46h, 18h, 89h, 46h, 1Ch, 0D8h, 0Dh, 0F4h, 88h, 08h, 01h, 0D9h, 5Eh, 24h, 8Bh, 0FFh
    db 8Bh, 44h, 24h, 18h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 89h, 44h, 24h, 28h
    db 8Bh, 4Ch, 24h, 14h, 8Dh, 54h, 24h, 2Ch, 52h, 8Dh, 44h, 24h, 28h, 89h, 4Ch, 24h
    db 28h, 50h, 8Bh, 0CEh, 0E8h, 0DAh, 9Bh, 0F0h, 0FFh, 8Bh, 5Ch, 24h, 30h, 8Bh, 44h, 24h
    db 2Ch, 8Bh, 17h, 6Ah, 00h, 53h, 50h, 8Bh, 0CFh, 0FFh, 52h, 18h, 0E8h, 0E7h, 0F4h, 8Eh
    db 00h, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 17h, 6Ah, 00h, 89h, 44h, 24h, 20h, 8Dh, 44h, 24h
    db 24h, 50h, 53h, 51h, 8Bh, 0CFh, 0FFh, 52h, 4Ch, 0DBh, 44h, 24h, 1Ch, 84h, 0C0h, 74h
    db 11h, 8Bh, 44h, 24h, 10h, 0D8h, 46h, 1Ch, 40h, 89h, 44h, 24h, 10h, 0D9h, 5Eh, 1Ch
    db 0EBh, 0Fh, 8Bh, 44h, 24h, 0Ch, 0D8h, 46h, 18h, 40h, 89h, 44h, 24h, 0Ch, 0D9h, 5Eh
    db 18h, 8Bh, 44h, 24h, 14h, 40h, 3Dh, 80h, 00h, 00h, 00h, 89h, 44h, 24h, 14h, 0Fh
    db 8Ch, 7Bh, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 18h, 40h, 3Dh, 80h, 00h, 00h, 00h, 89h
    db 44h, 24h, 18h, 0Fh, 8Ch, 57h, 0FFh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 85h, 0C9h, 0B8h
    db 01h, 00h, 00h, 00h, 75h, 04h, 89h, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 10h, 85h, 0C9h
    db 75h, 04h, 89h, 44h, 24h, 10h, 0DBh, 44h, 24h, 0Ch, 5Fh, 0D8h, 7Eh, 18h, 0D9h, 5Eh
    db 18h, 0DBh, 44h, 24h, 0Ch, 0D8h, 7Eh, 1Ch, 0D9h, 5Eh, 1Ch, 5Eh, 5Bh, 8Bh, 0E5h, 5Dh
    db 0C2h, 04h, 00h
?newMap@Radar@@UAEXPAVTerrainLogic@@@Z ENDP
_TEXT ENDS
END
