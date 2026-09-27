# PointGroup diffuse fill, 0x00912880

The independently matched PointGroupClass::Render at 0x00917B70 calls this
helper at +0x279 with ECX=this, Vector4 diffuse input, and active point count.
Its existing opaque pin is
`?rva00912880@PointGroupClass@@QAEXPAVVector4@@H@Z`; the body returns with
8-byte argument cleanup. Generated volume-render caller 0x00917E10 also
calls it at +0xB8. The helper contains no direct or indirect calls.

PointMode at +0x2C is independently established by matched Set_Point_Mode
0x00912080 (`mov [ecx+0x2C],eax`) and Get_Point_Mode 0x00912090. The local
partial PointGroup view follows the landed renderer because the canonical
pointgr.h lacks the split BFME method. All vector and buffer types come from
canonical headers; unused +0x24/+0x28 slots remain address-derived.

There is one DIR32 data reference: VertexDiffuse+4 resolves to VA 0x013466BC.
The independently matched pool sizing helper at 0x00914860 loads the same
VectorClass<Vector4> object base 0x013466B8 at +0x46 before invoking Resize.
The matched PointGroup shutdown clears that same VertexDiffuse vector.
The complete function extent is 1124 bytes, with its final `ret 8` at +0x461
and INT3 padding before 0x00912CF0. Ghidra independently reports 1124.

The native source checks for null input, selects three or four vertices by
PointMode, and duplicates each Vector4 with ordinary advancing pointer loops.
VC7.1 performs retail's four-point unrolling. The initial source was already
1124 bytes with only 16 prologue byte differences; moving output-buffer lookup
before the mode branch, as retail does, yielded an exact byte probe. There is
no assembly, volatile allocation aid, manually unrolled instruction copy, new
pin, helper-credit move, or guessed semantic method identity.
