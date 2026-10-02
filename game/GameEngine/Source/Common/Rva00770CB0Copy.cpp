// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: compiler-generated copy constructor for the 108-byte aggregate
// at retail 0x00770CB0. The two ten-dword tails are distinct subobjects.
#include <new>
#include <vector>
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef _STL::pair<AsciiString, unsigned int> Rva00770CB0Element;
typedef _STL::vector<Rva00770CB0Element,
	_STL::allocator<Rva00770CB0Element> > Rva00770CB0Vector;

// ILT 0x00037934 reaches this specialization at RVA 0x0076B080.
template <>
Rva00770CB0Vector::vector(const Rva00770CB0Vector &);
// This copy-only TU does not need to instantiate the vector destructor.
template <>
Rva00770CB0Vector::~vector();

class Rva00770CB0Payload
{
private:
	AsciiString m_at00;
public:
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva00770CB0Vector m_at10;
	int m_at1C[10];
	int m_at44[10];
};

Rva00770CB0Payload *Rva00770CB0CopyAnchor(
	Rva00770CB0Payload *slot, const Rva00770CB0Payload &source)
{
	return new (slot) Rva00770CB0Payload(source);
}
