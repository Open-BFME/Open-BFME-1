// stlport
// Five 73-byte __cdecl functions that pull items one at a time out of a source
// object and feed them to a sink until the sink says stop or the source runs
// dry, carrying two byte flags by address across every call:
//
//     bool a = false, b = false;
//     item = source->next( 0 );
//     while ( item ) { if ( !sink->handle( item, &b, &a ) ) break;
//                      item = source->next( 0 ); }
//
// WHAT THE BYTES SHOW.  Nothing reads ecx on entry and the `ret` is bare, so
// these are __cdecl free functions, not members.  The single `push ecx` in the
// prologue is the four bytes of locals: both flags live in it, at [entry-1] and
// [entry-2], and both are zeroed BEFORE the first source call, so they are
// initialised at declaration rather than assigned in the loop.
//
// The source call is entered with ecx = the first parameter and one pushed
// dword that the CALLEE pops -- __thiscall, one argument, returning a pointer
// (`test eax,eax`).  The sink call is entered with ecx = a different parameter
// and three pushed dwords, returning one byte (`test al,al`).  Two addresses of
// the SAME two locals are handed over on every iteration, so the sink writes
// through them and the caller keeps the values alive across iterations.
//
// THE MIDDLE PARAMETER IS NEVER READ.  The sink pointer is fetched from
// [entry+0xC], not [entry+8], which leaves a whole dword of argument space
// untouched; only the argument OFFSETS can show this, and they do.
//
// The loop is the rotated `while`: the source call appears twice, once ahead of
// the entry test and once at the bottom feeding a `jne` back to the top.  A
// `do`/`while` would have one copy and no leading test.
//
// ONE AXIS: the sink's REL32.  The source callee, both parameter offsets, both
// flag slots and the whole control flow are identical in all five rows, and the
// five sinks are five distinct addresses.
//
// The 320-bit sink at 0x00208810 is the token step of the engine's BitFlags
// parser.  It is kept beside the generated drain declarations because the
// source-side sink type is otherwise only visible through the caller's
// relocations.

#define _strcmpi _stlport_stricmp_decl
#include <bitset>
#undef _strcmpi

typedef int Int;

extern "C" __declspec( dllimport ) int __cdecl _strcmpi( const char *, const char * );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	static Int scanIndexList( const char *, const char *const * );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException( Int, const char *, ... );
	INIException( const INIException & );

private:
	Int m_code;
	const char *m_message;
};

class GenItem;

class Gen000140D8
{
public:
	__declspec( noinline ) bool handle( GenItem *, bool *, bool * );

private:
	std::bitset< 320 > m_bits;
};

__declspec( noinline ) bool Gen000140D8::handle( GenItem *item, bool *foundNormal, bool *foundAddOrSub )
{
	const char *token = reinterpret_cast< const char * >( item );
	if ( _strcmpi( token, "NONE" ) == 0 )
	{
		if ( *foundNormal || *foundAddOrSub )
			throw INIException( 2, "you may not mix normal and +- ops in bitstring lists" );
		m_bits.reset();
		return false;
	}

	if ( token[ 0 ] == '+' )
	{
		if ( *foundNormal )
			throw INIException( 2, "you may not mix normal and +- ops in bitstring lists" );
		unsigned int bitIndex = INI::scanIndexList( token + 1,
			reinterpret_cast< const char *const * >( 0x012A6918 ) );
		m_bits._Unchecked_set( bitIndex );
		*foundAddOrSub = true;
		return true;
	}

	if ( token[ 0 ] == '-' )
	{
		if ( *foundNormal )
			throw INIException( 2, "you may not mix normal and +- ops in bitstring lists" );
		unsigned int bitIndex = INI::scanIndexList( token + 1,
			reinterpret_cast< const char *const * >( 0x012A6918 ) );
		m_bits._Unchecked_reset( bitIndex );
		*foundAddOrSub = true;
		return true;
	}

	if ( *foundAddOrSub )
		throw INIException( 2, "you may not mix normal and +- ops in bitstring lists" );
	if ( !*foundNormal )
		m_bits.reset();
	unsigned int bitIndex = INI::scanIndexList( token,
		reinterpret_cast< const char *const * >( 0x012A6918 ) );
	m_bits._Unchecked_set( bitIndex );
	*foundNormal = true;
	return true;
}

// The other four sinks retain the compact declarations used by their drain
// loops.  This one is declared above so its bit storage can be recovered.

// IDENTITY IS NOT RECOVERED.  Every remaining name is derived from an
// address; the bytes do not say what is being drained or what the two flags
// mean.

class Gen008509C0
{
public:
	GenItem *next( int flags );
};

#define S3_DRAIN( NAME, ADDR )                                            \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		bool handle( GenItem *item, bool *first, bool *second );          \
	};                                                                    \
	void NAME( Gen008509C0 *source, int unused, Gen##ADDR *sink )         \
	{                                                                     \
		bool first = false;                                               \
		bool second = false;                                              \
		GenItem *item = source->next( 0 );                                \
		while( item )                                                     \
		{                                                                 \
			if( !sink->handle( item, &first, &second ) )                  \
				break;                                                    \
			item = source->next( 0 );                                     \
		}                                                                 \
	}

S3_DRAIN( Rva001EB560, 00049A2B )
S3_DRAIN( Rva0029D3D0, 00006F78 )
S3_DRAIN( Rva00369B30, 0002E893 )
S3_DRAIN( Rva0061CD10, 000341FD )

void Rva00369AD0( Gen008509C0 *source, int unused, Gen000140D8 *sink )
{
	bool first = false;
	bool second = false;
	GenItem *item = source->next( 0 );
	while( item )
	{
		if ( !sink->handle( item, &first, &second ) )
			break;
		item = source->next( 0 );
	}
}
