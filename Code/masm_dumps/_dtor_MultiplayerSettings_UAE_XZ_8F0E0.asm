.386
.model flat

; ??1MultiplayerSettings@@UAE@XZ
; Retail @ 0x0008F0E0 size 102
; True body (queue 0x9F282F was INSIDE unrelated fn @0x9F2800).
; Proved: MultiplayerSettings vtbl 0x107F954 slot0 ILT->scalar@0x8F0B0->this;
; colocated ctor@0x8EF80/getColor@0x8F250; destroys +0x64/+0x40 AsciiString
; (MultiplayerColorDefinition), map@+0x30, SubsystemInterface base@0x9A1A40.
_TEXT SEGMENT
public ??1MultiplayerSettings@@UAE@XZ
??1MultiplayerSettings@@UAE@XZ PROC
    db 6Ah,0FFh,68h,4Eh,59h,0FFh,00h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh
    db 0F1h,89h,74h,24h,04h,8Dh,4Eh,64h
    db 0C7h,44h,24h,10h,02h,00h,00h,00h
    db 0E8h,33h,88h,7Fh,00h,8Dh,4Eh,40h
    db 0C6h,44h,24h,10h,01h,0E8h,26h,88h
    db 7Fh,00h,8Dh,4Eh,30h,0C6h,44h,24h
    db 10h,00h,0E8h,0F4h,0AEh,0FBh,0FFh,8Bh
    db 0CEh,0C7h,44h,24h,10h,0FFh,0FFh,0FFh
    db 0FFh,0E8h,0Ah,29h,91h,00h,8Bh,4Ch
    db 24h,08h,5Eh,64h,89h,0Dh,00h,00h
    db 00h,00h,83h,0C4h,10h,0C3h
??1MultiplayerSettings@@UAE@XZ ENDP
_TEXT ENDS
END
