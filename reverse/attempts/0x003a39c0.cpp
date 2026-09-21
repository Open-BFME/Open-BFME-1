// ?rva003a39c0@Rva003A39C0Owner@@QAEXPBH@Z
// partial score=0.45 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// retail RVA 0x003A39C0. A temporary Rva003A35A0Element (the same 184-byte
// STLport vector element already landed at 0x003A35F0,
// Rva003A35F0VectorInsert.cpp) is default-constructed through the pinned
// 0x22F0C ctor, its first three dwords overwritten from the incoming
// pointer argument, and the result inserted at this->m_bfmeCount+2 into the
// vector at this+0x2C. No named caller, owner class or field identity is
// available, so the owner and fields are address-derived.

#include <vector>

struct Rva003A35A0Element
{
	int words[46];

	Rva003A35A0Element();
	Rva003A35A0Element(const Rva003A35A0Element &);
	~Rva003A35A0Element();
	Rva003A35A0Element &operator=(const Rva003A35A0Element &other);
};

template class _STL::vector<Rva003A35A0Element>;

struct Rva003A39C0Owner
{
	void rva003a39c0(const int *src);

	unsigned char m_bfmeHead[0x20];
	int m_bfmeCount;					// +0x20
	unsigned char m_bfmeGap[0x2c - 0x20 - 4];
	_STL::vector<Rva003A35A0Element> m_bfmeVec;	// +0x2c
};

// retail RVA 0x003A39C0
void Rva003A39C0Owner::rva003a39c0(const int *src)
{
	Rva003A35A0Element temp;

	temp.words[0] = src[0];
	temp.words[1] = src[1];
	temp.words[2] = src[2];

	m_bfmeVec.insert(m_bfmeVec.begin() + (m_bfmeCount + 2), temp);
}
