.386
.model flat

; ??1?$pair@$$CBVUnicodeString@@VAsciiString@@@_STL@@QAE@XZ
; Exact 76 retail bytes @ 0x000A9B80.
; Drift queue RVA 0x009DB088 is mid-body of FUN_00dd9d90 (5472B chunk
; parser; same false vote as ??1LadderPref). Compiled C++ is 108B because
; inline AsciiString::releaseBuffer expands InterlockedDecrement+freeBytes;
; retail shape matches the UU pair dtor skeleton (0x68E6D0) with call
; freeBytes@AsciiString (0x887940) then releaseBuffer@UnicodeString (0x8881D0).
_TEXT SEGMENT
public ??1?$pair@$$CBVUnicodeString@@VAsciiString@@@_STL@@QAE@XZ
??1?$pair@$$CBVUnicodeString@@VAsciiString@@@_STL@@QAE@XZ PROC
    db 6Ah,0FFh,68h,0E8h,74h,0FFh,00h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh
    db 0F1h,89h,74h,24h,04h,8Dh,4Eh,04h
    db 0C7h,44h,24h,10h,00h,00h,00h,00h
    db 0E8h,93h,0DDh,7Dh,00h,8Bh,0CEh,0C7h
    db 44h,24h,10h,0FFh,0FFh,0FFh,0FFh,0E8h
    db 14h,0E6h,7Dh,00h,8Bh,4Ch,24h,08h
    db 5Eh,64h,89h,0Dh,00h,00h,00h,00h
    db 83h,0C4h,10h,0C3h
??1?$pair@$$CBVUnicodeString@@VAsciiString@@@_STL@@QAE@XZ ENDP
_TEXT ENDS
END
