// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport copy over 16-byte elements whose assignment operator
// skips the first dword (0x003B37A0, 65 B gap claimed by its shape).
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
struct Rva003B37A0Elem {
	int m_id;
	int m_a;
	bool m_flag;
	int m_b;
	Rva003B37A0Elem& operator=(const Rva003B37A0Elem& o) { m_a = o.m_a; m_flag = o.m_flag; m_b = o.m_b; return *this; }
};
template Rva003B37A0Elem* _STL::copy<Rva003B37A0Elem*, Rva003B37A0Elem*>(Rva003B37A0Elem*, Rva003B37A0Elem*, Rva003B37A0Elem*);
