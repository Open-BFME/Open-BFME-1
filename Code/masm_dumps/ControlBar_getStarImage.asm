.386
.model flat

; ?getStarImage@ControlBar@@QAEPBVImage@@XZ
; Exact 208 retail bytes @ RVA 0x0049CC00
; Queue RVA 0x0049CBFF was leading int3 pad; true body at 0x49CC00.
; Shape matches ZH ControlBar::getStarImage; C++ blocked by ControlBar member
; offsets (retail 0x2c0..0x2cc vs ours 0x300..0x30c), Player getSciencePurchasePoints
; (retail +0x264 vs ours +0x190), and LOGICFRAMES_PER_SECOND (retail 5 vs ours 30).
_TEXT SEGMENT
public ?getStarImage@ControlBar@@QAEPBVImage@@XZ
?getStarImage@ControlBar@@QAEPBVImage@@XZ PROC
    db 0A1h,48h,0D7h,2Eh,01h,56h,8Bh,0F1h,8Bh,48h,0Ch,8Bh,81h,64h,02h,00h
    db 00h,39h,86h,0CCh,02h,00h,00h,57h,7Fh,0Ch,85h,0C0h,7Eh,08h,89h,86h
    db 0CCh,02h,00h,00h,0EBh,07h,0C6h,86h,0C8h,02h,00h,00h,00h,8Bh,15h,40h
    db 1Bh,2Fh,01h,8Bh,0Dh,00h,0D6h,2Eh,01h,8Bh,3Ah,68h,44h,0B8h,0Fh,01h
    db 0E8h,92h,0E1h,0B9h,0FFh,8Bh,0Dh,40h,1Bh,2Fh,01h,50h,6Ah,00h,0FFh,97h
    db 0DCh,00h,00h,00h,8Bh,0F8h,85h,0FFh,74h,71h,8Ah,86h,0C8h,02h,00h,00h
    db 84h,0C0h,75h,2Bh,8Bh,86h,0C0h,02h,00h,00h,50h,6Ah,00h,8Bh,0CFh,0E8h
    db 95h,91h,0B9h,0FFh,6Ah,00h,6Ah,05h,8Bh,0CFh,0E8h,8Ah,91h,0B9h,0FFh,6Ah
    db 00h,6Ah,06h,8Bh,0CFh,0E8h,7Fh,91h,0B9h,0FFh,5Fh,33h,0C0h,5Eh,0C3h,8Bh
    db 0Dh,98h,08h,2Fh,01h,8Bh,41h,3Ch,33h,0D2h,0B9h,05h,00h,00h,00h,0F7h
    db 0F1h,83h,0FAh,02h,76h,15h,8Bh,96h,0C4h,02h,00h,00h,52h,57h,0E8h,70h
    db 0BDh,0B9h,0FFh,83h,0C4h,08h,5Fh,33h,0C0h,5Eh,0C3h,8Bh,86h,0C0h,02h,00h
    db 00h,50h,57h,0E8h,5Bh,0BDh,0B9h,0FFh,83h,0C4h,08h,5Fh,33h,0C0h,5Eh,0C3h
?getStarImage@ControlBar@@QAEPBVImage@@XZ ENDP
_TEXT ENDS
END
