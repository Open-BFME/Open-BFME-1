// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<Gen_t_003b8f80_k4>::_M_copy at 0x003B8B80,
// twin of the map-anchor bodies in RvaTreeCopy.cpp but over a set (0x14-byte
// node: 16 header + 4 key, no separate mapped type) per that file's own note
// on the 0x000BF790 shape.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

struct Gen_t_003b8f80_k4
{
	int m_key;
	bool operator<( const Gen_t_003b8f80_k4 &rhs ) const { return m_key < rhs.m_key; }
};

typedef _STL::set<Gen_t_003b8f80_k4> Rva003B8B80Set;

// retail 0x003B8B80
void BfmeTreeCopyAnchor003B8B80( Rva003B8B80Set &out, const Rva003B8B80Set &in )
{
	out = in;
}
