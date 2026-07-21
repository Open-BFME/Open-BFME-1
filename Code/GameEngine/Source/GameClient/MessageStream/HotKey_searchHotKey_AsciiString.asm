.386
.model flat

; ?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABV2@@Z
; Exact 135 retail bytes @ 0x005B2AD0
; Identity: TheGameText->fetch (vtbl+0x24) then searchHotKey(UnicodeString)
; via thunk 0x12A49 -> 0x5B27E0 (L'&' scan). Queue RVA 0x9DB068 misplaced.
_TEXT SEGMENT
public ?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABV2@@Z
?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABV2@@Z PROC
    db 6Ah,0FFh,68h,0A1h,8Fh,03h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,08h
    db 56h,57h,6Ah,00h,51h,0C7h,44h,24h
    db 10h,00h,00h,00h,00h,8Bh,44h,24h
    db 2Ch,8Bh,0F1h,89h,64h,24h,14h,8Bh
    db 0CCh,50h,0E8h,59h,50h,2Dh,00h,8Bh
    db 0Dh,7Ch,14h,2Fh,01h,8Bh,11h,8Dh
    db 44h,24h,2Ch,50h,0FFh,52h,24h,8Bh
    db 7Ch,24h,20h,50h,57h,8Bh,0CEh,0C7h
    db 44h,24h,20h,01h,00h,00h,00h,0E8h
    db 1Dh,0FFh,0A5h,0FFh,8Dh,4Ch,24h,24h
    db 0C7h,44h,24h,08h,01h,00h,00h,00h
    db 0C6h,44h,24h,18h,00h,0E8h,8Eh,56h
    db 2Dh,00h,8Bh,4Ch,24h,10h,8Bh,0C7h
    db 5Fh,64h,89h,0Dh,00h,00h,00h,00h
    db 5Eh,83h,0C4h,14h,0C2h,08h,00h
?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABV2@@Z ENDP
_TEXT ENDS
END
