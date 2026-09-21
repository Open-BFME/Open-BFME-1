// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// partial score=0.08 date=2026-09-21
// stlport
// ??0Rva00900FF0VecOfVec@@QAE@ABV0@@Z -- copy constructor of the
// vector<basic_string<char>>-shaped container witnessed by
// Rva00900E40Constructor.cpp (base ctor at retail 0x008FF3E0, already
// matched via gen_small/tgrid_122.cpp's vec_p12cd instantiation). Each
// inner element is a 12-byte {start,finish,endOfStorage} string buffer
// (no SSO) matching stlport_narrow_string_reserve.cpp's allocator split.

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(void *dest, const void *src, unsigned int count);

struct Gen_t_008ff3e0_p12cd
{
	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

namespace _STL
{

void *__cdecl vectorLargeAllocate(unsigned int bytes);		// retail 0x00881F30
void *__cdecl vectorSmallAllocate(unsigned int bytes);		// retail 0x0082E540

template <class T>
class allocator
{
};

template <class T, class Alloc>
class _Vector_base
{
public:
	_Vector_base(unsigned int n, const Alloc &a);

	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

}

class Rva00900FF0VecOfVec
	: public _STL::_Vector_base<Gen_t_008ff3e0_p12cd, _STL::allocator<Gen_t_008ff3e0_p12cd> >
{
	typedef _STL::allocator<Gen_t_008ff3e0_p12cd> AllocT;
	typedef _STL::_Vector_base<Gen_t_008ff3e0_p12cd, AllocT> BaseT;

public:
	Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec &source);

	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	AllocT get_allocator() const { return *(AllocT *)&m_endOfStorage; }
};

Rva00900FF0VecOfVec::Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec &source)
	: BaseT(source.size(), source.get_allocator())
{
	Gen_t_008ff3e0_p12cd *destIter = m_start;
	Gen_t_008ff3e0_p12cd *srcIter = source.m_start;

	while (srcIter != source.m_finish)
	{
		destIter->m_start = 0;
		destIter->m_finish = 0;
		destIter->m_endOfStorage = 0;

		unsigned int length = (unsigned int)(srcIter->m_finish - srcIter->m_start);
		unsigned int capacity = length + 1;

		char *buffer;
		if (capacity <= length || capacity == 0)
		{
			buffer = 0;
		}
		else if (capacity <= 128)
		{
			buffer = (char *)_STL::vectorSmallAllocate(capacity);
		}
		else
		{
			buffer = (char *)_STL::vectorLargeAllocate(capacity);
		}

		destIter->m_start = buffer;
		destIter->m_finish = buffer;
		destIter->m_endOfStorage = buffer + capacity;

		if (srcIter->m_finish != srcIter->m_start)
			buffer = (char *)BfmeMemMove(buffer, srcIter->m_start, length);

		buffer = buffer + length;
		destIter->m_finish = buffer;
		*buffer = 0;

		++destIter;
		++srcIter;
		m_finish = destIter;
	}
}
