.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??1AIUpdateArrayElement@@QAE@XZ:NEAR
EXTERN ??1BFMERetailAsciiString@@QAE@XZ:NEAR
EXTERN ??1RenderObjClass@@UAE@XZ:NEAR
EXTERN ??1SubsystemInterface@@UAE@XZ:NEAR
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:NEAR
EXTERN ??_V@YAXPAX@Z:NEAR
EXTERN ?j_00001c80@@YAXXZ:NEAR
EXTERN ?j_00001f05@@YAXXZ:NEAR
EXTERN ?j_00005d2b@@YAXXZ:NEAR
EXTERN ?j_0001570d@@YAXXZ:NEAR
EXTERN ?j_00030652@@YAXXZ:NEAR
_TEXT SEGMENT

; retail @ 0x00BF2738 size 11
_TEXT ENDS
_TEXT$d00ff2738 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00FF2738 size 11
public ?d_00bf2738@@YAXXZ
?d_00bf2738@@YAXXZ PROC
    db 08Bh, 04Dh, 010h, 083h, 0C1h, 010h
    jmp ??1BFMERetailAsciiString@@QAE@XZ
?d_00bf2738@@YAXXZ ENDP
_TEXT$d00ff2738 ENDS
_TEXT SEGMENT

; retail @ 0x00BF4ED4 size 27
public ?d_00bf4ed4@@YAXXZ
?d_00bf4ed4@@YAXXZ PROC
    db 68h, 28h, 0D8h, 40h, 00h, 6Ah, 04h, 6Ah, 04h, 8Bh, 85h, 0CCh, 0FEh, 0FEh, 0FFh, 05h
    db 9Ch, 00h, 00h, 00h, 50h, 0E8h, 88h, 1Eh, 0E0h, 0FFh, 0C3h
?d_00bf4ed4@@YAXXZ ENDP

; retail @ 0x00BF4EEF size 17
_TEXT ENDS
_TEXT$d00ff4eef SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00FF4EEF size 17
public ?d_00bf4eef@@YAXXZ
?d_00bf4eef@@YAXXZ PROC
    db 08Bh, 08Dh, 0CCh, 0FEh, 0FEh, 0FFh, 081h, 0C1h, 000h, 002h, 000h, 000h
    jmp ??1BFMERetailAsciiString@@QAE@XZ
?d_00bf4eef@@YAXXZ ENDP
_TEXT$d00ff4eef ENDS
_TEXT SEGMENT

; retail @ 0x00BF4F62 size 27
_TEXT ENDS
_TEXT$d00ff4f62 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00FF4F62 size 27
public ?d_00bf4f62@@YAXXZ
?d_00bf4f62@@YAXXZ PROC
    db 068h
    dd ??1AIUpdateArrayElement@@QAE@XZ
    db 06Ah, 003h, 06Ah, 00Ch, 08Bh, 085h, 0CCh, 0FEh, 0FEh, 0FFh, 005h, 004h, 00Ah, 000h, 000h, 050h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 0C3h
?d_00bf4f62@@YAXXZ ENDP
_TEXT$d00ff4f62 ENDS
_TEXT SEGMENT

; retail @ 0x00BFAB57 size 11
_TEXT ENDS
_TEXT$d00ffab57 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00FFAB57 size 11
public ?d_00bfab57@@YAXXZ
?d_00bfab57@@YAXXZ PROC
    db 08Bh, 04Dh, 004h, 083h, 0C1h, 004h
    jmp ?j_0001570d@@YAXXZ
?d_00bfab57@@YAXXZ ENDP
_TEXT$d00ffab57 ENDS
_TEXT SEGMENT

; retail @ 0x00C08598 size 39
_TEXT ENDS
_TEXT$d01008598 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x01008598 size 39
public ?d_00c08598@@YAXXZ
?d_00c08598@@YAXXZ PROC
    db 083h, 07Dh, 0F0h, 000h, 00Fh, 084h, 00Eh, 000h, 000h, 000h, 08Bh, 045h, 0F0h, 083h, 0C0h, 004h
    db 089h, 045h, 0ECh, 0E9h, 007h, 000h, 000h, 000h, 0C7h, 045h, 0ECh, 000h, 000h, 000h, 000h, 08Bh
    db 04Dh, 0ECh
    jmp ??1SubsystemInterface@@UAE@XZ
