.386
.model flat

; ?objectChangedTeam@InGameUI@@UAEXPBVObject@@HH@Z
; Exact 394 retail bytes @ RVA 0x00449FC0; vtable slot after addSuperweapon/removeSuperweapon
; Identity: ret 0x0c (3 stack args), SEH+AsciiString, vcalls +0x84/+0x88 add/remove SW
; Queue RVA 0x44C3FA was INSIDE unrelated 1-arg fn @ 0x44C250; true body via InGameUI vtbl
_TEXT SEGMENT
public ?objectChangedTeam@InGameUI@@UAEXPBVObject@@HH@Z
?objectChangedTeam@InGameUI@@UAEXPBVObject@@HH@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh,68h,90h,31h,02h,01h,50h,8Bh,44h
    db 24h,10h,64h,89h,25h,00h,00h,00h,00h,83h,0ECh,0Ch,85h,0C0h,55h,8Bh
    db 0E9h,0Fh,84h,30h,01h,00h,00h,53h,8Bh,5Ch,24h,28h,85h,0DBh,0Fh,8Ch
    db 22h,01h,00h,00h,8Bh,4Ch,24h,2Ch,85h,0C9h,0Fh,8Ch,16h,01h,00h,00h
    db 8Bh,48h,74h,89h,4Ch,24h,08h,0C7h,44h,24h,28h,00h,00h,00h,00h,8Bh
    db 80h,0F0h,01h,00h,00h,89h,44h,24h,0Ch,8Bh,00h,85h,0C0h,0C7h,44h,24h
    db 1Ch,00h,00h,00h,00h,0Fh,84h,0DAh,00h,00h,00h,56h,57h,8Dh,49h,00h
    db 8Bh,50h,0Ch,8Dh,48h,0Ch,0FFh,52h,1Ch,85h,0C0h,0Fh,84h,0ADh,00h,00h
    db 00h,8Bh,10h,8Bh,0C8h,0FFh,52h,18h,8Bh,0F8h,8Dh,44h,24h,18h,50h,8Bh
    db 0CFh,0E8h,2Ch,0B6h,0BBh,0FFh,50h,8Dh,4Ch,24h,34h,0C6h,44h,24h,28h,01h
    db 0E8h,2Bh,0DCh,43h,00h,8Dh,4Ch,24h,18h,0C6h,44h,24h,24h,00h,0E8h,0CDh
    db 0D8h,43h,00h,8Dh,0Ch,5Bh,8Dh,0B4h,8Dh,0CCh,05h,00h,00h,8Dh,54h,24h
    db 30h,52h,8Bh,0CEh,0E8h,72h,3Ch,0BCh,0FFh,3Bh,06h,74h,1Fh,8Bh,40h,14h
    db 8Bh,08h,3Bh,0C8h,74h,16h,8Bh,51h,08h,8Bh,74h,24h,10h,39h,72h,18h
    db 0Fh,84h,83h,00h,00h,00h,8Bh,09h,3Bh,0C8h,75h,0EAh,8Bh,15h,98h,08h
    db 2Fh,01h,8Bh,42h,3Ch,85h,0C0h,75h,35h,8Bh,44h,24h,2Ch,0F6h,80h,90h
    db 00h,00h,00h,04h,75h,28h,6Ah,11h,8Bh,0C8h,0E8h,50h,84h,0BEh,0FFh,84h
    db 0C0h,75h,1Bh,8Bh,44h,24h,10h,57h,50h,8Bh,44h,24h,3Ch,8Dh,4Ch,24h
    db 38h,51h,50h,8Bh,55h,00h,8Bh,0CDh,0FFh,92h,84h,00h,00h,00h,8Bh,44h
    db 24h,14h,83h,0C0h,04h,89h,44h,24h,14h,8Bh,00h,85h,0C0h,0Fh,85h,2Dh
    db 0FFh,0FFh,0FFh,5Fh,5Eh,8Dh,4Ch,24h,28h,0C7h,44h,24h,1Ch,0FFh,0FFh,0FFh
    db 0FFh,0E8h,2Ah,0D8h,43h,00h,5Bh,8Bh,4Ch,24h,10h,5Dh,64h,89h,0Dh,00h
    db 00h,00h,00h,83h,0C4h,18h,0C2h,0Ch,00h,8Bh,45h,00h,57h,56h,8Dh,4Ch
    db 24h,38h,51h,53h,8Bh,0CDh,0FFh,90h,88h,00h,00h,00h,8Bh,4Ch,24h,34h
    db 57h,56h,8Dh,44h,24h,38h,50h,51h,0EBh,99h
?objectChangedTeam@InGameUI@@UAEXPBVObject@@HH@Z ENDP
_TEXT ENDS
END
