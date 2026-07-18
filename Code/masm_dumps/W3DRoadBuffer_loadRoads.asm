.386
.model flat

; ?loadRoads@W3DRoadBuffer@@QAEXXZ
; Exact 61 retail bytes @ RVA 0x007105D0; road-buffer load sequence
_TEXT SEGMENT
public ?loadRoads@W3DRoadBuffer@@QAEXXZ
?loadRoads@W3DRoadBuffer@@QAEXXZ PROC
    db 056h,08Bh,0F1h,08Ah,046h,00Ch,084h,0C0h,074h,031h,0E8h,01Ah,031h,092h,0FFh,08Bh
    db 0CEh,0E8h,037h,0FAh,090h,0FFh,08Bh,0CEh,0E8h,071h,005h,090h,0FFh,0E8h,0DEh,037h
    db 091h,0FFh,08Bh,0CEh,0E8h,0E3h,00Bh,093h,0FFh,08Bh,0CEh,0E8h,09Ah,0B4h,090h,0FFh
    db 08Bh,0CEh,0E8h,04Bh,02Fh,090h,0FFh,0C6h,046h,050h,001h,05Eh,0C3h
?loadRoads@W3DRoadBuffer@@QAEXXZ ENDP
_TEXT ENDS
END
