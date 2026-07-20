.386
.model flat
; ?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ
; Exact 44B @ 0x14EEB0; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ
?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 1Ch, 0E8h, 0B5h, 0F6h, 0EBh, 0FFh, 85h, 0C0h, 74h, 0Bh, 8Bh
    db 0C8h, 0E8h, 0D2h, 05h, 0ECh, 0FFh, 85h, 0C0h, 75h, 07h, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Eh
    db 0C3h, 8Bh, 0CEh, 0E8h, 3Bh, 30h, 0ECh, 0FFh, 33h, 0C0h, 5Eh, 0C3h
?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ ENDP
_TEXT ENDS
END
