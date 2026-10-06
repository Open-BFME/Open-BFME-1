.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?Gen01085F58@@3NA:BYTE
EXTERN ?bfmeGaussPdf@@YANNNN@Z:NEAR
EXTERN ?g_bfmeSubB3@@3NA:BYTE
EXTERN ?g_rva01356A9C@@3PAHA:BYTE
EXTERN __ftol2:NEAR
EXTERN __imp__rand:BYTE
EXTERN __real@3f8a01a01a01a01a:BYTE
EXTERN __real@3fe0000000000000:BYTE
EXTERN __real@4040000000000000:BYTE
EXTERN __real@4070000000000000:BYTE
EXTERN __real@c040000000000000:BYTE
EXTERN g_Va012D86D0:BYTE
EXTERN g_Va012D86E0:BYTE
EXTERN g_Va012D86F0:BYTE
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x009B9700 size 4240
_TEXT ENDS
_TEXT$d00db9700 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DB9700 size 4240
public ?d_009b9700@@YAXXZ
?d_009b9700@@YAXXZ PROC
    db 053h, 08Bh, 0DCh, 083h, 0ECh, 008h, 083h, 0E4h, 0F0h, 083h, 0C4h, 004h, 055h, 08Bh, 06Bh, 004h
    db 089h, 06Ch, 024h, 004h, 08Bh, 0ECh, 081h, 0ECh, 0D8h, 001h, 000h, 000h, 056h, 057h, 08Bh, 043h
    db 008h, 08Bh, 040h, 00Ch, 08Bh, 04Bh, 020h, 08Bh, 053h, 01Ch, 0C1h, 0E0h, 002h, 08Bh, 00Ch, 008h
    db 089h, 04Dh, 0ACh, 066h, 089h, 04Dh, 0B0h, 066h, 089h, 04Dh, 0B2h, 066h, 089h, 04Dh, 0B4h, 066h
    db 089h, 04Dh, 0B6h, 08Bh, 00Dh
    dd ?g_rva01356A9C@@3PAHA
    db 08Bh, 004h, 008h, 066h, 089h, 045h, 090h, 066h, 089h, 045h, 092h, 066h, 089h, 045h, 094h, 066h
    db 089h, 045h, 096h, 08Bh, 043h, 018h, 003h, 0C2h, 03Bh, 0D0h, 089h, 055h, 0D8h, 089h, 045h, 08Ch
    db 00Fh, 083h, 018h, 010h, 000h, 000h, 08Bh, 053h, 00Ch, 08Dh, 00Ch, 085h, 000h, 000h, 000h, 000h
    db 08Bh, 043h, 010h, 089h, 04Dh, 0DCh, 08Bh, 04Bh, 014h, 089h, 055h, 0D4h, 08Dh, 014h, 0CDh, 000h
    db 000h, 000h, 000h, 089h, 045h, 0D0h, 02Bh, 0C2h, 089h, 045h, 0CCh, 08Bh, 045h, 0D4h, 08Bh, 04Dh
    db 0D0h, 089h, 045h, 0C4h, 089h, 04Dh, 0C8h, 050h, 055h, 051h, 052h, 056h, 057h, 08Bh, 045h, 0ACh
    db 033h, 0D2h, 08Bh, 04Bh, 014h, 00Fh, 06Eh, 0E8h, 08Bh, 045h, 0C4h, 00Fh, 061h, 0EDh, 08Dh, 0B5h
    db 030h, 0FEh, 0FFh, 0FFh, 00Fh, 062h, 0EDh, 02Bh, 0D1h, 00Fh, 07Fh, 0EEh, 00Fh, 0FDh, 0F5h, 00Fh
    db 0FDh, 0F5h, 00Fh, 067h, 0EDh, 00Fh, 07Fh, 06Dh, 0B0h, 00Fh, 071h, 0E6h, 002h, 00Fh, 067h, 0F6h
    db 08Dh, 0BDh, 0B0h, 0FEh, 0FFh, 0FFh, 00Fh, 0EFh, 0FFh, 00Fh, 0F8h, 035h
    dd g_Va012D86F0
    db 08Dh, 004h, 090h, 00Fh, 06Fh, 004h, 010h, 00Fh, 07Fh, 0C1h, 00Fh, 060h, 0C7h, 00Fh, 07Fh, 0CCh
    db 00Fh, 07Fh, 0B5h, 070h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 010h, 00Fh, 068h, 0CFh, 00Fh, 07Fh, 007h
    db 00Fh, 07Fh, 0D5h, 00Fh, 07Fh, 0D3h, 00Fh, 07Fh, 04Fh, 008h, 00Fh, 06Fh, 004h, 008h, 00Fh, 0D8h
    db 0ECh, 00Fh, 0D8h, 0E2h, 00Fh, 060h, 0D7h, 00Fh, 0EBh, 0E5h, 00Fh, 07Fh, 057h, 010h, 00Fh, 07Fh
    db 0DEh, 00Fh, 068h, 0DFh, 00Fh, 07Fh, 05Fh, 018h, 00Fh, 07Fh, 0C1h, 00Fh, 060h, 0C7h, 00Fh, 07Fh
    db 047h, 020h, 00Fh, 06Fh, 014h, 048h, 00Fh, 07Fh, 0CDh, 00Fh, 0D8h, 0EEh, 00Fh, 0D8h, 0F1h, 00Fh
    db 0EBh, 0EEh, 00Fh, 07Fh, 0CEh, 00Fh, 068h, 0CFh, 00Fh, 07Fh, 0D3h, 00Fh, 07Fh, 04Fh, 028h, 00Fh
    db 0DCh, 0E5h, 00Fh, 07Fh, 0D5h, 00Fh, 0D8h, 0EEh, 00Fh, 0D8h, 0F2h, 00Fh, 0EBh, 0EEh, 00Fh, 07Fh
    db 0D6h, 00Fh, 060h, 0D7h, 08Dh, 004h, 088h, 00Fh, 068h, 0DFh, 00Fh, 06Fh, 004h, 010h, 00Fh, 07Fh
    db 057h, 030h, 00Fh, 0DCh, 0E5h, 00Fh, 07Fh, 0C5h, 00Fh, 07Fh, 05Fh, 038h, 00Fh, 07Fh, 0C1h, 00Fh
    db 0D8h, 0EEh, 00Fh, 0D8h, 0F1h, 00Fh, 060h, 0C7h, 00Fh, 0EBh, 0EEh, 00Fh, 07Fh, 047h, 040h, 00Fh
    db 07Fh, 0CEh, 00Fh, 068h, 0CFh, 00Fh, 07Fh, 04Fh, 048h, 00Fh, 06Fh, 000h, 00Fh, 0DCh, 0E5h, 00Fh
    db 07Fh, 065h, 0F0h, 00Fh, 06Fh, 0ADh, 070h, 0FFh, 0FFh, 0FFh, 00Fh, 0F8h, 025h
    dd g_Va012D86F0
    db 00Fh, 064h, 0ECh, 00Fh, 07Fh, 0C1h, 00Fh, 060h, 0C7h, 00Fh, 07Fh, 0CCh, 00Fh, 07Fh, 047h, 050h
    db 00Fh, 0D8h, 0E6h, 00Fh, 0D8h, 0F1h, 00Fh, 06Fh, 004h, 008h, 00Fh, 06Fh, 05Dh, 0B0h, 00Fh, 0EBh
    db 0E6h, 00Fh, 07Fh, 0CEh, 00Fh, 0F8h, 01Dh
    dd g_Va012D86F0
    db 00Fh, 0F8h, 025h
    dd g_Va012D86F0
    db 00Fh, 064h, 0DCh, 00Fh, 068h, 0CFh, 00Fh, 07Fh, 0C4h, 00Fh, 0DBh, 0EBh, 00Fh, 07Fh, 04Fh, 058h
    db 00Fh, 07Fh, 0C1h, 00Fh, 0D8h, 0E6h, 00Fh, 060h, 0C7h, 00Fh, 0D8h, 0F1h, 00Fh, 07Fh, 047h, 060h
    db 00Fh, 0EBh, 0E6h, 00Fh, 06Fh, 014h, 048h, 00Fh, 07Fh, 0CEh, 08Dh, 004h, 088h, 00Fh, 068h, 0CFh
    db 00Fh, 07Fh, 0D0h, 00Fh, 07Fh, 04Fh, 068h, 00Fh, 07Fh, 0C3h, 00Fh, 06Fh, 00Ch, 010h, 00Fh, 060h
    db 0D7h, 00Fh, 0D8h, 0DEh, 00Fh, 0D8h, 0F0h, 00Fh, 0EBh, 0DEh, 00Fh, 07Fh, 057h, 070h, 00Fh, 07Fh
    db 0C6h, 00Fh, 068h, 0C7h, 00Fh, 0DCh, 0E3h, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0CBh, 00Fh, 07Fh, 047h
    db 078h, 00Fh, 060h, 0CFh, 00Fh, 06Fh, 000h, 00Fh, 0D8h, 0DEh, 00Fh, 0D8h, 0F2h, 00Fh, 0EBh, 0DEh
    db 00Fh, 07Fh, 08Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0D6h, 00Fh, 068h, 0D7h, 00Fh, 0DCh, 0E3h
    db 00Fh, 07Fh, 0C1h, 00Fh, 07Fh, 0C3h, 00Fh, 07Fh, 097h, 088h, 000h, 000h, 000h, 00Fh, 060h, 0C7h
    db 00Fh, 0D8h, 0DEh, 00Fh, 07Fh, 087h, 090h, 000h, 000h, 000h, 00Fh, 0D8h, 0F1h, 00Fh, 0EBh, 0DEh
    db 00Fh, 068h, 0CFh, 00Fh, 0DCh, 0E3h, 00Fh, 07Fh, 065h, 0E0h, 00Fh, 06Fh, 0B5h, 070h, 0FFh, 0FFh
    db 0FFh, 00Fh, 0F8h, 025h
    dd g_Va012D86F0
    db 00Fh, 07Fh, 08Fh, 098h, 000h, 000h, 000h, 00Fh, 064h, 0F4h, 00Fh, 0DBh, 0F5h, 00Fh, 07Fh, 0F0h
    db 00Fh, 07Fh, 0F7h, 00Fh, 068h, 0C6h, 00Fh, 060h, 0FEh, 00Fh, 06Fh, 04Dh, 090h, 00Fh, 06Fh, 05Fh
    db 030h, 00Fh, 06Fh, 067h, 040h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0ECh
    db 00Fh, 0F9h, 0DEh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E5h, 00Fh, 0FDh, 01Dh
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0ECh, 00Fh, 0FDh, 0DDh, 00Fh, 071h, 0E3h, 003h, 00Fh, 07Fh, 0DAh, 00Fh, 071h, 0E3h
    db 00Fh, 00Fh, 0EFh, 0D3h, 00Fh, 0E9h, 0D3h, 00Fh, 0EBh, 01Dh
    dd g_Va012D86E0
    db 00Fh, 07Fh, 0CCh, 00Fh, 0F9h, 0CAh, 00Fh, 07Fh, 0CDh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 0EFh, 0E9h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0D9h, 0E5h, 00Fh, 0D5h, 0E3h, 00Fh, 06Fh, 04Fh, 040h, 00Fh, 06Fh, 057h
    db 050h, 00Fh, 0FDh, 0CCh, 00Fh, 0F9h, 0D4h, 00Fh, 0EFh, 0F6h, 00Fh, 067h, 0C9h, 00Fh, 067h, 0D2h
    db 00Fh, 060h, 0CEh, 00Fh, 07Fh, 08Dh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 060h, 0D6h, 00Fh, 07Fh, 095h
    db 060h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 01Fh, 00Fh, 06Fh, 097h, 090h, 000h, 000h, 000h, 00Fh, 07Fh
    db 0D9h, 00Fh, 0FDh, 0DBh, 00Fh, 06Fh, 067h, 010h, 00Fh, 0FDh, 0D9h, 00Fh, 0FDh, 05Fh, 020h, 00Fh
    db 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh, 025h
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0DCh, 00Fh, 07Fh, 0DCh, 00Fh, 06Fh, 06Fh, 010h, 00Fh, 0FDh, 0E5h, 00Fh, 071h, 0E4h
    db 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 026h, 00Fh, 06Fh, 06Fh
    db 020h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 050h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h
    db 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 010h, 00Fh
    db 06Fh, 06Fh, 030h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 060h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h
    db 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h
    db 020h, 00Fh, 06Fh, 06Fh, 040h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 070h, 00Fh, 07Fh, 0ECh, 00Fh
    db 0FDh, 0E3h, 00Fh, 06Fh, 0ADh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h
    db 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 06Fh, 0ADh, 060h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h
    db 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh
    db 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh
    db 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 050h, 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh
    db 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h
    db 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh, 06Fh, 0AFh, 080h, 000h
    db 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h
    db 083h, 0C7h, 008h, 083h, 0C6h, 008h, 00Fh, 06Fh, 04Dh, 090h, 00Fh, 06Fh, 05Fh, 030h, 00Fh, 06Fh
    db 067h, 040h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0ECh, 00Fh, 0F9h, 0DEh
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 01Dh
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 0DCh, 00Fh, 0FDh, 0DDh, 00Fh, 071h, 0E3h, 003h, 00Fh, 07Fh, 0DAh
    db 00Fh, 071h, 0E3h, 00Fh, 00Fh, 0EFh, 0D3h, 00Fh, 0E9h, 0D3h, 00Fh, 0EBh, 01Dh
    dd g_Va012D86E0
    db 00Fh, 07Fh, 0CCh, 00Fh, 0F9h, 0CAh, 00Fh, 07Fh, 0CDh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 0EFh, 0E9h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0D9h, 0E5h, 00Fh, 0D5h, 0E3h, 00Fh, 06Fh, 04Fh, 040h, 00Fh, 06Fh, 057h
    db 050h, 00Fh, 0FDh, 0CCh, 00Fh, 0F9h, 0D4h, 00Fh, 0EFh, 0F6h, 00Fh, 067h, 0C9h, 00Fh, 067h, 0D2h
    db 00Fh, 060h, 0CEh, 00Fh, 07Fh, 08Dh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 060h, 0D6h, 00Fh, 07Fh, 095h
    db 060h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 01Fh, 00Fh, 06Fh, 097h, 090h, 000h, 000h, 000h, 00Fh, 07Fh
    db 0D9h, 00Fh, 0FDh, 0DBh, 00Fh, 06Fh, 067h, 010h, 00Fh, 0FDh, 0D9h, 00Fh, 0FDh, 05Fh, 020h, 00Fh
    db 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh, 025h
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0DCh, 00Fh, 07Fh, 0DCh, 00Fh, 06Fh, 06Fh, 010h, 00Fh, 0FDh, 0E5h, 00Fh, 071h, 0E4h
    db 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 026h, 00Fh, 06Fh, 06Fh
    db 020h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 050h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h
    db 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 010h, 00Fh
    db 06Fh, 06Fh, 030h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 060h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h
    db 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h
    db 020h, 00Fh, 06Fh, 06Fh, 040h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 070h, 00Fh, 07Fh, 0ECh, 00Fh
    db 0FDh, 0E3h, 00Fh, 06Fh, 0ADh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h
    db 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 06Fh, 0ADh, 060h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h
    db 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh
    db 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh
    db 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 050h, 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh
    db 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h
    db 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh, 06Fh, 0AFh, 080h, 000h
    db 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h
    db 083h, 0C7h, 008h, 083h, 0EEh, 008h, 08Bh, 06Dh, 0C8h, 08Dh, 06Ch, 095h, 000h, 00Fh, 06Fh, 006h
    db 00Fh, 067h, 046h, 008h, 00Fh, 07Fh, 045h, 000h, 00Fh, 06Fh, 04Eh, 010h, 00Fh, 067h, 04Eh, 018h
    db 00Fh, 07Fh, 04Ch, 00Dh, 000h, 00Fh, 06Fh, 056h, 020h, 00Fh, 067h, 056h, 028h, 00Fh, 07Fh, 054h
    db 04Dh, 000h, 00Fh, 06Fh, 05Eh, 030h, 00Fh, 067h, 05Eh, 038h, 08Dh, 06Ch, 08Dh, 000h, 00Fh, 07Fh
    db 05Ch, 015h, 000h, 00Fh, 06Fh, 046h, 040h, 00Fh, 067h, 046h, 048h, 00Fh, 07Fh, 045h, 000h, 00Fh
    db 06Fh, 04Eh, 050h, 00Fh, 067h, 04Eh, 058h, 00Fh, 07Fh, 04Ch, 00Dh, 000h, 00Fh, 06Fh, 056h, 060h
    db 00Fh, 067h, 056h, 068h, 00Fh, 07Fh, 054h, 04Dh, 000h, 00Fh, 06Fh, 05Eh, 070h, 00Fh, 067h, 05Eh
    db 078h, 08Dh, 06Ch, 04Dh, 000h, 00Fh, 07Fh, 05Ch, 00Dh, 000h, 05Fh, 05Eh, 05Ah, 059h, 05Dh, 058h
    db 00Fh, 0B6h, 07Dh, 0F6h, 00Fh, 0B6h, 075h, 0F7h, 003h, 0F7h, 00Fh, 0B6h, 07Dh, 0F5h, 003h, 0F7h
    db 00Fh, 0B6h, 07Dh, 0F4h, 003h, 0F7h, 00Fh, 0B6h, 07Dh, 0F3h, 08Bh, 053h, 008h, 08Bh, 042h, 028h
    db 08Bh, 04Dh, 0D8h, 003h, 0F7h, 00Fh, 0B6h, 07Dh, 0F2h, 003h, 0F7h, 00Fh, 0B6h, 07Dh, 0F1h, 003h
    db 0F7h, 00Fh, 0B6h, 07Dh, 0F0h, 003h, 0F7h, 08Bh, 03Ch, 088h, 003h, 0FEh, 00Fh, 0B6h, 075h, 0E6h
    db 08Dh, 004h, 088h, 089h, 038h, 08Bh, 052h, 028h, 08Bh, 045h, 0DCh, 003h, 0C2h, 00Fh, 0B6h, 055h
    db 0E7h, 003h, 0D6h, 00Fh, 0B6h, 075h, 0E5h, 003h, 0D6h, 00Fh, 0B6h, 075h, 0E4h, 003h, 0D6h, 00Fh
    db 0B6h, 075h, 0E3h, 003h, 0D6h, 00Fh, 0B6h, 075h, 0E2h, 003h, 0D6h, 00Fh, 0B6h, 075h, 0E1h, 003h
    db 0D6h, 00Fh, 0B6h, 075h, 0E0h, 003h, 0D6h, 001h, 010h, 03Bh, 04Bh, 01Ch, 075h, 026h, 08Bh, 07Dh
    db 0D4h, 08Bh, 075h, 0D0h, 08Bh, 055h, 0CCh, 0B8h, 008h, 000h, 000h, 000h, 041h, 003h, 0F8h, 003h
    db 0F0h, 003h, 0D0h, 089h, 04Dh, 0D8h, 089h, 07Dh, 0D4h, 089h, 075h, 0D0h, 089h, 055h, 0CCh, 0E9h
    db 0EDh, 008h, 000h, 000h, 08Bh, 045h, 0CCh, 066h, 00Fh, 0B6h, 048h, 0FBh, 066h, 00Fh, 0B6h, 050h
    db 004h, 066h, 089h, 095h, 040h, 0FFh, 0FFh, 0FFh, 066h, 089h, 08Dh, 0B0h, 0FEh, 0FFh, 0FFh, 08Bh
    db 04Bh, 014h, 066h, 00Fh, 0B6h, 054h, 008h, 0FBh, 066h, 089h, 095h, 0B2h, 0FEh, 0FFh, 0FFh, 066h
    db 00Fh, 0B6h, 054h, 008h, 004h, 066h, 089h, 095h, 042h, 0FFh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h
    db 048h, 0FBh, 066h, 089h, 095h, 0B4h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h, 048h, 004h, 066h
    db 089h, 095h, 044h, 0FFh, 0FFh, 0FFh, 08Dh, 014h, 049h, 066h, 00Fh, 0B6h, 074h, 010h, 0FBh, 066h
    db 00Fh, 0B6h, 054h, 010h, 004h, 066h, 089h, 095h, 046h, 0FFh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h
    db 088h, 0FBh, 066h, 089h, 095h, 0B8h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h, 088h, 004h, 066h
    db 089h, 095h, 048h, 0FFh, 0FFh, 0FFh, 08Dh, 014h, 089h, 066h, 089h, 0B5h, 0B6h, 0FEh, 0FFh, 0FFh
    db 066h, 00Fh, 0B6h, 074h, 010h, 0FBh, 066h, 00Fh, 0B6h, 054h, 010h, 004h, 066h, 089h, 095h, 04Ah
    db 0FFh, 0FFh, 0FFh, 08Dh, 014h, 049h, 06Bh, 0C9h, 007h, 0D1h, 0E2h, 066h, 089h, 0B5h, 0BAh, 0FEh
    db 0FFh, 0FFh, 066h, 00Fh, 0B6h, 074h, 010h, 0FBh, 066h, 00Fh, 0B6h, 054h, 010h, 004h, 066h, 089h
    db 095h, 04Ch, 0FFh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h, 008h, 0FBh, 089h, 045h, 0C8h, 089h, 045h
    db 0C4h, 066h, 00Fh, 0B6h, 044h, 008h, 004h, 066h, 089h, 0B5h, 0BCh, 0FEh, 0FFh, 0FFh, 066h, 089h
    db 095h, 0BEh, 0FEh, 0FFh, 0FFh, 066h, 089h, 085h, 04Eh, 0FFh, 0FFh, 0FFh, 050h, 055h, 08Bh, 045h
    db 0ACh, 00Fh, 06Eh, 0C0h, 051h, 00Fh, 061h, 0C0h, 00Fh, 062h, 0C0h, 052h, 00Fh, 07Fh, 0C1h, 00Fh
    db 0FDh, 0C8h, 056h, 00Fh, 0FDh, 0C8h, 00Fh, 067h, 0C0h, 057h, 00Fh, 07Fh, 045h, 0B0h, 00Fh, 071h
    db 0E1h, 002h, 00Fh, 067h, 0C9h, 00Fh, 0F8h, 00Dh
    dd g_Va012D86F0
    db 00Fh, 07Fh, 08Dh, 070h, 0FFh, 0FFh, 0FFh, 08Bh, 045h, 0C4h, 033h, 0D2h, 083h, 0E8h, 004h, 08Dh
    db 0B5h, 030h, 0FEh, 0FFh, 0FFh, 08Dh, 0BDh, 0B0h, 0FEh, 0FFh, 0FFh, 08Bh, 04Bh, 014h, 02Bh, 0D1h
    db 00Fh, 06Fh, 000h, 00Fh, 06Fh, 00Ch, 008h, 00Fh, 06Fh, 014h, 048h, 08Dh, 004h, 088h, 00Fh, 06Fh
    db 01Ch, 010h, 00Fh, 07Fh, 0C4h, 00Fh, 060h, 0C1h, 00Fh, 068h, 0E1h, 00Fh, 07Fh, 0D5h, 00Fh, 060h
    db 0D3h, 00Fh, 068h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh, 061h, 0C2h, 00Fh, 069h, 0CAh, 00Fh, 07Fh, 0E2h
    db 00Fh, 069h, 0E5h, 00Fh, 061h, 0D5h, 00Fh, 0EFh, 0FFh, 00Fh, 07Fh, 0C5h, 00Fh, 060h, 0C7h, 00Fh
    db 07Fh, 047h, 010h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C8h, 00Fh, 07Fh, 06Fh, 020h, 00Fh, 060h, 0CFh
    db 00Fh, 068h, 0C7h, 00Fh, 07Fh, 04Fh, 030h, 00Fh, 07Fh, 0D3h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 047h
    db 040h, 00Fh, 060h, 0D7h, 00Fh, 068h, 0DFh, 00Fh, 07Fh, 057h, 050h, 00Fh, 060h, 0E7h, 00Fh, 068h
    db 0EFh, 00Fh, 07Fh, 05Fh, 060h, 00Fh, 06Fh, 000h, 00Fh, 06Fh, 00Ch, 008h, 00Fh, 07Fh, 067h, 070h
    db 00Fh, 06Fh, 014h, 048h, 08Dh, 004h, 088h, 00Fh, 07Fh, 0AFh, 080h, 000h, 000h, 000h, 00Fh, 07Fh
    db 0C4h, 00Fh, 06Fh, 01Ch, 010h, 00Fh, 060h, 0C1h, 00Fh, 068h, 0E1h, 00Fh, 07Fh, 0D5h, 00Fh, 060h
    db 0D3h, 00Fh, 068h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh, 061h, 0C2h, 00Fh, 069h, 0CAh, 00Fh, 07Fh, 0E2h
    db 00Fh, 069h, 0E5h, 00Fh, 061h, 0D5h, 00Fh, 07Fh, 0C5h, 00Fh, 060h, 0C7h, 00Fh, 07Fh, 047h, 018h
    db 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C8h, 00Fh, 07Fh, 06Fh, 028h, 00Fh, 060h, 0CFh, 00Fh, 068h, 0C7h
    db 00Fh, 07Fh, 04Fh, 038h, 00Fh, 07Fh, 0D3h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 047h, 048h, 00Fh, 060h
    db 0D7h, 00Fh, 068h, 0DFh, 00Fh, 07Fh, 057h, 058h, 00Fh, 060h, 0E7h, 00Fh, 068h, 0EFh, 00Fh, 07Fh
    db 05Fh, 068h, 00Fh, 07Fh, 067h, 078h, 00Fh, 07Fh, 0AFh, 088h, 000h, 000h, 000h, 00Fh, 06Fh, 007h
    db 00Fh, 06Fh, 04Fh, 010h, 00Fh, 06Fh, 057h, 020h, 00Fh, 067h, 047h, 008h, 00Fh, 067h, 04Fh, 018h
    db 00Fh, 067h, 057h, 028h, 00Fh, 06Fh, 05Fh, 030h, 00Fh, 06Fh, 067h, 040h, 00Fh, 067h, 05Fh, 038h
    db 00Fh, 067h, 067h, 048h, 00Fh, 07Fh, 0CDh, 00Fh, 07Fh, 0D6h, 00Fh, 0D8h, 0E8h, 00Fh, 0D8h, 0C1h
    db 00Fh, 0EBh, 0C5h, 00Fh, 0D8h, 0F1h, 00Fh, 0D8h, 0CAh, 00Fh, 07Fh, 0DDh, 00Fh, 0EBh, 0CEh, 00Fh
    db 0D8h, 0EAh, 00Fh, 0D8h, 0D3h, 00Fh, 07Fh, 0E6h, 00Fh, 0EBh, 0D5h, 00Fh, 0D8h, 0F3h, 00Fh, 0D8h
    db 0DCh, 00Fh, 0EBh, 0DEh, 00Fh, 0DCh, 0C1h, 00Fh, 0DCh, 0D3h, 00Fh, 06Fh, 0BDh, 070h, 0FFh, 0FFh
    db 0FFh, 00Fh, 0DCh, 0C2h, 00Fh, 07Fh, 045h, 0F0h, 00Fh, 07Fh, 0E6h, 00Fh, 0F8h, 005h
    dd g_Va012D86F0
    db 00Fh, 064h, 0F8h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 06Fh, 04Fh, 060h, 00Fh, 06Fh, 057h, 070h, 00Fh
    db 067h, 06Fh, 058h, 00Fh, 067h, 04Fh, 068h, 00Fh, 067h, 057h, 078h, 00Fh, 06Fh, 09Fh, 080h, 000h
    db 000h, 000h, 00Fh, 06Fh, 0A7h, 090h, 000h, 000h, 000h, 00Fh, 067h, 09Fh, 088h, 000h, 000h, 000h
    db 00Fh, 067h, 0A7h, 098h, 000h, 000h, 000h, 00Fh, 07Fh, 0E8h, 00Fh, 0D8h, 0EEh, 00Fh, 0D8h, 0F0h
    db 00Fh, 0EBh, 0EEh, 00Fh, 06Fh, 075h, 0B0h, 00Fh, 0F8h, 02Dh
    dd g_Va012D86F0
    db 00Fh, 0F8h, 035h
    dd g_Va012D86F0
    db 00Fh, 064h, 0F5h, 00Fh, 07Fh, 0CDh, 00Fh, 0DBh, 0FEh, 00Fh, 07Fh, 0D6h, 00Fh, 0D8h, 0E8h, 00Fh
    db 0D8h, 0C1h, 00Fh, 0EBh, 0C5h, 00Fh, 0D8h, 0F1h, 00Fh, 0D8h, 0CAh, 00Fh, 07Fh, 0DDh, 00Fh, 0EBh
    db 0CEh, 00Fh, 0D8h, 0EAh, 00Fh, 0D8h, 0D3h, 00Fh, 07Fh, 0E6h, 00Fh, 0EBh, 0D5h, 00Fh, 0D8h, 0F3h
    db 00Fh, 0D8h, 0DCh, 00Fh, 0EBh, 0DEh, 00Fh, 0DCh, 0C1h, 00Fh, 0DCh, 0D3h, 00Fh, 06Fh, 0B5h, 070h
    db 0FFh, 0FFh, 0FFh, 00Fh, 0DCh, 0C2h, 00Fh, 07Fh, 045h, 0E0h, 00Fh, 0F8h, 005h
    dd g_Va012D86F0
    db 00Fh, 064h, 0F0h, 00Fh, 0DBh, 0F7h, 00Fh, 07Fh, 0F0h, 00Fh, 07Fh, 0F7h, 00Fh, 068h, 0C6h, 00Fh
    db 060h, 0FEh, 00Fh, 06Fh, 04Dh, 090h, 00Fh, 06Fh, 05Fh, 030h, 00Fh, 06Fh, 067h, 040h, 00Fh, 06Fh
    db 06Fh, 050h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0ECh, 00Fh, 0F9h, 0DEh, 00Fh, 07Fh, 0ECh, 00Fh
    db 0FDh, 0E5h, 00Fh, 0FDh, 01Dh
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0ECh, 00Fh, 0FDh, 0DDh, 00Fh, 071h, 0E3h, 003h, 00Fh, 07Fh, 0DAh, 00Fh, 071h, 0E3h
    db 00Fh, 00Fh, 0EFh, 0D3h, 00Fh, 0E9h, 0D3h, 00Fh, 0EBh, 01Dh
    dd g_Va012D86E0
    db 00Fh, 07Fh, 0CCh, 00Fh, 0F9h, 0CAh, 00Fh, 07Fh, 0CDh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 0EFh, 0E9h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0D9h, 0E5h, 00Fh, 0D5h, 0E3h, 00Fh, 06Fh, 04Fh, 040h, 00Fh, 06Fh, 057h
    db 050h, 00Fh, 0FDh, 0CCh, 00Fh, 0F9h, 0D4h, 00Fh, 0EFh, 0F6h, 00Fh, 067h, 0C9h, 00Fh, 067h, 0D2h
    db 00Fh, 060h, 0CEh, 00Fh, 07Fh, 08Dh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 060h, 0D6h, 00Fh, 07Fh, 095h
    db 060h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 01Fh, 00Fh, 06Fh, 097h, 090h, 000h, 000h, 000h, 00Fh, 07Fh
    db 0D9h, 00Fh, 0FDh, 0DBh, 00Fh, 06Fh, 067h, 010h, 00Fh, 0FDh, 0D9h, 00Fh, 0FDh, 05Fh, 020h, 00Fh
    db 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh, 025h
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0DCh, 00Fh, 07Fh, 0DCh, 00Fh, 06Fh, 06Fh, 010h, 00Fh, 0FDh, 0E5h, 00Fh, 071h, 0E4h
    db 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 026h, 00Fh, 06Fh, 06Fh
    db 020h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 050h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h
    db 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 010h, 00Fh
    db 06Fh, 06Fh, 030h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 060h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h
    db 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h
    db 020h, 00Fh, 06Fh, 06Fh, 040h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 070h, 00Fh, 07Fh, 0ECh, 00Fh
    db 0FDh, 0E3h, 00Fh, 06Fh, 0ADh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h
    db 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 06Fh, 0ADh, 060h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h
    db 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh
    db 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh
    db 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 050h, 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh
    db 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h
    db 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh, 06Fh, 0AFh, 080h, 000h
    db 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h
    db 083h, 0C7h, 008h, 083h, 0C6h, 008h, 00Fh, 06Fh, 04Dh, 090h, 00Fh, 06Fh, 05Fh, 030h, 00Fh, 06Fh
    db 067h, 040h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0ECh, 00Fh, 0F9h, 0DEh
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E5h, 00Fh, 0FDh, 01Dh
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0ECh, 00Fh, 0FDh, 0DDh, 00Fh, 071h, 0E3h, 003h, 00Fh, 07Fh, 0DAh, 00Fh, 071h, 0E3h
    db 00Fh, 00Fh, 0EFh, 0D3h, 00Fh, 0E9h, 0D3h, 00Fh, 0EBh, 01Dh
    dd g_Va012D86E0
    db 00Fh, 07Fh, 0CCh, 00Fh, 0F9h, 0CAh, 00Fh, 07Fh, 0CDh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 0EFh, 0E9h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0D9h, 0E5h, 00Fh, 0D5h, 0E3h, 00Fh, 06Fh, 04Fh, 040h, 00Fh, 06Fh, 057h
    db 050h, 00Fh, 0FDh, 0CCh, 00Fh, 0F9h, 0D4h, 00Fh, 0EFh, 0F6h, 00Fh, 067h, 0C9h, 00Fh, 067h, 0D2h
    db 00Fh, 060h, 0CEh, 00Fh, 07Fh, 08Dh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 060h, 0D6h, 00Fh, 07Fh, 095h
    db 060h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 01Fh, 00Fh, 06Fh, 097h, 090h, 000h, 000h, 000h, 00Fh, 07Fh
    db 0D9h, 00Fh, 0FDh, 0DBh, 00Fh, 06Fh, 067h, 010h, 00Fh, 0FDh, 0D9h, 00Fh, 0FDh, 05Fh, 020h, 00Fh
    db 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh, 025h
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0DCh, 00Fh, 07Fh, 0DCh, 00Fh, 06Fh, 06Fh, 010h, 00Fh, 0FDh, 0E5h, 00Fh, 071h, 0E4h
    db 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 026h, 00Fh, 06Fh, 06Fh
    db 020h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 050h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h
    db 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 010h, 00Fh
    db 06Fh, 06Fh, 030h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 060h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h
    db 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h
    db 020h, 00Fh, 06Fh, 06Fh, 040h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 070h, 00Fh, 07Fh, 0ECh, 00Fh
    db 0FDh, 0E3h, 00Fh, 06Fh, 0ADh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h
    db 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 06Fh, 0ADh, 060h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h
    db 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh
    db 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh
    db 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 050h, 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh
    db 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E4h, 003h, 00Fh, 0F9h
    db 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh, 06Fh, 0AFh, 080h, 000h
    db 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 071h, 0E4h, 003h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h
    db 08Bh, 045h, 0C8h, 083h, 0C7h, 008h, 083h, 0EEh, 008h, 083h, 0E8h, 004h, 00Fh, 06Fh, 006h, 00Fh
    db 06Fh, 04Eh, 010h, 00Fh, 07Fh, 0C4h, 00Fh, 061h, 0C1h, 00Fh, 069h, 0E1h, 00Fh, 06Fh, 056h, 020h
    db 00Fh, 06Fh, 05Eh, 030h, 00Fh, 07Fh, 0D5h, 00Fh, 061h, 0D3h, 00Fh, 069h, 0EBh, 00Fh, 07Fh, 0C1h
    db 00Fh, 062h, 0C2h, 00Fh, 07Fh, 007h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 04Fh, 010h
    db 00Fh, 062h, 0C5h, 00Fh, 06Ah, 0E5h, 00Fh, 06Fh, 04Eh, 040h, 00Fh, 06Fh, 056h, 050h, 00Fh, 06Fh
    db 06Eh, 060h, 00Fh, 06Fh, 076h, 070h, 00Fh, 07Fh, 0CBh, 00Fh, 07Fh, 0EFh, 00Fh, 061h, 0CAh, 00Fh
    db 069h, 0DAh, 00Fh, 061h, 0EEh, 00Fh, 069h, 0FEh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0DEh, 00Fh, 062h
    db 0CDh, 00Fh, 06Ah, 0D5h, 00Fh, 062h, 0DFh, 00Fh, 06Ah, 0F7h, 00Fh, 06Fh, 02Fh, 00Fh, 067h, 0E9h
    db 00Fh, 07Fh, 028h, 00Fh, 06Fh, 07Fh, 010h, 00Fh, 067h, 0FAh, 00Fh, 07Fh, 03Ch, 008h, 00Fh, 067h
    db 0C3h, 00Fh, 067h, 0E6h, 00Fh, 07Fh, 004h, 048h, 08Dh, 004h, 088h, 00Fh, 07Fh, 024h, 010h, 083h
    db 0C7h, 008h, 083h, 0C6h, 008h, 00Fh, 06Fh, 006h, 00Fh, 06Fh, 04Eh, 010h, 00Fh, 07Fh, 0C4h, 00Fh
    db 061h, 0C1h, 00Fh, 069h, 0E1h, 00Fh, 06Fh, 056h, 020h, 00Fh, 06Fh, 05Eh, 030h, 00Fh, 07Fh, 0D5h
    db 00Fh, 061h, 0D3h, 00Fh, 069h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh, 062h, 0C2h, 00Fh, 07Fh, 007h, 00Fh
    db 06Ah, 0CAh, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 04Fh, 010h, 00Fh, 062h, 0C5h, 00Fh, 06Ah, 0E5h, 00Fh
    db 06Fh, 04Eh, 040h, 00Fh, 06Fh, 056h, 050h, 00Fh, 06Fh, 06Eh, 060h, 00Fh, 06Fh, 076h, 070h, 00Fh
    db 07Fh, 0CBh, 00Fh, 07Fh, 0EFh, 00Fh, 061h, 0CAh, 00Fh, 069h, 0DAh, 00Fh, 061h, 0EEh, 00Fh, 069h
    db 0FEh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0DEh, 00Fh, 062h, 0CDh, 00Fh, 06Ah, 0D5h, 00Fh, 062h, 0DFh
    db 00Fh, 06Ah, 0F7h, 00Fh, 06Fh, 02Fh, 00Fh, 067h, 0E9h, 00Fh, 07Fh, 028h, 00Fh, 06Fh, 07Fh, 010h
    db 00Fh, 067h, 0FAh, 00Fh, 07Fh, 03Ch, 008h, 00Fh, 067h, 0C3h, 00Fh, 067h, 0E6h, 00Fh, 07Fh, 004h
    db 048h, 08Dh, 004h, 088h, 00Fh, 07Fh, 024h, 010h, 05Fh, 05Eh, 05Ah, 059h, 05Dh, 058h, 00Fh, 0B6h
    db 07Dh, 0F6h, 00Fh, 0B6h, 075h, 0F7h, 003h, 0F7h, 00Fh, 0B6h, 07Dh, 0F5h, 003h, 0F7h, 00Fh, 0B6h
    db 07Dh, 0F4h, 08Bh, 053h, 008h, 08Bh, 04Ah, 028h, 003h, 0F7h, 00Fh, 0B6h, 07Dh, 0F3h, 08Bh, 045h
    db 0D8h, 003h, 0F7h, 00Fh, 0B6h, 07Dh, 0F2h, 003h, 0F7h, 00Fh, 0B6h, 07Dh, 0F1h, 003h, 0F7h, 00Fh
    db 0B6h, 07Dh, 0F0h, 003h, 0F7h, 08Bh, 07Ch, 081h, 0FCh, 003h, 0FEh, 00Fh, 0B6h, 075h, 0E6h, 08Dh
    db 04Ch, 081h, 0FCh, 089h, 039h, 08Bh, 052h, 028h, 08Dh, 00Ch, 082h, 00Fh, 0B6h, 055h, 0E7h, 003h
    db 0D6h, 00Fh, 0B6h, 075h, 0E5h, 003h, 0D6h, 00Fh, 0B6h, 075h, 0E4h, 003h, 0D6h, 00Fh, 0B6h, 075h
    db 0E3h, 003h, 0D6h, 00Fh, 0B6h, 075h, 0E2h, 003h, 0D6h, 00Fh, 0B6h, 075h, 0E1h, 003h, 0D6h, 00Fh
    db 0B6h, 075h, 0E0h, 003h, 0D6h, 08Bh, 031h, 003h, 0F2h, 08Bh, 055h, 0D0h, 089h, 031h, 08Bh, 075h
    db 0D4h, 08Bh, 04Dh, 0CCh, 040h, 089h, 045h, 0D8h, 0B8h, 008h, 000h, 000h, 000h, 003h, 0F0h, 003h
    db 0D0h, 003h, 0C8h, 089h, 04Dh, 0CCh, 08Bh, 04Dh, 0D8h, 089h, 075h, 0D4h, 089h, 055h, 0D0h, 083h
    db 045h, 0DCh, 004h, 03Bh, 04Dh, 08Ch, 00Fh, 082h, 00Dh, 0F0h, 0FFh, 0FFh, 05Fh, 05Eh, 08Bh, 0E5h
    db 05Dh, 08Bh, 0E3h, 05Bh, 0C3h
