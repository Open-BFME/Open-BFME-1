.386
.model flat

; ?isValidMap@@YA_NVAsciiString@@_N@Z
; Exact 170 retail bytes @ 0x00457ED0 (ghidra FUN_00857ed0).
; Drift queue 0x0078935E is mid-body of unrelated fn (starts 0x7892f0,
; "%s.const" path) — not isValidMap. Shape blockers vs ZH C++:
; BFME isEmpty is cmp word [m_data+4],0 (length); ZH peeks first char;
; by-value dtor is single call freeBytes@0x887940 (ICF), not inlined
; InterlockedDecrement; SEH-state store before mapName load.
_TEXT SEGMENT
public ?isValidMap@@YA_NVAsciiString@@_N@Z
?isValidMap@@YA_NVAsciiString@@_N@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh
    db 68h,18h,43h,02h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,56h,8Bh,0Dh
    db 94h,15h,2Fh,01h,85h,0C9h,0C7h,44h
    db 24h,0Ch,00h,00h,00h,00h,74h,5Fh
    db 8Bh,44h,24h,14h,85h,0C0h,74h,57h
    db 66h,83h,78h,04h,00h,74h,50h,0E8h
    db 00h,10h,0BCh,0FFh,8Dh,4Ch,24h,14h
    db 0E8h,8Bh,0FEh,42h,00h,8Bh,35h,94h
    db 15h,2Fh,01h,8Dh,44h,24h,14h,50h
    db 8Bh,0CEh,0E8h,0B0h,0E4h,0BCh,0FFh,3Bh
    db 06h,74h,2Ch,8Ah,4Ch,24h,18h,3Ah
    db 48h,38h,75h,23h,8Dh,4Ch,24h,14h
    db 0C7h,44h,24h,0Ch,0FFh,0FFh,0FFh,0FFh
    db 0E8h,0FBh,0F9h,42h,00h,0B0h,01h,8Bh
    db 4Ch,24h,04h,64h,89h,0Dh,00h,00h
    db 00h,00h,5Eh,83h,0C4h,0Ch,0C3h,8Dh
    db 4Ch,24h,14h,0C7h,44h,24h,0Ch,0FFh
    db 0FFh,0FFh,0FFh,0E8h,0D8h,0F9h,42h,00h
    db 8Bh,4Ch,24h,04h,32h,0C0h,64h,89h
    db 0Dh,00h,00h,00h,00h,5Eh,83h,0C4h
    db 0Ch,0C3h
?isValidMap@@YA_NVAsciiString@@_N@Z ENDP
_TEXT ENDS
END
