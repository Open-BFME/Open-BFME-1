.386
.model flat

; ?WriteGroupDataChunk@ScriptGroup@@SAXAAVDataChunkOutput@@PAV1@@Z
; Exact 204 retail bytes @ 0x00759EE0; writes the BFME script-group tree.
_TEXT SEGMENT
public ?WriteGroupDataChunk@ScriptGroup@@SAXAAVDataChunkOutput@@PAV1@@Z
?WriteGroupDataChunk@ScriptGroup@@SAXAAVDataChunkOutput@@PAV1@@Z PROC
    db 053h,08Bh,05Ch,024h,010h,085h,0DBh,00Fh,084h,0BDh,000h,000h,000h,055h,08Bh,06Ch
    db 024h,010h,056h,057h,08Bh,07Ch,024h,014h,0EBh,006h,08Dh,09Bh,000h,000h,000h,000h
    db 08Bh,043h,004h,08Bh,04Dh,018h,08Bh,053h,008h,08Dh,004h,080h,08Dh,004h,081h,00Fh
    db 0BFh,048h,00Eh,03Bh,0CAh,00Fh,085h,082h,000h,000h,000h,08Ah,048h,00Ch,084h,0C9h
    db 075h,07Bh,00Fh,0BFh,048h,00Eh,03Bh,0CAh,08Bh,070h,010h,07Eh,008h,02Bh,0CAh,090h
    db 049h,08Bh,036h,075h,0FBh,06Ah,003h,068h,078h,084h,00Eh,001h,08Bh,0CFh,0E8h,013h
    db 003h,0CEh,0FFh,08Bh,043h,004h,08Dh,014h,080h,08Bh,045h,018h,08Dh,04Ch,090h,008h
    db 051h,08Bh,0CFh,0E8h,066h,04Ch,0CCh,0FFh,033h,0D2h,08Ah,056h,010h,08Bh,0CFh,052h
    db 0E8h,01Eh,06Ah,0CBh,0FFh,033h,0C0h,08Ah,046h,011h,08Bh,0CFh,050h,0E8h,011h,06Ah
    db 0CBh,0FFh,08Bh,046h,008h,085h,0C0h,074h,00Bh,050h,055h,057h,0E8h,08Fh,083h,0CAh
    db 0FFh,083h,0C4h,00Ch,08Bh,076h,00Ch,085h,0F6h,074h,00Bh,056h,055h,057h,0E8h,040h
    db 0E6h,0CCh,0FFh,083h,0C4h,00Ch,08Bh,0CFh,0E8h,0A5h,0ABh,0CAh,0FFh,08Bh,01Bh,085h
    db 0DBh,00Fh,085h,059h,0FFh,0FFh,0FFh,05Fh,05Eh,05Dh,05Bh,0C3h
?WriteGroupDataChunk@ScriptGroup@@SAXAAVDataChunkOutput@@PAV1@@Z ENDP
_TEXT ENDS
END