?d_009b9700@@YAXXZ ENDP
_TEXT$d00db9700 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x009BD470 size 253
public ?d_009bd470@@YAXXZ
?d_009bd470@@YAXXZ PROC
    db 53h, 8Bh, 0DCh, 83h, 0ECh, 08h, 83h, 0E4h, 0F0h, 83h, 0C4h, 04h, 55h, 8Bh, 6Bh, 04h
    db 89h, 6Ch, 24h, 04h, 8Bh, 0ECh, 83h, 0ECh, 58h, 56h, 57h, 8Bh, 43h, 08h, 8Bh, 88h
    db 90h, 00h, 00h, 00h, 8Bh, 53h, 14h, 0C1h, 0E1h, 03h, 89h, 4Dh, 0ECh, 8Bh, 48h, 78h
    db 03h, 0D1h, 89h, 55h, 0FCh, 8Bh, 53h, 18h, 03h, 0CAh, 8Ah, 53h, 0Ch, 89h, 4Dh, 0F8h
    db 8Bh, 0B0h, 94h, 00h, 00h, 00h, 8Bh, 80h, 98h, 00h, 00h, 00h, 89h, 45h, 0F0h, 8Bh
    db 43h, 10h, 8Ah, 0C8h, 02h, 0CAh, 8Ah, 0D1h, 8Ah, 0F2h, 0C1h, 0E6h, 03h, 8Bh, 0CAh, 0C1h
    db 0E1h, 10h, 66h, 8Bh, 0CAh, 89h, 4Dh, 0C0h, 89h, 4Dh, 0C4h, 89h, 4Dh, 0C8h, 89h, 4Dh
    db 0CCh, 8Ah, 0C8h, 8Ah, 0E9h, 8Bh, 0C1h, 0C1h, 0E0h, 10h, 66h, 8Bh, 0C1h, 89h, 45h, 0D0h
    db 89h, 45h, 0D4h, 89h, 45h, 0D8h, 89h, 45h, 0DCh, 8Bh, 43h, 0Ch, 8Ah, 0D0h, 8Ah, 0F2h
    db 8Bh, 0C2h, 0C1h, 0E0h, 10h, 85h, 0F6h, 66h, 8Bh, 0C2h, 89h, 45h, 0B0h, 89h, 45h, 0B4h
    db 89h, 45h, 0B8h, 89h, 45h, 0BCh, 7Eh, 4Ch, 8Bh, 55h, 0F0h, 89h, 75h, 0F4h, 8Bh, 0FFh
    db 8Bh, 4Dh, 0ECh, 8Bh, 75h, 0FCh, 8Bh, 7Dh, 0F8h, 33h, 0C0h, 66h, 0Fh, 6Fh, 0Ch, 06h
    db 66h, 0Fh, 0D8h, 4Dh, 0B0h, 66h, 0Fh, 0DCh, 4Dh, 0C0h, 66h, 0Fh, 0D8h, 4Dh, 0D0h, 66h
    db 0Fh, 7Fh, 0Ch, 07h, 83h, 0C0h, 10h, 3Bh, 0C1h, 7Ch, 0E0h, 8Bh, 75h, 0FCh, 8Bh, 4Dh
    db 0F8h, 8Bh, 45h, 0F4h, 03h, 0F2h, 03h, 0CAh, 48h, 89h, 75h, 0FCh, 89h, 4Dh, 0F8h, 89h
    db 45h, 0F4h, 75h, 0BCh, 5Fh, 5Eh, 8Bh, 0E5h, 5Dh, 8Bh, 0E3h, 5Bh, 0C3h
