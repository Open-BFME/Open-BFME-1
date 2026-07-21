.386
.model flat

; ?onEnter@AIPanicState@@UAE?AW4StateReturnType@@XZ
; Exact 353B @ 0x0017B680. Drift queue 0x0044824A is INSIDE 0x8481C0
; (check_placement INSIDE); true body = AIPanicState vtbl 0x109A988 slot4
; (thunk 0x1B06D -> 0x17B680). Proved vs AIWander onEnter@0x17AEC0 by
; MODELCONDITION_PANICKING bit 0x1000 set + m_timer/m_waitFrames; __FILE__
; AIStates.cpp. C++ blocked by State/StateMachine/Object layout offsets
; (this+0x1c vs +0x20 machine; goal WP +0x50 vs +0x44). MASM exact.
_TEXT SEGMENT
public ?onEnter@AIPanicState@@UAE?AW4StateReturnType@@XZ
?onEnter@AIPanicState@@UAE?AW4StateReturnType@@XZ PROC
    db 083h,0ECh,00Ch,053h,055h,056h,08Bh,0F1h,08Bh,046h,01Ch,08Bh,048h,050h,085h,0C9h
    db 089h,04Eh,060h,08Bh,068h,010h,08Bh,09Dh,004h,002h,000h,000h,089h,05Ch,024h,014h
    db 075h,00Ch,05Eh,05Dh,0B8h,0FEh,0FFh,0FFh,0FFh,05Bh,083h,0C4h,00Ch,0C3h,057h,08Bh
    db 0BBh,0CCh,001h,000h,000h,085h,0FFh,00Fh,084h,0BFh,000h,000h,000h,08Bh,047h,004h
    db 085h,0C0h,074h,00Ch,08Bh,048h,004h,085h,0C9h,074h,005h,0E8h,0EBh,06Bh,0E8h,0FFh
    db 0D9h,080h,0ECh,000h,000h,000h,0D8h,01Dh,050h,053h,007h,001h,0DFh,0E0h,0F6h,0C4h
    db 041h,00Fh,085h,095h,000h,000h,000h,08Bh,047h,004h,085h,0C0h,074h,00Ch,08Bh,048h
    db 004h,085h,0C9h,074h,005h,0E8h,0C1h,06Bh,0E8h,0FFh,0D9h,080h,0ECh,000h,000h,000h
    db 083h,0ECh,008h,0D8h,005h,03Ch,053h,007h,001h,0DDh,01Ch,024h,0FFh,015h,0B8h,093h
    db 035h,001h,0D9h,05Ch,024h,018h,083h,0C4h,008h,0D9h,044h,024h,010h,0DBh,05Ch,024h
    db 014h,08Bh,05Ch,024h,014h,083h,0FBh,001h,07Dh,005h,0BBh,001h,000h,000h,000h,068h
    db 052h,026h,000h,000h,068h,09Ch,076h,009h,001h,08Bh,0FBh,0F7h,0DFh,053h,057h,0E8h
    db 06Ah,064h,0E8h,0FFh,08Dh,004h,080h,068h,053h,026h,000h,000h,0D1h,0E0h,089h,044h
    db 024h,028h,0DBh,044h,024h,028h,068h,09Ch,076h,009h,001h,053h,057h,0D9h,05Eh,050h
    db 0E8h,049h,064h,0E8h,0FFh,08Bh,05Ch,024h,038h,08Dh,00Ch,080h,083h,0C4h,020h,0D1h
    db 0E1h,089h,04Ch,024h,014h,0DBh,044h,024h,014h,0D9h,05Eh,054h,06Ah,000h,08Bh,0CEh
    db 0E8h,03Ch,0E6h,0E9h,0FFh,08Bh,0CEh,0E8h,09Bh,066h,0EAh,0FFh,08Bh,056h,01Ch,0C7h
    db 046h,070h,000h,000h,000h,000h,08Bh,0F8h,08Bh,042h,010h,08Bh,048h,074h,083h,0E1h
    db 007h,083h,0C1h,00Ah,089h,04Eh,06Ch,08Bh,0CEh,0E8h,03Ah,071h,0ECh,0FFh,051h,08Bh
    db 0CBh,0D9h,01Ch,024h,0E8h,0F2h,033h,0E9h,0FFh,08Bh,08Dh,018h,001h,000h,000h,0B8h
    db 000h,010h,000h,000h,085h,0C8h,075h,00Fh,00Bh,0C8h,089h,08Dh,018h,001h,000h,000h
    db 08Bh,0CDh,0E8h,046h,061h,0EAh,0FFh,08Bh,0C7h,05Fh,05Eh,05Dh,05Bh,083h,0C4h,00Ch
    db 0C3h
?onEnter@AIPanicState@@UAE?AW4StateReturnType@@XZ ENDP
_TEXT ENDS
END
