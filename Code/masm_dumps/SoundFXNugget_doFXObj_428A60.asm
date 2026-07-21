.386
.model flat

; ?doFXObj@SoundFXNugget@@UBEXPBVObject@@0@Z
; Exact 146B @ 0x00428A60; true body via Sound FX FieldParse+vtable slot2;
; queue 0x76E9B4 was inside Team::tryToRecruit; BFME Sound nugget m_name@+0xB4
; (not ZH +4); AudioEventRTS 2-arg + addAudioEvent vtbl+0x44 blocks C++
_TEXT SEGMENT
public ?doFXObj@SoundFXNugget@@UBEXPBVObject@@0@Z
?doFXObj@SoundFXNugget@@UBEXPBVObject@@0@Z PROC
    db 06Ah,0FFh,068h,058h,012h,002h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,070h,056h,081h,0C1h,0B4h,000h,000h,000h,06Ah
    db 000h,051h,08Dh,04Ch,024h,00Ch,0E8h,07Bh,0C8h,0BFh,0FFh,08Bh,0B4h,024h,084h,000h
    db 000h,000h,085h,0F6h,0C7h,044h,024h,07Ch,000h,000h,000h,000h,074h,021h,08Bh,0CEh
    db 0E8h,07Fh,07Dh,0BFh,0FFh,08Bh,040h,024h,050h,08Dh,04Ch,024h,008h,0E8h,0D6h,021h
    db 0C1h,0FFh,083h,0C6h,038h,056h,08Dh,04Ch,024h,008h,0E8h,0C9h,093h,0BDh,0FFh,08Bh
    db 00Dh,068h,0D6h,02Eh,001h,08Bh,001h,08Dh,054h,024h,004h,052h,0FFh,050h,044h,08Dh
    db 04Ch,024h,004h,0C7h,044h,024h,07Ch,0FFh,0FFh,0FFh,0FFh,0E8h,055h,0E4h,0BFh,0FFh
    db 08Bh,04Ch,024h,074h,05Eh,064h,089h,00Dh,000h,000h,000h,000h,083h,0C4h,07Ch,0C2h
    db 008h,000h
?doFXObj@SoundFXNugget@@UBEXPBVObject@@0@Z ENDP
_TEXT ENDS
END
