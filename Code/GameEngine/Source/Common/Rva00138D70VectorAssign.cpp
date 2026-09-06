// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: STLport vector<S4Poly00136170>::operator= at retail 0x00138D70.
// Retail proves a 0x5C element stride and the same clear ILT as the matched
// polymorphic vector destructor at 0x00136170.  The helper calls and their
// exact retail bodies are recorded in reverse/symbols.csv after decode_calls.
// This declaration follows the existing S4VectorDestructors.cpp stand-in for
// the clear specialization: 22 dwords plus a virtual destructor gives 0x5C.
// All element special members remain declared out of line.  The assignment TU
// must not synthesize their bodies or a local vtable when it only instantiates
// the vector member function.

#include <vector>

struct S4Poly00136170
{
	int m_storage[ 22 ];
	S4Poly00136170();
	S4Poly00136170( const S4Poly00136170 & );
	S4Poly00136170 &operator=( const S4Poly00136170 & );
	virtual ~S4Poly00136170();
};

template class _STL::vector<S4Poly00136170>;
