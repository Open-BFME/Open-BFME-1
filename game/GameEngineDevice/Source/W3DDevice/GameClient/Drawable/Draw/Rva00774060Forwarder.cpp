// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00774060, 20 bytes, in the W3DModelDraw/ModelConditionInfo code
// run: a __cdecl free function that hands its second and third arguments to a
// __thiscall member of its first argument (ILT 0x0003A8D7 -> 0x007710F0).
//
// The callee at 0x007710F0 (970 bytes, `ret 8`) keeps `this` in EBP, tests the
// first byte of its first argument, indexes 20-byte records at this+0x134 and
// reads TheGameLODManager and AsciiString data -- it is not
// BitFlags<116>::testSetAndClear, so this forwarder is not
// TEST_KINDOFMASK_MULTI, which an earlier gen-alias row named it. Neither
// identity is proven, so both keep address-derived names.

class Rva007710F0Owner
{
public:
	void method(void *first, void *second);
};

void Rva00774060(Rva007710F0Owner *owner, void *first, void *second)
{
	owner->method(first, second);
}
