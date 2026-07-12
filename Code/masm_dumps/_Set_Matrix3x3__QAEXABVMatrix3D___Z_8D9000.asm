.386
.model flat

; ?Set@Matrix3x3@@QAEXABVMatrix3D@@@Z
; Retail @ 0x00CD9000 size 59
_TEXT SEGMENT
public ?Set@Matrix3x3@@QAEXABVMatrix3D@@@Z
?Set@Matrix3x3@@QAEXABVMatrix3D@@@Z PROC
    db 8Bh,44h,24h,04h,0D9h,40h,08h,8Bh
    db 10h,0D9h,40h,04h,89h,11h,0D9h,59h
    db 04h,0D9h,59h,08h,8Bh,50h,10h,0D9h
    db 40h,18h,0D9h,40h,14h,89h,51h,0Ch
    db 0D9h,59h,10h,0D9h,59h,14h,0D9h,40h
    db 28h,0D9h,40h,24h,8Bh,40h,20h,0D9h
    db 59h,1Ch,89h,41h,18h,0D9h,59h,20h
    db 0C2h,04h,00h
?Set@Matrix3x3@@QAEXABVMatrix3D@@@Z ENDP
_TEXT ENDS
END
