// cl: /DNDEBUG /MD /EHsc
//
// MainMenu.apt provider at retail 0x0051E9B0.  The MainMenu constructor at
// 0x0051F3A0 binds the callback thunk at 0x0002BC2E to this body and owns the
// provider fields at +0x25D and +0x27C.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString
{
public:
	AsciiString( const char *text ) : m_data( text ) {}
	~AsciiString() {}
	AsciiString &operator=( const char *text );

	const char *str() const
	{
		return m_data.m_data ?
			(const char *)m_data.m_data + 8 : (const char *)0x0107388B;
	}

private:
	StringBase<char> m_data;
};

class GameState
{
public:
	bool doesSaveGameExist( AsciiString filename );
};

extern GameState *TheGameState;
extern char g_bfmeJpegSingleMessage;
extern char g_bfmeJpegExtendedMessage;

class BfmeAptScreenMainMenu
{
public:
	void bfmeProvide( const char *selector, void *value, bool setting );

private:
	char m_unmodelled[ 0x25D ];
	unsigned char m_25D;
	char m_padding[ 0x1E ];
	AsciiString m_27C;
};

// ?bfmeProvide@BfmeAptScreenMainMenu@@QAEXPBDPAX_N@Z
void BfmeAptScreenMainMenu::bfmeProvide(
	const char *selector, void *value, bool setting )
{
	char *output = (char *)value;
	if( !setting )
		output[ 0 ] = 0;

	switch( (int)selector )
	{
	case 0:
		if( setting )
			m_27C = output;
		else
		{
			const char *source = m_27C.str();
			char *destination = output;
			char value;
			do
			{
				value = *source++;
				*destination++ = value;
			} while( value != 0 );
		}
		break;

	case 1:
		if( !setting )
		{
			const char *source = TheGameState->doesSaveGameExist(
				AsciiString( "00000000.sav" ) )
				? &g_bfmeJpegSingleMessage : &g_bfmeJpegExtendedMessage;
			char *destination = output;
			char value;
			do
			{
				value = *source++;
				*destination++ = value;
			} while( value != 0 );
		}
		break;

	case 3:
		if( !setting )
		{
			const char *source = m_25D
				? &g_bfmeJpegExtendedMessage : &g_bfmeJpegSingleMessage;
			char *destination = output;
			char value;
			do
			{
				value = *source++;
				*destination++ = value;
			} while( value != 0 );
		}
		break;
	}
}
