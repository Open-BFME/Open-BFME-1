.386
.model flat

; ?findDamageFX@DamageFXStore@@QBEPBVDamageFX@@VAsciiString@@@Z
; Exact 192 retail bytes @ 0x00067440
; True body (queue 0x0079CED6 was mid-instruction inside unrelated fn).
; Identity: sole TheDamageFXStore call site from INI::parseDamageFX
; (None-check then AsciiString(token) temp) via ILT 0x3A01C -> 0x67440.
; C++ blocked by BFME AsciiString buffer layout (str at +8 vs ZH +4)
; and shorter retail AsciiString dtor path (192B vs 242B).
_TEXT SEGMENT
public ?findDamageFX@DamageFXStore@@QBEPBVDamageFX@@VAsciiString@@@Z
?findDamageFX@DamageFXStore@@QBEPBVDamageFX@@VAsciiString@@@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh,68h,0C8h,29h,0FFh,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,56h,57h,8Bh,0F1h,8Bh,44h,24h,18h,85h,0C0h,0C7h
    db 44h,24h,10h,00h,00h,00h,00h,74h,05h,83h,0C0h,08h,0EBh,05h,0B8h,8Bh
    db 38h,07h,01h,8Bh,0Dh,00h,0D6h,2Eh,01h,50h,0E8h,58h,39h,0FDh,0FFh,8Bh
    db 56h,0Ch,8Bh,7Eh,10h,2Bh,0FAh,0C1h,0FFh,02h,33h,0D2h,8Bh,0C8h,0F7h,0F7h
    db 8Bh,76h,0Ch,8Bh,04h,96h,85h,0C0h,74h,17h,8Dh,9Bh,00h,00h,00h,00h
    db 39h,48h,04h,74h,08h,8Bh,00h,85h,0C0h,75h,0F5h,0EBh,04h,85h,0C0h,75h
    db 26h,8Dh,4Ch,24h,18h,0C7h,44h,24h,10h,0FFh,0FFh,0FFh,0FFh,0E8h,7Eh,04h
    db 82h,00h,33h,0C0h,8Bh,4Ch,24h,08h,64h,89h,0Dh,00h,00h,00h,00h,5Fh
    db 5Eh,83h,0C4h,0Ch,0C2h,04h,00h,8Dh,4Ch,24h,18h,8Dh,70h,08h,0C7h,44h
    db 24h,10h,0FFh,0FFh,0FFh,0FFh,0E8h,55h,04h,82h,00h,8Bh,4Ch,24h,08h,5Fh
    db 8Bh,0C6h,64h,89h,0Dh,00h,00h,00h,00h,5Eh,83h,0C4h,0Ch,0C2h,04h,00h
?findDamageFX@DamageFXStore@@QBEPBVDamageFX@@VAsciiString@@@Z ENDP
_TEXT ENDS
END
