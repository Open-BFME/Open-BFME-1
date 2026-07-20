.386
.model flat

; ?doVictory@ScriptActions@@IAEXXZ
; Exact 290 retail bytes @ 0x006F1C10; BFME victory-window flow differs materially from ZH.
_TEXT SEGMENT
public ?doVictory@ScriptActions@@IAEXXZ
?doVictory@ScriptActions@@IAEXXZ PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh
    db 68h,0D8h,5Eh,01h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,0Ch
    db 56h,8Bh,0F1h,0C6h,46h,08h,00h,8Bh
    db 0Dh,98h,08h,2Fh,01h,0E8h,4Ch,18h
    db 0D1h,0FFh,8Bh,0CEh,0E8h,54h,79h,0D4h
    db 0FFh,8Ah,46h,08h,84h,0C0h,0Fh,85h
    db 0D6h,00h,00h,00h,0A1h,48h,0D7h,2Eh
    db 01h,8Bh,70h,0Ch,0A1h,9Ch,07h,2Fh
    db 01h,85h,0C0h,0Fh,84h,0C1h,00h,00h
    db 00h,85h,0F6h,0Fh,84h,0B9h,00h,00h
    db 00h,8Bh,46h,04h,85h,0C0h,74h,0Fh
    db 8Ah,88h,18h,01h,00h,00h,84h,0C9h
    db 0B8h,0B4h,00h,0Dh,01h,75h,05h,0B8h
    db 98h,00h,0Dh,01h,50h,8Dh,4Ch,24h
    db 10h,0E8h,32h,6Fh,59h,00h,68h,80h
    db 00h,0Dh,01h,8Dh,4Ch,24h,0Ch,0C7h
    db 44h,24h,1Ch,00h,00h,00h,00h,0E8h
    db 1Ch,6Fh,59h,00h,0C6h,44h,24h,18h
    db 01h,0E8h,0FDh,54h,0D3h,0FFh,84h,0C0h
    db 0B8h,6Ch,00h,0Dh,01h,75h,05h,0B8h
    db 54h,00h,0Dh,01h,50h,8Dh,4Ch,24h
    db 08h,0E8h,0FAh,6Eh,59h,00h,8Bh,46h
    db 04h,85h,0C0h,0C6h,44h,24h,18h,02h
    db 74h,08h,8Ah,80h,18h,01h,00h,00h
    db 0EBh,02h,32h,0C0h,8Bh,0Dh,9Ch,07h
    db 2Fh,01h,8Bh,11h,8Dh,74h,24h,0Ch
    db 56h,8Dh,74h,24h,0Ch,56h,50h,8Dh
    db 44h,24h,10h,50h,0FFh,52h,48h,8Dh
    db 4Ch,24h,04h,0C6h,44h,24h,18h,01h
    db 0E8h,3Bh,5Ch,59h,00h,8Bh,0CEh,0C6h
    db 44h,24h,18h,00h,0E8h,2Fh,5Ch,59h
    db 00h,8Dh,4Ch,24h,0Ch,0C7h,44h,24h
    db 18h,0FFh,0FFh,0FFh,0FFh,0E8h,1Eh,5Ch
    db 59h,00h,8Bh,4Ch,24h,10h,5Eh,64h
    db 89h,0Dh,00h,00h,00h,00h,83h,0C4h
    db 18h,0C3h
?doVictory@ScriptActions@@IAEXXZ ENDP
_TEXT ENDS
END
