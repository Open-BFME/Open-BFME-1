.386
.model flat

; ??1Anim2D@@MAE@XZ
; Exact 61 retail bytes @ 0x005BA670. Queue RVA 0x009F27FD was int3 pad before
; an unrelated dual-vtable SEH dtor. True body sits between Anim2D ctor and
; tryNextFrame; unlinks m_collectionSystem list (+0x20/+0x24/+0x28) then stores
; Snapshot vtable 0x01073744 (inline of ??1Snapshot@@UAE@XZ @ 0x5C520). C++
; emits a tail-jmp to the wrong ICF-folded Snapshot QAE alias instead.
_TEXT SEGMENT
public ??1Anim2D@@MAE@XZ
??1Anim2D@@MAE@XZ PROC
    db 08Bh,051h,020h,085h,0D2h,0C7h,001h,09Ch
    db 0F2h,010h,001h,074h,029h,08Bh,041h,024h
    db 085h,0C0h,074h,008h,056h,08Bh,071h,028h
    db 089h,070h,028h,05Eh,08Bh,041h,028h,085h
    db 0C0h,074h,00Dh,08Bh,051h,024h,089h,050h
    db 024h,0C7h,001h,044h,037h,007h,001h,0C3h
    db 08Bh,041h,024h,089h,042h,00Ch,0C7h,001h
    db 044h,037h,007h,001h,0C3h
??1Anim2D@@MAE@XZ ENDP
_TEXT ENDS

END
