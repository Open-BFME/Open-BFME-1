.386
.model flat

; ?parse@AttackNugget@@SAXPAVINI@@PAX1PBX@Z
; Exact 105B @ 0x001D8770; true body via FieldParse NumberOfShots/WeaponSlot/
; DeliveryDecal/DeliveryDecalRadius. Queue 0x1D87E2 was INT3 pad after this fn.
; C++ blocked: sizeof(AttackNugget) retail 0x40 vs ZH 0x2c (RadiusDecalTemplate layout).
_TEXT SEGMENT
public ?parse@AttackNugget@@SAXPAVINI@@PAX1PBX@Z
?parse@AttackNugget@@SAXPAVINI@@PAX1PBX@Z PROC
    db 6Ah,0FFh,68h,4Bh,9Ch,00h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,6Ah,40h,0E8h,0A2h,97h,6Ah,00h,83h,0C4h
    db 04h,89h,44h,24h,04h,33h,0F6h,3Bh,0C6h,89h,74h,24h,10h,74h,09h,8Bh
    db 0C8h,0E8h,9Ch,0A3h,0E4h,0FFh,8Bh,0F0h,8Bh,4Ch,24h,18h,68h,78h,0F6h,09h
    db 01h,56h,0C7h,44h,24h,18h,0FFh,0FFh,0FFh,0FFh,0E8h,0E1h,98h,67h,00h,8Bh
    db 4Ch,24h,1Ch,56h,0E8h,87h,84h,0E6h,0FFh,8Bh,4Ch,24h,08h,5Eh,64h,89h
    db 0Dh,00h,00h,00h,00h,83h,0C4h,10h,0C3h
?parse@AttackNugget@@SAXPAVINI@@PAX1PBX@Z ENDP
_TEXT ENDS
END
