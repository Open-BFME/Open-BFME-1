.386
.model flat

; ??1RTS2DScene@@UAE@XZ
; Retail @ 0x00711980 size 143
; Identity: stores RTS2DScene vtables 0x1120A80/0x1120A50 (same as matched ctor),
; Remove_Render_Object(m_status@+0x110), ref-release, member dtor @+0x108, SimpleScene dtor.
; Queue candidate 0x009F27F2 was mid-neighbor (mov eax,imm;ret + int3); true ENTRY is here.
_TEXT SEGMENT
public ??1RTS2DScene@@UAE@XZ
??1RTS2DScene@@UAE@XZ PROC
    db 6Ah,0FFh,68h,01h,0C7h,04h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,08h
    db 56h,8Bh,0F1h,57h,8Dh,0BEh,08h,01h
    db 00h,00h,89h,74h,24h,0Ch,0C7h,06h
    db 80h,0Ah,12h,01h,0C7h,07h,50h,0Ah
    db 12h,01h,8Bh,86h,10h,01h,00h,00h
    db 50h,0C7h,44h,24h,1Ch,01h,00h,00h
    db 00h,0E8h,0FAh,1Eh,23h,00h,8Bh,8Eh
    db 10h,01h,00h,00h,85h,0C9h,74h,13h
    db 0FFh,49h,04h,75h,04h,8Bh,11h,0FFh
    db 12h,0C7h,86h,10h,01h,00h,00h,00h
    db 00h,00h,00h,8Bh,0CFh,0C6h,44h,24h
    db 18h,00h,0E8h,51h,00h,29h,00h,8Bh
    db 0CEh,0C7h,44h,24h,18h,0FFh,0FFh,0FFh
    db 0FFh,0E8h,72h,24h,23h,00h,8Bh,4Ch
    db 24h,10h,5Fh,5Eh,64h,89h,0Dh,00h
    db 00h,00h,00h,83h,0C4h,14h,0C3h
??1RTS2DScene@@UAE@XZ ENDP
_TEXT ENDS
END
