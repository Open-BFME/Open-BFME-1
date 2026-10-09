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
};

extern WindowManager *g_rva012F19E8WindowManager;
extern void j_000347d9();

// The WindowManager members this destructor calls are reached through
// incremental-link thunks in retail: the call at 0x0058DBD4 goes to
// 0x000447B31, which jumps to the matched row
// ?invoke@Rva0046B2A0@@QAEXXZ, and the three calls at 0x0058DBC0+0xB4,
// +0xE4 and +0x114 go to 0x00041E277, which jumps to
// ?invoke@Rva0046DE10@@QAEXXZ (both in
// game/GameEngine/Source/Common/MemberOffsetTailThunks.cpp).  Each of those
// bodies adds its receiver's offset to ecx and jumps on, so the callers push
// the AsciiString* and load the manager into ecx themselves, which is what the
// calls below spell: the ledger's zero-argument __thiscall members are called
// with the pointer retail pushes.
class Rva0046B2A0
{
public:
	void invoke();
};

class Rva0046DE10
{
public:
	void invoke();
};

typedef void (WindowManager::*WindowManagerStringMember)( const AsciiString * );

union WindowManagerStringCast
{
	void (*cdeclCall)();
	void (Rva0046B2A0::*b2a0Member)();
	void (Rva0046DE10::*de10Member)();
	WindowManagerStringMember member;
};

static __forceinline void callWindowManagerString(
	WindowManager *manager, void (*function)(), AsciiString *name )
{
	WindowManagerStringCast cast;
	cast.cdeclCall = function;
	(manager->*cast.member)( name );
}

// MSVC 7.1 refuses to spell __thiscall on a function POINTER (error C4234), so
// the two thunk rows are handed over as the member-function pointers the
// ledger's `void invoke()` names really are and retyped through the union
// above.  A member-function pointer variable holds the member's address, so
// the call the union makes is the very call retail makes.
static __forceinline void callWindowManagerInvoke(
	WindowManager *manager, void (Rva0046B2A0::*function)(), AsciiString *name )
{
	WindowManagerStringCast cast;
	cast.b2a0Member = function;
	(manager->*cast.member)( name );
}

static __forceinline void callWindowManagerInvoke(
	WindowManager *manager, void (Rva0046DE10::*function)(), AsciiString *name )
{
	WindowManagerStringCast cast;
	cast.de10Member = function;
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
	if( g_rva012F19E8WindowManager )
	{
		{
			AsciiString name( "ResourceBar/ResourceIcon" );
			callWindowManagerInvoke( g_rva012F19E8WindowManager, &Rva0046B2A0::invoke, &name );
		}
		{
			AsciiString name( "RenderFactionIcon" );
			callWindowManagerString( g_rva012F19E8WindowManager, j_000347d9, &name );
		}
		{
			AsciiString name( "Palantir/ResourceBar/Resources/" );
			callWindowManagerInvoke( g_rva012F19E8WindowManager, &Rva0046DE10::invoke, &name );
		}
		{
			AsciiString name( "Palantir/ResourceBar/ResourceMultiplier/" );
			callWindowManagerInvoke( g_rva012F19E8WindowManager, &Rva0046DE10::invoke, &name );
		}
		{
			AsciiString name( "Palantir/ResourceBar/CommandPoints/" );
			callWindowManagerInvoke( g_rva012F19E8WindowManager, &Rva0046DE10::invoke, &name );
		}
	}

}
