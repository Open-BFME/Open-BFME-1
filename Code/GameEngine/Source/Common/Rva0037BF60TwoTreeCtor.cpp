// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: constructor taking (int, int), retail 0x0037BF60, 161 bytes.
// Stores the two arguments, zero-initializes a byte, a short, and an int,
// then default-constructs two STLport _Rb_tree members back to back -- each
// allocates a 24-byte header node (16 header + 8 value) through
// __node_alloc::_M_allocate and self-links it (parent = 0, left = right =
// the header itself, the classic empty red-black tree), finally zeroing two
// trailing int members.  The key/value types are only known to total 8
// bytes, so the tree element carries an address-derived tag; owning class
// and field 0x28 (left untouched by this body) are unidentified.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

struct Rva0037BF60Less
{
	bool operator()( int a, int b ) const { return a < b; }
};

typedef _STL::pair<const int, int> Rva0037BF60Elem;

typedef _STL::_Rb_tree<int, Rva0037BF60Elem, _STL::_Select1st<Rva0037BF60Elem>,
	Rva0037BF60Less, _STL::allocator<Rva0037BF60Elem> > Rva0037BF60Tree;

class Rva0037BF60Owner
{
public:
	Rva0037BF60Owner( int a, int b );
private:
	int m_f0;
	int m_f4;
	int m_f8;
	short m_fc;
	int m_f10;
	Rva0037BF60Tree m_tree1;
	Rva0037BF60Tree m_tree2;
	int m_f2c;
	int m_f30;
};

Rva0037BF60Owner::Rva0037BF60Owner( int a, int b ) :
	m_f0( a ),
	m_f4( b ),
	m_f8( 0 ),
	m_fc( 0 ),
	m_f10( 0 )
{
	m_f2c = 0;
	m_f30 = 0;
}
