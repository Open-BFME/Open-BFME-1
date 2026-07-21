.386
.model flat

; ??1TextTypeTransition@@UAE@XZ
; Exact 133 retail bytes @ 0x005A0670.
; Ownership: vtable 0x110CCFC slot0 deleting-dtor 0x5A0A50 -> ILT -> this body;
; ctor @ 0x5A0620 stores same vtable, sets frameLength=30 and m_dStr@+0x34.
; freeDisplayString via TheDisplayStringManager vcall slot +0x28; two UnicodeString
; members at +0x30/+0x2c then base Transition dtor (matches ZH TextType shape).
_TEXT SEGMENT
public ??1TextTypeTransition@@UAE@XZ
??1TextTypeTransition@@UAE@XZ PROC
    db 6Ah, 0FFh, 68h, 0BEh, 84h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0FCh
    db 0CCh, 10h, 01h, 8Bh, 46h, 34h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 02h, 00h, 00h, 00h
    db 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 74h, 0Ch, 8Bh, 0Dh, 0CCh, 12h, 2Fh, 01h, 8Bh
    db 11h, 50h, 0FFh, 52h, 28h, 8Dh, 4Eh, 30h, 0C7h, 46h, 34h, 00h, 00h, 00h, 00h, 0C6h
    db 44h, 24h, 10h, 01h, 0E8h, 07h, 7Bh, 2Eh, 00h, 8Dh, 4Eh, 2Ch, 0C6h, 44h, 24h, 10h
    db 00h, 0E8h, 0FAh, 7Ah, 2Eh, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 0B6h, 0A3h, 0A7h, 0FFh, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C3h
??1TextTypeTransition@@UAE@XZ ENDP
_TEXT ENDS
END
