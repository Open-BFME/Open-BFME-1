.386
.model flat

; ?isPlayer@GameSlot@@QBE_NVAsciiString@@@Z
; Exact 133 retail bytes @ RVA 0x00620210
; Queue RVA 0x009DB05F was INSIDE FUN_00dd9d90 (5472B type-tag parser), not this function.
; True body: SEH + UnicodeString::translate + StringBase<G>::compareNoCase on m_name@+0x28.
_TEXT SEGMENT
public ?isPlayer@GameSlot@@QBE_NVAsciiString@@@Z
?isPlayer@GameSlot@@QBE_NVAsciiString@@@Z PROC
    db 6Ah,0FFh,68h,20h,0F3h,03h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,53h,56h,8Bh,0F1h,33h,0C0h,89h,44h,24h,14h
    db 89h,44h,24h,08h,8Dh,44h,24h,1Ch,0B3h,01h,50h,8Dh,4Ch,24h,0Ch,88h
    db 5Ch,24h,18h,0E8h,0A8h,8Fh,26h,00h,83h,7Eh,04h,05h,75h,11h,8Dh,4Ch
    db 24h,08h,51h,8Dh,4Eh,28h,0E8h,44h,5Eh,9Fh,0FFh,85h,0C0h,74h,02h,32h
    db 0DBh,8Dh,4Ch,24h,08h,0C6h,44h,24h,14h,00h,0E8h,61h,7Fh,26h,00h,8Dh
    db 4Ch,24h,1Ch,0C7h,44h,24h,14h,0FFh,0FFh,0FFh,0FFh,0E8h,0C0h,76h,26h,00h
    db 8Bh,4Ch,24h,0Ch,5Eh,8Ah,0C3h,5Bh,64h,89h,0Dh,00h,00h,00h,00h,83h
    db 0C4h,10h,0C2h,04h,00h
?isPlayer@GameSlot@@QBE_NVAsciiString@@@Z ENDP
_TEXT ENDS
END
