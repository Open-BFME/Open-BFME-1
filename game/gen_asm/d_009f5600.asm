.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
_TEXT SEGMENT

; retail @ 0x009F5600 size 45
_TEXT ENDS
_TEXT$d00df5600 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DF5600 size 45
public ?d_009f5600@@YAXXZ
?d_009f5600@@YAXXZ PROC
    db 08Bh, 011h, 085h, 0D2h, 074h, 026h, 08Bh, 041h, 008h, 02Bh, 0C2h, 0C1h, 0F8h, 003h, 0C1h, 0E0h
    db 003h, 03Dh, 080h, 000h, 000h, 000h, 076h, 00Ah, 052h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0C3h, 050h, 052h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 0C3h
?d_009f5600@@YAXXZ ENDP
_TEXT$d00df5600 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
