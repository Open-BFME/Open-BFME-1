// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: the seven per-instantiation routines the BitFlags INI parser
// hands each token to -- 405 bytes where the flag set fits in one word, 441 at
// three words and 459 at six.
//
// BitFlagsParseFromINI.cpp already found these: retail's parseFromINI is Zero
// Hour's parse() with the whole body of its token loop hoisted into a routine
// whose `this` is the BitFlags being filled in, taking the token and the
// addresses of the two "found" flags and returning false to break the loop.
// This file writes that body.  It is Zero Hour's loop body line for line: the
// NONE case that clears and stops, the + and - cases that reject a mix with a
// normal token and set or reset the named bit, and the normal case that clears
// once and then sets.  Three scanIndexList calls and four throws, in that
// order.
//
// The two Bool* arguments are ordered foundNormal then foundAddOrSub: the +
// case tests the FIRST and writes the SECOND, and the stack offsets only line
// up that way once the `pop edi` before the store is accounted for.
//
// EACH BODY'S NAME LIST IS ITS IDENTITY.  The list pushed to scanIndexList is
// NULL-terminated, so it can be read straight out of the binary:
//
//   0x00141320  0x012A68D8   11 names, VETERAN..AS_TOWER       weapon bonuses
//   0x001EB180  0x012AD6B0   29 names, VETERAN..ONE_RING_MODE  weapon sets
//   0x0029C7B0  0x012A9200   11 names, DEFAULT..SCRIPT_UNDERP  disabled types
//   0x00368EA0  0x012A68B0    7 names, NONE..LEVEL             bonus sources
//   0x0061C870  0x012B90E0    9 names, ZOOMED_IN..EVIL_CAMPGN  subtitle flags
//   0x00204770  0x012A6670   86 names, DESTROYED..CANCELED     object status
//   0x00128510  0x012AA068  181 names, OBSTACLE..MOVE_FOR_NOO  kind-of flags
//
// The list length is NOT the template argument.  Two of the seven lists hold
// exactly 11 names, and BitFlags<11> is one type with one s_bitNameList, so at
// most one of them can be it -- the weapon-bonus body, whose neighbours at
// 0x0013CDE0, 0x0013E8C0 and 0x00140900 are already ledgered as BitFlags<11>.
// The other list is 11 names of some wider enum.  Until a width is proven per
// body the classes keep address-derived names; what the sizes DO prove is the
// word count, which is all the codegen depends on: one word at 405 bytes,
// three at 441, six at 459.
//
// The set is the UNCHECKED one: retail has no range check in front of it, so
// the source reaches _Unchecked_set / _Unchecked_reset rather than set(), whose
// bounds test would call __stl_throw_out_of_range.
//
// The flags are an STLport bitset and only that spelling reaches the code
// retail emits -- `and ecx,0x1f / mov edx,1 / shl edx,cl` over a scalar word,
// which is _Base_bitset<1>'s _M_getword, not an indexed array.
//
// The compare goes through the import table, and the retail import is
// MSVCR71's _strcmpi, not _stricmp: the slot at 0x0135933C is _strcmpi.  The
// address is a copied DIR32, so the pair has to be told apart by reading the
// imports rather than by trusting a green build.
//
// The throw is the shape CommandButton::parseCommand already proved: BFME's
// variadic, and therefore __cdecl, INIException constructor at 0x00850600
// taking `this` as its first stack argument, then _CxxThrowException on that
// same eight-byte frame slot.  The declared copy constructor is what keeps
// MSVC from building the object and copying it into a second slot, and
// exceptions are off in the build line because retail's frames carry no
// exception record at all.

#include <bitset>

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _strcmpi( const char *left, const char *right );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	static Int scanIndexList( const char *token, const char *const *names );	// retail 0x008509E0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException( Int code, const char *msg, ... );		///< direct call to 0x00850600
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

// INI_INVALID_NAME_LIST -- BFME rebases the ErrorCode enum at 1, so Zero Hour's
// third entry is 2 here (see INI_stl.cpp).
enum { BFME_INI_INVALID_NAME_LIST = 2 };

#define BFME_INI_MIX_MESSAGE "you may not mix normal and +- ops in bitstring lists"

#define BFME_BITFLAGS_PARSE_TOKEN( NAME, NUMBITS )                                  \
class NAME                                                                          \
{                                                                                   \
public:                                                                             \
	Bool parseToken( const char *token, Bool *foundNormal, Bool *foundAddOrSub );    \
                                                                                    \
private:                                                                            \
	void clear() { m_bits.reset(); }                                                \
                                                                                    \
	static const char *const s_bitNameList[];                                       \
                                                                                    \
	_STL::bitset<NUMBITS> m_bits;                                                    \
};                                                                                  \
                                                                                    \
Bool NAME::parseToken( const char *token, Bool *foundNormal, Bool *foundAddOrSub )   \
{                                                                                   \
	if ( _strcmpi( token, "NONE" ) == 0 )                                           \
	{                                                                               \
		if ( *foundNormal || *foundAddOrSub )                                       \
			throw INIException( BFME_INI_INVALID_NAME_LIST, BFME_INI_MIX_MESSAGE ); \
		clear();                                                                    \
		return false;                                                               \
	}                                                                               \
                                                                                    \
	if ( token[ 0 ] == '+' )                                                        \
	{                                                                               \
		if ( *foundNormal )                                                         \
			throw INIException( BFME_INI_INVALID_NAME_LIST, BFME_INI_MIX_MESSAGE ); \
		m_bits._Unchecked_set( INI::scanIndexList( token + 1, s_bitNameList ) );     \
		*foundAddOrSub = true;                                                      \
	}                                                                               \
	else if ( token[ 0 ] == '-' )                                                   \
	{                                                                               \
		if ( *foundNormal )                                                         \
			throw INIException( BFME_INI_INVALID_NAME_LIST, BFME_INI_MIX_MESSAGE ); \
		m_bits._Unchecked_reset( INI::scanIndexList( token + 1, s_bitNameList ) );   \
		*foundAddOrSub = true;                                                      \
	}                                                                               \
	else                                                                            \
	{                                                                               \
		if ( *foundAddOrSub )                                                       \
			throw INIException( BFME_INI_INVALID_NAME_LIST, BFME_INI_MIX_MESSAGE ); \
		if ( !*foundNormal )                                                        \
			clear();                                                                \
		m_bits._Unchecked_set( INI::scanIndexList( token, s_bitNameList ) );         \
		*foundNormal = true;                                                        \
	}                                                                               \
                                                                                    \
	return true;                                                                    \
}

BFME_BITFLAGS_PARSE_TOKEN( Rva00141320BitFlagsParser, 11 )
BFME_BITFLAGS_PARSE_TOKEN( Rva001EB180BitFlagsParser, 29 )
BFME_BITFLAGS_PARSE_TOKEN( Rva0029C7B0BitFlagsParser, 11 )
BFME_BITFLAGS_PARSE_TOKEN( Rva00368EA0BitFlagsParser, 7 )
BFME_BITFLAGS_PARSE_TOKEN( Rva0061C870BitFlagsParser, 9 )
BFME_BITFLAGS_PARSE_TOKEN( Rva00204770BitFlagsParser, 86 )
BFME_BITFLAGS_PARSE_TOKEN( Rva00128510BitFlagsParser, 181 )
