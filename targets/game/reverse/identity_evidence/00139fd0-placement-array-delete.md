# Standard array placement delete at 00139FD0

b1 session 3, model=gpt-6-astra.

The untouched native `VectorClass<StringClass>::Resize` in WWLib/mixfile.cpp
strictly matches all 340 bytes at 0013B450. WWLib/vector.h:423 uses
`new((void*)array) T[newsize]`. The compiler's native exception action therefore
names `??_V@YAXPAX0@Z`, the standard cdecl operator delete[](void*, void*) declared
and defined by the compiler's `<new>` header (line 79).

Independent retail ownership:
- 0013B450 loads FS:[0], pushes -1, then pushes handler 00C0366C at +8.
- Handler 00C0366C names FuncInfo 00DF1C00; its two states both unwind to -1.
- State 1 owns action 00C0365B, which pushes EBP+8 and EBP+4, calls
  ILT 00033D3E, pops eight bytes and returns at 00C0366B.
- ILT 00033D3E reaches 00139FD0. That body is one RET, followed by INT3.
- Native state 1 selects $L5440, whose REL32 at action+9 names
  `??_V@YAXPAX0@Z`. All seventeen action bytes match; the existing native
  definition of that symbol in the same object is exactly C3.

This is a callee identity from a matched parent, a native EH state, the genuine
placement-array expression and its cleanup ABI; it is not inferred from the
one-byte helper alone. Ghidra agrees with the raw action and helper extents.

The old canonical row at 001EE7C0 in parameter.cpp has only `icf-scan` evidence.
It is another RET/INT3 body; no named caller establishes this identity there.
Retail was linked without identical COMDAT folding. Retire that unsupported
name/address claim rather than introduce a second canonical binding. Do not
claim to know the identity of 001EE7C0. Its generated b_001ee7c0 pin is unchanged.

The generated member placeholder at 00139FD0 is replaced by the native standard
operator already emitted in mixfile.cpp. No new source definition, shared header
change, forced alias or symbol pin is needed. The dependent 00C0365B action must
pass strict relocation verification with this repaired binding, followed by the
normal affected-caller commit hook.
