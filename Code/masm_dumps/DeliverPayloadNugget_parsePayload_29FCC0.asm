.386
.model flat

; ?parsePayload@DeliverPayloadNugget@@SAXPAVINI@@PAX1PBX@Z
; Exact 217B retail @ 0x0029FCC0; queue 0x0029FCBF was leading int3.
; Identity: SEH parse name+count into vector<{str,int}> at self+0x1C; first 53B
; matches C++ compile; adjacent COMDAT push_back@vector<Payload> @ 0x29FC70 (8B elems).
; Zero FieldParse/xref (DeliverPayload DCE) but body retained; C++ blocked by
; AsciiString::set vs StringBase::set(PBDH) + layout + regalloc.
_TEXT SEGMENT
public ?parsePayload@DeliverPayloadNugget@@SAXPAVINI@@PAX1PBX@Z
?parsePayload@DeliverPayloadNugget@@SAXPAVINI@@PAX1PBX@Z PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 88h, 24h, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 56h, 8Bh, 74h, 24h, 1Ch, 57h, 6Ah, 00h
    db 8Bh, 0CEh, 0E8h, 89h, 0Ch, 5Bh, 00h, 6Ah, 00h, 8Bh, 0CEh, 8Bh, 0F8h, 0E8h, 0CEh, 0Ch
    db 5Bh, 00h, 85h, 0C0h, 74h, 0Bh, 50h, 0E8h, 24h, 29h, 5Bh, 00h, 83h, 0C4h, 04h, 0EBh
    db 05h, 0B8h, 01h, 00h, 00h, 00h, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 85h, 0FFh
    db 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 89h, 44h, 24h, 0Ch, 74h, 10h, 8Bh, 0C7h
    db 8Dh, 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 0EBh, 02h, 33h, 0C0h
    db 50h, 57h, 8Dh, 4Ch, 24h, 10h, 0E8h, 0E5h, 7Fh, 5Eh, 00h, 8Bh, 74h, 24h, 24h, 8Bh
    db 4Eh, 24h, 8Bh, 46h, 20h, 83h, 0C6h, 1Ch, 3Bh, 0C1h, 8Dh, 4Ch, 24h, 08h, 74h, 15h
    db 51h, 50h, 0E8h, 94h, 0A6h, 0D9h, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 83h, 0C0h, 08h
    db 89h, 46h, 04h, 0EBh, 12h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 2Ch, 52h, 51h, 50h
    db 8Bh, 0CEh, 0E8h, 0ABh, 0F2h, 0D8h, 0FFh, 8Dh, 4Ch, 24h, 08h, 0C7h, 44h, 24h, 18h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 0B8h, 7Bh, 5Eh, 00h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?parsePayload@DeliverPayloadNugget@@SAXPAVINI@@PAX1PBX@Z ENDP
_TEXT ENDS
END
