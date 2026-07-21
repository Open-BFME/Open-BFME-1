.386
.model flat

; ??0DamageFXStore@@QAE@XZ
; Exact 113 retail bytes @ 0x00067C10
; True body (queue 0x009F272E was int3 pad before matched ??0ControlBar@@QAE@XZ).
; Identity: adjacent to matched parseDamageFXDefinition@0x67A60; SubsystemInterface
; base @0x9A1A30; m_dfxmap@+8 with 0x64 buckets; clear. C++ emits fat STLport
; hashtable(n,hash,eq,alloc) with stack temps (109B) vs retail empty-functor inline.
_TEXT SEGMENT
public ??0DamageFXStore@@QAE@XZ
??0DamageFXStore@@QAE@XZ PROC
    db 06Ah,0FFh,068h,08Eh,02Ah,0FFh,000h,064h
    db 0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,008h
    db 056h,08Bh,0F1h,057h,089h,074h,024h,008h
    db 0E8h,0FBh,09Dh,093h,000h,033h,0C0h,08Dh
    db 07Eh,008h,08Bh,0CFh,0C7h,006h,0F8h,058h
    db 007h,001h,089h,041h,004h,089h,041h,008h
    db 089h,044h,024h,018h,089h,04Ch,024h,00Ch
    db 089h,041h,00Ch,06Ah,064h,0C6h,044h,024h
    db 01Ch,001h,089h,041h,010h,0E8h,09Ah,064h
    db 0FAh,0FFh,08Bh,0CFh,0C6h,044h,024h,018h
    db 002h,0E8h,088h,0ADh,0FDh,0FFh,08Bh,04Ch
    db 024h,010h,05Fh,08Bh,0C6h,05Eh,064h,089h
    db 00Dh,000h,000h,000h,000h,083h,0C4h,014h
    db 0C3h
??0DamageFXStore@@QAE@XZ ENDP
_TEXT ENDS
END