?d_009bd470@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009C0A30 size 524
_TEXT ENDS
_TEXT$d00dc0a30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DC0A30 size 524
public ?d_009c0a30@@YAXXZ
?d_009c0a30@@YAXXZ PROC
    db 053h, 08Bh, 0DCh, 083h, 0ECh, 008h, 083h, 0E4h, 0F0h, 083h, 0C4h, 004h, 055h, 08Bh, 06Bh, 004h
    db 089h, 06Ch, 024h, 004h, 08Bh, 0ECh, 081h, 0ECh, 088h, 009h, 000h, 000h, 056h, 057h, 00Fh, 077h
    db 08Bh, 04Bh, 018h, 0B8h, 03Fh, 000h, 000h, 000h, 02Bh, 0C1h, 089h, 045h, 0FCh, 0DBh, 045h, 0FCh
    db 033h, 0FFh, 089h, 07Dh, 0F8h, 0DCh, 00Dh
    dd __real@3f8a01a01a01a01a
    db 0DCh, 005h
    dd ?g_bfmeSubB3@@3NA
    db 0DDh, 05Dh, 0D8h, 0DDh, 005h
    dd __real@c040000000000000
    db 0DDh, 055h, 0E8h, 08Dh, 049h, 000h, 083h, 0ECh, 018h, 0DDh, 05Ch, 024h, 010h, 0DDh, 005h
    dd ?Gen01085F58@@3NA
    db 0DDh, 05Ch, 024h, 008h, 0DDh, 045h, 0D8h, 0DDh, 01Ch, 024h
    call ?bfmeGaussPdf@@YANNNN@Z
    db 0DCh, 00Dh
    dd __real@4070000000000000
    db 083h, 0C4h, 018h, 0DCh, 005h
    dd __real@3fe0000000000000
    call __ftol2
    db 08Bh, 0F0h, 085h, 0F6h, 089h, 075h, 0F4h, 074h, 040h, 033h, 0C0h, 085h, 0F6h, 07Eh, 035h, 0DDh
    db 045h, 0E8h, 08Dh, 0BCh, 03Dh, 080h, 0FEh, 0FFh, 0FFh
    call __ftol2
    db 08Bh, 0CEh, 08Bh, 0D1h, 089h, 055h, 0FCh, 08Ah, 0D0h, 08Ah, 0F2h, 0C1h, 0E9h, 002h, 08Bh, 0C2h
    db 0C1h, 0E0h, 010h, 066h, 08Bh, 0C2h, 08Bh, 0D6h, 0F3h, 0ABh, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h
    db 0AAh, 08Bh, 07Dh, 0F8h, 08Bh, 0C6h, 003h, 0F8h, 089h, 07Dh, 0F8h, 0DDh, 045h, 0E8h, 0DCh, 005h
    dd ?g_bfmeSubB3@@3NA
    db 0DCh, 015h
    dd __real@4040000000000000
    db 0DDh, 055h, 0E8h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh, 08Bh, 06Ah, 0FFh, 0FFh, 0FFh, 081h, 0FFh
    db 000h, 001h, 000h, 000h, 0DDh, 0D8h, 07Dh, 020h, 08Dh, 094h, 03Dh, 080h, 0FEh, 0FFh, 0FFh, 0B9h
    db 000h, 001h, 000h, 000h, 02Bh, 0CFh, 08Bh, 0FAh, 08Bh, 0D1h, 0C1h, 0E9h, 002h, 033h, 0C0h, 0F3h
    db 0ABh, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h, 0AAh, 033h, 0F6h, 0FFh, 015h
    dd __imp__rand
    db 025h, 0FFh, 000h, 000h, 000h, 08Ah, 084h, 005h, 080h, 0FEh, 0FFh, 0FFh, 088h, 084h, 035h, 080h
    db 0F6h, 0FFh, 0FFh, 046h, 081h, 0FEh, 000h, 008h, 000h, 000h, 072h, 0DEh, 08Ah, 085h, 080h, 0FEh
    db 0FFh, 0FFh, 08Ah, 0C8h, 0B2h, 0FEh, 0F6h, 0EAh, 08Ah, 0D0h, 08Ah, 0F2h, 0F6h, 0D9h, 08Bh, 0C2h
    db 0C1h, 0E0h, 010h, 066h, 08Bh, 0C2h, 089h, 045h, 0B0h, 089h, 045h, 0B4h, 089h, 045h, 0B8h, 089h
    db 045h, 0BCh, 08Ah, 0C1h, 08Ah, 0D0h, 08Ah, 0F2h, 08Bh, 0C2h, 0C1h, 0E0h, 010h, 066h, 08Bh, 0C2h
    db 089h, 045h, 0D0h, 089h, 045h, 0D4h, 089h, 045h, 0D8h, 089h, 045h, 0DCh, 08Ah, 0C1h, 08Ah, 0E0h
    db 08Bh, 0C8h, 0C1h, 0E1h, 010h, 066h, 08Bh, 0C8h, 08Bh, 043h, 010h, 085h, 0C0h, 089h, 04Dh, 0C0h
    db 089h, 04Dh, 0C4h, 089h, 04Dh, 0C8h, 089h, 04Dh, 0CCh, 076h, 070h, 08Bh, 04Bh, 008h, 089h, 04Dh
    db 0F8h, 089h, 045h, 0FCh, 08Dh, 064h, 024h, 000h, 08Bh, 055h, 0F8h, 089h, 055h, 0ECh, 0FFh, 015h
    dd __imp__rand
    db 025h, 0FFh, 000h, 000h, 000h, 08Dh, 084h, 005h, 080h, 0F6h, 0FFh, 0FFh, 089h, 045h, 0F4h, 08Bh
    db 04Bh, 00Ch, 08Bh, 075h, 0ECh, 08Bh, 07Dh, 0F4h, 033h, 0C0h, 0F3h, 00Fh, 06Fh, 00Ch, 006h, 066h
    db 00Fh, 0D8h, 04Dh, 0C0h, 066h, 00Fh, 0DCh, 04Dh, 0B0h, 066h, 00Fh, 0D8h, 04Dh, 0D0h, 0F3h, 00Fh
    db 06Fh, 014h, 007h, 066h, 00Fh, 0FCh, 0CAh, 0F3h, 00Fh, 07Fh, 00Ch, 006h, 083h, 0C0h, 010h, 03Bh
    db 0C1h, 07Ch, 0D7h, 08Bh, 055h, 0F8h, 08Bh, 04Bh, 014h, 08Bh, 045h, 0FCh, 003h, 0D1h, 048h, 089h
    db 055h, 0F8h, 089h, 045h, 0FCh, 075h, 09Dh, 05Fh, 05Eh, 08Bh, 0E5h, 05Dh, 08Bh, 0E3h, 05Bh, 0C3h
