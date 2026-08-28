// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// FILE: INIBannerType.cpp ////////////////////////////////////////////////////
//
// The BannerType block, retail 0x00584550. BFME-only; the INI block table in
// .data names it, and the parser is spelled parse<Block> like the rest of them.
//
// The store is not a global of its own: retail loads 0x012F4B70 and adds 8,
// so the lookup runs on a member at +8 of the subsystem there. That subsystem
// is TheBannerUI - its constructor at 0x005849E0 hands "TheBannerUI" to the
// name setter, and the field table this block parses with (0x0110B898) sits in
// the same literal run as that string.
//
// The name is a temporary, not a local: retail releases the AsciiString before
// it calls initFromINI, which is end-of-full-expression for an argument passed
// by const reference, not the end of the block.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "Common/AsciiString.h"

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

class BannerTypeString
{
public:
	BannerTypeString() : m_data( 0 ) {}
	BannerTypeString( const BannerTypeString &other );
	~BannerTypeString();

private:
	void *m_data;
};

// The missing-key path zeroes four dwords, and its cleanup calls a non-trivial
// destructor over the same 16-byte span; their meanings are not recoverable.
class BannerType
{
public:
	BannerType() {}
	BannerType( const BannerType &other );
	~BannerType();
	static const FieldParse m_fieldParseTable[];		// 0x0110B898

private:
	BannerTypeString m_field0;
	BannerTypeString m_field1;
	BannerTypeString m_field2;
	BannerTypeString m_field3;
};

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()( T value ) const;
	};
}

typedef _STL::hash_map<AsciiString, BannerType, rts::hash<AsciiString> > BannerTypeStore;

class BannerUI
{
public:
	unsigned char m_unmodelled_00[ 8 ];
	BannerTypeStore m_bannerTypes;						// +0x08
};

extern BannerUI *TheBannerUI;							// 0x012F4B70

// ?parseBannerType@@YAXPAVINI@@@Z
void parseBannerType( INI *ini )
{
	BannerType *type = &TheBannerUI->m_bannerTypes[ AsciiString( ini->getNextToken() ) ];

	ini->initFromINI( type, BannerType::m_fieldParseTable );
}
