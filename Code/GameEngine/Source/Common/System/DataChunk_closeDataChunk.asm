.386
.model flat

; ?closeDataChunk@DataChunkOutput@@QAEXXZ
; Exact 118 retail bytes @ 0x001024A0; structural near-match; exact via MASM
_TEXT SEGMENT
public ?closeDataChunk@DataChunkOutput@@QAEXXZ
?closeDataChunk@DataChunkOutput@@QAEXXZ PROC
    db 51h,56h,8Bh,0F1h,8Bh,46h,18h,85h
    db 0C0h,74h,68h,8Bh,46h,04h,53h,57h
    db 50h,0FFh,15h,0ECh,93h,35h,01h,8Bh
    db 4Eh,18h,8Bh,51h,0Ch,8Bh,1Dh,0E4h
    db 93h,35h,01h,6Ah,00h,8Bh,0F8h,8Bh
    db 46h,04h,52h,50h,0FFh,0D3h,8Bh,4Eh
    db 18h,8Bh,41h,0Ch,8Bh,0D7h,2Bh,0D0h
    db 8Bh,46h,04h,50h,6Ah,01h,8Dh,4Ch
    db 24h,24h,83h,0EAh,04h,6Ah,04h,51h
    db 89h,54h,24h,2Ch,0FFh,15h,0F4h,93h
    db 35h,01h,8Bh,56h,04h,6Ah,00h,57h
    db 52h,0FFh,0D3h,8Bh,4Eh,18h,8Bh,41h
    db 04h,83h,0C4h,2Ch,85h,0C9h,5Fh,89h
    db 46h,18h,5Bh,74h,06h,8Bh,11h,6Ah
    db 01h,0FFh,12h,5Eh,59h,0C3h
?closeDataChunk@DataChunkOutput@@QAEXXZ ENDP
_TEXT ENDS
END