?d_009c0a30@@YAXXZ ENDP
_TEXT$d00dc0a30 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x009C8730 size 8
public ?d_009c8730@@YAXXZ
?d_009c8730@@YAXXZ PROC
    db 0C6h, 05h, 4Dh, 0CBh, 34h, 01h, 01h, 0C3h
?d_009c8730@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009C9350 size 11
public ?d_009c9350@@YAXXZ
?d_009c9350@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_009c9350@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009C9380 size 33
public ?d_009c9380@@YAXXZ
?d_009c9380@@YAXXZ PROC
    db 56h, 6Ah, 30h, 0E8h, 0B8h, 51h, 0E6h, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 0Ch, 50h, 8Dh
    db 4Eh, 10h, 51h, 0E8h, 88h, 0FDh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_009c9380@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009C94C0 size 50
public ?d_009c94c0@@YAXXZ
?d_009c94c0@@YAXXZ PROC
    db 56h, 57h, 6Ah, 30h, 0E8h, 77h, 50h, 0E6h, 0FFh, 8Bh, 7Ch, 24h, 10h, 8Bh, 0F0h, 8Dh
    db 47h, 10h, 50h, 8Dh, 4Eh, 10h, 51h, 0E8h, 44h, 0FCh, 0FFh, 0FFh, 8Ah, 17h, 33h, 0C0h
    db 83h, 0C4h, 0Ch, 89h, 46h, 08h, 89h, 46h, 0Ch, 5Fh, 88h, 16h, 8Bh, 0C6h, 5Eh, 0C2h
    db 04h, 00h
