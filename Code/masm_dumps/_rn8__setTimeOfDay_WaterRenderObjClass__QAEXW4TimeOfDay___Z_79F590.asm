.386
.model flat
; ?setTimeOfDay@WaterRenderObjClass@@QAEXW4TimeOfDay@@@Z
; Exact 35B @ 0x79F590; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?setTimeOfDay@WaterRenderObjClass@@QAEXW4TimeOfDay@@@Z
?setTimeOfDay@WaterRenderObjClass@@QAEXW4TimeOfDay@@@Z PROC
    db 8Bh, 44h, 24h, 04h, 89h, 81h, 00h, 04h, 00h, 00h, 83h, 0B9h, 1Ch, 01h, 00h, 00h
    db 02h, 75h, 0Dh, 6Ah, 01h, 6Ah, 18h, 6Ah, 0Fh, 6Ah, 0Fh, 0E8h, 0B2h, 0ACh, 87h, 0FFh
    db 0C2h, 04h, 00h
?setTimeOfDay@WaterRenderObjClass@@QAEXW4TimeOfDay@@@Z ENDP
_TEXT ENDS
END
