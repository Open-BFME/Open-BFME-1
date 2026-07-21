.386
.model flat

; ?allocateCellInfos@PathfindCellInfo@@SAXXZ
; Exact 123 retail bytes @ 0x003F6AD0
; BFME rewrote ZH's one-shot 30000-cell pool: grow free list by 256 entries
; of sizeof 0x34, head at 0x12F1094. Lazy-init when free list empty.
_TEXT SEGMENT
public ?allocateCellInfos@PathfindCellInfo@@SAXXZ
?allocateCellInfos@PathfindCellInfo@@SAXXZ PROC
    db 53h,56h,68h,00h,34h,00h,00h,0E8h,94h,0B4h,48h,00h,33h,0F6h,83h,0C4h
    db 04h,3Bh,0C6h,74h,18h,8Dh,48h,30h,0BAh,00h,01h,00h,00h,8Dh,49h,00h
    db 89h,71h,0FCh,89h,31h,83h,0C1h,34h,4Ah,75h,0F5h,0EBh,02h,33h,0C0h,83h
    db 0C0h,2Ch,0BAh,00h,01h,00h,00h,8Bh,48h,04h,3Bh,0CEh,74h,15h,8Bh,18h
    db 89h,19h,8Bh,08h,3Bh,0CEh,74h,06h,8Bh,58h,04h,89h,59h,30h,89h,70h
    db 04h,89h,30h,0C7h,40h,04h,94h,10h,2Fh,01h,8Bh,0Dh,94h,10h,2Fh,01h
    db 3Bh,0CEh,89h,08h,74h,03h,89h,41h,30h,8Dh,48h,0D4h,83h,0C0h,34h,4Ah
    db 89h,0Dh,94h,10h,2Fh,01h,75h,0BFh,5Eh,5Bh,0C3h
?allocateCellInfos@PathfindCellInfo@@SAXXZ ENDP
_TEXT ENDS
END
