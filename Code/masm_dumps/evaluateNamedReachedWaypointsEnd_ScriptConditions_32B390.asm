.386
.model flat

; ?evaluateNamedReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z
; Exact 311 retail bytes @ 0x0032B390
; identity: evaluateCondition jump table case NAMED_REACHED_WAYPOINTS_END (enum 34)
;   switch @ 0x32D720 jmp [type-5]*4+0x32FB4C -> case 0x32DF5A calls thunk 0x21A53 -> body 0x32B390
; semantics: TheScriptEngine vcall+0x68 getUnitNamed; Object+0x204 AI; AI+0x13c completedWaypoint;
;   Parameter string +0x10; pathLabel1/2/3 compare via getters; ret 8
; queue RVA 0x7892F0 was wrong fn (FUN "%s.const"/op new 0x30, size 261, plain ret)
; C++ blocked: ScriptEngine vtbl getUnitNamed 0x68 vs ZH 0x5c; Object.m_ai 0x204 vs 0x19c;
;   AI.m_completedWaypoint 0x13c vs 0x12c; Parameter string 0x10 vs 0x14 (class layout)
_TEXT SEGMENT
public ?evaluateNamedReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z
?evaluateNamedReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z PROC
    db 064h,0A1h,000h,000h,000h,000h,08Bh,00Dh,06Ch,007h,02Fh,001h,08Bh,054h,024h,004h
    db 06Ah,0FFh,068h,078h,073h,001h,001h,050h,064h,089h,025h,000h,000h,000h,000h,08Bh
    db 001h,053h,056h,052h,0FFh,050h,068h,085h,0C0h,00Fh,084h,0F3h,000h,000h,000h,08Bh
    db 080h,004h,002h,000h,000h,085h,0C0h,00Fh,084h,0E5h,000h,000h,000h,08Bh,0B0h,03Ch
    db 001h,000h,000h,085h,0F6h,00Fh,084h,0D7h,000h,000h,000h,08Bh,044h,024h,01Ch,083h
    db 0C0h,010h,050h,08Dh,04Ch,024h,01Ch,0E8h,074h,0C7h,055h,000h,08Dh,04Ch,024h,01Ch
    db 051h,08Bh,0CEh,0C7h,044h,024h,014h,000h,000h,000h,000h,0E8h,0B4h,067h,0D1h,0FFh
    db 08Dh,054h,024h,018h,052h,08Bh,0C8h,0E8h,0B9h,06Ch,0CFh,0FFh,08Bh,0D8h,0F7h,0DBh
    db 01Ah,0DBh,08Dh,04Ch,024h,01Ch,0FEh,0C3h,0E8h,023h,0C5h,055h,000h,084h,0DBh,075h
    db 02Dh,08Dh,044h,024h,01Ch,050h,08Bh,0CEh,0E8h,0F8h,0D4h,0CFh,0FFh,08Dh,04Ch,024h
    db 018h,051h,08Bh,0C8h,0E8h,08Ch,06Ch,0CFh,0FFh,08Bh,0D8h,0F7h,0DBh,01Ah,0DBh,08Dh
    db 04Ch,024h,01Ch,0FEh,0C3h,0E8h,0F6h,0C4h,055h,000h,084h,0DBh,074h,026h,08Dh,04Ch
    db 024h,018h,0C7h,044h,024h,010h,0FFh,0FFh,0FFh,0FFh,0E8h,0E1h,0C4h,055h,000h,0B0h
    db 001h,08Bh,04Ch,024h,008h,064h,089h,00Dh,000h,000h,000h,000h,05Eh,05Bh,083h,0C4h
    db 00Ch,0C2h,008h,000h,08Dh,054h,024h,01Ch,052h,08Bh,0CEh,0E8h,0CBh,01Ch,0D0h,0FFh
    db 08Dh,04Ch,024h,018h,051h,08Bh,0C8h,0E8h,039h,06Ch,0CFh,0FFh,08Bh,0D8h,0F7h,0DBh
    db 01Ah,0DBh,08Dh,04Ch,024h,01Ch,0FEh,0C3h,0E8h,0A3h,0C4h,055h,000h,08Dh,04Ch,024h
    db 018h,0C7h,044h,024h,010h,0FFh,0FFh,0FFh,0FFh,0E8h,092h,0C4h,055h,000h,084h,0DBh
    db 075h,0ADh,08Bh,04Ch,024h,008h,05Eh,032h,0C0h,064h,089h,00Dh,000h,000h,000h,000h
    db 05Bh,083h,0C4h,00Ch,0C2h,008h,000h
?evaluateNamedReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z ENDP
_TEXT ENDS
END
