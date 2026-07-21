.386
.model flat

; ??0WeaponStore@@QAE@XZ
; Exact 29 retail bytes @ 0x001E5290
; True body (queue 0x009F2731 was inside matched ??0ControlBar@@QAE@XZ @ 0x9F2730).
; Identity: GameEngine init new(0x14)->ILT 0x24668->body; "TheWeaponStore" string
; immediately after; SubsystemInterface base @0x9A1A30; vtbl 0x10A13C8; zeros +8/+c/+10
; (vector only, sizeof 0x14). Same 29B shape as ScienceStore/RankInfoStore/PlayerTemplateStore.
; C++ blocked: ZH m_weaponDDI list adds SEH frame (~100B) vs retail empty vector-only body.
_TEXT SEGMENT
public ??0WeaponStore@@QAE@XZ
??0WeaponStore@@QAE@XZ PROC
    db 056h,08Bh,0F1h,0E8h,098h,0C7h,07Bh,000h,033h,0C0h,0C7h,006h,0C8h,013h,00Ah,001h
    db 089h,046h,008h,089h,046h,00Ch,089h,046h,010h,08Bh,0C6h,05Eh,0C3h
??0WeaponStore@@QAE@XZ ENDP
_TEXT ENDS
END
