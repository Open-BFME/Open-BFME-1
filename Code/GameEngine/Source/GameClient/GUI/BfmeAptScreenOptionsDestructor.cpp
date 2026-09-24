#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// BfmeAptScreenOptions destructor, retail 0x0055E320 (255 bytes).
// The Options.apt constructor installs vtables 0x0110912C and 0x01109128,
// and AptOptions::InitGadgets references this destructor's cleanup path.

#include "ascii_string.h"

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

void _bfme_closeAptScreen( const AsciiString &name );

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

class OptionPreferences
{
public:
	virtual ~OptionPreferences();

private:
	char m_unmodelled[ 0x10 ];
};

class Gen_0042E7C0
{
public:
	void bfmeSet( int first, int second, int third );
};

class Shell
{
public:
	void pop();
};

class __declspec(novtable) __multiple_inheritance BfmeAptScreenOptions
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~BfmeAptScreenOptions();

private:
	char m_unmodelled[ 0x3C ];
	int m_field258;
	int m_field25C;
	OptionPreferences m_options;
	int m_fields274[ 4 ];
	int m_fields284[ 5 ];
	char m_padding298[ 4 ];
	int m_fields29C[ 2 ];
	char m_padding2A4[ 4 ];
	int m_fields2A8[ 24 ];
	bool m_field308;
	char m_padding309[ 3 ];
	int m_field30C;
};

BfmeAptScreenOptions::~BfmeAptScreenOptions()
{
	*(const void ***)( (char *)this ) = (const void **)0x0110912C;
	*(const void ***)( (char *)this + 0x218 ) = (const void **)0x01109128;

	if( *(void **)0x012F4AD4 == this )
	{
		*(void **)0x012F4AD4 = 0;
		{
			BFMERetailAsciiString name( "AptOptions::InitGadgets" );
			_bfme_closeAptScreen( reinterpret_cast<const AsciiString &>( name ) );
		}

		if( m_field308 )
		{
			(*(Gen_0042E7C0 **)0x012F1464)->bfmeSet(
				m_fields274[ 0 ], m_fields274[ 1 ], m_fields274[ 2 ] );
		}

		void *menu = *(void **)0x012F4B40;
		if( menu != 0 && *(unsigned char *)( (char *)menu + 0x254 ) )
		{
			char *shell = (char *)*(volatile void **)0x012F4B58;
			if( shell != 0 )
			{
				shell[ 0x50 ] = 1;
				((Shell *)*(volatile Shell **)0x012F4B58)->pop();
			}
		}
	}
}
