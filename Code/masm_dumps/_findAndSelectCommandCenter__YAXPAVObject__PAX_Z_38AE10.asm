.386
.model flat
; ?findAndSelectCommandCenter@@YAXPAVObject@@PAX@Z
; Exact 93B @ 0x0038AE10; startNewGame@0x395BB0 pushes VA 0x78AE10; kindof/selectObject body
_TEXT SEGMENT
public ?findAndSelectCommandCenter@@YAXPAVObject@@PAX@Z
?findAndSelectCommandCenter@@YAXPAVObject@@PAX@Z PROC
    db 57h, 8Bh, 7Ch, 24h, 08h, 85h, 0FFh, 74h, 4Dh, 8Bh, 47h, 04h, 85h, 0C0h, 74h, 0Ch
    db 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 8Fh, 74h, 0C7h, 0FFh, 0F7h, 80h, 0C8h, 00h
    db 00h, 00h, 00h, 00h, 02h, 00h, 74h, 2Eh, 56h, 8Bh, 0CFh, 0E8h, 0E4h, 59h, 0C9h, 0FFh
    db 8Bh, 48h, 24h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 8Bh, 0CFh, 0E8h, 40h, 51h, 0C9h
    db 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 56h, 6Ah, 01h, 57h, 0E8h, 0A6h, 0D2h, 0C7h
    db 0FFh, 5Eh, 33h, 0C0h, 5Fh, 0C3h, 0B8h, 01h, 00h, 00h, 00h, 5Fh, 0C3h
?findAndSelectCommandCenter@@YAXPAVObject@@PAX@Z ENDP
_TEXT ENDS
END