?d_009c94c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009CBC00 size 11
public ?d_009cbc00@@YAXXZ
?d_009cbc00@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_009cbc00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009CDDF0 size 31
public ?d_009cddf0@@YAXXZ
?d_009cddf0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 78h, 3Bh, 14h, 01h, 74h, 09h
    db 56h, 0E8h, 0AAh, 40h, 0EBh, 0FFh, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_009cddf0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009CDF50 size 571
public ?d_009cdf50@@YAXXZ
?d_009cdf50@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 13h, 0Ah, 06h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 53h, 8Bh, 5Ch, 24h, 2Ch, 55h, 56h, 8Bh
    db 0C3h, 57h, 8Bh, 0F9h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h
    db 89h, 44h, 24h, 20h, 75h, 17h, 33h, 0C0h, 8Bh, 4Ch, 24h, 28h, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 24h, 0C2h, 10h, 00h, 6Ah, 18h, 0E8h
    db 8Ch, 3Fh, 0EBh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 33h, 0EDh, 3Bh, 0C5h, 89h
    db 6Ch, 24h, 30h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 74h, 39h, 00h, 00h, 8Bh, 0F0h, 0EBh, 02h
    db 33h, 0F6h, 0F6h, 44h, 24h, 3Ch, 02h, 0C7h, 44h, 24h, 30h, 0FFh, 0FFh, 0FFh, 0FFh, 89h
    db 74h, 24h, 20h, 0Fh, 84h, 46h, 01h, 00h, 00h, 89h, 6Ch, 24h, 1Ch, 3Bh, 0DDh, 0C7h
    db 44h, 24h, 30h, 01h, 00h, 00h, 00h, 74h, 12h, 8Bh, 0C3h, 8Dh, 50h, 01h, 8Bh, 0FFh
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 0EBh, 02h, 33h, 0C0h, 50h, 53h, 8Dh
    db 4Ch, 24h, 24h, 0E8h, 18h, 9Dh, 0EBh, 0FFh, 89h, 6Ch, 24h, 14h, 89h, 6Ch, 24h, 18h
    db 68h, 28h, 53h, 07h, 01h, 8Dh, 44h, 24h, 18h, 50h, 8Dh, 4Ch, 24h, 24h, 0C6h, 44h
    db 24h, 38h, 03h, 0E8h, 0B8h, 0A0h, 0EBh, 0FFh, 8Dh, 4Ch, 24h, 14h, 51h, 8Dh, 4Ch, 24h
    db 1Ch, 0E8h, 5Ah, 9Ch, 0EBh, 0FFh, 0B3h, 5Ch, 8Bh, 4Ch, 24h, 14h, 3Bh, 0CDh, 74h, 09h
    db 8Dh, 41h, 08h, 0Fh, 0B7h, 49h, 04h, 0EBh, 07h, 0B8h, 8Bh, 38h, 07h, 01h, 33h, 0C9h
    db 03h, 0C8h, 3Bh, 0C1h, 74h, 0Ah, 80h, 38h, 2Eh, 74h, 67h, 40h, 3Bh, 0C1h, 75h, 0F6h
    db 51h, 8Dh, 54h, 24h, 1Ch, 89h, 64h, 24h, 28h, 8Bh, 0CCh, 52h, 0E8h, 0EFh, 9Ah, 0EBh
    db 0FFh, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 1Ch, 68h, 28h, 53h, 07h, 01h, 8Dh, 4Ch, 24h
    db 18h, 51h, 8Dh, 4Ch, 24h, 24h, 0E8h, 55h, 0A0h, 0EBh, 0FFh, 6Ah, 01h, 8Dh, 54h, 24h
    db 14h, 52h, 8Dh, 4Ch, 24h, 20h, 88h, 5Ch, 24h, 18h, 0E8h, 0C1h, 9Ch, 0EBh, 0FFh, 8Bh
    db 44h, 24h, 14h, 3Bh, 0C5h, 0Fh, 84h, 9Ah, 00h, 00h, 00h, 0Fh, 0B7h, 48h, 04h, 51h
    db 83h, 0C0h, 08h, 50h, 8Dh, 4Ch, 24h, 20h, 0E8h, 0A3h, 9Ch, 0EBh, 0FFh, 0E9h, 76h, 0FFh
    db 0FFh, 0FFh, 8Bh, 4Ch, 24h, 1Ch, 3Bh, 0CDh, 74h, 09h, 8Dh, 41h, 08h, 0Fh, 0B7h, 49h
    db 04h, 0EBh, 07h, 0B8h, 8Bh, 38h, 07h, 01h, 33h, 0C9h, 03h, 0C8h, 3Bh, 0C1h, 74h, 0Eh
    db 80h, 38h, 2Eh, 0Fh, 84h, 77h, 0FFh, 0FFh, 0FFh, 40h, 3Bh, 0C1h, 75h, 0F2h, 8Dh, 4Ch
    db 24h, 18h, 0C6h, 44h, 24h, 30h, 02h, 0E8h, 44h, 98h, 0EBh, 0FFh, 8Dh, 4Ch, 24h, 14h
    db 0C6h, 44h, 24h, 30h, 01h, 0E8h, 36h, 98h, 0EBh, 0FFh, 8Dh, 4Ch, 24h, 1Ch, 0C7h, 44h
    db 24h, 30h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 25h, 98h, 0EBh, 0FFh, 8Bh, 5Ch, 24h, 38h, 8Bh
    db 4Ch, 24h, 3Ch, 8Bh, 06h, 51h, 53h, 8Bh, 0CEh, 0FFh, 50h, 04h, 84h, 0C0h, 75h, 2Ch
    db 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 08h, 8Bh, 06h, 6Ah, 01h, 8Bh, 0CEh, 0FFh, 10h, 89h
    db 6Ch, 24h, 20h, 0EBh, 2Dh, 33h, 0C9h, 51h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 8Dh, 4Ch
    db 24h, 20h, 0E8h, 09h, 9Ch, 0EBh, 0FFh, 0E9h, 0DCh, 0FEh, 0FFh, 0FFh, 8Bh, 44h, 24h, 40h
    db 3Bh, 0C5h, 0C6h, 46h, 0Dh, 01h, 74h, 0Ah, 8Bh, 16h, 6Ah, 01h, 50h, 8Bh, 0CEh, 0FFh
    db 52h, 14h, 8Bh, 4Ch, 24h, 28h, 8Bh, 44h, 24h, 20h, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 24h, 0C2h, 10h, 00h
