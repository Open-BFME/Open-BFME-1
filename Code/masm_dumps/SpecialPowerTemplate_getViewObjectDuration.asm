.386
.model flat

; ?getViewObjectDuration@SpecialPowerTemplate@@QBEIXZ
; Exact 33B retail @ 0x00268950. Queue 0x00614FEB was mid-function (starts with je).
; True ENTRY in SpecialPowerTemplate FO-getter cluster (after isSharedNSync-style
; byte getters @0x2688F0/0x268920). Same dual-path getFO shape as getReloadTime
; but FO field +0x108 (UnsignedInt m_viewObjectDuration; ZH headers had +0xF0).
; Calls friend_getFinalOverride@Overridable @ 0x48C61 (REL32 in dump).
_TEXT SEGMENT
public ?getViewObjectDuration@SpecialPowerTemplate@@QBEIXZ
?getViewObjectDuration@SpecialPowerTemplate@@QBEIXZ PROC
    db 08Bh,041h,004h,085h,0C0h,074h,013h,08Bh,048h,004h,085h,0C9h,074h,005h,0E8h,0FEh
    db 002h,0DEh,0FFh,08Bh,080h,008h,001h,000h,000h,0C3h,08Bh,081h,008h,001h,000h,000h
    db 0C3h
?getViewObjectDuration@SpecialPowerTemplate@@QBEIXZ ENDP
_TEXT ENDS
END
