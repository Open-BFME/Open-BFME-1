.386
.model flat

; ?setText@WinInstanceData@@QAEXVUnicodeString@@@Z
; Exact 123 retail bytes @ 0x00499D60
; True body: ghidra FUN_00899d60 ENTRY size 123; sibling cluster with matched
; ??0WinInstanceData@0x499B40, dtor@0x499BD0, setTooltipText@0x499CC0 (m_tooltip+0x1a0).
; Queue 0x665642 was INSIDE FUN_00a655c0 (not this symbol).
; C++ blocked: DisplayStringManager::newDisplayString vtbl +0x24 vs ZH +0x18;
; DisplayString::setText vtbl +0x4 vs ZH +0x8 (systemic layout).
_TEXT SEGMENT
public ?setText@WinInstanceData@@QAEXVUnicodeString@@@Z
?setText@WinInstanceData@@QAEXVUnicodeString@@@Z PROC
    db 06Ah,0FFh,068h,038h,079h,002h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,056h,08Bh,0F1h,08Bh,086h,09Ch,001h,000h,000h,085h
    db 0C0h,0C7h,044h,024h,010h,000h,000h,000h,000h,075h,011h,08Bh,00Dh,0CCh,012h,02Fh
    db 001h,08Bh,001h,0FFh,050h,024h,089h,086h,09Ch,001h,000h,000h,051h,08Dh,054h,024h
    db 01Ch,089h,064h,024h,008h,08Bh,0CCh,052h,0E8h,053h,0E6h,03Eh,000h,08Bh,08Eh,09Ch
    db 001h,000h,000h,08Bh,001h,0FFh,050h,004h,08Dh,04Ch,024h,018h,0C7h,044h,024h,010h
    db 0FFh,0FFh,0FFh,0FFh,0E8h,007h,0E4h,03Eh,000h,08Bh,04Ch,024h,008h,064h,089h,00Dh
    db 000h,000h,000h,000h,05Eh,083h,0C4h,010h,0C2h,004h,000h
?setText@WinInstanceData@@QAEXVUnicodeString@@@Z ENDP
_TEXT ENDS
END
