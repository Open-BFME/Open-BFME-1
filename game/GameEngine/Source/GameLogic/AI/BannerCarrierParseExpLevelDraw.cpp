// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oi /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/stringinline
// stlport
//
// The BannerCarrierUpdateModuleData field table at 0x00CBBD38 maps
// ExpLevelDraw to the ILT thunk at 0x00046146, which enters retail
// 0x00284C80.  The adjacent table fields and the matched BannerCarrier
// module-data methods independently establish the owner.

template <typename T> class StringBase
{
protected:
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
	AsciiString &operator=( const char *text );
};

extern "C" int __cdecl strcmp( const char *left, const char *right );

#include "Common/INIException.h"

class INI
{
public:
	const char *getNextToken( const char *separators );
	const char *getNextTokenOrNull( const char *separators );
	const char *getSepsColon() const { return m_sepsColon; }
	const char *getSepsQuote() const { return m_sepsQuote; }

private:
	unsigned char m_prefix[ 0x41C ];
	const char *m_sepsColon;
	const char *m_sepsQuote;
};

class Rva002E7E00Owner
{
public:
	void parse( AsciiString text );

private:
	unsigned char m_fields[ 0x28 ];
};

class Rva00283DF0ExpLevelDrawEntry
{
public:
	Rva00283DF0ExpLevelDrawEntry();

	AsciiString m_unitType;
	unsigned int m_field04;
	Rva002E7E00Owner m_modelState;
	AsciiString m_locomotor;
};

#pragma comment(linker, "/alternatename:??0Rva00283DF0ExpLevelDrawEntry@@QAE@XZ=?j_00002239@@YAXXZ")

struct Gen_t_00284a20_p4pod
{
	Rva00283DF0ExpLevelDrawEntry *m_entry;
};

#include <vector>

typedef _STL::vector<Gen_t_00284a20_p4pod> ExpLevelDrawVector;

void parseBannerCarrierExpLevelDraw( INI *ini, void *instance, void *store,
	const void *userData )
{
	Rva00283DF0ExpLevelDrawEntry *entry =
		new Rva00283DF0ExpLevelDrawEntry;
	Gen_t_00284a20_p4pod slot;
	slot.m_entry = entry;

	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "UnitType" ) != 0 )
		throw INIException( 3, "UnitType expected" );

	entry->m_unitType = ini->getNextToken( ini->getSepsColon() );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token != 0 && strcmp( token, "Locomotor" ) == 0 )
	{
		const char *locomotor = ini->getNextToken( ini->getSepsColon() );
		if ( locomotor != 0 )
			entry->m_locomotor = locomotor;
		token = ini->getNextTokenOrNull( ini->getSepsColon() );
	}

	if ( token == 0 || strcmp( token, "ModelState" ) != 0 )
		throw INIException( 3, "'ModelState' expected" );

	entry->m_modelState.parse(
		AsciiString( ini->getNextToken( ini->getSepsQuote() ) ) );

	( (ExpLevelDrawVector *)store )->push_back( slot );
}
