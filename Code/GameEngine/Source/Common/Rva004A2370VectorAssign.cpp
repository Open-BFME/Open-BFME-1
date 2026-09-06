// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: STLport vector<S4Poly000BC2E0>::operator= at retail
// 0x004A2370, 308 bytes.  The called 0x000BC2E0 vector destructor is
// the same 0x70-element family and dispatches each element through virtual
// destructor slot zero, proving the element is polymorphic: one vptr plus
// 27 dwords of opaque payload.  The assignment body divides pointer spans by
// 0x70 with the 0x92492493 reciprocal and calls the matching 112-byte helper
// family at the retail ILTs recorded in reverse/symbols.csv.
//
// This TU instantiates only the vector member.  The element special members
// are declarations because their retail bodies are separate and the target
// assignment must not synthesize an extra local vtable or helper definitions.

#include <vector>

struct S4Poly000BC2E0
{
	int m_storage[ 27 ];
	S4Poly000BC2E0();
	S4Poly000BC2E0( const S4Poly000BC2E0 & );
	S4Poly000BC2E0 &operator=( const S4Poly000BC2E0 & );
	virtual ~S4Poly000BC2E0();
};

template class _STL::vector<S4Poly000BC2E0>;
