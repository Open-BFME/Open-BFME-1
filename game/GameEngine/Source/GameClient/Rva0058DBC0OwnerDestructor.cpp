// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0058DBC0 (339 bytes).  The caller at GameClient+0x460 supplies
// this subobject.  Its five string literals and the three WindowManager
// thunk calls are directly witnessed by the retail body; the owner name is
// deliberately address-derived because no semantic class identity is proven.

extern void __cdecl operator delete( void *value ) throw();

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class WindowManager
{
public:
	void _bfme_removeNamedAptGadget( const AsciiString &name );
	void removeAptObject( const AsciiString &name );
};

extern WindowManager *g_theWindowManager;
extern void j_000347d9();

typedef void (WindowManager::*WindowManagerStringMember)( const AsciiString * );

union WindowManagerStringCast
{
	void (*raw)();
	WindowManagerStringMember member;
};

static __forceinline void callWindowManagerString(
	WindowManager *manager, void (*function)(), AsciiString *name )
{
	WindowManagerStringCast cast;
	cast.raw = function;
	(manager->*cast.member)( name );
}

class Rva0058DBC0ConditionalDeleteField
{
public:
	~Rva0058DBC0ConditionalDeleteField() throw()
	{
		if( m_data )
			::operator delete( m_data );
	}

private:
	void *m_data;
};

class Rva0058DBC0DeleteField
{
public:
	~Rva0058DBC0DeleteField() throw()
	{
		::operator delete( m_data );
	}

private:
	void *m_data;
};

class Rva0058DBC0Owner
{
public:
	~Rva0058DBC0Owner();

private:
	unsigned char m_beforeFields[ 0x20 ];
	Rva0058DBC0ConditionalDeleteField m_field20;
	Rva0058DBC0DeleteField m_field24;
};

Rva0058DBC0Owner::~Rva0058DBC0Owner()
{
	if( g_theWindowManager )
	{
		{
			AsciiString name( "ResourceBar/ResourceIcon" );
			g_theWindowManager->_bfme_removeNamedAptGadget( name );
		}
		{
			AsciiString name( "RenderFactionIcon" );
			callWindowManagerString( g_theWindowManager, j_000347d9, &name );
		}
		{
			AsciiString name( "Palantir/ResourceBar/Resources/" );
			g_theWindowManager->removeAptObject( name );
		}
		{
			AsciiString name( "Palantir/ResourceBar/ResourceMultiplier/" );
			g_theWindowManager->removeAptObject( name );
		}
		{
			AsciiString name( "Palantir/ResourceBar/CommandPoints/" );
			g_theWindowManager->removeAptObject( name );
		}
	}

}
