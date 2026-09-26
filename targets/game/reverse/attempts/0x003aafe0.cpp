// ??0?$vector@UGen_t_003aafe0@@V?$allocator@UGen_t_003aafe0@@@_STL@@@_STL@@QAE@ABV01@@Z
// partial score=0.63 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x003AAFE0 copies a vector whose elements are a 16-byte record: an
// AsciiString-like field at +0 (copied through the ICF-shared GameSpyGroupRoom
// copy constructor, same as Rva000F6C10Value in Rva000F1E00HashResize.cpp) and
// three plain dwords at +4/+8/+c.  Matching the register allocation (edi=other,
// ebp=this) takes the template-instantiation shape used by
// BfmeGen003A8910VectorCopy.cpp (_STLP_NO_EXCEPTIONS + <vector>) rather than
// the manually declared _Vector_base used by Rva003AADF0VectorCopy.cpp, which
// compiles the empty-vector early-out into a separate merged tail.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Gen_t_003aafe0Str
{
public:
	Gen_t_003aafe0Str(const Gen_t_003aafe0Str &other);
	~Gen_t_003aafe0Str(void);

private:
	char *m_bfmeData;
};

#pragma comment(linker, "/alternatename:??0Gen_t_003aafe0Str@@QAE@ABV0@@Z=??0GameSpyGroupRoom@@QAE@ABV0@@Z")

struct Gen_t_003aafe0
{
	Gen_t_003aafe0Str m_bfmeStr;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

template _STL::vector<Gen_t_003aafe0, _STL::allocator<Gen_t_003aafe0> >::vector(
	const _STL::vector<Gen_t_003aafe0, _STL::allocator<Gen_t_003aafe0> > &);
