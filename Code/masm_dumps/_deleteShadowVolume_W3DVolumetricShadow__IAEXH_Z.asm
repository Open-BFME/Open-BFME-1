.386
.model flat

; ?deleteShadowVolume@W3DVolumetricShadow@@IAEXH@Z
; Retail @ 0x007BAFA0 size 142
; true body (queue 0x007BCF93 was INSIDE ~W3DVolumetricShadow 0x7BCF50/280);
; field offsets m_shadowVolume@+0x80 m_shadowVolumeCount@+0xf80 (ZH/our C++ +0x50/+0xf50);
; layout root-cause; exact MASM until class layout fixed
_TEXT SEGMENT
public ?deleteShadowVolume@W3DVolumetricShadow@@IAEXH@Z
?deleteShadowVolume@W3DVolumetricShadow@@IAEXH@Z PROC
    db 8Bh,44h,24h,04h,55h,33h,0EDh,3Bh,0C5h,7Ch,7Fh,83h,0F8h,01h,7Dh,7Ah
    db 53h,8Dh,04h,80h,56h,0C1h,0E0h,07h,57h,8Dh,99h,80h,0Fh,00h,00h,8Dh
    db 0BCh,08h,80h,00h,00h,00h,0C7h,44h,24h,14h,0A0h,00h,00h,00h,8Bh,0FFh
    db 8Bh,37h,3Bh,0F5h,74h,40h,8Bh,06h,3Bh,0C5h,74h,0Bh,50h,0E8h,0Eh,6Fh
    db 0Ch,00h,83h,0C4h,04h,89h,2Eh,8Bh,46h,04h,3Bh,0C5h,74h,0Ch,50h,0E8h
    db 0FCh,6Eh,0Ch,00h,83h,0C4h,04h,89h,6Eh,04h,56h,89h,6Eh,08h,89h,6Eh
    db 10h,89h,6Eh,0Ch,89h,6Eh,14h,0E8h,0A4h,6Eh,0Ch,00h,89h,2Fh,8Bh,03h
    db 83h,0C4h,04h,48h,89h,03h,8Bh,44h,24h,14h,83h,0C7h,04h,83h,0C3h,04h
    db 48h,89h,44h,24h,14h,75h,0A9h,5Fh,5Eh,5Bh,5Dh,0C2h,04h,00h
?deleteShadowVolume@W3DVolumetricShadow@@IAEXH@Z ENDP
_TEXT ENDS
END
