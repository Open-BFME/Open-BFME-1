// carved dump placeholder: d_00770270
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Carved body at retail 0x00770270. Destroys each 0x38-byte element's three
// BFMERetailAsciiString members (retail calls releaseBuffer directly, in
// reverse-declaration order 0x08, 0x04, 0x00 -- the compiler inlined the
// element's own destructor), then runs STLport's two-arm _Vector_base
// deallocate: the proven small-block node allocator (_M_deallocate) for a
// span at or under 0x80 bytes, else operator delete. Caller is the proven
// ~Gen_t_00776240_p128pod (Gen_t_00776240Destructor.cpp), whose
// BFMERetailAsciiString shim is reused verbatim here.

#define _STLP_USE_STATIC_LIB
#include <vector>

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

struct Rva00770270Elem
{
	BFMERetailAsciiString m_str0;
	BFMERetailAsciiString m_str4;
	BFMERetailAsciiString m_str8;
	char m_pad[0x38 - 0xc];
};

template class _STL::vector<Rva00770270Elem>;
