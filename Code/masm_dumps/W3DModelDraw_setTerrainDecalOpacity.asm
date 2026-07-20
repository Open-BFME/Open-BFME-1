.386
.model flat

; ?setTerrainDecalOpacity@W3DModelDraw@@UAEXM@Z
; Exact 35 retail bytes @ 0x00B5BDD0; applies the BFME W3DModelDraw terrain-decal layout.
_TEXT SEGMENT
public ?setTerrainDecalOpacity@W3DModelDraw@@UAEXM@Z
?setTerrainDecalOpacity@W3DModelDraw@@UAEXM@Z PROC
    db 056h,08Bh,071h,040h,085h,0F6h,074h,017h,0D9h,044h,024h,008h,0D8h,00Dh,068h,040h
    db 008h,001h,0E8h,051h,0B0h,029h,000h,050h,08Bh,0CEh,0E8h,08Fh,01Eh,08Bh,0FFh,05Eh
    db 0C2h,004h,000h
?setTerrainDecalOpacity@W3DModelDraw@@UAEXM@Z ENDP
_TEXT ENDS
END
