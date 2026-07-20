.386
.model flat

; ??0MetaEventTranslator@@QAE@XZ
; Exact 42 retail bytes @ 0x009B6B30; installs the derived vtable and initializes translator state.
_TEXT SEGMENT
public ??0MetaEventTranslator@@QAE@XZ
??0MetaEventTranslator@@QAE@XZ PROC
    db 8Bh,0C1h,33h,0C9h,56h,0C7h,00h,50h
    db 0F0h,10h,01h,89h,48h,04h,89h,48h
    db 08h,33h,0D2h,8Dh,70h,10h,88h,4Ch
    db 10h,24h,89h,4Eh,0FCh,89h,0Eh,42h
    db 83h,0C6h,08h,83h,0FAh,03h,7Ch,0EEh
    db 5Eh,0C3h
??0MetaEventTranslator@@QAE@XZ ENDP
_TEXT ENDS
END
