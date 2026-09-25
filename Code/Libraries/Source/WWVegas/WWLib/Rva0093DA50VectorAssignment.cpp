// cl: /DNDEBUG /MD /EHsc
// Retail 0x0093DA50: DynamicVectorClass assignment wrapper (33 bytes).
// Retail 0x0093CEA0 is the 120-byte base assignment body. Its witnessed
// contract is thiscall(const source reference), ret 4, virtual Clear at slot
// 0x0C, allocation of source count * 4, and a four-byte element copy stride.
// The base's 16 opaque bytes and the two DWORD tail fields are the independently
// witnessed layout; no element or pointee semantics are asserted here.

struct Rva0093CEA0VectorBase
{
	Rva0093CEA0VectorBase &operator=(const Rva0093CEA0VectorBase &source);

	unsigned char opaque[16];
};

struct Rva0093DA50Vector : Rva0093CEA0VectorBase
{
	Rva0093DA50Vector &operator=(const Rva0093DA50Vector &source);

	unsigned long word10;
	unsigned long word14;
};

Rva0093DA50Vector &Rva0093DA50Vector::operator=(
	const Rva0093DA50Vector &source)
{
	Rva0093CEA0VectorBase::operator=(source);
	word10 = source.word10;
	word14 = source.word14;
	return *this;
}
