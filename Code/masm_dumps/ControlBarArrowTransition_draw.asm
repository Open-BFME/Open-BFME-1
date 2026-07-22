.386
.model flat

; ?draw@ControlBarArrowTransition@@UAEXXZ
; Exact 362B retail @ 0x0059BAB0; true body after sibling update/skip/init cluster.
; Queue RVA 0x009DE7D4 was wrong (mid unrelated fild/fdiv helper). Identity:
; m_drawState@+0x30 matches matched update@0x59B810; BEGIN_FADE cmp 0x10;
; Display vtbl drawImage path; reverse@CountUp @0x59BCA0 sits after ret+pad.
_TEXT SEGMENT
public ?draw@ControlBarArrowTransition@@UAEXXZ
?draw@ControlBarArrowTransition@@UAEXXZ PROC
    db 083h, 0ECh, 010h, 056h, 08Bh, 0F1h, 08Bh, 04Eh, 030h, 085h, 0C9h, 00Fh, 08Ch, 054h, 001h, 000h
    db 000h, 083h, 0F9h, 010h, 057h, 00Fh, 08Dh, 088h, 000h, 000h, 000h, 08Bh, 046h, 01Ch, 08Bh, 07Eh
    db 014h, 00Fh, 0AFh, 0C1h, 08Bh, 04Eh, 024h, 08Bh, 056h, 020h, 003h, 0C7h, 003h, 0C8h, 089h, 04Ch
    db 024h, 008h, 08Bh, 00Dh, 070h, 012h, 02Fh, 001h, 089h, 044h, 024h, 014h, 08Bh, 046h, 010h, 0DBh
    db 044h, 024h, 008h, 08Bh, 076h, 034h, 003h, 0D0h, 0D9h, 05Ch, 024h, 010h, 089h, 054h, 024h, 008h
    db 089h, 044h, 024h, 00Ch, 08Bh, 001h, 0DBh, 044h, 024h, 008h, 08Bh, 0F9h, 0D9h, 05Ch, 024h, 008h
    db 0DBh, 044h, 024h, 00Ch, 0D9h, 05Ch, 024h, 00Ch, 0FFh, 090h, 0B0h, 000h, 000h, 000h, 08Bh, 044h
    db 024h, 010h, 0DBh, 044h, 024h, 014h, 08Bh, 04Ch, 024h, 008h, 08Bh, 017h, 06Ah, 002h, 06Ah, 0FFh
    db 050h, 08Bh, 044h, 024h, 018h, 051h, 051h, 0D9h, 01Ch, 024h, 050h, 056h, 08Bh, 0CFh, 0FFh, 092h
    db 0D4h, 000h, 000h, 000h, 08Bh, 017h, 08Bh, 0CFh, 05Fh, 05Eh, 083h, 0C4h, 010h, 0FFh, 0A2h, 0DCh
    db 000h, 000h, 000h, 083h, 0C1h, 0F0h, 089h, 04Ch, 024h, 014h, 0DBh, 044h, 024h, 014h, 053h, 0D8h
    db 04Eh, 02Ch, 0D8h, 02Dh, 034h, 053h, 007h, 001h, 0D8h, 00Dh, 068h, 040h, 008h, 001h, 0E8h, 0C5h
    db 0B2h, 045h, 000h, 08Bh, 0D8h, 081h, 0FBh, 0FFh, 000h, 000h, 000h, 07Eh, 005h, 0BBh, 0FFh, 000h
    db 000h, 000h, 08Bh, 046h, 01Ch, 08Bh, 07Eh, 014h, 06Bh, 0C0h, 00Fh, 08Bh, 04Eh, 024h, 08Bh, 056h
    db 020h, 003h, 0C7h, 003h, 0C8h, 089h, 04Ch, 024h, 018h, 08Bh, 00Dh, 070h, 012h, 02Fh, 001h, 089h
    db 044h, 024h, 00Ch, 08Bh, 046h, 010h, 0DBh, 044h, 024h, 018h, 08Bh, 076h, 034h, 003h, 0D0h, 0D9h
    db 05Ch, 024h, 010h, 089h, 054h, 024h, 018h, 089h, 044h, 024h, 014h, 08Bh, 001h, 0DBh, 044h, 024h
    db 018h, 08Bh, 0F9h, 0D9h, 05Ch, 024h, 018h, 0DBh, 044h, 024h, 014h, 0D9h, 05Ch, 024h, 014h, 0FFh
    db 090h, 0B0h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 0DBh, 044h, 024h, 00Ch, 08Bh, 017h, 06Ah
    db 002h, 00Fh, 0B6h, 0C3h, 0C1h, 0E0h, 018h, 00Dh, 0FFh, 0FFh, 0FFh, 000h, 050h, 08Bh, 044h, 024h
    db 020h, 051h, 050h, 051h, 08Bh, 04Ch, 024h, 028h, 0D9h, 01Ch, 024h, 051h, 056h, 08Bh, 0CFh, 0FFh
    db 092h, 0D4h, 000h, 000h, 000h, 08Bh, 017h, 05Bh, 08Bh, 0CFh, 05Fh, 05Eh, 083h, 0C4h, 010h, 0FFh
    db 0A2h, 0DCh, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 010h, 0C3h
?draw@ControlBarArrowTransition@@UAEXXZ ENDP
_TEXT ENDS
END