?d_009cdf50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009CEA90 size 45
public ?d_009cea90@@YAXXZ
?d_009cea90@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 57h, 8Bh, 0F1h, 0E8h, 0F2h, 91h, 0EBh, 0FFh, 8Dh, 47h
    db 04h, 50h, 8Dh, 4Eh, 04h, 0E8h, 0E6h, 91h, 0EBh, 0FFh, 8Bh, 4Fh, 08h, 89h, 4Eh, 08h
    db 8Bh, 57h, 0Ch, 5Fh, 89h, 56h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_009cea90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009CED80 size 33
public ?d_009ced80@@YAXXZ
?d_009ced80@@YAXXZ PROC
    db 56h, 6Ah, 30h, 0E8h, 0B8h, 0F7h, 0E5h, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 0Ch, 50h, 8Dh
    db 4Eh, 10h, 51h, 0E8h, 18h, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_009ced80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009CF570 size 33
public ?d_009cf570@@YAXXZ
?d_009cf570@@YAXXZ PROC
    db 56h, 6Ah, 24h, 0E8h, 0C8h, 0EFh, 0E5h, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 0Ch, 50h, 8Dh
    db 4Eh, 10h, 51h, 0E8h, 38h, 0FEh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_009cf570@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D02C0 size 50
public ?d_009d02c0@@YAXXZ
?d_009d02c0@@YAXXZ PROC
    db 56h, 57h, 6Ah, 24h, 0E8h, 77h, 0E2h, 0E5h, 0FFh, 8Bh, 7Ch, 24h, 10h, 8Bh, 0F0h, 8Dh
    db 47h, 10h, 50h, 8Dh, 4Eh, 10h, 51h, 0E8h, 0E4h, 0F0h, 0FFh, 0FFh, 8Ah, 17h, 33h, 0C0h
    db 83h, 0C4h, 0Ch, 89h, 46h, 08h, 89h, 46h, 0Ch, 5Fh, 88h, 16h, 8Bh, 0C6h, 5Eh, 0C2h
    db 04h, 00h
?d_009d02c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D1A70 size 81
public ?d_009d1a70@@YAXXZ
?d_009d1a70@@YAXXZ PROC
    db 8Bh, 0D1h, 53h, 8Bh, 5Ah, 14h, 85h, 0DBh, 75h, 07h, 83h, 0C8h, 0FFh, 5Bh, 0C2h, 08h
    db 00h, 8Bh, 4Ah, 1Ch, 8Bh, 44h, 24h, 0Ch, 56h, 8Bh, 72h, 18h, 2Bh, 0CEh, 3Bh, 0C1h
    db 7Eh, 02h, 8Bh, 0C1h, 85h, 0C0h, 7Eh, 1Ch, 57h, 8Bh, 7Ch, 24h, 10h, 85h, 0FFh, 74h
    db 12h, 03h, 0F3h, 8Bh, 0C8h, 8Bh, 0D9h, 0C1h, 0E9h, 02h, 0F3h, 0A5h, 8Bh, 0CBh, 83h, 0E1h
    db 03h, 0F3h, 0A4h, 5Fh, 8Bh, 4Ah, 18h, 03h, 0C8h, 5Eh, 89h, 4Ah, 18h, 5Bh, 0C2h, 08h
    db 00h
?d_009d1a70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D1AD0 size 6
public ?d_009d1ad0@@YAXXZ
?d_009d1ad0@@YAXXZ PROC
    db 83h, 0C8h, 0FFh, 0C2h, 08h, 00h
?d_009d1ad0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D1AE0 size 70
public ?d_009d1ae0@@YAXXZ
?d_009d1ae0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 83h, 0E8h, 00h, 74h, 1Eh, 48h, 74h, 12h, 48h, 74h, 06h, 83h
    db 0C8h, 0FFh, 0C2h, 08h, 00h, 8Bh, 41h, 1Ch, 03h, 44h, 24h, 04h, 0EBh, 0Dh, 8Bh, 41h
    db 18h, 03h, 44h, 24h, 04h, 0EBh, 04h, 8Bh, 44h, 24h, 04h, 85h, 0C0h, 7Dh, 08h, 33h
    db 0C0h, 89h, 41h, 18h, 0C2h, 08h, 00h, 8Bh, 51h, 1Ch, 3Bh, 0C2h, 7Eh, 02h, 8Bh, 0C2h
    db 89h, 41h, 18h, 0C2h, 08h, 00h
?d_009d1ae0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D1B30 size 128
public ?d_009d1b30@@YAXXZ
?d_009d1b30@@YAXXZ PROC
    db 8Bh, 51h, 18h, 55h, 8Bh, 6Ch, 24h, 0Ch, 56h, 8Bh, 71h, 1Ch, 33h, 0C0h, 3Bh, 0D6h
    db 8Bh, 74h, 24h, 0Ch, 57h, 7Dh, 29h, 8Bh, 51h, 14h, 8Bh, 79h, 18h, 8Ah, 14h, 3Ah
    db 80h, 0FAh, 0Ah, 74h, 1Bh, 85h, 0F6h, 74h, 0Bh, 8Dh, 7Dh, 0FFh, 3Bh, 0C7h, 7Dh, 04h
    db 88h, 14h, 30h, 40h, 8Bh, 51h, 18h, 42h, 89h, 51h, 18h, 3Bh, 51h, 1Ch, 7Ch, 0D7h
    db 8Bh, 79h, 18h, 3Bh, 79h, 1Ch, 7Dh, 15h, 85h, 0F6h, 74h, 0Eh, 3Bh, 0C5h, 7Dh, 0Ah
    db 8Bh, 51h, 14h, 8Ah, 14h, 17h, 88h, 14h, 30h, 40h, 0FFh, 41h, 18h, 85h, 0F6h, 74h
    db 0Eh, 3Bh, 0C5h, 7Dh, 06h, 0C6h, 04h, 30h, 00h, 0EBh, 04h, 0C6h, 04h, 2Eh, 00h, 8Bh
    db 41h, 1Ch, 39h, 41h, 18h, 5Fh, 5Eh, 5Dh, 7Ch, 03h, 89h, 41h, 18h, 0C2h, 08h, 00h
?d_009d1b30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D1BF0 size 36
public ?d_009d1bf0@@YAXXZ
?d_009d1bf0@@YAXXZ PROC
    db 56h, 8Bh, 71h, 14h, 85h, 0F6h, 75h, 0Ch, 6Ah, 01h, 0E8h, 71h, 03h, 0EBh, 0FFh, 83h
    db 0C4h, 04h, 5Eh, 0C3h, 8Bh, 01h, 0C7h, 41h, 14h, 00h, 00h, 00h, 00h, 0FFh, 50h, 08h
    db 8Bh, 0C6h, 5Eh, 0C3h
?d_009d1bf0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2020 size 130
public ?d_009d2020@@YAXXZ
?d_009d2020@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 85h, 0FFh, 8Bh, 0F1h, 74h, 61h, 8Bh, 47h, 04h, 85h
    db 0C0h, 8Bh, 4Fh, 08h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h
    db 51h, 50h, 8Bh, 0CEh, 0E8h, 0B7h, 97h, 0FFh, 0FFh, 84h, 0C0h, 74h, 40h, 8Bh, 07h, 8Bh
    db 0CFh, 0FFh, 50h, 2Ch, 50h, 89h, 46h, 1Ch, 0E8h, 13h, 0FFh, 0EAh, 0FFh, 83h, 0C4h, 04h
    db 85h, 0C0h, 89h, 46h, 14h, 74h, 26h, 8Bh, 4Eh, 1Ch, 8Bh, 17h, 51h, 50h, 8Bh, 0CFh
    db 0FFh, 52h, 0Ch, 85h, 0C0h, 89h, 46h, 1Ch, 7Dh, 1Ah, 8Bh, 56h, 14h, 52h, 0E8h, 6Dh
    db 0FEh, 0EAh, 0FFh, 83h, 0C4h, 04h, 0C7h, 46h, 14h, 00h, 00h, 00h, 00h, 5Fh, 32h, 0C0h
    db 5Eh, 0C2h, 04h, 00h, 5Fh, 0C7h, 46h, 18h, 00h, 00h, 00h, 00h, 0B0h, 01h, 5Eh, 0C2h
    db 04h, 00h
?d_009d2020@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D20E0 size 5
public ?d_009d20e0@@YAXXZ
?d_009d20e0@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_009d20e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D20F0 size 5
public ?d_009d20f0@@YAXXZ
?d_009d20f0@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_009d20f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2100 size 5
public ?d_009d2100@@YAXXZ
?d_009d2100@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_009d2100@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2110 size 5
public ?d_009d2110@@YAXXZ
?d_009d2110@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_009d2110@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D21D0 size 5
public ?d_009d21d0@@YAXXZ
?d_009d21d0@@YAXXZ PROC
    db 0B0h, 01h, 0C2h, 04h, 00h
?d_009d21d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2260 size 70
public ?d_009d2260@@YAXXZ
?d_009d2260@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 83h, 0E8h, 00h, 74h, 1Eh, 48h, 74h, 12h, 48h, 74h, 06h, 83h
    db 0C8h, 0FFh, 0C2h, 08h, 00h, 8Bh, 41h, 1Ch, 03h, 44h, 24h, 04h, 0EBh, 0Dh, 8Bh, 41h
    db 28h, 03h, 44h, 24h, 04h, 0EBh, 04h, 8Bh, 44h, 24h, 04h, 85h, 0C0h, 7Dh, 08h, 33h
    db 0C0h, 89h, 41h, 28h, 0C2h, 08h, 00h, 8Bh, 51h, 1Ch, 3Bh, 0C2h, 7Eh, 02h, 8Bh, 0C2h
    db 89h, 41h, 28h, 0C2h, 08h, 00h
