.386
.model flat

; ??1VideoPlayer@@UAE@XZ
; Exact 35 retail bytes @ 0x0081C590.
; Identity: vtable 0x112CCC0 slot0 scalar-dtor 0x81C7C0 calls this body; slot1 is
; matched init@VideoPlayer @ 0x81CB30; body stores same vtable, clears TheVideoPlayer
; (0x130B190), restores interface vtable 0x112CC60, tail-jumps base dtor 0x9A1A40.
; C++ blocked: ZH vector<Video> member emits SEH+vector dtor (101B) vs retail 35B.
_TEXT SEGMENT
public ??1VideoPlayer@@UAE@XZ
??1VideoPlayer@@UAE@XZ PROC
    db 0C7h, 01h, 0C0h, 0CCh, 12h, 01h, 3Bh, 0Dh, 90h, 0B1h, 30h, 01h, 75h, 0Ah, 0C7h, 05h
    db 90h, 0B1h, 30h, 01h, 00h, 00h, 00h, 00h, 0C7h, 01h, 60h, 0CCh, 12h, 01h, 0E9h, 8Dh
    db 54h, 18h, 00h
??1VideoPlayer@@UAE@XZ ENDP
_TEXT ENDS
END
