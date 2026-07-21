.386
.model flat

; ?setCampaignDifficulty@OptionPreferences@@QAEXH@Z
; Exact 169B retail @ 0x000920F0; true ENTRY (queue 0x920FF was mid-SEH prologue)
; Identity: push "CampaignDifficulty" + "%d" + map[] assign
_TEXT SEGMENT
public ?setCampaignDifficulty@OptionPreferences@@QAEXH@Z
?setCampaignDifficulty@OptionPreferences@@QAEXH@Z PROC
    db 06Ah,0FFh,068h,0A0h,05Ah,0FFh,000h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,056h,08Bh,0F1h,0C7h,044h,024h,004h,000h,000h,000h
    db 000h,08Bh,044h,024h,018h,050h,051h,089h,064h,024h,020h,08Bh,0CCh,068h,0B4h,0C7h
    db 007h,001h,0C7h,044h,024h,01Ch,000h,000h,000h,000h,0E8h,091h,06Ah,07Fh,000h,08Dh
    db 04Ch,024h,00Ch,051h,0E8h,0B7h,06Eh,07Fh,000h,083h,0C4h,00Ch,068h,0F4h,0F9h,007h
    db 001h,08Dh,04Ch,024h,01Ch,0E8h,076h,06Ah,07Fh,000h,08Dh,054h,024h,018h,052h,08Dh
    db 04Eh,004h,0C6h,044h,024h,014h,001h,0E8h,07Eh,0C5h,0FAh,0FFh,08Dh,04Ch,024h,004h
    db 051h,08Bh,0C8h,0E8h,028h,05Bh,07Fh,000h,08Dh,04Ch,024h,018h,0C6h,044h,024h,010h
    db 000h,0E8h,0CAh,057h,07Fh,000h,08Dh,04Ch,024h,004h,0C7h,044h,024h,010h,0FFh,0FFh
    db 0FFh,0FFh,0E8h,0B9h,057h,07Fh,000h,08Bh,04Ch,024h,008h,064h,089h,00Dh,000h,000h
    db 000h,000h,05Eh,083h,0C4h,010h,0C2h,004h,000h
?setCampaignDifficulty@OptionPreferences@@QAEXH@Z ENDP
_TEXT ENDS
END