?d_009d2260@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2480 size 183
public ?d_009d2480@@YAXXZ
?d_009d2480@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 50h, 57h, 8Bh, 0F1h, 0E8h, 6Dh
    db 93h, 0FFh, 0FFh, 84h, 0C0h, 0Fh, 84h, 8Eh, 00h, 00h, 00h, 8Bh, 46h, 08h, 33h, 0C9h
    db 0A8h, 08h, 74h, 05h, 0B9h, 00h, 01h, 00h, 00h, 0A8h, 10h, 74h, 06h, 81h, 0C9h, 00h
    db 02h, 00h, 00h, 0A8h, 04h, 74h, 03h, 83h, 0C9h, 08h, 0A8h, 20h, 74h, 06h, 81h, 0C9h
    db 00h, 40h, 00h, 00h, 0A8h, 40h, 74h, 06h, 81h, 0C9h, 00h, 80h, 00h, 00h, 8Bh, 0D0h
    db 83h, 0E2h, 03h, 80h, 0FAh, 03h, 75h, 05h, 83h, 0C9h, 02h, 0EBh, 0Ah, 0A8h, 02h, 74h
    db 06h, 81h, 0C9h, 01h, 01h, 00h, 00h, 68h, 80h, 01h, 00h, 00h, 51h, 57h, 0FFh, 15h
    db 1Ch, 93h, 35h, 01h, 83h, 0C4h, 0Ch, 83h, 0F8h, 0FFh, 89h, 46h, 14h, 74h, 23h, 8Bh
    db 0Dh, 64h, 0D0h, 34h, 01h, 8Ah, 46h, 08h, 41h, 0A8h, 04h, 89h, 0Dh, 64h, 0D0h, 34h
    db 01h, 74h, 1Dh, 8Bh, 06h, 6Ah, 02h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 50h, 14h, 85h, 0C0h
    db 7Dh, 0Eh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 08h, 5Fh, 32h, 0C0h, 5Eh, 0C2h, 08h, 00h
    db 5Fh, 0B0h, 01h, 5Eh, 0C2h, 08h, 00h
?d_009d2480@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2550 size 72
public ?d_009d2550@@YAXXZ
?d_009d2550@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 08h, 0B8h, 0FFh, 0FFh, 0FFh, 0FFh, 0C2h, 08h, 00h, 8Bh
    db 44h, 24h, 04h, 85h, 0C0h, 75h, 1Bh, 8Bh, 41h, 14h, 56h, 8Bh, 74h, 24h, 0Ch, 6Ah
    db 01h, 56h, 50h, 0FFh, 15h, 00h, 93h, 35h, 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h
    db 08h, 00h, 8Bh, 54h, 24h, 08h, 52h, 50h, 8Bh, 41h, 14h, 50h, 0FFh, 15h, 20h, 93h
    db 35h, 01h, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_009d2550@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D25A0 size 43
public ?d_009d25a0@@YAXXZ
?d_009d25a0@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 74h, 1Eh, 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 16h, 8Bh
    db 54h, 24h, 08h, 52h, 50h, 8Bh, 41h, 14h, 50h, 0FFh, 15h, 6Ch, 93h, 35h, 01h, 83h
    db 0C4h, 0Ch, 0C2h, 08h, 00h, 83h, 0C8h, 0FFh, 0C2h, 08h, 00h
?d_009d25a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D25D0 size 59
public ?d_009d25d0@@YAXXZ
?d_009d25d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 83h, 0E8h, 00h, 74h, 1Ah, 48h, 74h, 10h, 48h, 74h, 06h, 83h
    db 0C8h, 0FFh, 0C2h, 08h, 00h, 0B8h, 02h, 00h, 00h, 00h, 0EBh, 09h, 0B8h, 01h, 00h, 00h
    db 00h, 0EBh, 02h, 33h, 0C0h, 8Bh, 49h, 14h, 50h, 8Bh, 44h, 24h, 08h, 50h, 51h, 0FFh
    db 15h, 00h, 93h, 35h, 01h, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_009d25d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2610 size 124
public ?d_009d2610@@YAXXZ
?d_009d2610@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 2Dh, 20h, 93h, 35h, 01h, 56h, 57h, 8Bh, 0D9h, 0C6h, 44h, 24h
    db 13h, 00h, 33h, 0FFh, 8Bh, 74h, 24h, 18h, 85h, 0F6h, 74h, 20h, 8Bh, 44h, 24h, 1Ch
    db 48h, 3Bh, 0F8h, 7Dh, 17h, 8Bh, 4Bh, 14h, 03h, 0F7h, 6Ah, 01h, 56h, 51h, 0FFh, 0D5h
    db 8Ah, 16h, 8Bh, 74h, 24h, 24h, 88h, 54h, 24h, 1Fh, 0EBh, 0Dh, 8Bh, 4Bh, 14h, 6Ah
    db 01h, 8Dh, 44h, 24h, 17h, 50h, 51h, 0FFh, 0D5h, 83h, 0C4h, 0Ch, 47h, 85h, 0C0h, 74h
    db 07h, 80h, 7Ch, 24h, 13h, 0Ah, 75h, 0BCh, 85h, 0F6h, 74h, 18h, 8Bh, 44h, 24h, 1Ch
    db 3Bh, 0F8h, 7Dh, 0Ch, 0C6h, 04h, 37h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 08h, 00h
    db 0C6h, 04h, 06h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 08h, 00h
?d_009d2610@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2CB0 size 78
public ?d_009d2cb0@@YAXXZ
?d_009d2cb0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 75h, 0Ah, 8Bh, 35h, 78h, 0D4h, 34h, 01h, 85h
    db 0F6h, 74h, 39h, 8Bh, 44h, 24h, 0Ch, 50h, 0E8h, 13h, 16h, 0E8h, 0FFh, 8Bh, 56h, 2Ch
    db 8Bh, 0C8h, 2Bh, 0CAh, 0B8h, 0D3h, 4Dh, 62h, 10h, 0F7h, 0E9h, 0C1h, 0FAh, 06h, 8Bh, 0CAh
    db 0C1h, 0E9h, 1Fh, 03h, 0CAh, 8Bh, 15h, 0D0h, 90h, 2Dh, 01h, 51h, 52h, 68h, 0ACh, 3Dh
    db 14h, 01h, 56h, 0FFh, 15h, 04h, 91h, 2Dh, 01h, 83h, 0C4h, 14h, 5Eh, 0C3h
?d_009d2cb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D2DD0 size 78
public ?d_009d2dd0@@YAXXZ
?d_009d2dd0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 75h, 0Ah, 8Bh, 35h, 78h, 0D4h, 34h, 01h, 85h
    db 0F6h, 74h, 39h, 8Bh, 44h, 24h, 0Ch, 50h, 0E8h, 0F3h, 14h, 0E8h, 0FFh, 8Bh, 56h, 2Ch
    db 8Bh, 0C8h, 2Bh, 0CAh, 0B8h, 0D3h, 4Dh, 62h, 10h, 0F7h, 0E9h, 0C1h, 0FAh, 06h, 8Bh, 0CAh
    db 0C1h, 0E9h, 1Fh, 03h, 0CAh, 8Bh, 15h, 0D0h, 90h, 2Dh, 01h, 51h, 52h, 68h, 0ACh, 3Dh
    db 14h, 01h, 56h, 0FFh, 15h, 0F8h, 90h, 2Dh, 01h, 83h, 0C4h, 14h, 5Eh, 0C3h
?d_009d2dd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D6290 size 106
public ?d_009d6290@@YAXXZ
?d_009d6290@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0F1h, 3Bh, 0F7h, 74h, 57h, 8Bh, 06h, 50h, 0E8h
    db 4Ch, 0BCh, 0EAh, 0FFh, 8Bh, 07h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 3Ah, 8Dh, 50h, 01h
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 40h, 50h, 0E8h, 0B0h, 0BCh, 0EAh, 0FFh
    db 89h, 06h, 8Bh, 0Fh, 83h, 0C4h, 04h, 8Bh, 0D0h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Ah, 01h, 41h, 88h, 02h, 42h, 84h, 0C0h, 75h, 0F6h, 8Bh, 4Fh, 04h, 5Fh, 89h, 4Eh
    db 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 4Fh, 04h
    db 89h, 4Eh, 04h, 5Fh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_009d6290@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D7600 size 39
public ?d_009d7600@@YAXXZ
?d_009d7600@@YAXXZ PROC
    db 56h, 6Ah, 0Ch, 0E8h, 38h, 6Fh, 0E5h, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 0Ch, 50h, 8Dh
    db 4Eh, 04h, 51h, 0C7h, 06h, 00h, 00h, 00h, 00h, 0E8h, 0B2h, 0FDh, 0FFh, 0FFh, 83h, 0C4h
    db 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_009d7600@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D8090 size 27
public ?d_009d8090@@YAXXZ
?d_009d8090@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 57h, 8Bh, 0F1h, 0E8h, 73h, 4Ah, 64h, 0FFh, 8Bh, 47h
    db 0Ch, 89h, 46h, 0Ch, 5Fh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_009d8090@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D8CF0 size 5
public ?d_009d8cf0@@YAXXZ
?d_009d8cf0@@YAXXZ PROC
    db 8Bh, 0C1h, 0C2h, 04h, 00h
?d_009d8cf0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009D9AD0 size 244
public ?d_009d9ad0@@YAXXZ
?d_009d9ad0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0F8h, 10h, 06h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 8Bh, 46h, 0Ch, 8Bh, 4Eh
    db 10h, 3Bh, 0C1h, 0Fh, 84h, 0BBh, 00h, 00h, 00h, 8Bh, 0C1h, 83h, 0C0h, 0F4h, 50h, 8Dh
    db 4Ch, 24h, 08h, 0E8h, 09h, 30h, 64h, 0FFh, 8Bh, 46h, 10h, 83h, 0C0h, 0F4h, 89h, 46h
    db 10h, 8Bh, 08h, 8Bh, 40h, 08h, 2Bh, 0C1h, 85h, 0C9h, 0C7h, 44h, 24h, 18h, 00h, 00h
    db 00h, 00h, 74h, 1Ch, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 7Fh, 83h, 0EAh
    db 0FFh, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 0B3h, 4Ah, 0E5h, 0FFh, 83h, 0C4h, 08h
    db 8Ah, 46h, 04h, 84h, 0C0h, 74h, 12h, 68h, 94h, 02h, 08h, 01h, 56h, 0E8h, 2Eh, 0F6h
    db 0FFh, 0FFh, 83h, 0C4h, 08h, 0C6h, 46h, 04h, 00h, 6Ah, 00h, 56h, 0E8h, 1Fh, 0F6h, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 0Ch, 51h, 68h, 30h, 45h, 14h, 01h, 56h, 0E8h, 0Fh, 0F6h, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 18h, 8Bh, 44h, 24h, 20h, 83h, 0C4h, 14h, 2Bh, 0C1h, 85h, 0C9h
    db 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 2Ah, 3Dh, 80h, 00h, 00h, 00h, 76h
    db 19h, 51h, 0E8h, 19h, 83h, 0EAh, 0FFh, 83h, 0C4h, 04h, 5Eh, 8Bh, 4Ch, 24h, 0Ch, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C3h, 50h, 51h, 0E8h, 3Fh, 4Ah, 0E5h
    db 0FFh, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 10h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 18h, 0C3h
?d_009d9ad0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009DB610 size 31
public ?d_009db610@@YAXXZ
?d_009db610@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 44h, 48h, 14h, 01h, 74h, 09h
    db 56h, 0E8h, 8Ah, 68h, 0EAh, 0FFh, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_009db610@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009EB8D0 size 36
public ?d_009eb8d0@@YAXXZ
?d_009eb8d0@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 48h, 04h, 81h, 0E1h, 00h, 00h, 0FFh, 00h, 81h, 0F9h, 00h, 00h, 07h
    db 00h, 74h, 10h, 8Bh, 0Dh, 0ACh, 0FAh, 34h, 01h, 85h, 0C9h, 74h, 06h, 50h, 0E8h, 8Dh
    db 39h, 00h, 00h, 0C3h
?d_009eb8d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009EBA30 size 8
public ?d_009eba30@@YAXXZ
?d_009eba30@@YAXXZ PROC
    db 8Bh, 49h, 08h, 0E9h, 0D8h, 5Ah, 00h, 00h
