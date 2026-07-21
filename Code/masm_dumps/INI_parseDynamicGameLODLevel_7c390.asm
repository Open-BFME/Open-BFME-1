.386
.model flat

; ?parseDynamicGameLODLevel@INI@@SAXPAV1@PAX1PBX@Z
; Retail @ 0x0007C390 size 105
; Identity: invalid-GameLODLevel crash string site; DynamicGameLODNames
; table (VeryLow..VeryHigh count=5) @ 0x012A73FC; neighbors
; getStaticGameLODLevelName@0x7C370 getDynamicGameLODLevelName@0x7C420
; Queue RVA 0x9A15D7 was INSIDE unrelated SEH fn (sub esp,0x38 mid-byte).
_TEXT SEGMENT
public ?parseDynamicGameLODLevel@INI@@SAXPAV1@PAX1PBX@Z
?parseDynamicGameLODLevel@INI@@SAXPAV1@PAX1PBX@Z PROC
    db 08Bh,04Ch,024h,004h,083h,0ECh,008h,053h,056h,057h,06Ah,000h,0E8h,0CFh,045h,07Dh
    db 000h,08Bh,01Dh,03Ch,093h,035h,001h,08Bh,0F8h,033h,0F6h,0EBh,003h,08Dh,049h,000h
    db 08Bh,004h,0B5h,0FCh,073h,02Ah,001h,050h,057h,0FFh,0D3h,083h,0C4h,008h,085h,0C0h
    db 074h,02Ah,046h,083h,0FEh,005h,07Ch,0E8h,057h,068h,0CCh,06Bh,007h,001h,08Dh,054h
    db 024h,014h,06Ah,003h,052h,0E8h,026h,042h,07Dh,000h,083h,0C4h,010h,068h,030h,0FCh
    db 01Dh,001h,08Dh,044h,024h,010h,050h,0E8h,014h,0A9h,097h,000h,08Bh,04Ch,024h,020h
    db 05Fh,089h,031h,05Eh,05Bh,083h,0C4h,008h,0C3h
?parseDynamicGameLODLevel@INI@@SAXPAV1@PAX1PBX@Z ENDP
_TEXT ENDS
END
