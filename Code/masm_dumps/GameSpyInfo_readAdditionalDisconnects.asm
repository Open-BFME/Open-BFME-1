.386
.model flat

; ?readAdditionalDisconnects@GameSpyInfo@@UAEXXZ
; Exact 23 retail bytes @ 0x00A30650; reads and stores the BFME-layout disconnect count.
_TEXT SEGMENT
public ?readAdditionalDisconnects@GameSpyInfo@@UAEXXZ
?readAdditionalDisconnects@GameSpyInfo@@UAEXXZ PROC
    db 056h,08Bh,0F1h,08Bh,046h,070h,050h,0E8h,0E9h,084h,0A0h,0FFh,083h,0C4h,004h,089h
    db 086h,0F8h,006h,000h,000h,05Eh,0C3h
?readAdditionalDisconnects@GameSpyInfo@@UAEXXZ ENDP
_TEXT ENDS
END
