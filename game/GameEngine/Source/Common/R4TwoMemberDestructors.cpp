// Two-member destructors use the ledger's string and container callees.
struct Gen00196F30;
struct Gen_t_002237f0_p4pod;
struct Gen_t_0037b4d0_p4pod;
struct Gen_t_002360c0_k4;

template <class Char>
class StringBase
{
public:
    __forceinline ~StringBase() { releaseBuffer(); }
private:
    void releaseBuffer();
    Char *m_buffer;
};

namespace _STL
{
template <class T> class allocator;
template <class T> struct less;
template <class T> struct _Select1st;
template <class T> struct _Identity;
template <class First, class Second> struct pair;

template <class T, class Allocator>
class vector
{
public:
    ~vector();
private:
    char m_body[0xC];
};

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
class _Rb_tree
{
public:
    ~_Rb_tree();
private:
    char m_body[0xC];
};
}

typedef StringBase<char> Rva00887940String;
typedef StringBase<unsigned short> Rva008881D0String;
typedef _STL::vector<Gen00196F30, _STL::allocator<Gen00196F30> > Rva00196F30Vector;
typedef _STL::pair<const int, Gen_t_002237f0_p4pod> Rva002237F0Pair;
typedef _STL::pair<const int, Gen_t_0037b4d0_p4pod> Rva0037B4D0Pair;
typedef _STL::_Rb_tree<int, Rva002237F0Pair, _STL::_Select1st<Rva002237F0Pair>,
    _STL::less<int>, _STL::allocator<Rva002237F0Pair> > Rva002237F0Tree;
typedef _STL::_Rb_tree<int, Rva0037B4D0Pair, _STL::_Select1st<Rva0037B4D0Pair>,
    _STL::less<int>, _STL::allocator<Rva0037B4D0Pair> > Rva0037B4D0Tree;
typedef _STL::_Rb_tree<Gen_t_002360c0_k4, Gen_t_002360c0_k4,
    _STL::_Identity<Gen_t_002360c0_k4>, _STL::less<Gen_t_002360c0_k4>,
    _STL::allocator<Gen_t_002360c0_k4> > Rva002360C0Tree;

#define R4_TWO_MEMBER_DTOR( NAME, LEAD, M1, M2 )                              \
	struct NAME                                                               \
	{                                                                         \
		char m_lead[ LEAD ];                                                  \
		M1 m_first;                                                           \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

#define R4_TWO_MEMBER_DTOR_HEAD( NAME, M1, M2 )                               \
	struct NAME                                                               \
	{                                                                         \
		M1 m_first;                                                           \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}


R4_TWO_MEMBER_DTOR( Rva00072490, 0x28, Rva008881D0String, Rva00887940String )
R4_TWO_MEMBER_DTOR( Rva001976F0, 4, Rva00196F30Vector, Rva00196F30Vector )
R4_TWO_MEMBER_DTOR( Rva0037B990, 0x14, Rva002237F0Tree, Rva0037B4D0Tree )
R4_TWO_MEMBER_DTOR( Rva00385F50, 4, Rva00887940String, Rva00887940String )
R4_TWO_MEMBER_DTOR( Rva0048C270, 4, Rva00887940String, Rva00887940String )
R4_TWO_MEMBER_DTOR( Rva00591890, 0x10, Rva002360C0Tree, Rva002360C0Tree )
R4_TWO_MEMBER_DTOR( Rva00740C80, 0xAC, Rva00887940String, Rva00887940String )
