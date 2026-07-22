.386
.model flat

; ?checkForDuplicateColors@@YAXPAVGameInfo@@@Z
; Exact 104B @ 0x00386520; true body (queue 0x38651F was leading int3);
; C++ blocked by MultiplayerSettings layout (getNumColors m_numColors@+0x3c vs ZH +0x28)
_TEXT SEGMENT
public ?checkForDuplicateColors@@YAXPAVGameInfo@@@Z
?checkForDuplicateColors@@YAXPAVGameInfo@@@Z PROC
    db 085h,0DBh,074h,063h,055h,056h,057h,0BDh,007h,000h,000h,000h,08Dh,064h,024h,000h
    db 055h,08Bh,0CBh,0E8h,0E0h,086h,0C9h,0FFh,08Bh,0F0h,085h,0F6h,074h,043h,08Bh,0CEh
    db 0E8h,04Eh,0A0h,0CBh,0FFh,084h,0C0h,074h,038h,08Bh,07Eh,00Ch,085h,0FFh,07Ch,031h
    db 08Bh,00Dh,0FCh,0D5h,02Eh,001h,08Bh,051h,03Ch,085h,0D2h,08Dh,041h,03Ch,075h,005h
    db 08Bh,049h,034h,089h,008h,03Bh,038h,07Dh,018h,06Ah,0FFh,057h,08Bh,0CBh,0C7h,046h
    db 00Ch,0FFh,0FFh,0FFh,0FFh,0E8h,04Bh,0B6h,0C9h,0FFh,084h,0C0h,075h,003h,089h,07Eh
    db 00Ch,04Dh,079h,0ACh,05Fh,05Eh,05Dh,0C3h
?checkForDuplicateColors@@YAXPAVGameInfo@@@Z ENDP
_TEXT ENDS
END
