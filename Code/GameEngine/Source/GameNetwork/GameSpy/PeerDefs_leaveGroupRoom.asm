.386
.model flat

; ?leaveGroupRoom@GameSpyInfo@@UAEXXZ
; Exact 188 retail bytes @ 0x00634CE0
; Identity: PEERREQUEST_LEAVEGROUPROOM(5) + addRequest + setCurrentGroupRoom(0) + m_playerInfoMap.clear
; Queue RVA 0x637480 was FUN_00a37480 (35B) — wrong; true ghidra ENTRY @ 0x634CE0 size 188
_TEXT SEGMENT
public ?leaveGroupRoom@GameSpyInfo@@UAEXXZ
?leaveGroupRoom@GameSpyInfo@@UAEXXZ PROC
    db 06Ah,0FFh,068h,04Bh,00Bh,004h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,081h,0ECh,094h,001h,000h,000h,056h,08Bh,0F1h,08Dh,04Ch
    db 024h,004h,0E8h,0F5h,024h,09Eh,0FFh,08Bh,006h,08Bh,0CEh,0C7h,084h,024h,0A0h,001h
    db 000h,000h,000h,000h,000h,000h,0C7h,044h,024h,004h,005h,000h,000h,000h,0FFh,050h
    db 02Ch,08Bh,00Dh,0C8h,071h,02Fh,001h,089h,084h,024h,0E8h,000h,000h,000h,08Bh,011h
    db 08Dh,044h,024h,004h,050h,0FFh,052h,018h,08Bh,016h,06Ah,000h,08Bh,0CEh,0FFh,052h
    db 028h,08Bh,046h,050h,083h,0C6h,04Ch,085h,0C0h,074h,027h,08Bh,006h,08Bh,048h,004h
    db 051h,08Bh,0CEh,0E8h,0BAh,011h,0A0h,0FFh,08Bh,006h,089h,040h,008h,08Bh,016h,0C7h
    db 042h,004h,000h,000h,000h,000h,08Bh,006h,089h,040h,00Ch,0C7h,046h,004h,000h,000h
    db 000h,000h,08Dh,04Ch,024h,004h,0C7h,084h,024h,0A0h,001h,000h,000h,0FFh,0FFh,0FFh
    db 0FFh,0E8h,04Fh,01Eh,09Eh,0FFh,08Bh,08Ch,024h,098h,001h,000h,000h,05Eh,064h,089h
    db 00Dh,000h,000h,000h,000h,081h,0C4h,0A0h,001h,000h,000h,0C3h
?leaveGroupRoom@GameSpyInfo@@UAEXXZ ENDP
_TEXT ENDS
END
