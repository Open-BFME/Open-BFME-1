// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// Retail 0x00753B50: the element destructor of the 12-byte list payload
// (begin, end, end-of-storage of an int buffer) reached by Gen00754850::handle
// and Gen007558B0::~Gen007558B0 through ILT 0x25C25.  Byte-identical to the
// STLport _Vector_base<int> destructor at 0x0081D920, but retail kept this
// copy for its own class (no identical-COMDAT folding).
struct Gen_t_007546f0_p12cd
{
	int *m_start;
	int *m_finish;
	int *m_end;
	~Gen_t_007546f0_p12cd();
};

Gen_t_007546f0_p12cd::~Gen_t_007546f0_p12cd()
{
	if (m_start)
		_STL::allocator<int>().deallocate(m_start, m_end - m_start);
}