?d_00c08598@@YAXXZ ENDP
_TEXT$d01008598 ENDS
_TEXT SEGMENT

; retail @ 0x00C097A8 size 39
_TEXT ENDS
_TEXT$d010097a8 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x010097A8 size 39
public ?d_00c097a8@@YAXXZ
?d_00c097a8@@YAXXZ PROC
    db 083h, 07Dh, 0ECh, 000h, 00Fh, 084h, 00Eh, 000h, 000h, 000h, 08Bh, 045h, 0ECh, 083h, 0C0h, 060h
    db 089h, 045h, 0E8h, 0E9h, 007h, 000h, 000h, 000h, 0C7h, 045h, 0E8h, 000h, 000h, 000h, 000h, 08Bh
    db 04Dh, 0E8h
    jmp ?j_00001c80@@YAXXZ
?d_00c097a8@@YAXXZ ENDP
_TEXT$d010097a8 ENDS
_TEXT SEGMENT

; retail @ 0x00C1BED8 size 39
public ?d_00c1bed8@@YAXXZ
?d_00c1bed8@@YAXXZ PROC
    db 83h, 7Dh, 0F0h, 00h, 0Fh, 84h, 0Eh, 00h, 00h, 00h, 8Bh, 45h, 0F0h, 83h, 0C0h, 08h
    db 89h, 45h, 0ECh, 0E9h, 07h, 00h, 00h, 00h, 0C7h, 45h, 0ECh, 00h, 00h, 00h, 00h, 8Bh
    db 4Dh, 0ECh, 0E9h, 81h, 5Dh, 3Eh, 0FFh
?d_00c1bed8@@YAXXZ ENDP

; retail @ 0x00C209F8 size 39
public ?d_00c209f8@@YAXXZ
?d_00c209f8@@YAXXZ PROC
    db 83h, 7Dh, 0F0h, 00h, 0Fh, 84h, 0Eh, 00h, 00h, 00h, 8Bh, 45h, 0F0h, 83h, 0C0h, 60h
    db 89h, 45h, 0E8h, 0E9h, 07h, 00h, 00h, 00h, 0C7h, 45h, 0E8h, 00h, 00h, 00h, 00h, 8Bh
    db 4Dh, 0E8h, 0E9h, 61h, 12h, 3Eh, 0FFh
?d_00c209f8@@YAXXZ ENDP

; retail @ 0x00C20FF8 size 39
public ?d_00c20ff8@@YAXXZ
?d_00c20ff8@@YAXXZ PROC
    db 83h, 7Dh, 0F0h, 00h, 0Fh, 84h, 0Eh, 00h, 00h, 00h, 8Bh, 45h, 0F0h, 83h, 0C0h, 08h
    db 89h, 45h, 0ECh, 0E9h, 07h, 00h, 00h, 00h, 0C7h, 45h, 0ECh, 00h, 00h, 00h, 00h, 8Bh
    db 4Dh, 0ECh, 0E9h, 61h, 0Ch, 3Eh, 0FFh
?d_00c20ff8@@YAXXZ ENDP

; retail @ 0x00C21DA8 size 39
_TEXT ENDS
_TEXT$d01021da8 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x01021DA8 size 39
public ?d_00c21da8@@YAXXZ
?d_00c21da8@@YAXXZ PROC
    db 083h, 07Dh, 0F0h, 000h, 00Fh, 084h, 00Eh, 000h, 000h, 000h, 08Bh, 045h, 0F0h, 083h, 0C0h, 008h
    db 089h, 045h, 0ECh, 0E9h, 007h, 000h, 000h, 000h, 0C7h, 045h, 0ECh, 000h, 000h, 000h, 000h, 08Bh
    db 04Dh, 0ECh
    jmp ?j_00001c80@@YAXXZ
