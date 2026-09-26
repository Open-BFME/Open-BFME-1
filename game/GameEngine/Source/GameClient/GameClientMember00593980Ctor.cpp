// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Constructor at retail RVA 0x00593980.  Its only call xref is the ILT at
// 0x00030283, used by GameClient::GameClient at 0x00597FC0 with the receiver
// GameClient + 0x154.  The paired destructor at 0x00591890 proves that the
// members at +0x10 and +0x1C are two instances of the same STLport red-black
// tree type.  Their 53-byte _M_erase helper frees 0x14-byte nodes without a key
// destructor call, proving that the four-byte key is POD.  No higher-level name
// for this owned GameClient member is known.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

struct Rva00593980Key
{
	int m_value;
};

bool operator<( const Rva00593980Key &a, const Rva00593980Key &b );

typedef _STL::_Rb_tree<
	Rva00593980Key,
	Rva00593980Key,
	_STL::_Identity<Rva00593980Key>,
	_STL::less<Rva00593980Key>,
	_STL::allocator<Rva00593980Key> > Rva00593980SetTree;

class Rva00593980GameClientMember
{
public:
	Rva00593980GameClientMember();

private:
	unsigned int m_value00;
	bool m_flag04;
	unsigned char m_padding05[3];
	unsigned int m_value08;
	unsigned int m_value0C;
	Rva00593980SetTree m_firstSet;
	Rva00593980SetTree m_secondSet;
};

Rva00593980GameClientMember::Rva00593980GameClientMember()
	: m_value00( 0 ),
	  m_flag04( false ),
	  m_value08( 0 ),
	  m_value0C( 0 )
{
}
