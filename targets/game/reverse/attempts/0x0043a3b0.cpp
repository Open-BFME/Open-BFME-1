// ?parseFontFileName@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.990147783 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "string_base.h"
#include "ascii_string.h"

class INI
{
public:
	AsciiString getNextAsciiString();
};

class Open2Rec439370
{
public:
	Open2Rec439370() {}
	Open2Rec439370( const Open2Rec439370 &other );

	AsciiString m_at00;
	AsciiString m_at04;
};

#include <list>

class GlobalLanguage
{
public:
	static void parseFontFileName( INI *ini, void *instance, void *store, const void *userData );

	unsigned char m_unmodelled[ 0x134 ];
	_STL::list<Open2Rec439370, _STL::allocator<Open2Rec439370> > *m_localFonts;
};

void GlobalLanguage::parseFontFileName( INI *ini, void *instance, void *store, const void *userData )
{
	GlobalLanguage *self = (GlobalLanguage *)instance;
	AsciiString token = ini->getNextAsciiString();
	Open2Rec439370 entry;
	entry.m_at00.set( token );
	self->m_localFonts->push_back( entry );
}

// Native STLport list resolves the FS restore / EBX epilogue mismatch.
// Two non-relocation bytes remain: entry address uses EAX instead of EDX
// at +0x76/+0x7a. Visible noinline landed copy constructor was neutral.