?d_00c21da8@@YAXXZ ENDP
_TEXT$d01021da8 ENDS
_TEXT SEGMENT

; retail @ 0x00C2F5C8 size 41
_TEXT ENDS
_TEXT$d0102f5c8 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0102F5C8 size 41
public ?d_00c2f5c8@@YAXXZ
?d_00c2f5c8@@YAXXZ PROC
    db 083h, 07Dh, 0F0h, 000h, 00Fh, 084h, 010h, 000h, 000h, 000h, 08Bh, 045h, 0F0h, 005h, 058h, 002h
    db 000h, 000h, 089h, 045h, 0E8h, 0E9h, 007h, 000h, 000h, 000h, 0C7h, 045h, 0E8h, 000h, 000h, 000h
    db 000h, 08Bh, 04Dh, 0E8h
    jmp ?j_00005d2b@@YAXXZ
?d_00c2f5c8@@YAXXZ ENDP
_TEXT$d0102f5c8 ENDS
_TEXT SEGMENT

; retail @ 0x00C35D18 size 41
_TEXT ENDS
_TEXT$d01035d18 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x01035D18 size 41
public ?d_00c35d18@@YAXXZ
?d_00c35d18@@YAXXZ PROC
    db 083h, 07Dh, 0F0h, 000h, 00Fh, 084h, 010h, 000h, 000h, 000h, 08Bh, 045h, 0F0h, 005h, 058h, 002h
    db 000h, 000h, 089h, 045h, 0E8h, 0E9h, 007h, 000h, 000h, 000h, 0C7h, 045h, 0E8h, 000h, 000h, 000h
    db 000h, 08Bh, 04Dh, 0E8h
    jmp ?j_00005d2b@@YAXXZ
?d_00c35d18@@YAXXZ ENDP
_TEXT$d01035d18 ENDS
_TEXT SEGMENT

; retail @ 0x00C37BB8 size 39
_TEXT ENDS
_TEXT$d01037bb8 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x01037BB8 size 39
public ?d_00c37bb8@@YAXXZ
?d_00c37bb8@@YAXXZ PROC
    db 083h, 07Dh, 0F0h, 000h, 00Fh, 084h, 00Eh, 000h, 000h, 000h, 08Bh, 045h, 0F0h, 083h, 0C0h, 008h
    db 089h, 045h, 0E8h, 0E9h, 007h, 000h, 000h, 000h, 0C7h, 045h, 0E8h, 000h, 000h, 000h, 000h, 08Bh
    db 04Dh, 0E8h
    jmp ?j_00001c80@@YAXXZ
?d_00c37bb8@@YAXXZ ENDP
_TEXT$d01037bb8 ENDS
_TEXT SEGMENT

; retail @ 0x00C39F58 size 39
_TEXT ENDS
_TEXT$d01039f58 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x01039F58 size 39
public ?d_00c39f58@@YAXXZ
?d_00c39f58@@YAXXZ PROC
    db 083h, 07Dh, 0F0h, 000h, 00Fh, 084h, 00Eh, 000h, 000h, 000h, 08Bh, 045h, 0F0h, 083h, 0C0h, 008h
    db 089h, 045h, 0E4h, 0E9h, 007h, 000h, 000h, 000h, 0C7h, 045h, 0E4h, 000h, 000h, 000h, 000h, 08Bh
    db 04Dh, 0E4h
    jmp ?j_00001c80@@YAXXZ
?d_00c39f58@@YAXXZ ENDP
_TEXT$d01039f58 ENDS
_TEXT SEGMENT

; retail @ 0x00C4D0F0 size 8
_TEXT ENDS
_TEXT$d0104d0f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0104D0F0 size 8
public ?d_00c4d0f0@@YAXXZ
?d_00c4d0f0@@YAXXZ PROC
    db 08Bh, 04Dh, 0F0h
    jmp ??1RenderObjClass@@UAE@XZ
?d_00c4d0f0@@YAXXZ ENDP
_TEXT$d0104d0f0 ENDS
_TEXT SEGMENT

