.386
.model flat

; ?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z
; Exact 134 retail bytes @ 0x00104300; queue RVA 0x00454F43 was INSIDE MapUtil (Player_%d_Start);
; true body via keyToName+allocateID+shl8|or3+fwrite; C++ blocked by inline ~AsciiString vs ICF 0x887940
_TEXT SEGMENT
public ?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z
?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z PROC
    db 6Ah,0FFh,68h,78h,0CBh,0FFh,00h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,8Bh,44h
    db 24h,14h,56h,8Bh,0F1h,50h,8Dh,4Ch
    db 24h,1Ch,51h,8Bh,0Dh,00h,0D6h,2Eh
    db 01h,0E8h,4Ch,0A9h,0F3h,0FFh,8Dh,54h
    db 24h,18h,52h,8Dh,4Eh,08h,0C7h,44h
    db 24h,14h,00h,00h,00h,00h,0E8h,61h
    db 0A7h,0F3h,0FFh,0C1h,0E0h,08h,83h,0C8h
    db 03h,89h,44h,24h,04h,8Bh,46h,04h
    db 50h,6Ah,01h,8Dh,4Ch,24h,0Ch,6Ah
    db 04h,51h,0FFh,15h,0F4h,93h,35h,01h
    db 83h,0C4h,10h,8Dh,4Ch,24h,18h,0C7h
    db 44h,24h,10h,0FFh,0FFh,0FFh,0FFh,0E8h
    db 0CCh,35h,78h,00h,8Bh,4Ch,24h,08h
    db 5Eh,64h,89h,0Dh,00h,00h,00h,00h
    db 83h,0C4h,10h,0C2h,04h,00h
?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z ENDP
_TEXT ENDS
END
