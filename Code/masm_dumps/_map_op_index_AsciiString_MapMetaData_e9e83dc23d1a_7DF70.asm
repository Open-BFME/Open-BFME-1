.386
.model flat

; ??A?$map@VAsciiString@@VMapMetaData@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@4@@_STL@@QAEAAVMapMetaData@@ABVAsciiString@@@Z
; Exact 231B map<AsciiString,MapMetaData>::operator[] true body @ 0x7DF70;
; queue 0x64E689 was int3 pad before unrelated 12B-key/4B-value map::operator[]
; (insert_unique@0x64CBD0 is 0x20-node; MapMetaData nodes are 0x68 via allocate@0x1AFF70).
; Anchors: lower_bound thunk 0x2D029 (MapMetaData equal_range sibling cluster),
; value at +0x14, SEH cookie matches compiled TU, insert_unique@0x7DBC0.
_TEXT SEGMENT
public _bfme_export_e9e83dc23d1a
_bfme_export_e9e83dc23d1a PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h, 080h, 044h, 0FFh, 000h, 050h, 064h, 089h
    db 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 00Ch, 055h, 08Bh, 06Ch, 024h, 020h, 056h, 057h, 055h
    db 08Bh, 0F1h, 0E8h, 092h, 0F0h, 0FAh, 0FFh, 08Bh, 0F8h, 03Bh, 03Eh, 074h, 013h, 08Dh, 047h, 010h
    db 050h, 08Bh, 0CDh, 0E8h, 01Dh, 041h, 0FAh, 0FFh, 085h, 0C0h, 00Fh, 08Dh, 090h, 000h, 000h, 000h
    db 0C7h, 044h, 024h, 028h, 000h, 000h, 000h, 000h, 055h, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h
    db 024h, 000h, 000h, 000h, 000h, 0E8h, 096h, 09Bh, 080h, 000h, 08Dh, 04Ch, 024h, 028h, 051h, 08Dh
    db 04Ch, 024h, 018h, 0C6h, 044h, 024h, 024h, 001h, 0E8h, 083h, 09Bh, 080h, 000h, 08Dh, 054h, 024h
    db 010h, 052h, 051h, 08Bh, 0C4h, 089h, 038h, 08Dh, 044h, 024h, 014h, 050h, 08Bh, 0CEh, 0C6h, 044h
    db 024h, 02Ch, 002h, 0E8h, 02Bh, 0B4h, 0FBh, 0FFh, 08Bh, 074h, 024h, 00Ch, 08Dh, 04Ch, 024h, 014h
    db 0C6h, 044h, 024h, 020h, 003h, 0E8h, 036h, 099h, 080h, 000h, 08Dh, 04Ch, 024h, 010h, 0C6h, 044h
    db 024h, 020h, 000h, 0E8h, 028h, 099h, 080h, 000h, 08Dh, 04Ch, 024h, 028h, 0C7h, 044h, 024h, 020h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 017h, 099h, 080h, 000h, 08Dh, 046h, 014h, 08Bh, 04Ch, 024h, 018h
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 083h, 0C4h, 018h, 0C2h, 004h, 000h
    db 08Bh, 04Ch, 024h, 018h, 08Dh, 047h, 014h, 05Fh, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 05Dh, 083h, 0C4h, 018h, 0C2h, 004h, 000h
_bfme_export_e9e83dc23d1a ENDP
_TEXT ENDS
END
