.386
.model flat

; ?clear@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@@3@@_STL@@QAEXXZ
; Exact 51 retail bytes @ 0x005B3370
; Identity: standalone thiscall clear of HotKey map tree; immediately precedes
; matched ??1?$_Rb_tree@...HotKey... @ 0x005B33B0 (124B). Calls same
; _M_erase thunk 0x20E37 already matched for this specialization.
; Queue RVA 0x005B387F is INSIDE dual-map clear body @ 0x005B3850 (94B), not ENTRY.
_TEXT SEGMENT
public ?clear@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@@3@@_STL@@QAEXXZ
?clear@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@@3@@_STL@@QAEXXZ PROC
    db 56h,8Bh,0F1h,8Bh,46h,04h,85h,0C0h
    db 74h,27h,8Bh,06h,8Bh,48h,04h,51h
    db 8Bh,0CEh,0E8h,0B0h,0DAh,0A6h,0FFh,8Bh
    db 06h,89h,40h,08h,8Bh,16h,0C7h,42h
    db 04h,00h,00h,00h,00h,8Bh,06h,89h
    db 40h,0Ch,0C7h,46h,04h,00h,00h,00h
    db 00h,5Eh,0C3h
?clear@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VHotKey@@@_STL@@@3@@_STL@@QAEXXZ ENDP
_TEXT ENDS
END
