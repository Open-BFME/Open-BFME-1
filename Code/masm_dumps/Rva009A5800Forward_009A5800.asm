.386
.model flat
; Forwards three cdecl stack args to 0x009A5620. That callee reads its
; middle argument from EAX, a register-passed parameter no C/C++ calling
; convention (cdecl/stdcall/fastcall/thiscall) can express, so this stays MASM.
_TEXT SEGMENT
extern ?d_009a5620@@YAXXZ:PROC
public ?Rva009A5800Forward@@YAXHHH@Z
?Rva009A5800Forward@@YAXHHH@Z PROC
    mov eax, [esp+0Ch]
    mov ecx, [esp+04h]
    push eax
    mov eax, [esp+0Ch]
    push ecx
    call ?d_009a5620@@YAXXZ
    add esp, 8
    ret
?Rva009A5800Forward@@YAXHHH@Z ENDP
_TEXT ENDS
END