; retail @ 0x00C51008 size 11
_TEXT ENDS
_TEXT$d01051008 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x01051008 size 11
public ?d_00c51008@@YAXXZ
?d_00c51008@@YAXXZ PROC
    db 08Bh, 04Dh, 004h, 083h, 0C1h, 004h
    jmp ?j_0001570d@@YAXXZ
?d_00c51008@@YAXXZ ENDP
_TEXT$d01051008 ENDS
_TEXT SEGMENT

; retail @ 0x00C521F8 size 39
public ?d_00c521f8@@YAXXZ
?d_00c521f8@@YAXXZ PROC
    db 83h, 7Dh, 0F0h, 00h, 0Fh, 84h, 0Eh, 00h, 00h, 00h, 8Bh, 45h, 0F0h, 83h, 0C0h, 04h
    db 89h, 45h, 0E8h, 0E9h, 07h, 00h, 00h, 00h, 0C7h, 45h, 0E8h, 00h, 00h, 00h, 00h, 8Bh
    db 4Dh, 0E8h, 0E9h, 0F1h, 0D9h, 0CCh, 0FFh
?d_00c521f8@@YAXXZ ENDP

; retail @ 0x00C5FD89 size 11
_TEXT ENDS
_TEXT$d0105fd89 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FD89 size 11
public ?d_00c5fd89@@YAXXZ
?d_00c5fd89@@YAXXZ PROC
    db 08Bh, 045h, 004h, 050h
    call ??_V@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fd89@@YAXXZ ENDP
_TEXT$d0105fd89 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FD94 size 11
_TEXT ENDS
_TEXT$d0105fd94 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FD94 size 11
public ?d_00c5fd94@@YAXXZ
?d_00c5fd94@@YAXXZ PROC
    db 08Bh, 045h, 004h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fd94@@YAXXZ ENDP
_TEXT$d0105fd94 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FD9F size 8
_TEXT ENDS
_TEXT$d0105fd9f SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FD9F size 8
public ?d_00c5fd9f@@YAXXZ
?d_00c5fd9f@@YAXXZ PROC
    db 08Bh, 04Dh, 004h
    jmp ?j_00001f05@@YAXXZ
?d_00c5fd9f@@YAXXZ ENDP
_TEXT$d0105fd9f ENDS
_TEXT SEGMENT

; retail @ 0x00C5FDA7 size 11
_TEXT ENDS
_TEXT$d0105fda7 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FDA7 size 11
public ?d_00c5fda7@@YAXXZ
?d_00c5fda7@@YAXXZ PROC
    db 08Bh, 045h, 004h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fda7@@YAXXZ ENDP
_TEXT$d0105fda7 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FDBA size 11
_TEXT ENDS
_TEXT$d0105fdba SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FDBA size 11
public ?d_00c5fdba@@YAXXZ
?d_00c5fdba@@YAXXZ PROC
    db 08Bh, 045h, 004h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fdba@@YAXXZ ENDP
_TEXT$d0105fdba ENDS
_TEXT SEGMENT

; retail @ 0x00C5FDCD size 11
_TEXT ENDS
_TEXT$d0105fdcd SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FDCD size 11
public ?d_00c5fdcd@@YAXXZ
?d_00c5fdcd@@YAXXZ PROC
    db 08Bh, 045h, 004h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fdcd@@YAXXZ ENDP
_TEXT$d0105fdcd ENDS
_TEXT SEGMENT

; retail @ 0x00C5FDD8 size 8
_TEXT ENDS
_TEXT$d0105fdd8 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FDD8 size 8
public ?d_00c5fdd8@@YAXXZ
?d_00c5fdd8@@YAXXZ PROC
    db 08Bh, 04Dh, 004h
    jmp ?j_00001f05@@YAXXZ
?d_00c5fdd8@@YAXXZ ENDP
_TEXT$d0105fdd8 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FDE0 size 11
_TEXT ENDS
_TEXT$d0105fde0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FDE0 size 11
public ?d_00c5fde0@@YAXXZ
?d_00c5fde0@@YAXXZ PROC
    db 08Bh, 045h, 004h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fde0@@YAXXZ ENDP
