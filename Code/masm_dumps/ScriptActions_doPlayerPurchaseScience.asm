.386
.model flat

; ?doPlayerPurchaseScience@ScriptActions@@IAEXABVAsciiString@@0@Z
; Exact 91 retail bytes @ 0x006F0140; resolves a player and purchases the requested science.
_TEXT SEGMENT
public ?doPlayerPurchaseScience@ScriptActions@@IAEXABVAsciiString@@0@Z
?doPlayerPurchaseScience@ScriptActions@@IAEXABVAsciiString@@0@Z PROC
    db 08Bh,044h,024h,008h,08Bh,00Dh,0ACh,0D7h,02Eh,001h,056h,050h,0E8h,01Bh,0B2h,0D5h
    db 0FFh,08Bh,0F0h,083h,0FEh,0FFh,074h,03Fh,08Bh,04Ch,024h,008h,06Ah,000h,051h,08Bh
    db 00Dh,06Ch,007h,02Fh,001h,0E8h,026h,0B1h,0D5h,0FFh,066h,085h,0C0h,089h,044h,024h
    db 00Ch,074h,024h,08Bh,00Dh,048h,0D7h,02Eh,001h,08Dh,054h,024h,00Ch,052h,0E8h,0DDh
    db 0ECh,0D3h,0FFh,085h,0C0h,074h,008h,056h,08Bh,0C8h,0E8h,035h,04Ah,0D1h,0FFh,066h
    db 083h,07Ch,024h,00Ch,000h,075h,0DCh,05Eh,0C2h,008h,000h
?doPlayerPurchaseScience@ScriptActions@@IAEXABVAsciiString@@0@Z ENDP
_TEXT ENDS
END
