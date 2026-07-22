.386
.model flat

; ?W3DCameoMovieDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
; Exact 148 retail bytes @ 0x00799D00; FunctionLexicon {key,str,fn} entry.
; Drift 0x0079C8DE was mid-body elsewhere; ILT 0x3C213 -> 0x799D00 (adjacent to RightHUD 0x44099->0x799F20).
; C++ blocked: InGameUI::cameoVideoBuffer vtable slot retail +0x148 vs ZH +0x128 + float draw path size 148 vs 110.
_TEXT SEGMENT
public ?W3DCameoMovieDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
?W3DCameoMovieDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z PROC
    db 08Bh,00Dh,08Ch,014h,02Fh,001h,08Bh,001h,083h,0ECh,014h,057h,0FFh,090h,048h,001h
    db 000h,000h,08Bh,0F8h,085h,0FFh,074h,077h,056h,08Bh,074h,024h,020h,08Dh,04Ch,024h
    db 010h,051h,08Dh,054h,024h,010h,052h,08Bh,0CEh,0E8h,01Dh,05Ch,089h,0FFh,08Dh,044h
    db 024h,018h,050h,08Dh,04Ch,024h,018h,051h,08Bh,0CEh,0E8h,07Dh,0D1h,089h,0FFh,08Bh
    db 044h,024h,010h,08Bh,074h,024h,018h,08Bh,00Dh,070h,012h,02Fh,001h,08Bh,011h,003h
    db 0F0h,08Bh,044h,024h,00Ch,089h,074h,024h,008h,08Bh,074h,024h,014h,0DBh,044h,024h
    db 008h,06Ah,0FFh,083h,0ECh,010h,0D9h,05Ch,024h,00Ch,003h,0F0h,089h,074h,024h,01Ch
    db 0DBh,044h,024h,01Ch,0D9h,05Ch,024h,008h,0DBh,044h,024h,024h,0D9h,05Ch,024h,004h
    db 0DBh,044h,024h,020h,0D9h,01Ch,024h,057h,0FFh,092h,0E0h,000h,000h,000h,05Eh,05Fh
    db 083h,0C4h,014h,0C3h
?W3DCameoMovieDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z ENDP
_TEXT ENDS
END
