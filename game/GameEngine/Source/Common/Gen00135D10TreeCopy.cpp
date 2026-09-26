// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<Gen_t_009ee8e0_k4>::_M_copy at 0x00135D10,
// twin of Gen003B8B80TreeCopy.cpp / RvaTreeCopy.cpp: identical 0x14-byte set
// node instruction sequence (push 0x14 allocate) proves the set-shaped
// instantiation, not the pair<int,Gen_t_00135df0_p12cd> map also pinned here.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

struct Gen_t_009ee8e0_k4
{
	int m_key;
	bool operator<( const Gen_t_009ee8e0_k4 &rhs ) const { return m_key < rhs.m_key; }
};

typedef _STL::set<Gen_t_009ee8e0_k4> Rva00135D10Set;

// retail 0x00135D10
void BfmeTreeCopyAnchor00135D10( Rva00135D10Set &out, const Rva00135D10Set &in )
{
	out = in;
}
