.386
.model flat

; ??0LadderPref@@QAE@ABV0@@Z
; Exact 93B @ 0x000A9BE0. ILT thunk 0x48329 has five callers; the
; byte-matched pair<const long, LadderPref> ctor at 0xA9D50 passes its value
; reference here and constructs at this+4. This body copies UnicodeString,
; AsciiString, port, and lastPlayDate, then returns this.
_TEXT SEGMENT
public ??0LadderPref@@QAE@ABV0@@Z
??0LadderPref@@QAE@ABV0@@Z PROC
    db 6Ah,0FFh,68h,08h,75h,0FFh,00h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,57h
    db 8Bh,7Ch,24h,1Ch,8Bh,0F1h,57h,89h
    db 74h,24h,0Ch,0E8h,0F8h,0E7h,7Dh,00h
    db 8Dh,47h,04h,50h,8Dh,4Eh,04h,0C7h
    db 44h,24h,18h,00h,00h,00h,00h,0E8h
    db 44h,0DFh,7Dh,00h,66h,8Bh,4Fh,08h
    db 66h,89h,4Eh,08h,8Bh,57h,0Ch,8Bh
    db 4Ch,24h,0Ch,89h,56h,0Ch,5Fh,8Bh
    db 0C6h,5Eh,64h,89h,0Dh,00h,00h,00h
    db 00h,83h,0C4h,10h,0C2h,04h,00h
??0LadderPref@@QAE@ABV0@@Z ENDP
_TEXT ENDS
END
