.386
.model flat
; ?ConstructNetCommandMsgFromRawData@NetPacket@@SAPAVNetCommandRef@@PAEG@Z
; Exact 515B @ 0x00682FF0; Open-BFME4
_TEXT SEGMENT
public ?ConstructNetCommandMsgFromRawData@NetPacket@@SAPAVNetCommandRef@@PAEG@Z
?ConstructNetCommandMsgFromRawData@NetPacket@@SAPAVNetCommandRef@@PAEG@Z PROC
    db 6Ah, 0FFh, 68h, 0B1h, 61h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h
    db 0C7h, 04h, 24h, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h, 1Ch, 83h, 0F8h, 03h, 0C7h, 44h
    db 24h, 10h, 01h, 00h, 00h, 00h, 75h, 15h, 6Ah, 18h, 68h, 2Ch, 0AEh, 11h, 01h, 8Dh
    db 4Ch, 24h, 08h, 0E8h, 0E8h, 4Ch, 20h, 00h, 0E9h, 7Dh, 01h, 00h, 00h, 83h, 0F8h, 05h
    db 75h, 15h, 6Ah, 2Ch, 68h, 0F4h, 0ADh, 11h, 01h, 8Dh, 4Ch, 24h, 08h, 0E8h, 0CEh, 4Ch
    db 20h, 00h, 0E9h, 63h, 01h, 00h, 00h, 83h, 0F8h, 06h, 75h, 0Ah, 68h, 0C8h, 0ADh, 11h
    db 01h, 0E9h, 4Bh, 01h, 00h, 00h, 83h, 0F8h, 04h, 75h, 0Ah, 68h, 0A8h, 0ADh, 11h, 01h
    db 0E9h, 3Ch, 01h, 00h, 00h, 83h, 0F8h, 0Ah, 75h, 0Ah, 68h, 88h, 0ADh, 11h, 01h, 0E9h
    db 2Dh, 01h, 00h, 00h, 83h, 0F8h, 08h, 75h, 0Ah, 68h, 58h, 0ADh, 11h, 01h, 0E9h, 1Eh
    db 01h, 00h, 00h, 83h, 0F8h, 09h, 75h, 0Ah, 68h, 30h, 0ADh, 11h, 01h, 0E9h, 0Fh, 01h
    db 00h, 00h, 83h, 0F8h, 07h, 75h, 0Ah, 68h, 08h, 0ADh, 11h, 01h, 0E9h, 00h, 01h, 00h
    db 00h, 83h, 0F8h, 0Bh, 75h, 0Ah, 68h, 0E4h, 0ACh, 11h, 01h, 0E9h, 0F1h, 00h, 00h, 00h
    db 85h, 0C0h, 75h, 0Ah, 68h, 0C8h, 0ACh, 11h, 01h, 0E9h, 0E3h, 00h, 00h, 00h, 83h, 0F8h
    db 01h, 75h, 0Ah, 68h, 0A8h, 0ACh, 11h, 01h, 0E9h, 0D4h, 00h, 00h, 00h, 83h, 0F8h, 02h
    db 75h, 0Ah, 68h, 88h, 0ACh, 11h, 01h, 0E9h, 0C5h, 00h, 00h, 00h, 83h, 0F8h, 0Ch, 75h
    db 0Ah, 68h, 68h, 0ACh, 11h, 01h, 0E9h, 0B6h, 00h, 00h, 00h, 83h, 0F8h, 0Dh, 75h, 0Ah
    db 68h, 44h, 0ACh, 11h, 01h, 0E9h, 0A7h, 00h, 00h, 00h, 83h, 0F8h, 0Eh, 75h, 0Ah, 68h
    db 2Ch, 0ACh, 11h, 01h, 0E9h, 98h, 00h, 00h, 00h, 83h, 0F8h, 18h, 75h, 0Ah, 68h, 00h
    db 0ACh, 11h, 01h, 0E9h, 89h, 00h, 00h, 00h, 83h, 0F8h, 19h, 75h, 07h, 68h, 0D8h, 0ABh
    db 11h, 01h, 0EBh, 7Dh, 83h, 0F8h, 1Ah, 75h, 07h, 68h, 0B4h, 0ABh, 11h, 01h, 0EBh, 71h
    db 83h, 0F8h, 0Fh, 75h, 07h, 68h, 98h, 0ABh, 11h, 01h, 0EBh, 65h, 83h, 0F8h, 10h, 75h
    db 07h, 68h, 74h, 0ABh, 11h, 01h, 0EBh, 59h, 83h, 0F8h, 11h, 75h, 07h, 68h, 50h, 0ABh
    db 11h, 01h, 0EBh, 4Dh, 83h, 0F8h, 12h, 75h, 07h, 68h, 34h, 0ABh, 11h, 01h, 0EBh, 41h
    db 83h, 0F8h, 13h, 75h, 07h, 68h, 1Ch, 0ABh, 11h, 01h, 0EBh, 35h, 83h, 0F8h, 14h, 75h
    db 07h, 68h, 0F8h, 0AAh, 11h, 01h, 0EBh, 29h, 83h, 0F8h, 15h, 75h, 07h, 68h, 0D4h, 0AAh
    db 11h, 01h, 0EBh, 1Dh, 83h, 0F8h, 1Bh, 75h, 07h, 68h, 0ACh, 0AAh, 11h, 01h, 0EBh, 11h
    db 83h, 0F8h, 1Ch, 75h, 07h, 68h, 80h, 0AAh, 11h, 01h, 0EBh, 05h, 68h, 34h, 02h, 08h
    db 01h, 8Dh, 4Ch, 24h, 04h, 0E8h, 99h, 7Bh, 98h, 0FFh, 56h, 8Bh, 74h, 24h, 1Ch, 8Dh
    db 44h, 24h, 04h, 50h, 8Bh, 0CEh, 0E8h, 95h, 49h, 20h, 00h, 8Dh, 4Ch, 24h, 04h, 0C7h
    db 44h, 24h, 08h, 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 14h, 00h, 0E8h, 5Fh, 47h, 20h
    db 00h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 14h, 0C3h
?ConstructNetCommandMsgFromRawData@NetPacket@@SAPAVNetCommandRef@@PAEG@Z ENDP
_TEXT ENDS
END