_TEXT$d0105fde0 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FDFE size 8
_TEXT ENDS
_TEXT$d0105fdfe SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FDFE size 8
public ?d_00c5fdfe@@YAXXZ
?d_00c5fdfe@@YAXXZ PROC
    db 08Dh, 04Dh, 004h
    jmp ?j_00030652@@YAXXZ
?d_00c5fdfe@@YAXXZ ENDP
_TEXT$d0105fdfe ENDS
_TEXT SEGMENT

; retail @ 0x00C5FE11 size 8
_TEXT ENDS
_TEXT$d0105fe11 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FE11 size 8
public ?d_00c5fe11@@YAXXZ
?d_00c5fe11@@YAXXZ PROC
    db 08Dh, 04Dh, 0D8h
    jmp ?j_00030652@@YAXXZ
?d_00c5fe11@@YAXXZ ENDP
_TEXT$d0105fe11 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FE19 size 11
_TEXT ENDS
_TEXT$d0105fe19 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FE19 size 11
public ?d_00c5fe19@@YAXXZ
?d_00c5fe19@@YAXXZ PROC
    db 08Bh, 045h, 0E8h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fe19@@YAXXZ ENDP
_TEXT$d0105fe19 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FE4A size 11
_TEXT ENDS
_TEXT$d0105fe4a SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FE4A size 11
public ?d_00c5fe4a@@YAXXZ
?d_00c5fe4a@@YAXXZ PROC
    db 08Bh, 045h, 0E8h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fe4a@@YAXXZ ENDP
_TEXT$d0105fe4a ENDS
_TEXT SEGMENT

; retail @ 0x00C5FE5D size 11
_TEXT ENDS
_TEXT$d0105fe5d SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FE5D size 11
public ?d_00c5fe5d@@YAXXZ
?d_00c5fe5d@@YAXXZ PROC
    db 08Bh, 045h, 0E8h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fe5d@@YAXXZ ENDP
_TEXT$d0105fe5d ENDS
_TEXT SEGMENT

; retail @ 0x00C5FE68 size 8
_TEXT ENDS
_TEXT$d0105fe68 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FE68 size 8
public ?d_00c5fe68@@YAXXZ
?d_00c5fe68@@YAXXZ PROC
    db 08Bh, 04Dh, 0E8h
    jmp ?j_00001f05@@YAXXZ
?d_00c5fe68@@YAXXZ ENDP
_TEXT$d0105fe68 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FE70 size 11
_TEXT ENDS
_TEXT$d0105fe70 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FE70 size 11
public ?d_00c5fe70@@YAXXZ
?d_00c5fe70@@YAXXZ PROC
    db 08Bh, 045h, 004h, 050h
    call ??3@YAXPAX@Z
    db 059h, 0C3h
?d_00c5fe70@@YAXXZ ENDP
_TEXT$d0105fe70 ENDS
_TEXT SEGMENT

; retail @ 0x00C5FE7B size 8
_TEXT ENDS
_TEXT$d0105fe7b SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0105FE7B size 8
public ?d_00c5fe7b@@YAXXZ
?d_00c5fe7b@@YAXXZ PROC
    db 08Bh, 04Dh, 004h
    jmp ?j_00001f05@@YAXXZ
?d_00c5fe7b@@YAXXZ ENDP
_TEXT$d0105fe7b ENDS
_TEXT SEGMENT

; retail @ 0x00C5FEB4 size 18
public ?d_00c5feb4@@YAXXZ
?d_00c5feb4@@YAXXZ PROC
    db 8Bh, 4Dh, 04h, 0E9h, 49h, 20h, 3Ah, 0FFh, 0B8h, 9Ch, 0F3h, 24h, 01h, 0E9h, 10h, 6Fh
    db 0D9h, 0FFh
?d_00c5feb4@@YAXXZ ENDP
_TEXT ENDS
END
