.386
.model flat

; ?doAmbientSoundsPause@ScriptActions@@IAEX_N@Z
; Exact 30 retail bytes @ 0x002EF2E0
_TEXT SEGMENT
public ?doAmbientSoundsPause@ScriptActions@@IAEX_N@Z
?doAmbientSoundsPause@ScriptActions@@IAEX_N@Z PROC
    db 08Ah, 04Ch, 024h, 004h, 033h, 0C0h, 084h, 0C9h
    db 08Bh, 00Dh, 068h, 0D6h, 02Eh, 001h, 08Bh, 011h
    db 00Fh, 094h, 0C0h, 050h, 06Ah, 001h, 06Ah, 000h
    db 0FFh, 052h, 070h, 0C2h, 004h, 000h
?doAmbientSoundsPause@ScriptActions@@IAEX_N@Z ENDP
_TEXT ENDS
END
