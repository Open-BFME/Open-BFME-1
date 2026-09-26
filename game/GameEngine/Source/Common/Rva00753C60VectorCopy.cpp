// cl: /DNDEBUG /MD /EHs-c-

// 0x00753C60 -- vector copy constructor of a 4-byte POD.
//
//     lea tag=[arg slot] / source->get_allocator(tag) / dest->_Vector_base(n, tag) /
//     if (last != first) memmove / finish = start + bytes
//
// Matches STLport 4.5.3 vector(const vector&) plus __copy_trivial. The empty
// allocator is returned into the source-pointer argument slot. Helpers stay
// out of line so they remain the retail calls at 0x00035724 and 0x00004AF7.

struct BfmeAllocAY
{
};

class BfmeVecBaseAY
{
public:
	BfmeVecBaseAY(unsigned int count, const BfmeAllocAY &alloc) throw();

	int *m_start;
	int *m_finish;
	int *m_end;
};

class BfmeVecAY : public BfmeVecBaseAY
{
public:
	BfmeVecAY(const BfmeVecAY &other);
	BfmeAllocAY get_allocator() const throw();
};

extern "C" __declspec(dllimport) void *__cdecl memmove(void *destination, const void *source, unsigned int bytes);

// ??0BfmeVecAY@@QAE@ABV0@@Z
BfmeVecAY::BfmeVecAY(const BfmeVecAY &other)
	: BfmeVecBaseAY((unsigned int)(other.m_finish - other.m_start), other.get_allocator())
{
	int *last = other.m_finish;
	int *first = other.m_start;
	int *result = m_start;

	m_finish = (last == first) ? result :
		(int *)((char *)memmove(result, first, (unsigned int)((char *)last - (char *)first))
			+ ((char *)last - (char *)first));
}
