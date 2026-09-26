// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: the BannerUI UnitCategory INI field parser, retail 0x00584C30,
// 192 bytes.
//
// The FieldParse table at 0x0110B984 has two rows, HeroFilter and
// UnitCategory, and the landed parseBannerUI at 0x00584D20 hands that table to
// INI::initFromINI as BannerUI::m_fieldParseTable. Row 0x0110B994 pairs the
// string "UnitCategory" with this body, so the field names the function. The
// body sits directly above parseBannerUI in the image.
//
// It builds one twelve-byte record on the stack, fills it from the nested
// table at 0x0110B918 whose rows are Name, PluralName and Filter, and appends
// it to the STLport vector the store argument points at. The record's copy
// constructor is the landed Open2Rec5822D0 copy at 0x005822D0, which already
// models the same three members.
#include <vector>
#include "string_base.h"
#include "ascii_string.h"

class INI;

struct FieldParse
{
	const char *token;
	void (*parse)( INI *ini, void *instance, void *store, const void *userData );
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseAsciiString( INI *ini, void *instance, void *store, const void *userData );
	void initFromINI( void *what, const FieldParse *parseTable );
};

class IniParseObjectFilterShim
{
public:
	static void run( INI *ini, void *instance, void *store, const void *userData );
};

class Gen003A0410
{
public:
	Gen003A0410();

private:
	void *m_held;
};

class Open2Rec5822D0
{
public:
	Open2Rec5822D0() {}
	Open2Rec5822D0( const Open2Rec5822D0 &other );
	~Open2Rec5822D0();

	AsciiString m_at00;
	AsciiString m_at04;
	Gen003A0410 m_at08;
};

static const FieldParse theUnitCategoryFieldParse[] =
{
	{ "Name", INI::parseAsciiString, 0, 0 },
	{ "PluralName", INI::parseAsciiString, 0, 4 },
	{ "Filter", IniParseObjectFilterShim::run, 0, 8 },
	{ 0, 0, 0, 0 }
};

void parseUnitCategory( INI *ini, void *instance, void *store, const void *userData )
{
	Open2Rec5822D0 record;
	ini->initFromINI( &record, theUnitCategoryFieldParse );
	( (_STL::vector<Open2Rec5822D0> *)store )->push_back( record );
}

