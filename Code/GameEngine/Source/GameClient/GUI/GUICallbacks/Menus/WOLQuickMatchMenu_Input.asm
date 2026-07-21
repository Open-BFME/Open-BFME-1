.386
.model flat

; ?WOLQuickMatchMenuInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
; Exact 98 retail bytes @ 0x005054B0; BFME object-form input callback
; (thiscall ret 12). Queue RVA 0x79CEC3 was mid-instruction inside MOTDSystem
; (already matched @ 0x79CEC0). True body sits in the QM object cluster next
; to UpdateStartButton/System; layout table @ 0xD04020 pins this thunk.
_TEXT SEGMENT
public ?WOLQuickMatchMenuInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
?WOLQuickMatchMenuInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z PROC
    db 083h,07Ch,024h,004h,015h,056h,08Bh,0F1h
    db 075h,011h,0A0h,001h,048h,02Fh,001h,084h
    db 0C0h,075h,008h,00Fh,0B6h,044h,024h,00Ch
    db 048h,074h,006h,033h,0C0h,05Eh,0C2h,00Ch
    db 000h,0F6h,044h,024h,010h,001h,074h,031h
    db 08Bh,08Eh,064h,002h,000h,000h,0E8h,0D4h
    db 050h,0B3h,0FFh,084h,0C0h,075h,022h,08Bh
    db 096h,060h,002h,000h,000h,08Bh,00Dh,040h
    db 01Bh,02Fh,001h,08Bh,001h,052h,08Bh,096h
    db 064h,002h,000h,000h,052h,068h,008h,040h
    db 000h,000h,056h,0FFh,090h,0D4h,000h,000h
    db 000h,0B8h,001h,000h,000h,000h,05Eh,0C2h
    db 00Ch,000h
?WOLQuickMatchMenuInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z ENDP
_TEXT ENDS
END
