.386
.model flat
_TEXT SEGMENT

; retail @ 0x00C70D50 size 28
public ?d_00c70d50@@YAXXZ
?d_00c70d50@@YAXXZ PROC
    db 0A1h, 0D8h, 0BEh, 30h, 01h, 8Bh, 48h, 04h, 0C7h, 81h, 0D8h, 0BEh, 30h, 01h, 0F4h, 0F2h
    db 12h, 01h, 0B9h, 0E0h, 0BEh, 30h, 01h, 0E9h, 4Fh, 07h, 3Dh, 0FFh
?d_00c70d50@@YAXXZ ENDP

; retail @ 0x00C70EC0 size 19
public ?d_00c70ec0@@YAXXZ
?d_00c70ec0@@YAXXZ PROC
    db 68h, 30h, 6Eh, 33h, 01h, 0FFh, 15h, 0Ch, 8Dh, 35h, 01h, 0C6h, 05h, 48h, 6Eh, 33h
    db 01h, 00h, 0C3h
?d_00c70ec0@@YAXXZ ENDP

; retail @ 0x00C70EE0 size 19
public ?d_00c70ee0@@YAXXZ
?d_00c70ee0@@YAXXZ PROC
    db 68h, 10h, 6Eh, 33h, 01h, 0FFh, 15h, 0Ch, 8Dh, 35h, 01h, 0C6h, 05h, 28h, 6Eh, 33h
    db 01h, 00h, 0C3h
?d_00c70ee0@@YAXXZ ENDP
_TEXT ENDS
END
