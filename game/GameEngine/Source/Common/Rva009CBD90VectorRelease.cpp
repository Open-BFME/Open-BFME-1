// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CBD90: release storage for vector-like eight-byte records.
void __cdecl operator delete(void *);

namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}

struct Rva009CBD90Element
{
    char m_bytes[8];
};

class Rva009CBD90Vector
{
public:
    ~Rva009CBD90Vector();

private:
    Rva009CBD90Element *m_start;
    Rva009CBD90Element *m_finish;
    Rva009CBD90Element *m_end;
};

Rva009CBD90Vector::~Rva009CBD90Vector()
{
    if (m_start != 0)
    {
        unsigned int bytes = (unsigned int)(m_end - m_start) * sizeof(Rva009CBD90Element);
        if (bytes > 0x80)
            ::operator delete(m_start);
        else
            _STL::nodePoolDeallocate(m_start, bytes);
    }
}
