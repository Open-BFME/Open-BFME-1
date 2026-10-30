.386
.model flat
; ??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z  -- retail 139 B @ 0x001F8970.
; The shared base constructor of the twenty-four upgrade module constructors
; (they call it through ILT 0x0000C315; symbols.csv pins the name there). The
; ledger row was a naked lift misnamed ??1CostModifierUpgrade; the body ends in
; `ret 8`, installs vftables, and is this constructor (identity evidence at
; targets/game/reverse/identity_evidence/0x001f8970.md).
;
; Shape: the ObjectModule constructor (ILT 0x000170E4), the inline
; BehaviorModule vptr round (0x0109C9D0 then 0x0109CB5C/0x0109CA98), the shared
; UpgradeMux constructor at +0x10 (ILT 0x0003D24E), a ModuleInterface base at
; +0x18 (0x010A1BFC), then the UpgradeModule vptr round. esi=this (arg at
; [esp+1Ch]), edi=this+0x10h from +0x43 onward.
;
; C++ blocked: the body opens with the VC7.1 SEH establisher prologue
; (push -1 / push handler / mov eax,fs:[0] / push eax / mov fs:[0],esp), which
; cl 13.10.3077 -O2 -EHsc emits only for a polymorphic function. Proven on this
; toolchain: the original TU fresh-compiles to the 139-byte SEH body (0
; non-reloc diffs vs retail, build/diag/compile_fresh_orig.py), while a
; non-polymorphic twin with the same explicit vptr stores compiles to 106
; bytes with no SEH prologue (build/diag/compile_reseat_probe.py) and a
; minimal non-polymorphic ctor to 34 bytes with no SEH
; (build/diag/seh_probe_nonpoly.cpp). Polymorphism is required for the SEH, but
; the four UpgradeModule secondary vtables it forces are compiler-named
; ??_7UpgradeModule@@6B...@@@ and their retail addresses (0x010A36CC/0x010A36E0
; /0x010A3740/0x010A3804) are either already recorded under other classes'
; names or unowned, so no C++ spelling can make the stores reference a name the
; DIR32 gate accepts. The TU therefore stays byte-assembled.
;
; The eight vtable stores below are the only reloc sites: the three Behavior
; Module-round stores and the ModuleInterface primary store keep the recorded /
; whitelisted names; the four UpgradeModule-round stores reference the
; recorded secondary-vtable names at 0x010A36E0/0x010A36CC (the debt lines
; they cleared) and the address names g_Va010A3804/g_Va010A3740 for the two
; unowned bases. Every other byte, both call rel32s and the SEH prologue /
; epilogue imm32s, comes from the retail bytes, not from a dump guess.

EXTERN ??_7BehaviorModuleInterface@@6B@:BYTE
EXTERN ??_7BehaviorModule@@6BObjectModule@@@:BYTE
EXTERN ??_7BehaviorModule@@6BBehaviorModuleInterface@@@:BYTE
EXTERN ??_7ModuleInterface@@6B@:BYTE
EXTERN ??_7DynamicPortalUpgradeModule@@6BDynamicPortalUpgradeMux@@@:BYTE
EXTERN ??_7DynamicPortalUpgradeModule@@6BDynamicPortalModuleInterface@@@:BYTE
EXTERN g_Va010A3804:BYTE
EXTERN g_Va010A3740:BYTE

_TEXT SEGMENT
public ??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z
??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z PROC
    ; SEH establisher prologue (retail imm32s hardcoded)
    db 06Ah,0FFh,068h,0D8h,0AFh,00h,01h,064h,0A1h,00h,00h,00h,00h,050h,064h,089h,025h,00h,00h,00h,00h
    ; push ecx; mov eax,[esp+18]; push esi; push edi; mov esi,ecx
    db 051h,08Bh,044h,024h,018h,056h,057h,08Bh,0F1h
    ; mov ecx,[esp+1Ch]; push eax; push ecx; mov ecx,esi; mov [esp+10h],esi
    db 08Bh,04Ch,024h,01Ch,050h,051h,08Bh,0CEh,089h,074h,024h,010h
    ; call ObjectModule ctor (ILT 0x000170E4); retail rel32
    db 0E8h,045h,0E7h,0E1h,0FFh
    ; BehaviorModule vptr round
    db 0C7h,046h,00Ch
    dd ??_7BehaviorModuleInterface@@6B@
    db 0C7h,006h
    dd ??_7BehaviorModule@@6BObjectModule@@@
    db 0C7h,046h,00Ch
    dd ??_7BehaviorModule@@6BBehaviorModuleInterface@@@
    ; lea edi,[esi+10h]; mov ecx,esi; mov [esp+14h],0
    db 08Dh,07Eh,010h,08Bh,0CFh,0C7h,044h,024h,014h,00h,00h,00h,00h
    ; call UpgradeMux ctor (ILT 0x0003D24E); retail rel32
    db 0E8h,089h,048h,0E4h,0FFh
    ; mov ecx,[esp+0Ch]
    db 08Bh,04Ch,024h,00Ch
    ; UpgradeModule vptr round
    db 0C7h,046h,018h
    dd ??_7ModuleInterface@@6B@
    db 0C7h,007h
    dd ??_7DynamicPortalUpgradeModule@@6BDynamicPortalUpgradeMux@@@
    db 0C7h,006h
    dd g_Va010A3804
    db 0C7h,046h,00Ch
    dd g_Va010A3740
    db 0C7h,046h,018h
    dd ??_7DynamicPortalUpgradeModule@@6BDynamicPortalModuleInterface@@@
    ; pop edi; mov eax,esi; pop esi
    db 05Fh,08Bh,0C6h,05Eh
    ; SEH epilogue (retail fs:[0] imm32 hardcoded); add esp,10h; ret 8
    db 064h,089h,00Dh,00h,00h,00h,00h,083h,0C4h,010h,0C2h,008h,000h
??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z ENDP
_TEXT ENDS
end
