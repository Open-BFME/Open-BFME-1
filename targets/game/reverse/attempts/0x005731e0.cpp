// ?rva005731E0@BfmeAptScreenScoreScreen@@QAEXHPAD_N@Z
// partial score=0.93 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2
// stlport
// Score-screen provider callback, retail 0x005731E0, 734 bytes.

#include <string.h>
#include <vector>

struct StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[ 1 ];
};

template <typename T>
class StringBase
{
protected:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();
	StringHeader *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other );
	~AsciiString() {}
	AsciiString &operator=( const char *text );

	StringHeader *rawData() const
	{
		return m_data;
	}

	const char *str() const;
};

extern char Rva006A16B0Empty[];

const char *AsciiString::str() const
{
	return m_data ? &m_data->data[ 0 ] : Rva006A16B0Empty;
}

class AsciiStringAI : public StringBase<char>
{
public:
	AsciiStringAI( const AsciiStringAI &other )
		: StringBase<char>( other ) {}
	~AsciiStringAI() {}

	StringHeader *rawDataAI() const
	{
		return m_data;
	}
};

class BfmeTableAI
{
public:
	AsciiStringAI bfmeLookupAI( AsciiStringAI key ) throw();
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
			{
				*(int *)( output + 0 ) = *(int *)0x0110A9CC;
				*(int *)( output + 4 ) = *(int *)0x0110A9D0;
				*(int *)( output + 8 ) = *(int *)0x0110A9D4;
				*(short *)( output + 12 ) = *(short *)0x0110A9D8;
			}
			else if( m_slot290 == 1 )
			{
				*(int *)( output + 0 ) = *(int *)0x0110A9C0;
				*(int *)( output + 4 ) = *(int *)0x0110A9C4;
				*(char *)( output + 8 ) = *(char *)0x0110A9C8;
			}
			else
			{
				*(int *)( output + 0 ) = *(int *)0x0110A9B4;
				*(int *)( output + 4 ) = *(int *)0x0110A9B8;
				*(short *)( output + 8 ) = *(short *)0x0110A9BC;
			}
		}
	}
	else if( selector == 9 )
	{
		if( !setting )
			sprintf( output, g_aptPalantirNumberFormat,
				*(int *)( (char *)*(void **)0x012ED5C8 + 0x123c ) );
	}
	else if( selector == 10 )
	{
		if( setting )
			m_s320 = output;
		else
		{
			AsciiStringAI result = ((BfmeTableAI *)this)->bfmeLookupAI(
				(const AsciiStringAI &)AsciiString( m_s320 ) );
			StringHeader *data = result.rawDataAI();
			const char *text;
			if( data != 0 && data->length < 0xff )
				text = data->data;
			else
				text = Rva006A16B0Empty;
			strcpy( output, text );
		}
	}
}