?d_009eba30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009ED110 size 43
public ?d_009ed110@@YAXXZ
?d_009ed110@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 3Bh, 0F7h, 73h, 18h, 8Bh, 0FFh
    db 68h, 80h, 00h, 00h, 00h, 0E8h, 16h, 14h, 0E4h, 0FFh, 89h, 06h, 83h, 0C6h, 04h, 83h
    db 0C4h, 04h, 3Bh, 0F7h, 72h, 0EAh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_009ed110@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009ED490 size 11
public ?d_009ed490@@YAXXZ
?d_009ed490@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_009ed490@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009ED7B0 size 33
public ?d_009ed7b0@@YAXXZ
?d_009ed7b0@@YAXXZ PROC
    db 56h, 6Ah, 18h, 0E8h, 88h, 0Dh, 0E4h, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 0Ch, 50h, 8Dh
    db 4Eh, 10h, 51h, 0E8h, 0C8h, 0FFh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_009ed7b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009EDBB0 size 39
public ?d_009edbb0@@YAXXZ
?d_009edbb0@@YAXXZ PROC
    db 56h, 6Ah, 0Ch, 0E8h, 88h, 09h, 0E4h, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 0Ch, 50h, 8Dh
    db 4Eh, 04h, 51h, 0C7h, 06h, 00h, 00h, 00h, 00h, 0E8h, 0C2h, 0FBh, 0FFh, 0FFh, 83h, 0C4h
    db 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_009edbb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F2630 size 8
public ?d_009f2630@@YAXXZ
?d_009f2630@@YAXXZ PROC
    db 8Bh, 49h, 0Ch, 0E9h, 08h, 2Ah, 00h, 00h
?d_009f2630@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F27D0 size 8
public ?d_009f27d0@@YAXXZ
?d_009f27d0@@YAXXZ PROC
    db 83h, 0E9h, 08h, 0E9h, 28h, 01h, 00h, 00h
?d_009f27d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F27F0 size 6
public ?d_009f27f0@@YAXXZ
?d_009f27f0@@YAXXZ PROC
    db 0B8h, 1Ch, 58h, 14h, 01h, 0C3h
?d_009f27f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F2880 size 46
public ?d_009f2880@@YAXXZ
?d_009f2880@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 0B0h, 01h, 8Dh, 4Ch, 24h, 08h, 88h
    db 44h, 24h, 08h, 88h, 44h, 24h, 09h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 28h, 8Bh
    db 4Fh, 04h, 56h, 0E8h, 48h, 21h, 00h, 00h, 5Fh, 5Eh, 59h, 0C2h, 04h, 00h
?d_009f2880@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F3010 size 11
public ?d_009f3010@@YAXXZ
?d_009f3010@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_009f3010@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F4B30 size 11
public ?d_009f4b30@@YAXXZ
?d_009f4b30@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_009f4b30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F52E0 size 65
public ?d_009f52e0@@YAXXZ
?d_009f52e0@@YAXXZ PROC
    db 56h, 8Bh, 31h, 85h, 0F6h, 74h, 38h, 8Bh, 49h, 08h, 2Bh, 0CEh, 0B8h, 0ABh, 0AAh, 0AAh
    db 2Ah, 0F7h, 0E9h, 0C1h, 0FAh, 02h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 40h
    db 0C1h, 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 56h, 0E8h, 0A0h, 0CBh, 0E8h, 0FFh
    db 83h, 0C4h, 04h, 5Eh, 0C3h, 50h, 56h, 0E8h, 0D4h, 92h, 0E3h, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 0C3h
?d_009f52e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F53D0 size 93
public ?d_009f53d0@@YAXXZ
?d_009f53d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 56h, 50h, 8Bh, 44h, 24h, 10h, 8Dh, 48h, 0E8h, 8Bh, 31h, 83h
    db 0ECh, 18h, 8Bh, 0D4h, 89h, 32h, 8Bh, 71h, 04h, 89h, 72h, 04h, 8Bh, 71h, 08h, 89h
    db 72h, 08h, 8Bh, 71h, 0Ch, 89h, 72h, 0Ch, 8Bh, 71h, 10h, 8Bh, 49h, 14h, 89h, 72h
    db 10h, 89h, 4Ah, 14h, 8Bh, 4Ch, 24h, 24h, 2Bh, 0C1h, 8Bh, 0D0h, 0B8h, 0ABh, 0AAh, 0AAh
    db 2Ah, 0F7h, 0EAh, 0C1h, 0FAh, 02h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 6Ah, 00h, 8Dh, 54h, 02h
    db 0FFh, 52h, 51h, 0E8h, 0C8h, 0F7h, 0FFh, 0FFh, 83h, 0C4h, 28h, 5Eh, 0C3h
?d_009f53d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F5580 size 65
public ?d_009f5580@@YAXXZ
?d_009f5580@@YAXXZ PROC
    db 56h, 8Bh, 31h, 85h, 0F6h, 74h, 38h, 8Bh, 49h, 08h, 2Bh, 0CEh, 0B8h, 0ABh, 0AAh, 0AAh
    db 2Ah, 0F7h, 0E9h, 0C1h, 0FAh, 02h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 40h
    db 0C1h, 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 56h, 0E8h, 00h, 0C9h, 0E8h, 0FFh
    db 83h, 0C4h, 04h, 5Eh, 0C3h, 50h, 56h, 0E8h, 34h, 90h, 0E3h, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 0C3h
?d_009f5580@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F6C28 size 6
public ?d_009f6c28@@YAXXZ
?d_009f6c28@@YAXXZ PROC
    db 0FFh, 25h, 0C0h, 91h, 35h, 01h
?d_009f6c28@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F6C2E size 6
public ?d_009f6c2e@@YAXXZ
?d_009f6c2e@@YAXXZ PROC
    db 0FFh, 25h, 0CCh, 91h, 35h, 01h
?d_009f6c2e@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009F7EEC size 6
public ?d_009f7eec@@YAXXZ
?d_009f7eec@@YAXXZ PROC
    db 0FFh, 25h, 58h, 92h, 35h, 01h
?d_009f7eec@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00AFD4FE size 6
public ?d_00afd4fe@@YAXXZ
?d_00afd4fe@@YAXXZ PROC
    db 0FFh, 25h, 5Ch, 97h, 35h, 01h
?d_00afd4fe@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00AFD50A size 6
public ?d_00afd50a@@YAXXZ
?d_00afd50a@@YAXXZ PROC
    db 0FFh, 25h, 64h, 97h, 35h, 01h
?d_00afd50a@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00AFD516 size 6
public ?d_00afd516@@YAXXZ
?d_00afd516@@YAXXZ PROC
    db 0FFh, 25h, 50h, 97h, 35h, 01h
?d_00afd516@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00AFD51C size 6
public ?d_00afd51c@@YAXXZ
?d_00afd51c@@YAXXZ PROC
    db 0FFh, 25h, 58h, 97h, 35h, 01h
?d_00afd51c@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00AFD522 size 6
public ?d_00afd522@@YAXXZ
?d_00afd522@@YAXXZ PROC
    db 0FFh, 25h, 54h, 97h, 35h, 01h
?d_00afd522@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00B00260 size 121
public ?d_00b00260@@YAXXZ
?d_00b00260@@YAXXZ PROC
    db 57h, 8Bh, 7Ch, 24h, 14h, 85h, 0FFh, 7Eh, 6Eh, 8Bh, 54h, 24h, 08h, 8Bh, 4Ch, 24h
    db 10h, 53h, 8Bh, 5Ch, 24h, 10h, 56h, 8Bh, 0F2h, 8Dh, 43h, 08h, 2Bh, 0D3h, 8Bh, 0FFh
    db 0D9h, 41h, 08h, 83h, 0C0h, 0Ch, 0D8h, 48h, 0F4h, 83h, 0C6h, 0Ch, 4Fh, 0D9h, 41h, 04h
    db 0D8h, 48h, 0F0h, 0DEh, 0C1h, 0D9h, 01h, 0D8h, 48h, 0ECh, 0DEh, 0C1h, 0D9h, 5Eh, 0F4h, 0D9h
    db 41h, 10h, 0D8h, 48h, 0ECh, 0D9h, 41h, 18h, 0D8h, 48h, 0F4h, 0DEh, 0C1h, 0D9h, 41h, 14h
    db 0D8h, 48h, 0F0h, 0DEh, 0C1h, 0D9h, 5Ch, 10h, 0F0h, 0D9h, 41h, 28h, 0D8h, 48h, 0F4h, 0D9h
    db 41h, 24h, 0D8h, 48h, 0F0h, 0DEh, 0C1h, 0D9h, 41h, 20h, 0D8h, 48h, 0ECh, 0DEh, 0C1h, 0D9h
    db 5Ch, 10h, 0F4h, 75h, 0ABh, 5Eh, 5Bh, 5Fh, 0C3h
?d_00b00260@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C6FC90 size 10
public ?d_00c6fc90@@YAXXZ
?d_00c6fc90@@YAXXZ PROC
    db 0B9h, 5Ch, 0D5h, 2Eh, 01h, 0E9h, 0D0h, 0FAh, 3Ch, 0FFh
?d_00c6fc90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C6FCA0 size 10
public ?d_00c6fca0@@YAXXZ
?d_00c6fca0@@YAXXZ PROC
    db 0B9h, 48h, 0D5h, 2Eh, 01h, 0E9h, 0C0h, 0FAh, 3Ch, 0FFh
?d_00c6fca0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C6FF70 size 39
public ?d_00c6ff70@@YAXXZ
?d_00c6ff70@@YAXXZ PROC
    db 56h, 8Bh, 35h, 0DCh, 13h, 2Fh, 01h, 85h, 0F6h, 74h, 1Ah, 8Dh, 46h, 04h, 50h, 0FFh
    db 15h, 54h, 8Eh, 35h, 01h, 85h, 0C0h, 7Fh, 0Ch, 85h, 0F6h, 74h, 08h, 8Bh, 16h, 6Ah
    db 01h, 8Bh, 0CEh, 0FFh, 12h, 5Eh, 0C3h
?d_00c6ff70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C70510 size 10
public ?d_00c70510@@YAXXZ
?d_00c70510@@YAXXZ PROC
    db 0B9h, 60h, 69h, 2Fh, 01h, 0E9h, 0Eh, 0D3h, 39h, 0FFh
?d_00c70510@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C70620 size 10
public ?d_00c70620@@YAXXZ
?d_00c70620@@YAXXZ PROC
    db 0B9h, 0C8h, 6Ah, 2Fh, 01h, 0E9h, 0FEh, 0D1h, 39h, 0FFh
?d_00c70620@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C70640 size 10
public ?d_00c70640@@YAXXZ
?d_00c70640@@YAXXZ PROC
    db 0B9h, 0A4h, 6Ah, 2Fh, 01h, 0E9h, 0DEh, 0D1h, 39h, 0FFh
?d_00c70640@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C706A0 size 10
public ?d_00c706a0@@YAXXZ
?d_00c706a0@@YAXXZ PROC
    db 0B9h, 44h, 6Ah, 2Fh, 01h, 0E9h, 7Eh, 0D1h, 39h, 0FFh
?d_00c706a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C706B0 size 10
public ?d_00c706b0@@YAXXZ
?d_00c706b0@@YAXXZ PROC
    db 0B9h, 38h, 6Ah, 2Fh, 01h, 0E9h, 6Eh, 0D1h, 39h, 0FFh
?d_00c706b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00C706E0 size 10
public ?d_00c706e0@@YAXXZ
?d_00c706e0@@YAXXZ PROC
    db 0B9h, 08h, 6Ah, 2Fh, 01h, 0E9h, 3Eh, 0D1h, 39h, 0FFh
?d_00c706e0@@YAXXZ ENDP
_TEXT ENDS
END
