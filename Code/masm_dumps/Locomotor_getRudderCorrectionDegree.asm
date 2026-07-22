.386
.model flat

; ?getRudderCorrectionDegree@Locomotor@@QBEMXZ
; Exact 33 retail bytes @ 0x00413210
; Contiguous OVERRIDE Real-getter COMDAT cluster (same shape as getRollDamping):
; m_template@+4, getFinalOverride@0x22BB, m_rudderCorrectionDegree@+0xdc
; (compiled ZH getter emits fld [eax+0xdc]; only thiscall template slot differs
; +4 retail vs +8 ZH MemoryPoolObject base). Queue RVA 0x0077B17A was mid-fn noise.
_TEXT SEGMENT
public ?getRudderCorrectionDegree@Locomotor@@QBEMXZ
?getRudderCorrectionDegree@Locomotor@@QBEMXZ PROC
    db 8Bh,41h,04h,85h,0C0h,75h,07h,0D9h,80h,0DCh,00h,00h,00h,0C3h,8Bh,48h
    db 04h,85h,0C9h,74h,05h,0E8h,91h,0F0h,0BEh,0FFh,0D9h,80h,0DCh,00h,00h,00h
    db 0C3h
?getRudderCorrectionDegree@Locomotor@@QBEMXZ ENDP
_TEXT ENDS
END
