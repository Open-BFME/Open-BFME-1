// ?parseNameCountListEntry@Rva0022DA50@@SAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
// Retail 0x0022DA50, 223B: parse a name and optional count, then append the
// eight-byte entry to the native STLport list at instance+0x174. Missing
// count defaults to one. Preserve the banked address-derived identity.
// Native list::push_back fixes the old hand-spliced list's EH epilogue.
// ILT0x000402C8 reaches _Construct at0x0022D4D0, not list::insert0022D610
// (the bank had conflated those). Its79B body copies StringBase<char> and
// the count; the native _Construct instantiation below independently matches.
// The string destructor is visible here because retail calls releaseBuffer
// directly at0x00887940. Shared ascii_string.h supplies the type declaration.

typedef int Int;

extern "C" unsigned int __cdecl strlen( const char *s );
#pragma intrinsic( strlen )

#include "ascii_string.h"
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}
typedef AsciiString RetailLayoutString;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
	static Int scanInt( const char *token );
};

struct Rva0022DA50Entry
{
	Rva0022DA50Entry() : m_count( 0 ) {}

	RetailLayoutString m_name;
	Int m_count;
};

namespace _STL {
template void _Construct(Rva0022DA50Entry *, const Rva0022DA50Entry &);
}
typedef _STL::list<Rva0022DA50Entry> Rva0022DA50List;

struct Rva0022DA50Owner
{
	char m_unreconstructed[ 0x174 ];
	Rva0022DA50List m_entries;
};

class Rva0022DA50
{
public:
	static void parseNameCountListEntry( register INI *ini, void *instance, void *store, const void *userData );
};

// ?parseNameCountListEntry@Rva0022DA50@@SAXPAVINI@@PAX1PBX@Z
void Rva0022DA50::parseNameCountListEntry( register INI *ini, void *instance, void *, const void * )
{
	const char *name;
	const char *num;
	Int count;
	Rva0022DA50Owner *self = (Rva0022DA50Owner *)instance;
	register INI *cursor = ini;
	name = cursor->getNextToken();
	num = cursor->getNextTokenOrNull();
	count = num ? INI::scanInt( num ) : 1;
	Rva0022DA50Entry entry;
	((StringBase<char> *)&entry.m_name)->set( name, name ? (int)strlen( name ) : 0 );
	entry.m_count = count;
	self->m_entries.push_back( entry );
}
