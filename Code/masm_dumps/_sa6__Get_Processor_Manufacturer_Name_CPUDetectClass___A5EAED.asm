.386
.model flat
; ?Get_Processor_Manufacturer_Name@CPUDetectClass@@
; Exact 228B @ 0x00A5EAED; Open-BFME4
_TEXT SEGMENT
public ?Get_Processor_Manufacturer_Name@CPUDetectClass@@
?Get_Processor_Manufacturer_Name@CPUDetectClass@@ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 28h, 53h, 56h, 57h, 0BEh, 80h, 0F4h, 14h, 01h, 8Dh, 7Dh
    db 0E8h, 0A5h, 0A5h, 0A5h, 0A4h, 0BEh, 0B8h, 38h, 14h, 01h, 8Dh, 7Dh, 0D8h, 0A5h, 0A5h, 0A5h
    db 0A4h, 33h, 0C0h, 33h, 0DBh, 33h, 0C9h, 33h, 0D2h, 0Fh, 0A2h, 0C7h, 45h, 0FCh, 01h, 00h
    db 00h, 00h, 33h, 0C0h, 0Fh, 0A2h, 89h, 5Dh, 0E8h, 89h, 55h, 0ECh, 89h, 4Dh, 0F0h, 85h
    db 0C0h, 0Fh, 84h, 95h, 00h, 00h, 00h, 83h, 4Dh, 0FCh, 02h, 0B8h, 01h, 00h, 00h, 00h
    db 0Fh, 0A2h, 89h, 45h, 0F8h, 0B9h, 00h, 00h, 80h, 00h, 23h, 0CAh, 0F7h, 0D9h, 1Bh, 0C9h
    db 83h, 0E1h, 20h, 09h, 4Dh, 0FCh, 0B9h, 00h, 00h, 00h, 02h, 23h, 0CAh, 0F7h, 0D9h, 1Bh
    db 0C9h, 83h, 0E1h, 40h, 09h, 4Dh, 0FCh, 0B8h, 00h, 00h, 00h, 80h, 0Fh, 0A2h, 3Dh, 00h
    db 00h, 00h, 80h, 76h, 57h, 83h, 4Dh, 0FCh, 04h, 0B8h, 01h, 00h, 00h, 80h, 0Fh, 0A2h
    db 0B9h, 00h, 00h, 00h, 80h, 23h, 0CAh, 0F7h, 0D9h, 1Bh, 0C9h, 81h, 0E1h, 80h, 00h, 00h
    db 00h, 09h, 4Dh, 0FCh, 8Dh, 75h, 0D8h, 8Dh, 7Dh, 0E8h, 0B9h, 0Ch, 00h, 00h, 00h, 0FCh
    db 0F3h, 0A6h, 0B9h, 00h, 00h, 00h, 40h, 23h, 0CAh, 0F7h, 0D9h, 1Bh, 0C9h, 81h, 0E1h, 00h
    db 01h, 00h, 00h, 09h, 4Dh, 0FCh, 0B9h, 00h, 00h, 40h, 00h, 23h, 0CAh, 0F7h, 0D9h, 1Bh
    db 0C9h, 81h, 0E1h, 00h, 02h, 00h, 00h, 09h, 4Dh, 0FCh, 0EBh, 00h, 8Bh, 45h, 0FCh, 5Fh
    db 5Eh, 5Bh, 0C9h, 0C3h
?Get_Processor_Manufacturer_Name@CPUDetectClass@@ ENDP
_TEXT ENDS
END
