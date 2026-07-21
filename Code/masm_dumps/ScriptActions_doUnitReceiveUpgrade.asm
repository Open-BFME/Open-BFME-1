.386
.model flat

; ?doUnitReceiveUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z
; Exact 117 retail bytes @ 0x002FE070. Drift 0x001D0A65 was mid mega-fn (inside
; call imm32). Identity: sole ScriptEngine getUnitNamed (vtbl+0x68) + findUpgrade
; (0x2F95A) pair in .text; giveUpgrade cold path; ret 8; ScriptActions cluster.
_TEXT SEGMENT
public ?doUnitReceiveUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z
?doUnitReceiveUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z PROC
    db 08Bh,00Dh,06Ch,007h,02Fh,001h,08Bh,054h,024h,004h,08Bh,001h,056h,052h,0FFh,050h
    db 068h,08Bh,0F0h,085h,0F6h,074h,05Ah,08Bh,044h,024h,00Ch,08Bh,00Dh,088h,0F1h,02Eh
    db 001h,057h,050h,0E8h,0C2h,018h,0D3h,0FFh,08Bh,0F8h,085h,0FFh,074h,042h,06Ah,06Ch
    db 08Bh,0CEh,0E8h,078h,044h,0D3h,0FFh,084h,0C0h,08Bh,0CEh,074h,02Dh,0E8h,007h,0F3h
    db 0D0h,0FFh,08Bh,0F0h,085h,0F6h,074h,028h,08Bh,047h,020h,08Bh,016h,050h,08Bh,0CEh
    db 0FFh,092h,0A8h,000h,000h,000h,084h,0C0h,075h,016h,08Bh,006h,057h,08Bh,0CEh,0FFh
    db 090h,0ACh,000h,000h,000h,05Fh,05Eh,0C2h,008h,000h,057h,0E8h,09Eh,0C8h,0D1h,0FFh
    db 05Fh,05Eh,0C2h,008h,000h
?doUnitReceiveUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z ENDP
_TEXT ENDS
END
