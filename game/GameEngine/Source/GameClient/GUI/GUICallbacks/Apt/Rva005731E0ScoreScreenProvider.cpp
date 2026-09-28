// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Score-screen provider callback, retail 0x005731E0, 734 bytes.

#include <string.h>
#include <vector>
#include "ascii_string.h"

struct StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[ 1 ];
};

extern char Rva006A16B0Empty[];

template <> inline const char *StringBase<char>::str() const
{
	return m_data ? &m_data->data[ 0 ] : Rva006A16B0Empty;
}

// ?nullStringAI@@YAXXZ absent-from-retail
void nullStringAI();

// The lookup's value type: an AsciiString view whose copy is the call at +0x278.
class AsciiStringAI : public AsciiString
{
public:
	AsciiStringAI( const AsciiString &other )
		: AsciiString( other ) {}
	AsciiStringAI( const AsciiStringAI &other )
		: AsciiString( other ) {}
	~AsciiStringAI() {}

	StringHeader *rawDataAI() const
	{
		return *(StringHeader *const *)this;
	}

	int getLengthAI() const
	{
		return rawDataAI() ? rawDataAI()->length : 0;
	}

	const char *strAI() const
	{
		return rawDataAI() ? peekAI() : Rva006A16B0Empty;
	}

	// Retail keeps an unwind state for the lookup result with no store, so a
	// possibly-throwing call was inlined away; this null check reproduces it.
	char *peekAI() const
	{
		if( rawDataAI() == 0 )
			nullStringAI();
		return &rawDataAI()->data[ 0 ];
	}
};

class BfmeTableAI
{
public:
	AsciiStringAI bfmeLookupAI( AsciiStringAI key );
};

struct BfmeScoreScreenPlayerRow
{
	int color;
	AsciiString faction;
};

class BfmeAptScreenScoreScreen
{
public:
	void rva005731E0( int selector, char *output, bool setting );

private:
	char m_prefix[ 0x25c ];
	int m_gameType;
	char m_pad260[ 4 ];
	_STL::vector<BfmeScoreScreenPlayerRow> m_rows;
	char m_pad270[ 8 ];
	int m_opaque278[ 5 ];
	int m_slot28c;
	int m_slot290;
	int m_zero294[ 21 ];
	_STL::vector<bool> m_heroVetUpgrades;
	int m_slot2fc;
	AsciiString m_s300;
	int m_slot304;
	bool m_field308[ 8 ];
	int m_slot310;
	int m_slot314;
	int m_slot318;
	int m_slot31c;
	AsciiString m_s320;
	int m_slot324;
	int m_slot328;
	int m_slot32c;
	AsciiString m_s330;
};

extern "C" __declspec( dllimport ) int __cdecl sprintf(
	char *destination, const char *format, ... );
extern char g_aptPalantirNumberFormat[];
class GlobalData;
extern GlobalData *TheWritableGlobalData;

// ?rva005731E0@BfmeAptScreenScoreScreen@@QAEXHPAD_N@Z
void BfmeAptScreenScoreScreen::rva005731E0(
	int selector, char *output, bool setting )
{
	if( !setting )
	{
		output[ 0 ] = '0';
		output[ 1 ] = 0;
	}

	if( selector == 0 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat, m_rows.size() );
	}
	else if( selector == 1 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat,
				m_gameType == 3 || m_gameType == 2 );
	}
	else if( selector == 2 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat, m_gameType == 0 );
	}
	else if( selector == 3 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat, m_slot28c );
	}
	else if( selector == 4 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat, m_heroVetUpgrades.size() );
	}
	else if( selector == 5 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat, m_slot2fc );
	}
	else if( selector == 6 )
	{
		if( !setting )
			strcpy( output, m_s300.str() );
	}
	else if( selector == 7 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat, m_slot304 );
	}
	else if( selector == 8 )
	{
		if( !setting )
		{
			if( m_slot290 == 2 )
				strcpy( output, "_totalvictory" );
			else if( m_slot290 == 1 )
				strcpy( output, "_victory" );
			else
				strcpy( output, "_survived" );
		}
	}
	else if( selector == 9 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat,
				*(int *)( (char *)TheWritableGlobalData + 0x123c ) );
	}
	else if( selector == 10 )
	{
		if( setting )
			m_s320 = output;
		else
		{
			AsciiStringAI result = ((BfmeTableAI *)this)->bfmeLookupAI( m_s320 );
			if( result.getLengthAI() < 0xff )
				strcpy( output, result.strAI() );
		}
	}
}
