// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CBD90: release storage for vector-like eight-byte records.
void __cdecl operator delete(void *);

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
    static void _M_deallocate(void *, unsigned int);
};
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
            _STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
    }
}
