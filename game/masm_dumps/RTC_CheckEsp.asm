.386
.model flat

; Native stack.obj compiler machinery, BFME1 retail 0x009F7502..0x009F7525.
; The caller's ZF is the input: an ordinary C++ prologue cannot implement
; this entry contract. The failure path also preserves live EAX and EDX.
; It remains assembly and receives zero C++ credit. The ordinary fastcall
; guard-checking sibling is recovered in CRT/RtcStack.cpp.
EXTERN ?_RTC_Failure@@YAXPAXH@Z:PROC

_TEXT SEGMENT
public __RTC_CheckEsp
__RTC_CheckEsp PROC
    jne bad_stack
    ret
bad_stack:
    push ebp
    mov ebp,esp
    sub esp,0
    push eax
    push edx
    push ebx
    push esi
    push edi
    push 0
    push DWORD PTR [ebp+4]
    call ?_RTC_Failure@@YAXPAXH@Z
    pop ecx
    pop ecx
    pop edi
    pop esi
    pop ebx
    pop edx
    pop eax
    mov esp,ebp
    pop ebp
    ret
__RTC_CheckEsp ENDP
_TEXT ENDS
END
