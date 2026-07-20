.386
.model flat

; ?doDebugMessage@ScriptActions@@IAEXABVAsciiString@@_N@Z
; Exact 51 retail bytes @ 0x006F20E0; BFME dispatches through the GUI message interface.
_TEXT SEGMENT
public ?doDebugMessage@ScriptActions@@IAEXABVAsciiString@@_N@Z
?doDebugMessage@ScriptActions@@IAEXABVAsciiString@@_N@Z PROC
    db 51h,8Bh,44h,24h,08h,6Ah,00h,51h
    db 89h,64h,24h,08h,8Bh,0CCh,50h,0E8h
    db 6Ch,5Ah,59h,00h,8Bh,0Dh,6Ch,07h
    db 2Fh,01h,8Bh,11h,0FFh,52h,44h,85h
    db 0C0h,74h,0Ch,8Bh,4Ch,24h,0Ch,51h
    db 8Bh,0C8h,0E8h,39h,0B0h,0D1h,0FFh,59h
    db 0C2h,08h,00h
?doDebugMessage@ScriptActions@@IAEXABVAsciiString@@_N@Z ENDP
_TEXT ENDS
END
