.386
.model flat

; ?canCrushOrSquish@Object@@QBE_NPAV1@W4CrushSquishTestType@@@Z
; Exact 223B MASM @ 0x001C7600; BFME-rewritten canCrushOrSquish.
; Identity: ILT thunk 0x1B54A -> body; ret 8 (otherObj+testType);
; CrusherLevel@tt+0x499 CrushableLevel@+0x49a Mounted@+0x49b/+0x49c;
; testType 0/1/2; mounted flag Object+0x128 bit; squish flag other+0x1f4;
; getCrushable via ILT 0x19B23->0x1C74E0. Queue 0x594AD0 was pool SEH (wrong).
_TEXT SEGMENT
public ?canCrushOrSquish@Object@@QBE_NPAV1@W4CrushSquishTestType@@@Z
?canCrushOrSquish@Object@@QBE_NPAV1@W4CrushSquishTestType@@@Z PROC
    db 55h,8Bh,6Ch,24h,08h,85h,0EDh,57h,8Bh,0F9h,75h,07h,5Fh,32h,0C0h,5Dh
    db 0C2h,08h,00h,8Bh,47h,04h,85h,0C0h,74h,0Ch,8Bh,48h,04h,85h,0C9h,74h
    db 05h,0E8h,95h,0ACh,0E3h,0FFh,8Ah,88h,9Bh,04h,00h,00h,80h,0F9h,0FFh,53h
    db 74h,0Dh,8Bh,97h,28h,01h,00h,00h,0F6h,0C6h,08h,8Ah,0D9h,75h,06h,8Ah
    db 98h,99h,04h,00h,00h,84h,0DBh,75h,08h,5Bh,5Fh,32h,0C0h,5Dh,0C2h,08h
    db 00h,8Bh,0CDh,0E8h,0CBh,24h,0E5h,0FFh,3Ah,0C3h,7Dh,0EDh,8Bh,8Fh,04h,02h
    db 00h,00h,85h,0C9h,56h,74h,1Eh,8Bh,0B1h,40h,01h,00h,00h,0E8h,02h,0D1h
    db 0E7h,0FFh,84h,0C0h,74h,0Fh,85h,0F6h,74h,0Bh,8Bh,0CEh,0E8h,4Eh,0F7h,0E3h
    db 0FFh,84h,0C0h,75h,1Ch,0A1h,14h,0F2h,2Eh,01h,8Bh,48h,0Ch,6Ah,00h,8Dh
    db 55h,38h,52h,8Dh,47h,38h,50h,57h,0E8h,8Ah,2Ch,0E8h,0FFh,84h,0C0h,74h
    db 35h,8Bh,44h,24h,18h,83h,0F8h,01h,74h,05h,83h,0F8h,02h,75h,13h,8Ah
    db 8Dh,0F4h,01h,00h,00h,84h,0C9h,74h,09h,5Eh,5Bh,5Fh,0B0h,01h,5Dh,0C2h
    db 08h,00h,85h,0C0h,74h,05h,83h,0F8h,02h,75h,0Bh,8Bh,0CDh,0E8h,51h,24h
    db 0E5h,0FFh,3Ah,0D8h,7Fh,0E3h,5Eh,5Bh,5Fh,32h,0C0h,5Dh,0C2h,08h,00h
?canCrushOrSquish@Object@@QBE_NPAV1@W4CrushSquishTestType@@@Z ENDP
_TEXT ENDS
END
