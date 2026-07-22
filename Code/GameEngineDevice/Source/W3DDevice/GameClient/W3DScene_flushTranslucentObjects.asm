.386
.model flat

; ?flushTranslucentObjects@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
; Exact 392 retail bytes @ 0x00715340
; True body: Flush@0x7158F0 calls ILT 0x19042->here after Render_And_Clear_Static_Sort_Lists,
; before DoParticles (ZH Flush order). Queue 0x00943720 was INSIDE neighbor @0x9436c0
; (Convert_Color/ambient mid-body), not this symbol. Twin @0x715530 (clears count, inverted
; robj+0xc4 test) is a later BFME post-sort pass — not this name.
; Identity: m_translucentObjectsCount@+0x86c, buffer@+0x870; Get_User_Data vtbl+0x158;
; renderOneObject via ILT 0x17238; Flush@DX8MeshRenderer 0x949dd0; Render_And_Clear 0x8fd4e0;
; alphaOverride=1.0; Get_Ambient_Light vtbl+0x1c; Set_DX8_Render_State D3DRS_AMBIENT.
; C++ blocked: RTS3DScene layout 0x86c vs ZH 0x590 (systemic); BFME loop (robj+0xc4 + dual
; opacity via vtbl+0x60 vs drawable +0xb0/+0xb4); no count clear in this body.
_TEXT SEGMENT
public ?flushTranslucentObjects@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
?flushTranslucentObjects@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z PROC
    db 55h,8Bh,0ECh,83h,0ECh,0Ch,53h,56h,57h,8Bh,0F9h,8Bh,87h,6Ch,08h,00h
    db 00h,33h,0D2h,3Bh,0C2h,0Fh,84h,0BEh,00h,00h,00h,8Bh,0Dh,48h,0D7h,2Eh
    db 01h,3Bh,0CAh,74h,0Bh,8Bh,49h,0Ch,8Bh,49h,24h,89h,4Dh,0F8h,0EBh,03h
    db 89h,55h,0F8h,3Bh,0C2h,89h,55h,0FCh,0Fh,8Eh,7Dh,00h,00h,00h,8Bh,0FFh
    db 8Bh,97h,70h,08h,00h,00h,8Bh,45h,0FCh,8Bh,34h,82h,8Bh,16h,8Bh,0CEh
    db 0FFh,92h,58h,01h,00h,00h,8Bh,58h,04h,8Ah,86h,0C4h,00h,00h,00h,84h
    db 0C0h,75h,47h,8Bh,06h,8Bh,0CEh,0FFh,50h,60h,0D8h,1Dh,50h,53h,07h,01h
    db 0DFh,0E0h,0F6h,0C4h,01h,75h,0Fh,8Bh,16h,8Bh,0CEh,0FFh,52h,60h,8Bh,45h
    db 08h,0D9h,58h,10h,0EBh,12h,0D9h,83h,0B4h,00h,00h,00h,8Bh,4Dh,08h,0D8h
    db 8Bh,0B0h,00h,00h,00h,0D9h,59h,10h,8Bh,55h,0F8h,8Bh,45h,08h,6Ah,00h
    db 52h,56h,50h,8Bh,0CFh,0E8h,4Eh,1Eh,90h,0FFh,8Bh,45h,0FCh,8Bh,8Fh,6Ch
    db 08h,00h,00h,40h,3Bh,0C1h,89h,45h,0FCh,7Ch,85h,8Bh,0Dh,0E8h,0B0h,34h
    db 01h,0E8h,0CAh,49h,23h,00h,8Bh,75h,08h,56h,0E8h,0D1h,80h,1Eh,00h,83h
    db 0C4h,04h,0C7h,46h,10h,00h,00h,80h,3Fh,8Bh,17h,8Bh,0CFh,0C7h,45h,08h
    db 00h,00h,00h,00h,0FFh,52h,1Ch,89h,45h,0FCh,0C7h,45h,0F8h,00h,00h,7Fh
    db 43h,83h,0ECh,14h,9Bh,9Bh,0D9h,7Ch,24h,10h,8Bh,44h,24h,10h,8Bh,0F8h
    db 25h,0FFh,0F3h,0FFh,0FFh,0Dh,00h,0Ch,00h,00h,2Bh,0F8h,74h,06h,89h,04h
    db 24h,0D9h,2Ch,24h,8Bh,75h,0FCh,0D9h,45h,0F8h,0D9h,06h,0D9h,46h,04h,0D9h
    db 46h,08h,0D9h,45h,08h,0D9h,0C4h,0DCh,0CCh,0DCh,0CBh,0DCh,0CAh,0DEh,0C9h,0DBh
    db 1Ch,24h,0DBh,5Ch,24h,04h,0DBh,5Ch,24h,08h,0DBh,5Ch,24h,0Ch,8Bh,0Ch
    db 24h,8Bh,44h,24h,04h,8Bh,54h,24h,08h,8Bh,5Ch,24h,0Ch,0C1h,0E1h,18h
    db 0C1h,0E3h,10h,0C1h,0E2h,08h,0Bh,0C1h,0Bh,0C3h,0Bh,0C2h,0DDh,0D8h,83h,0FFh
    db 00h,74h,05h,9Bh,0D9h,6Ch,24h,10h,83h,0C4h,14h,89h,45h,0F4h,8Bh,45h
    db 0F4h,50h,68h,8Bh,00h,00h,00h,0E8h,62h,0DDh,8Fh,0FFh,83h,0C4h,08h,5Fh
    db 5Eh,5Bh,8Bh,0E5h,5Dh,0C2h,04h,00h
?flushTranslucentObjects@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z ENDP
_TEXT ENDS
END
