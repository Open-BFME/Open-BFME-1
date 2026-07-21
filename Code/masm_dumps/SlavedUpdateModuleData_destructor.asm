.386
.model flat

; ??1SlavedUpdateModuleData@@UAE@XZ
; Exact 80 retail bytes @ 0x00126980; factory friend_newModuleData@SlavedUpdate 0x125A60
; stores unique vtable 0x108E730; slot0 ILT 0x293A2 -> scalar 0x126950 -> thunk 0x1EB96 -> this body.
; Destroys AsciiString members at +0x4c/+0x48 via 0x887940; base vtable 0x1073744.
_TEXT SEGMENT
public ??1SlavedUpdateModuleData@@UAE@XZ
??1SlavedUpdateModuleData@@UAE@XZ PROC
    db 6Ah, 0FFh, 68h, 0A3h, 19h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Dh, 4Eh, 4Ch
    db 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 0E8h, 93h, 0Fh, 76h, 00h, 8Dh, 4Eh, 48h
    db 0C6h, 44h, 24h, 10h, 00h, 0E8h, 86h, 0Fh, 76h, 00h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h
    db 44h, 37h, 07h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
??1SlavedUpdateModuleData@@UAE@XZ ENDP
_TEXT ENDS
END
