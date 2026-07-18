.386
.model flat

; ?getDisallowNonAsianText@GameSpyInfo@@UAE_NXZ
; Exact 7 retail bytes @ 0x00A30790; returns the BFME-layout flag at offset 0x245.
_TEXT SEGMENT
public ?getDisallowNonAsianText@GameSpyInfo@@UAE_NXZ
?getDisallowNonAsianText@GameSpyInfo@@UAE_NXZ PROC
    db 08Ah,081h,045h,002h,000h,000h,0C3h
?getDisallowNonAsianText@GameSpyInfo@@UAE_NXZ ENDP
_TEXT ENDS
END
