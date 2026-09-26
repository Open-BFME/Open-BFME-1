// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x002E4470, 301 bytes through the `ret 0x10` at +0x12A, including the
// catch(...) funclet at +0xE6 (it returns the continuation +0xEC).  Ghidra split
// it into the try body, that funclet and the tail at +0xF1.  It runs a Lua
// buffer on the state at +0xC with the context parked at +0x78, naming the
// chunk after the final override of the context's template, and returns the
// first stack result as a string.  Its only caller (0x00765FB0, through an ILT)
// is itself unnamed, so the names keep the address.  The named status local is
// what makes retail test the lua_dobuffer result against the zero held in EBX.
#include <string.h>
#include "ascii_string.h"

typedef struct lua_State lua_State;

extern "C"
{
	void __cdecl lua_settop( lua_State *L, int idx );
	int __cdecl lua_dobuffer( lua_State *L, const char *buff, unsigned long size, const char *name );
	int __cdecl lua_gettop( lua_State *L );
	const char *__cdecl lua_tostring( lua_State *L, int idx );
}

class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}
private:
	void *m_vptr;
	Overridable *m_nextOverride;
};

struct Rva002E4470Template : public Overridable
{
	char m_unmodelled08[ 0x18 ];
	const char *m_nameText;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->( void ) const
	{
		if( !m_overridable )
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
private:
	const Overridable *m_overridable;
};

struct Rva002E4470Source
{
	char m_unmodelled00[ 4 ];
	OVERRIDE<Rva002E4470Template> m_template;
};

struct Rva002E4470Context
{
	char m_unmodelled00[ 0xC ];
	Rva002E4470Source *m_source;
};

class Rva002E4470Owner
{
public:
	AsciiString run( const char *buffer, unsigned long size, Rva002E4470Context *context );
private:
	char m_unmodelled00[ 0xC ];
	lua_State *m_L;
	char m_unmodelled10[ 0x68 ];
	Rva002E4470Context *m_context78;
};

AsciiString Rva002E4470Owner::run( const char *buffer, unsigned long size, Rva002E4470Context *context )
{
	m_context78 = context;
	AsciiString result;
	try
	{
		lua_settop( m_L, 0 );
		const char *name = context->m_source->m_template->m_nameText;
		int status = lua_dobuffer( m_L, buffer, size, name ? name + 8 : "" );
		if( status == 0 && lua_gettop( m_L ) > 0 )
		{
			const char *text = lua_tostring( m_L, 1 );
			( (StringBase<char> *)&result )->set( text, text ? strlen( text ) : 0 );
		}
		lua_settop( m_L, 0 );
	}
	catch( ... )
	{
	}
	m_context78 = 0;
	return result;
}
