// ?d_00591d60@@YAXXZ
// partial score=0.45 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

class WindowManager
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30( void *value ) = 0;
	void removeAptObject( const AsciiString &name );
};

extern WindowManager *TheWindowManager;
extern WindowManager *g_theWindowManager;
extern void j_0001e277();
extern void j_00025464();

typedef void (WindowManager::*RemoveNameMember)( const AsciiString * );

union RemoveNameCast
{
	void (*raw)();
	RemoveNameMember member;
};

static __forceinline void removeName( WindowManager *manager,
	void (*function)(), AsciiString *name )
{
	RemoveNameCast cast;
	cast.raw = function;
	(manager->*cast.member)( name );
}

namespace _STL
{
	template <int Threads, int Instance> class __node_alloc
	{
	public:
		static void _M_deallocate( void *block, unsigned int bytes );
	};
}

struct Rva00591D60Node
{
	Rva00591D60Node *m_next;
	Rva00591D60Node *m_prev;
	char m_value[12];
};

class Rva00591D60GameClientMember
{
public:
	~Rva00591D60GameClientMember();

private:
	char m_prefix[4];
	Rva00591D60Node *m_header;
	char m_padding[0x19c];
	void *m_item;
};

Rva00591D60GameClientMember::~Rva00591D60GameClientMember()
{
	Rva00591D60GameClientMember *self = this;
	void *empty = 0;
	if ( self->m_item != empty )
	{
		TheWindowManager->slot30( self->m_item );
	}

	if ( g_theWindowManager != empty )
	{
		if ( self->m_item != empty )
		{
			AsciiString name( "Palantir/HeroSelectUI/SelectAllHeroesBttn/" );
			removeName( g_theWindowManager, j_0001e277, &name );
		}

		int index = 0;
		do
		{
			++index;
			AsciiString name;
			name.format( AsciiString( "Palantir/HeroSelectUI/Hero%d/" ), index );
			removeName( g_theWindowManager, j_0001e277, &name );
		} while ( index < 16 );

		AsciiString name( "AptPalantir::OnBttnSelectAllHeroes" );
		removeName( g_theWindowManager, j_00025464, &name );
	}

	Rva00591D60Node *node = self->m_header->m_next;
	if ( node != self->m_header )
	{
		do
		{
			Rva00591D60Node *next = node->m_next;
			_STL::__node_alloc<true, 0>::_M_deallocate( node, 0x14 );
			node = next;
		} while ( node != self->m_header );
	}
	self->m_header->m_next = self->m_header;
	self->m_header->m_prev = self->m_header;
	if ( self->m_header != empty )
		_STL::__node_alloc<true, 0>::_M_deallocate( self->m_header, 0x14 );
}
