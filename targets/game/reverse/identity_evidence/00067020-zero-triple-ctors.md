# Twenty address-derived zero-triple constructors (0x00067020 ... 0x000E5110)

Each address holds its own 15-byte body (int3-padded on both sides):

    8b c1          mov eax, ecx
    33 c9          xor ecx, ecx
    89 08          mov [eax], ecx
    89 48 04       mov [eax+4], ecx
    89 48 08       mov [eax+8], ecx
    c2 04 00       ret 4

i.e. a thiscall constructor (returns `this`) that zeroes three dwords and
ignores one stack argument, the shape of an STLport `vector(const allocator&)`.
Each is the target of its own gen-thunk ILT stub, so it is an external function;
which element type each instantiates is not witnessed (no pin, dir32 name,
caller or vtable slot names any of them).

Before: `?dup_XXXXXXXX@@YAXXZ` gen-alias placeholders borrowing the byte-identical
`??0?$vector@VAsciiString@@...` COMDAT from GameAudio.cpp; no identity was ever
claimed, and one COMDAT cannot be twenty retail bodies.

After: `??0RvaXXXXXXXX@@QAE@ABH@Z` in
game/GameEngine/Source/Common/UnclaimedZeroTripleConstructors.cpp. The names are
derived from the address and say only what the bytes do; the `const int &`
parameter is a placeholder for an unread reference. Identity is not recovered.

| body | ILT stub |
|---|---|
| 0x00067020 | 0x000360E8 |
| 0x00068EE0 | 0x0001B829 |
| 0x00076250 | 0x00003887 |
| 0x000762D0 | 0x0004692F |
| 0x00076330 | 0x0002344D |
| 0x00076390 | 0x0003CF0B |
| 0x00095A30 | 0x00026D87 |
| 0x00095AC0 | 0x00032C2C |
| 0x000A0EC0 | 0x0003FCB5 |
| 0x000A7930 | 0x0002C05C |
| 0x000A7950 | 0x0001E984 |
| 0x000B0320 | 0x0000D6A7 |
| 0x000B0340 | 0x00026B07 |
| 0x000CE870 | 0x00030567 |
| 0x000D0170 | 0x000493FF |
| 0x000D01F0 | 0x0000D1D9 |
| 0x000D04D0 | 0x00035062 |
| 0x000E17F0 | 0x0002EF5F |
| 0x000E50F0 | 0x000290F0 |
| 0x000E5110 | 0x00032961 |
