.386
.model flat

; ?startBurningSound@FlammableUpdate@@IAEXXZ
; Exact 113 retail bytes @ RVA 0x00293520; AudioEventRTS(name,objID)+addAudioEvent; m_audioHandle@+0x34
_TEXT SEGMENT
public ?startBurningSound@FlammableUpdate@@IAEXXZ
?startBurningSound@FlammableUpdate@@IAEXXZ PROC
    db 06Ah,0FFh,068h,058h,01Bh,001h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,070h,056h,08Bh,0F1h,08Bh,04Eh,008h,08Bh,049h
    db 074h,08Bh,046h,004h,051h,083h,0C0h,018h,050h,08Dh,04Ch,024h,00Ch,0E8h,0CAh,060h
    db 0DAh,0FFh,08Bh,00Dh,068h,0D6h,02Eh,001h,08Bh,001h,08Dh,054h,024h,004h,052h,0C7h
    db 084h,024h,080h,000h,000h,000h,000h,000h,000h,000h,0FFh,050h,044h,08Dh,04Ch,024h
    db 004h,089h,046h,034h,0C7h,044h,024h,07Ch,0FFh,0FFh,0FFh,0FFh,0E8h,0B4h,039h,0D9h
    db 0FFh,08Bh,04Ch,024h,074h,05Eh,064h,089h,00Dh,000h,000h,000h,000h,083h,0C4h,07Ch
    db 0C3h
?startBurningSound@FlammableUpdate@@IAEXXZ ENDP
_TEXT ENDS
END
