.386
.model flat

; ??A?$map@VAsciiString@@_NU?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@_N@_STL@@@3@@_STL@@QAEAA_NABVAsciiString@@@Z
; Exact 169B map<AsciiString,bool>::operator[] true body @ 0x63960;
; queue 0x64E68F was 1B int3 before unrelated 12B-key/4B-val map::op[] (0x64E690/229B,
; insert_unique@0x64CBD0 0x20-node). True family: 169B ICF x8, value at +0x14,
; AsciiString::compare@0x220C5, StringBase copy@0x887B60, releaseBuffer@0x887940.
_TEXT SEGMENT
public _bfme_export_d5b504ddfcf2
_bfme_export_d5b504ddfcf2 PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h, 098h, 028h, 0FFh, 000h, 050h, 064h, 089h
    db 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 008h, 053h, 08Bh, 05Ch, 024h, 01Ch, 056h, 057h, 053h
    db 08Bh, 0F1h, 0E8h, 0F3h, 0C1h, 0FDh, 0FFh, 08Bh, 0F8h, 03Bh, 03Eh, 074h, 00Fh, 08Dh, 047h, 010h
    db 050h, 08Bh, 0CBh, 0E8h, 02Dh, 0E7h, 0FBh, 0FFh, 085h, 0C0h, 07Dh, 056h, 053h, 08Dh, 04Ch, 024h
    db 010h, 0E8h, 0BAh, 041h, 082h, 000h, 033h, 0C0h, 089h, 044h, 024h, 010h, 08Dh, 04Ch, 024h, 00Ch
    db 051h, 051h, 089h, 044h, 024h, 024h, 08Bh, 0C4h, 08Dh, 054h, 024h, 02Ch, 052h, 08Bh, 0CEh, 089h
    db 038h, 0E8h, 063h, 06Bh, 0FAh, 0FFh, 08Bh, 074h, 024h, 024h, 08Dh, 04Ch, 024h, 00Ch, 0C7h, 044h
    db 024h, 01Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 065h, 03Fh, 082h, 000h, 08Dh, 046h, 014h, 08Bh, 04Ch
    db 024h, 014h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Bh, 083h, 0C4h, 014h, 0C2h
    db 004h, 000h, 08Bh, 04Ch, 024h, 014h, 08Dh, 047h, 014h, 05Fh, 05Eh, 064h, 089h, 00Dh, 000h, 000h
    db 000h, 000h, 05Bh, 083h, 0C4h, 014h, 0C2h, 004h, 000h
_bfme_export_d5b504ddfcf2 ENDP
_TEXT ENDS
END
