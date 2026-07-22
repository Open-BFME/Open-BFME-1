.386
.model flat

; ?parseAiDataDefinition@AI@@SAXPAVINI@@@Z
; Exact 50 retail bytes @ RVA 0x0014E580.
; Identity: sole .text push of TheAIFieldParseTable (StructureSeconds..),
; TheAI @ 0x12EF214, newOverride @ 0x44404, initFromINI @ 0x8520A0.
; C++ blocked: BFME INI::m_loadType at +8 vs ZH File+8K buffer layout (+0x2010).
_TEXT SEGMENT
public ?parseAiDataDefinition@AI@@SAXPAVINI@@@Z
?parseAiDataDefinition@AI@@SAXPAVINI@@@Z PROC
    db 08Bh,00Dh,014h,0F2h,02Eh,001h,085h,0C9h
    db 074h,027h,056h,08Bh,074h,024h,008h,083h
    db 07Eh,008h,002h,075h,00Bh,0E8h,06Ah,05Eh
    db 0EFh,0FFh,08Bh,00Dh,014h,0F2h,02Eh,001h
    db 08Bh,041h,014h,068h,000h,04Bh,009h,001h
    db 050h,08Bh,0CEh,0E8h,0F0h,03Ah,070h,000h
    db 05Eh,0C3h
?parseAiDataDefinition@AI@@SAXPAVINI@@@Z ENDP
_TEXT ENDS
END
