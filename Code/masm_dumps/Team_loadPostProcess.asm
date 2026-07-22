.386
.model flat

; ?loadPostProcess@Team@@MAEXXZ
; Exact 265 retail bytes @ 0x000F1800.
; Team vtable 0x1085F88 slot 1 reaches this body through thunk 0x43B764.
; Iterates ObjectIDs at Team+0x100, resolves them through TheGameLogic,
; validates Team membership, throws on failure, then clears the ID list.
_TEXT SEGMENT
public ?loadPostProcess@Team@@MAEXXZ
?loadPostProcess@Team@@MAEXXZ PROC
    db 83h,0ECh,08h,53h,55h,8Bh,0D9h,8Bh,83h,00h,01h,00h,00h,56h,8Bh,30h
    db 3Bh,0F0h,57h,89h,44h,24h,10h,0Fh,84h,8Eh,00h,00h,00h,8Bh,3Dh,98h
    db 08h,2Fh,01h,8Bh,4Eh,08h,85h,0C9h,74h,31h,8Bh,87h,0B4h,00h,00h,00h
    db 8Bh,0AFh,0B8h,00h,00h,00h,2Bh,0E8h,33h,0D2h,0C1h,0FDh,02h,8Bh,0C1h,0F7h
    db 0F5h,8Bh,87h,0B4h,00h,00h,00h,8Bh,14h,90h,85h,0D2h,74h,0Dh,8Bh,0FFh
    db 39h,4Ah,04h,74h,26h,8Bh,12h,85h,0D2h,75h,0F5h,6Ah,00h,8Dh,4Ch,24h
    db 14h,6Ah,05h,51h,0E8h,0B7h,49h,8Eh,00h,83h,0C4h,0Ch,68h,5Ch,0FEh,1Dh
    db 01h,8Dh,54h,24h,14h,52h,0E8h,85h,54h,90h,00h,85h,0D2h,74h,0DCh,8Bh
    db 52h,08h,85h,0D2h,74h,0D5h,39h,53h,0Ch,74h,14h,8Bh,82h,5Ch,02h,00h
    db 00h,85h,0C0h,75h,0Ah,8Bh,82h,60h,02h,00h,00h,85h,0C0h,74h,4Ah,8Bh
    db 36h,3Bh,74h,24h,10h,0Fh,85h,78h,0FFh,0FFh,0FFh,8Bh,83h,00h,01h,00h
    db 00h,8Bh,30h,3Bh,0F0h,74h,19h,8Bh,0C6h,8Bh,36h,6Ah,0Ch,50h,0E8h,2Dh
    db 0CDh,73h,00h,8Bh,83h,00h,01h,00h,00h,83h,0C4h,08h,3Bh,0F0h,75h,0E7h
    db 8Bh,83h,00h,01h,00h,00h,5Fh,5Eh,89h,00h,8Bh,83h,00h,01h,00h,00h
    db 5Dh,89h,40h,04h,5Bh,83h,0C4h,08h,0C3h,6Ah,00h,8Dh,44h,24h,14h,6Ah
    db 05h,50h,0E8h,29h,49h,8Eh,00h,83h,0C4h,0Ch,68h,5Ch,0FEh,1Dh,01h,8Dh
    db 4Ch,24h,14h,51h,0E8h,0F7h,53h,90h,00h
?loadPostProcess@Team@@MAEXXZ ENDP
_TEXT ENDS
END
