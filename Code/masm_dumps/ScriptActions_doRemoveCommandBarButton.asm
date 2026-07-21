.386
.model flat

; ?doRemoveCommandBarButton@ScriptActions@@IAEXABVAsciiString@@0@Z
; Exact 463 retail bytes @ 0x002FC570; queue RVA 0x002FC632 was INSIDE this body.
; BFME expands ZH doRemove: primary CommandSet loop + ThingTemplate+0x294 vector of related sets.
; Identity: only setControlBarOverride callers are doAdd@0x2F0740 and this fn; ret 8; findTemplate+findCommandSet+getCommandButton.
_TEXT SEGMENT
public ?doRemoveCommandBarButton@ScriptActions@@IAEXABVAsciiString@@0@Z
?doRemoveCommandBarButton@ScriptActions@@IAEXABVAsciiString@@0@Z PROC
    db 083h,0ECh,010h,08Bh,044h,024h,018h,08Bh,00Dh,0D8h,0F1h,02Eh,001h,055h,050h,0E8h
    db 0DCh,0BFh,0D2h,0FFh,08Bh,0E8h,085h,0EDh,089h,06Ch,024h,010h,00Fh,084h,0A6h,001h
    db 000h,000h,08Bh,00Dh,0F8h,033h,02Fh,001h,053h,056h,057h,08Dh,05Dh,02Ch,053h,0E8h
    db 026h,0C7h,0D4h,0FFh,08Bh,0F8h,033h,0F6h,085h,0FFh,074h,033h,056h,08Bh,0CFh,0E8h
    db 0CCh,079h,0D0h,0FFh,085h,0C0h,074h,027h,056h,08Bh,0CFh,0E8h,0C0h,079h,0D0h,0FFh
    db 08Bh,04Ch,024h,024h,051h,08Dh,048h,00Ch,0E8h,0F8h,05Ah,0D2h,0FFh,085h,0C0h,075h
    db 00Eh,08Bh,00Dh,098h,008h,02Fh,001h,050h,056h,053h,0E8h,05Eh,053h,0D0h,0FFh,046h
    db 083h,0FEh,014h,07Ch,0C3h,08Bh,0B5h,094h,002h,000h,000h,08Bh,08Dh,098h,002h,000h
    db 000h,02Bh,0CEh,0B8h,067h,066h,066h,066h,0F7h,0E9h,0C1h,0FAh,003h,08Bh,0C2h,0C1h
    db 0E8h,01Fh,033h,0FFh,003h,0C2h,085h,0C0h,089h,07Ch,024h,010h,00Fh,08Eh,023h,001h
    db 000h,000h,033h,0DBh,089h,05Ch,024h,014h,085h,0DBh,00Fh,08Ch,0E2h,000h,000h,000h
    db 03Bh,0F8h,00Fh,083h,0DAh,000h,000h,000h,08Bh,04Ch,033h,008h,085h,0C9h,00Fh,084h
    db 0CEh,000h,000h,000h,08Bh,011h,0FFh,052h,03Ch,085h,0C0h,00Fh,084h,0C1h,000h,000h
    db 000h,08Bh,00Dh,0F8h,033h,02Fh,001h,083h,0C0h,070h,050h,089h,044h,024h,01Ch,0E8h
    db 076h,0C6h,0D4h,0FFh,08Bh,0F0h,089h,074h,024h,028h,033h,0EDh,08Dh,064h,024h,000h
    db 085h,0F6h,00Fh,084h,084h,000h,000h,000h,055h,08Bh,0CEh,0E8h,010h,079h,0D0h,0FFh
    db 085h,0C0h,074h,078h,055h,08Bh,0CEh,0E8h,004h,079h,0D0h,0FFh,08Bh,04Ch,024h,024h
    db 08Bh,009h,083h,0C0h,00Ch,085h,0C9h,074h,006h,00Fh,0B7h,059h,004h,0EBh,002h,033h
    db 0DBh,085h,0C9h,08Dh,079h,008h,075h,005h,0BFh,08Bh,038h,007h,001h,08Bh,000h,085h
    db 0C0h,074h,006h,00Fh,0B7h,050h,004h,0EBh,002h,033h,0D2h,085h,0C0h,08Dh,070h,008h
    db 075h,005h,0BEh,08Bh,038h,007h,001h,03Bh,0D3h,08Bh,0CAh,07Ch,002h,08Bh,0CBh,033h
    db 0C0h,0F3h,0A6h,074h,005h,01Bh,0C0h,083h,0D8h,0FFh,085h,0C0h,075h,01Ah,02Bh,0D3h
    db 08Bh,0C2h,085h,0C0h,075h,012h,08Bh,00Dh,098h,008h,02Fh,001h,052h,08Bh,054h,024h
    db 01Ch,055h,052h,0E8h,055h,052h,0D0h,0FFh,08Bh,074h,024h,028h,045h,083h,0FDh,014h
    db 00Fh,08Ch,06Ah,0FFh,0FFh,0FFh,08Bh,06Ch,024h,01Ch,08Bh,05Ch,024h,014h,08Bh,07Ch
    db 024h,010h,08Bh,0B5h,094h,002h,000h,000h,08Bh,08Dh,098h,002h,000h,000h,02Bh,0CEh
    db 0B8h,067h,066h,066h,066h,0F7h,0E9h,0C1h,0FAh,003h,08Bh,0C2h,0C1h,0E8h,01Fh,047h
    db 083h,0C3h,014h,003h,0C2h,03Bh,0F8h,089h,07Ch,024h,010h,089h,05Ch,024h,014h,00Fh
    db 08Ch,0E3h,0FEh,0FFh,0FFh,05Fh,05Eh,05Bh,05Dh,083h,0C4h,010h,0C2h,008h,000h
?doRemoveCommandBarButton@ScriptActions@@IAEXABVAsciiString@@0@Z ENDP
_TEXT ENDS
END
