.386
.model flat

; ?Set_Line_Mode@LineGroupClass@@QAEXW4LineModeType@1@@Z
; Retail @ 0x00D8E950 size 10
_TEXT SEGMENT
public ?Set_Line_Mode@LineGroupClass@@QAEXW4LineModeType@1@@Z
?Set_Line_Mode@LineGroupClass@@QAEXW4LineModeType@1@@Z PROC
    db 8Bh,44h,24h,04h,89h,41h,58h,0C2h
    db 04h,00h
?Set_Line_Mode@LineGroupClass@@QAEXW4LineModeType@1@@Z ENDP
_TEXT ENDS
END
