# Eighty-one address-derived zero-triple constructors (0x00067020 ... 0x00293910)

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
| 0x000E7720 | 0x00001794 |
| 0x000EB8E0 | 0x000226A6 |
| 0x000FA370 | 0x000471B8 |
| 0x000FD760 | 0x00044CDD |
| 0x000FD780 | 0x00024A4B |
| 0x00127380 | 0x0000C338 |
| 0x00127540 | 0x00019F4C |
| 0x00127560 | 0x00041326 |
| 0x00127580 | 0x0001E187 |
| 0x001401F0 | 0x00021742 |
| 0x00140210 | 0x0003CBB4 |
| 0x00140230 | 0x000254E1 |
| 0x001402F0 | 0x00009B56 |
| 0x00140490 | 0x00033537 |
| 0x001406D0 | 0x00009859 |
| 0x00140A40 | 0x0001D2AA |
| 0x00151A60 | 0x00033474 |
| 0x00195710 | 0x0002AECD |
| 0x00195770 | 0x0003397E |
| 0x00195790 | 0x00042C76 |
| 0x001957F0 | 0x00048806 |
| 0x001B69A0 | 0x0003484C |
| 0x001B6B70 | 0x000462F9 |
| 0x001C4AD0 | 0x00027F9D |
| 0x001D7130 | 0x00023AB5 |
| 0x001D71B0 | 0x0004356D |
| 0x001DF8A0 | 0x0002B8E1 |
| 0x001E5040 | 0x00021210 |
| 0x001E5060 | 0x000262EC |
| 0x001E5100 | 0x0002978F |
| 0x001F9580 | 0x00046790 |
| 0x001F95A0 | 0x0001A311 |
| 0x002061D0 | 0x00037A47 |
| 0x00208540 | 0x0004382E |
| 0x0020EFE0 | 0x00045188 |
| 0x00230270 | 0x0002CBE2 |
| 0x00235EE0 | 0x00043027 |
| 0x00235F40 | 0x0003378A |
| 0x00235FA0 | 0x0002A626 |
| 0x00236160 | 0x00005ABF |
| 0x002361C0 | 0x00042451 |
| 0x00236200 | 0x0001D877 |
| 0x00236260 | 0x00016301 |
| 0x00236280 | 0x0003472A |
| 0x002523C0 | 0x000454D5 |
| 0x00258AB0 | 0x0003FD96 |
| 0x0025BC20 | 0x0000B78A |
| 0x0025DC90 | 0x0000E156 |
| 0x002612C0 | 0x00026986 |
| 0x002612E0 | 0x00017922 |
| 0x00262EA0 | 0x00047B0E |
| 0x00272EA0 | 0x0000D198 |
| 0x00281EC0 | 0x00011B85 |
| 0x00283B20 | 0x0002957D |
| 0x00283B80 | 0x0002FFC2 |
| 0x00283BE0 | 0x00008A94 |
| 0x00288310 | 0x000449C2 |
| 0x0028D890 | 0x000303FF |
| 0x0028F780 | 0x0000A5CE |
| 0x0028F7E0 | 0x00043C34 |
| 0x00293910 | 0x0001BC1B |
