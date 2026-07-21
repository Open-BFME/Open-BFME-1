.386
.model flat

; ??1WeaponSet@@QAE@XZ
; Exact 95 retail bytes @ 0x001EAD40.
; Identity: scalar-deleting dtor ILT 0x6587 -> body; vtable 0x10A1678 slot0
; (??_G) calls this; co-located with matched findWaypoint/getWeaponInWeaponSlot;
; 4-slot weapon array at +8 (BFME WEAPONSLOT_COUNT=4) then Snapshot vtbl 0x1073744.
; Queue RVA 0x9F27F7 was int3 pad before already-matched PartitionManager dtor.
_TEXT SEGMENT
public ??1WeaponSet@@QAE@XZ
??1WeaponSet@@QAE@XZ PROC
    db 6Ah,0FFh,68h,78h,0A6h,00h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,53h,56h
    db 57h,8Bh,0F9h,89h,7Ch,24h,0Ch,0C7h
    db 07h,78h,16h,0Ah,01h,0C7h,44h,24h
    db 18h,00h,00h,00h,00h,8Dh,77h,08h
    db 0BBh,04h,00h,00h,00h,8Bh,0Eh,85h
    db 0C9h,74h,06h,8Bh,01h,6Ah,01h,0FFh
    db 10h,83h,0C6h,04h,4Bh,75h,0EEh,8Bh
    db 4Ch,24h,10h,0C7h,07h,44h,37h,07h
    db 01h,5Fh,5Eh,5Bh,64h,89h,0Dh,00h
    db 00h,00h,00h,83h,0C4h,10h,0C3h
??1WeaponSet@@QAE@XZ ENDP
_TEXT ENDS
END
