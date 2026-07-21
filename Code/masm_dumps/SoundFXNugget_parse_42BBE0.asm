.386
.model flat

; ?parse@SoundFXNugget@@SAXPAVINI@@PAX1PBX@Z
; Exact 240 retail bytes @ 0x0042BBE0; FX type table Sound -> ILT 0x91A1 -> body
; BFME rewrite: global new(0xB8)+filters MultiIniFieldParse; Name@+0xB4; not ZH pool newInstance
_TEXT SEGMENT
public ?parse@SoundFXNugget@@SAXPAVINI@@PAX1PBX@Z
?parse@SoundFXNugget@@SAXPAVINI@@PAX1PBX@Z PROC
    db 6Ah,0FFh,68h,0Eh,16h,02h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,81h,0ECh,88h
    db 00h,00h,00h,53h,56h,57h,68h,0B8h
    db 00h,00h,00h,0E8h,28h,63h,45h,00h
    db 8Bh,0F0h,83h,0C4h,04h,89h,74h,24h
    db 0Ch,33h,0DBh,3Bh,0F3h,89h,9Ch,24h
    db 9Ch,00h,00h,00h,74h,1Ch,8Bh,0CEh
    db 0E8h,0BBh,6Ah,0C1h,0FFh,0C7h,06h,0D8h
    db 33h,0Fh,01h,89h,9Eh,0B4h,00h,00h
    db 00h,0C7h,46h,04h,01h,00h,00h,00h
    db 0EBh,02h,33h,0F6h,0C7h,84h,24h,9Ch
    db 00h,00h,00h,0FFh,0FFh,0FFh,0FFh,89h
    db 9Ch,24h,90h,00h,00h,00h,33h,0C0h
    db 89h,5Ch,84h,50h,89h,5Ch,84h,10h
    db 40h,83h,0F8h,10h,7Ch,0F2h,53h,68h
    db 9Ch,25h,0Fh,01h,8Dh,4Ch,24h,18h
    db 0E8h,0B3h,4Ch,42h,00h,53h,68h,80h
    db 24h,0Fh,01h,8Dh,4Ch,24h,18h,0E8h
    db 0A4h,4Ch,42h,00h,8Bh,8Ch,24h,0A4h
    db 00h,00h,00h,8Dh,44h,24h,10h,50h
    db 56h,0E8h,82h,5Ch,42h,00h,8Bh,8Ch
    db 24h,0A8h,00h,00h,00h,8Bh,79h,04h
    db 6Ah,0Ch,0E8h,0A1h,28h,40h,00h,8Dh
    db 48h,08h,83h,0C4h,04h,3Bh,0CBh,74h
    db 02h,89h,31h,8Bh,4Fh,04h,89h,38h
    db 89h,48h,04h,89h,01h,8Bh,8Ch,24h
    db 94h,00h,00h,00h,89h,47h,04h,5Fh
    db 5Eh,64h,89h,0Dh,00h,00h,00h,00h
    db 5Bh,81h,0C4h,94h,00h,00h,00h,0C3h
?parse@SoundFXNugget@@SAXPAVINI@@PAX1PBX@Z ENDP
_TEXT ENDS
END
