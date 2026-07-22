.386
.model flat

; ?canUseSpecialPower@SpecialPowerStore@@QAE_NPAVObject@@PBVSpecialPowerTemplate@@@Z
; Exact 120B retail @ 0x000EB710; queue 0x76E9AF was INSIDE Team::tryToRecruit;
; true body in SpecialPowerStore cluster after findSpecialPowerTemplateByID@0xEB690.
; BFME adds Player check after ZH science gate (Lorenzen charge/conyard comment).
_TEXT SEGMENT
public ?canUseSpecialPower@SpecialPowerStore@@QAE_NPAVObject@@PBVSpecialPowerTemplate@@@Z
?canUseSpecialPower@SpecialPowerStore@@QAE_NPAVObject@@PBVSpecialPowerTemplate@@@Z PROC
    db 53h,8Bh,5Ch,24h,08h,85h,0DBh,57h,74h,67h,8Bh,7Ch,24h,10h,85h,0FFh
    db 74h,5Fh,57h,8Bh,0CBh,0E8h,95h,4Ah,0F5h,0FFh,85h,0C0h,74h,53h,8Bh,47h
    db 04h,85h,0C0h,74h,0Eh,8Bh,48h,04h,85h,0C9h,74h,09h,0E8h,20h,0D5h,0F5h
    db 0FFh,0EBh,02h,8Bh,0C7h,56h,8Bh,70h,1Ch,83h,0FEh,0FFh,74h,19h,8Bh,0CBh
    db 0E8h,0CFh,50h,0F3h,0FFh,56h,8Bh,0C8h,0E8h,0E2h,0DCh,0F1h,0FFh,84h,0C0h,75h
    db 06h,5Eh,5Fh,5Bh,0C2h,08h,00h,57h,8Bh,0CBh,0E8h,0B5h,50h,0F3h,0FFh,8Bh
    db 0C8h,0E8h,0F5h,6Ah,0F1h,0FFh,5Eh,84h,0C0h,5Fh,0Fh,95h,0C0h,5Bh,0C2h,08h
    db 00h,5Fh,32h,0C0h,5Bh,0C2h,08h,00h
?canUseSpecialPower@SpecialPowerStore@@QAE_NPAVObject@@PBVSpecialPowerTemplate@@@Z ENDP
_TEXT ENDS
END
