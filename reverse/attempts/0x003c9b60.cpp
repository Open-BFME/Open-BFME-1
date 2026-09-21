// ?Rva003C9B60Parse@@YAXPAVINI@@@Z
// partial score=0.92 date=2026-09-16
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// Attempt at 0x003C9B60, the LivingWorldRegionCampaign block parser.
// Size matches retail at 261 bytes. 47 of those bytes still differ.

// Every instruction matches except one store, and that store is the whole
// remaining gap. Retail writes the new region pointer into the frame slot at
// EBP-0x14 right after the two arms of the allocation merge, at +0x7B. This
// build writes the same pointer into EBP-0x10 at +0xB6, just before the vector
// capacity test. The 4-byte shift between those two points accounts for all 47
// bytes.

// The slot choice follows from the placement. Retail parks the pointer in the
// slot the temporary-alive flag used, because the flag dies at the `test bl,1'
// two bytes earlier. This build parks it in the slot the raw allocation used,
// because that slot dies when the exception state goes to -1. Both are legal
// coalescings of a dead slot, so the slot is a symptom and the placement is the
// cause.

// Retail stores at the definition, which is what MSVC does when a local is
// address-taken. The pointer is address-taken here too, through the const
// reference that STLport's push_back binds it to, yet this compiler sinks the
// store to the one branch that reads it.

// Fifteen spellings failed to move that store on 2026-09-16. Three changed how
// push_back receives the value: by value, by const reference, and through a
// second const reference bound inside the body. Five changed where the append
// lives: straight in the parser, in a member wrapper taking the pointer by
// value, in a member wrapper taking it by const reference, in a free function
// taking the manager and the pointer, and in a member wrapper holding the
// vector in a local.

// Two more added a second pointer variable copied from the first right after
// the allocation, once plain and once as a const reference to it. Two changed
// the construct call, writing the placement new inline and then through a
// _Construct helper shaped the way STLport shapes one. Three changed
// qualifiers: `const' on the pointer, `inline' rather than `__forceinline' on
// the wrapper, and `__forceinline' on push_back itself.

// Six flag sets also failed. They were /O2, /Ox, /O1 /Ob1, /O2 /Ob2,
// /O2 /Ob1 /Oy-, and /Og /Oi /Ot /Oy /Ob1 /Gs.

// Two levers did land earlier walls and are worth keeping. Spelling the name
// temporary as `class AsciiString : private StringBase<char>' with an inline
// constructor delegating to the base made MSVC recompute the temporary's
// address with a lea rather than reuse the constructor's return in EAX. Retail
// does the same, and that closed a 4-byte size gap. Routing the append through
// a wrapper that takes the pointer by value, rather than calling push_back from
// the parser body, swapped the manager into EBP and the token into EDI to match
// retail.

// The retail body calls the four targets through their existing ILT symbols.
// The constructor and Gen003C7B10Owner::step already have verified source
// identities. The other two bodies remain anonymous, so these aliases keep
// their address-derived source names and route only to the witnessed ILTs;
// they are not semantic pins.


#include "string_base.h"

struct FieldParse;

inline void *operator new( unsigned int, void *where ) { return where; }

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

class LivingWorldRegion
{
public:
	LivingWorldRegion( const AsciiString &name );

private:
	unsigned char m_body[ 0x58 ];
};

class Gen003C7B10Owner
{
public:
	void step();
};

class Rva003C7A40Owner
{
public:
	void rva003C7A40();
};

#pragma comment(linker, "/alternatename:??0LivingWorldRegion@@QAE@ABVAsciiString@@@Z=?j_0004602e@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003C7A40@Rva003C7A40Owner@@QAEXXZ=?j_0002e88e@@YAXXZ")
#pragma comment(linker, "/alternatename:?_M_insert_overflow@?$vector@PAVLivingWorldRegion@@V?$allocator@PAVLivingWorldRegion@@@_STL@@@_STL@@IAEXPAPAVLivingWorldRegion@@ABQAV3@ABU__false_type@2@I_N@Z=?j_0001a0ff@@YAXXZ")

class LivingWorldRegionManager;

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	friend class ::LivingWorldRegionManager;

protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

public:
	void push_back( const Type &value )
	{
		if ( m_finish != m_end_of_storage )
		{
			new ( m_finish ) Type( value );
			m_finish = m_finish + 1;
		}
		else
		{
			__false_type tag;
			_M_insert_overflow( m_finish, value, tag, 1, true );
		}
	}

	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};
}

typedef _STL::vector<LivingWorldRegion *, _STL::allocator<LivingWorldRegion *> > RegionVector;

class LivingWorldRegionManager
{
public:
	__forceinline void add( LivingWorldRegion *region );

	unsigned char m_pad00[ 0x28 ];
	RegionVector m_regions;
};

class Glo012F1028Type
{
public:
	unsigned char m_pad00[ 0x28 ];
	LivingWorldRegionManager *m_regionManager;
};

extern Glo012F1028Type *Glo012F1028;

__forceinline void LivingWorldRegionManager::add( LivingWorldRegion *region )
{
	m_regions.push_back( region );
}

void Rva003C9B60Parse( INI *ini )
{
	LivingWorldRegionManager *manager = Glo012F1028->m_regionManager;

	const char *token = ini->getNextToken();

	LivingWorldRegion *region = new LivingWorldRegion( AsciiString( token ) );

	ini->initFromINI( region, (const FieldParse *)0x010EDC48 );

	( (Rva003C7A40Owner *)region )->rva003C7A40();
	( (Gen003C7B10Owner *)region )->step();

	manager->add( region );
}
