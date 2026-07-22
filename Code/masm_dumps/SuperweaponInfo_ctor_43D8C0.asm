.386
.model flat
; ??0SuperweaponInfo@@QAE@W4ObjectID@@I_N111ABVAsciiString@@H1HPBVSpecialPowerTemplate@@@Z
; Exact 236B @ 0x0043D8C0; true body via addSuperweapon@0x44C970 call
; (thunk 0x751D -> body). Queue 0x57CF1B was int3 pad. C++ blocked: BFME drops
; evaReadyPlayed (ret 0x28/sizeof 0x24 vs ZH 0x2C/0x28) + DisplayStringManager
; vtable slot drift (newDisplayString retail +0x24 vs ZH +0x18).
_TEXT SEGMENT
public ??0SuperweaponInfo@@QAE@W4ObjectID@@I_N111ABVAsciiString@@H1HPBVSpecialPowerTemplate@@@Z
??0SuperweaponInfo@@QAE@W4ObjectID@@I_N111ABVAsciiString@@H1HPBVSpecialPowerTemplate@@@Z PROC
    db 6Ah, 0FFh, 68h, 0Bh, 29h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 54h, 24h, 38h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h
    db 38h, 33h, 0C0h, 0C7h, 06h, 54h, 57h, 0Fh, 01h, 89h, 46h, 04h, 89h, 46h, 08h, 89h
    db 4Eh, 0Ch, 89h, 56h, 10h, 89h, 74h, 24h, 04h, 89h, 46h, 14h, 8Bh, 4Ch, 24h, 18h
    db 8Bh, 54h, 24h, 1Ch, 89h, 4Eh, 18h, 8Ah, 4Ch, 24h, 20h, 89h, 56h, 1Ch, 8Ah, 54h
    db 24h, 24h, 88h, 4Eh, 20h, 8Ah, 4Ch, 24h, 28h, 88h, 56h, 21h, 88h, 4Eh, 22h, 88h
    db 46h, 23h, 8Bh, 0Dh, 0CCh, 12h, 2Fh, 01h, 8Bh, 11h, 89h, 44h, 24h, 10h, 0FFh, 52h
    db 24h, 89h, 46h, 04h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 14h, 51h, 89h, 64h, 24h, 24h
    db 8Bh, 0CCh, 68h, 54h, 6Eh, 33h, 01h, 0E8h, 0B4h, 0AAh, 44h, 00h, 8Bh, 4Eh, 04h, 8Bh
    db 01h, 0FFh, 50h, 04h, 8Bh, 0Dh, 0CCh, 12h, 2Fh, 01h, 8Bh, 11h, 0FFh, 52h, 24h, 89h
    db 46h, 08h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 14h, 51h, 89h, 64h, 24h, 24h, 8Bh, 0CCh
    db 68h, 54h, 6Eh, 33h, 01h, 0E8h, 86h, 0AAh, 44h, 00h, 8Bh, 4Eh, 08h, 8Bh, 01h, 0FFh
    db 50h, 04h, 8Bh, 4Ch, 24h, 34h, 8Bh, 54h, 24h, 30h, 8Bh, 44h, 24h, 2Ch, 51h, 52h
    db 50h, 8Bh, 0CEh, 0E8h, 7Dh, 0CFh, 0BDh, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 10h, 0C2h, 28h, 00h
??0SuperweaponInfo@@QAE@W4ObjectID@@I_N111ABVAsciiString@@H1HPBVSpecialPowerTemplate@@@Z ENDP
_TEXT ENDS
END
