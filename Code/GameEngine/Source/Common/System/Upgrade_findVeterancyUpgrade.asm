.386
.model flat

; ?findVeterancyUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4VeterancyLevel@@@Z
; Retail @ 0x0010B480 size 101
; Identity: only non-friend_makeVeterancy caller of getVetUpgradeName@0x10AD90;
; then findUpgrade@0x2F95A; temp AsciiString via releaseBuffer@0x887940.
; Queue RVA 0x60810D was mid-body of unrelated bitset loop (size 126 mis-vote).
; C++ near-match first 0x3E then inlines AsciiString dtor vs retail call releaseBuffer.
_TEXT SEGMENT
public ?findVeterancyUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4VeterancyLevel@@@Z
?findVeterancyUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4VeterancyLevel@@@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh
    db 68h,98h,0D4h,0FFh,00h,50h,8Bh,44h
    db 24h,10h,64h,89h,25h,00h,00h,00h
    db 00h,56h,8Bh,0F1h,50h,8Dh,4Ch,24h
    db 18h,51h,0E8h,0E9h,0F8h,0FFh,0FFh,83h
    db 0C4h,08h,8Dh,54h,24h,14h,52h,8Bh
    db 0CEh,0C7h,44h,24h,10h,00h,00h,00h
    db 00h,0E8h,9Ch,44h,0F2h,0FFh,8Dh,4Ch
    db 24h,14h,8Bh,0F0h,0C7h,44h,24h,0Ch
    db 0FFh,0FFh,0FFh,0FFh,0E8h,6Fh,0C4h,77h
    db 00h,8Bh,4Ch,24h,04h,8Bh,0C6h,64h
    db 89h,0Dh,00h,00h,00h,00h,5Eh,83h
    db 0C4h,0Ch,0C2h,04h,00h
?findVeterancyUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4VeterancyLevel@@@Z ENDP
_TEXT ENDS
END
