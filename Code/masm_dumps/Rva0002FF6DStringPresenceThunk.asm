.386
.model flat
; Retail 0x0002FF6D is a five-byte ILT thunk to Dict::getAsciiString.
; MSVC 7.1 cannot emit this class-return tail jump from a normal wrapper.
_TEXT SEGMENT
extern ?getAsciiString@Dict@@QBE?AVAsciiString@@W4NameKeyType@@PA_N@Z:PROC
public ?forward@Rva0002FF6DStringPresenceThunk@@QBE?AVAsciiString@@HPA_N@Z
?forward@Rva0002FF6DStringPresenceThunk@@QBE?AVAsciiString@@HPA_N@Z PROC
    jmp ?getAsciiString@Dict@@QBE?AVAsciiString@@W4NameKeyType@@PA_N@Z
?forward@Rva0002FF6DStringPresenceThunk@@QBE?AVAsciiString@@HPA_N@Z ENDP
_TEXT ENDS
END
