.386
.model flat

; ?calcCRC@@YAIVAsciiString@@0@Z
; Exact 457 retail bytes @ 0x00450560.
; Drift queue 0x00AFDBD3 is INSIDE unrelated SEH fn @ 0xAFDB40 (starts mid-body
; mov [ebp-40h],edx) — not calcCRC. True body via addMap@0x4570F0 call
; site 0x4572D6 (add esp,8 = 2 by-value AsciiString args) + FileSystem::openFile
; @0x9C8860 + read loop push 1000h / call [eax+0Ch] / close [edx+8].
; C++ blocked: File vtable read@+0x0C/close@+0x08 vs ZH +0x10/+0x0C; retail CRC is
; out-of-line 3-arg helper @0x65250 (thunk 0xA984) not CRC.h forceinline; ESP-only
; alloca SEH frame (no ebp) size 0x120C.
_TEXT SEGMENT
public ?calcCRC@@YAIVAsciiString@@0@Z
?calcCRC@@YAIVAsciiString@@0@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh
    db 68h,0Bh,3Bh,02h,01h,50h,0B8h,0Ch
    db 12h,00h,00h,64h,89h,25h,00h,00h
    db 00h,00h,0E8h,0E1h,66h,5Ah,00h,53h
    db 56h,57h,33h,0DBh,89h,9Ch,24h,20h
    db 12h,00h,00h,89h,5Ch,24h,0Ch,8Bh
    db 84h,24h,2Ch,12h,00h,00h,3Bh,0C3h
    db 0C6h,84h,24h,20h,12h,00h,00h,02h
    db 8Dh,48h,08h,75h,05h,0B9h,8Bh,38h
    db 07h,01h,8Dh,54h,24h,10h,8Bh,0FFh
    db 8Ah,01h,41h,88h,02h,42h,3Ah,0C3h
    db 75h,0F6h,8Dh,44h,24h,10h,8Dh,50h
    db 01h,8Ah,08h,40h,3Ah,0CBh,75h,0F9h
    db 2Bh,0C2h,8Bh,0D0h,83h,0FAh,04h,7Ch
    db 2Ah,33h,0C0h,0B9h,41h,00h,00h,00h
    db 8Dh,0BCh,24h,14h,01h,00h,00h,0F3h
    db 0ABh,83h,0C2h,0FCh,52h,8Dh,44h,24h
    db 14h,50h,8Dh,8Ch,24h,1Ch,01h,00h
    db 00h,51h,0FFh,15h,0C0h,94h,35h,01h
    db 83h,0C4h,0Ch,8Dh,94h,24h,2Ch,12h
    db 00h,00h,52h,8Dh,4Ch,24h,10h,0E8h
    db 84h,76h,43h,00h,8Bh,44h,24h,0Ch
    db 3Bh,0C3h,74h,05h,83h,0C0h,08h,0EBh
    db 05h,0B8h,8Bh,38h,07h,01h,8Bh,0Dh
    db 48h,0CBh,34h,01h,6Ah,01h,50h,0E8h
    db 34h,82h,57h,00h,8Bh,0F0h,3Bh,0F3h
    db 75h,55h,8Dh,4Ch,24h,0Ch,0C6h,84h
    db 24h,20h,12h,00h,00h,01h,0E8h,0FDh
    db 72h,43h,00h,8Dh,8Ch,24h,28h,12h
    db 00h,00h,88h,9Ch,24h,20h,12h,00h
    db 00h,0E8h,0EAh,72h,43h,00h,8Dh,8Ch
    db 24h,2Ch,12h,00h,00h,0C7h,84h,24h
    db 20h,12h,00h,00h,0FFh,0FFh,0FFh,0FFh
    db 0E8h,0D3h,72h,43h,00h,5Fh,5Eh,33h
    db 0C0h,5Bh,8Bh,8Ch,24h,0Ch,12h,00h
    db 00h,64h,89h,0Dh,00h,00h,00h,00h
    db 81h,0C4h,18h,12h,00h,00h,0C3h,8Bh
    db 06h,68h,00h,10h,00h,00h,8Dh,8Ch
    db 24h,1Ch,02h,00h,00h,51h,8Bh,0CEh
    db 33h,0FFh,0FFh,50h,0Ch,3Bh,0C3h,7Eh
    db 2Ch,57h,50h,8Dh,94h,24h,20h,02h
    db 00h,00h,52h,0E8h,0D4h,0A2h,0BBh,0FFh
    db 83h,0C4h,0Ch,68h,00h,10h,00h,00h
    db 8Dh,8Ch,24h,1Ch,02h,00h,00h,8Bh
    db 0F8h,8Bh,06h,51h,8Bh,0CEh,0FFh,50h
    db 0Ch,3Bh,0C3h,7Fh,0D4h,8Bh,16h,8Bh
    db 0CEh,0FFh,52h,08h,8Dh,4Ch,24h,0Ch
    db 0C6h,84h,24h,20h,12h,00h,00h,01h
    db 0E8h,5Bh,72h,43h,00h,8Dh,8Ch,24h
    db 28h,12h,00h,00h,88h,9Ch,24h,20h
    db 12h,00h,00h,0E8h,48h,72h,43h,00h
    db 8Dh,8Ch,24h,2Ch,12h,00h,00h,0C7h
    db 84h,24h,20h,12h,00h,00h,0FFh,0FFh
    db 0FFh,0FFh,0E8h,31h,72h,43h,00h,8Bh
    db 8Ch,24h,18h,12h,00h,00h,8Bh,0C7h
    db 5Fh,5Eh,5Bh,64h,89h,0Dh,00h,00h
    db 00h,00h,81h,0C4h,18h,12h,00h,00h
    db 0C3h
?calcCRC@@YAIVAsciiString@@0@Z ENDP
_TEXT ENDS
END
