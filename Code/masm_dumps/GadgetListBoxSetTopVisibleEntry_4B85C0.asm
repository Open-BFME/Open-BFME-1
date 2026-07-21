.386
.model flat

; ?GadgetListBoxSetTopVisibleEntry@@YAXPAVGameWindow@@H@Z
; BFME rewrote ZH delta-adjustDisplay shape into a thin wrapper that null-checks
; window/userData then calls the absolute set-entry helper @ 0x4B7DC0 with
; newPos in EAX, window + TRUE on the stack. Retail @ 0x004B85C0 size 37.
_TEXT SEGMENT
public ?GadgetListBoxSetTopVisibleEntry@@YAXPAVGameWindow@@H@Z
?GadgetListBoxSetTopVisibleEntry@@YAXPAVGameWindow@@H@Z PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 1Ah, 8Bh, 0CEh, 0E8h, 68h, 0DFh, 0B8h, 0FFh
    db 85h, 0C0h, 74h, 0Fh, 8Bh, 44h, 24h, 0Ch, 6Ah, 01h, 56h, 0E8h, 0E0h, 0F7h, 0FFh, 0FFh
    db 83h, 0C4h, 08h, 5Eh, 0C3h
?GadgetListBoxSetTopVisibleEntry@@YAXPAVGameWindow@@H@Z ENDP
_TEXT ENDS
END
