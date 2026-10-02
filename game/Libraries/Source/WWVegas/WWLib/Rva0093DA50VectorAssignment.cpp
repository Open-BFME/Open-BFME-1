// Retail 0x0093DA50: DynamicVectorClass assignment wrapper (33 bytes).
// Retail 0x0093CEA0 is the 120-byte base assignment body. Its witnessed
// contract is thiscall(const source reference), ret 4, virtual Clear at slot
// 0x0C, allocation of source count * 4, and a four-byte element copy stride.
// The base's 16 opaque bytes and the two DWORD tail fields are the independently
// witnessed layout; no element or pointee semantics are asserted here.
//
// Retail's base here is WWLib's VectorClass<T>; the body at 0x0093CEA0 is the
// four-byte element instantiation (VectorClassTrivialAssignment.cpp,
// dup_0093cea0). The sibling TUs that call that same body spell the reference
// with the VectorClassDummy stand-in symbols.csv pins to it
// (??4VectorClassDummy@@QAEAAV0@ABV0@@Z at 0x0093CEA0) and that body defines,
// so this stand-in carries that name: the call keeps its bytes and resolves to
// the retail address instead of an undefined ??4Rva0093CEA0VectorBase.

// A class, not a struct: the pinned name's return type mangles as V0 (class by
// value), so a struct here would spell U0 and miss the pin.
class VectorClassDummy
{
public:
	VectorClassDummy &operator=(const VectorClassDummy &source);

	unsigned char opaque[16];
};

struct Rva0093DA50Vector : VectorClassDummy
{
	Rva0093DA50Vector &operator=(const Rva0093DA50Vector &source);

	unsigned long word10;
	unsigned long word14;
};

Rva0093DA50Vector &Rva0093DA50Vector::operator=(
	const Rva0093DA50Vector &source)
{
	VectorClassDummy::operator=(source);
	word10 = source.word10;
	word14 = source.word14;
	return *this;
}
