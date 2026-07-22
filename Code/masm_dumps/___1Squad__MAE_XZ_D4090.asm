.386
.model flat
; ??1Squad@@MAE@XZ
; Exact 156B @ 0x000D4090; vtable-anchored Squad vt@0xC83E78 slot0
; (inline ctor sets vt 0x01083E78 + zeros +4..+18; sizeof 0x1C)
; G-dtor @ 0xD4060 -> thunk 0xC257 -> this body; queue 0x9F27DB is int3 pad
; BFME layout: single vptr + m_objectIDs@+4 + m_objectsCached@+0x10 (no Snapshot vptr)
_TEXT SEGMENT
public ??1Squad@@MAE@XZ
??1Squad@@MAE@XZ PROC
    db 6Ah, 0FFh, 68h, 83h, 9Ah, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Bh, 4Eh, 10h
    db 85h, 0C9h, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 74h, 27h, 8Bh, 46h, 18h, 2Bh
    db 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h
    db 0DCh, 0DDh, 7Ah, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 10h, 0A5h, 75h, 00h
    db 83h, 0C4h, 08h, 8Bh, 4Eh, 04h, 85h, 0C9h, 0C6h, 44h, 24h, 10h, 00h, 74h, 27h, 8Bh
    db 46h, 0Ch, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h
    db 0Bh, 51h, 0E8h, 0A9h, 0DDh, 7Ah, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 0DDh
    db 0A4h, 75h, 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 44h, 37h, 07h, 01h
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
??1Squad@@MAE@XZ ENDP
_TEXT ENDS
END
