.386
.model flat

; ?setDisallowNonAsianText@GameSpyInfo@@UAEX_N@Z
; Exact 13 retail bytes @ 0x00A30770; stores the BFME-layout flag at offset 0x245.
_TEXT SEGMENT
public ?setDisallowNonAsianText@GameSpyInfo@@UAEX_N@Z
?setDisallowNonAsianText@GameSpyInfo@@UAEX_N@Z PROC
    db 08Ah,044h,024h,004h,088h,081h,045h,002h,000h,000h,0C2h,004h,000h
?setDisallowNonAsianText@GameSpyInfo@@UAEX_N@Z ENDP
_TEXT ENDS
END
