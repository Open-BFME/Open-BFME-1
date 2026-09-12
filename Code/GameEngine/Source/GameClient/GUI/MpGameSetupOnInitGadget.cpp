// cl: /O2 /DNDEBUG /MD /EHsc-
// MpGameSetup gadget initialization callback, retail 0x00525AB0.

extern "C" int __cdecl strcmp( const char *left, const char *right );

class WinInstanceData;

class GameWindow
{
public:
	int winSetTooltipFunc(
		void (*tooltip)(GameWindow *, WinInstanceData *, unsigned int) );
};

typedef void (*GameWinTooltipFunc)(
	GameWindow *, WinInstanceData *, unsigned int );

void GadgetComboBoxReset( GameWindow *window );
GameWindow *GadgetComboBoxGetListBox( GameWindow *window );
void GadgetListBoxSetColumnWidths( GameWindow *window, int count, int *widths );
const char *bfmePathLeafAfterMarker( const char *path );

extern "C" __declspec( dllimport ) int __cdecl bfmeScanDYG(
	const char *source, const char *format, void *output );

extern char g_aptPalantirNumberFormat[];

class Gen_004b5a80
{
public:
	void *m( int value );

private:
	int m_value;
};

class MpGameSetup
{
public:
	void _bfme_onInitGadget(
		const char *name, void *argument, GameWindow *window );

private:
	unsigned char m_unmodelled[ 0x68 ];
	GameWindow *m_player[ 8 ];
	Gen_004b5a80 m_color[ 8 ];
	GameWindow *m_team[ 8 ];
	GameWindow *m_playerTemplate[ 8 ];
	GameWindow *m_readyButton[ 8 ];
	GameWindow *m_mapList;
	unsigned char m_unmodelled10c[ 0xc ];
	GameWindow *m_mapType;
	GameWindow *m_gameType;
	unsigned char m_mapListReady;
};

// ?_bfme_onInitGadget@MpGameSetup@@QAEXPBDPAXPAVGameWindow@@@Z
void MpGameSetup::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window )
{
	if( window == 0 )
		return;

	if( strcmp( name, "MapList" ) == 0 )
	{
		m_mapList = window;
		if( !( m_mapListReady & 1 ) )
			return;

		int widths[ 2 ] = { 10, 90 };
		GadgetListBoxSetColumnWidths( window, 2, widths );
		return;
	}

	if( strcmp( name, "MpGameSetup::GameType" ) == 0 )
	{
		m_gameType = window;
		return;
	}

	if( strcmp( name, "MpGameSetup::MapType" ) == 0 )
	{
		m_mapType = window;
		return;
	}

	unsigned int index;
	if( bfmeScanDYG( name, g_aptPalantirNumberFormat, &index ) != 1 || index > 8 )
		return;

	const char *leaf = bfmePathLeafAfterMarker( name );
	if( strcmp( leaf, "Player" ) == 0 )
	{
		GadgetComboBoxReset( window );
		m_player[ index ] = window;
		GadgetComboBoxGetListBox( window )->winSetTooltipFunc(
			(GameWinTooltipFunc)0x0042D727 );
		return;
	}

	if( strcmp( leaf, "PlayerTemplate" ) == 0 )
	{
		GadgetComboBoxReset( window );
		m_playerTemplate[ index ] = window;
		return;
	}

	if( strcmp( leaf, "Team" ) == 0 )
	{
		GadgetComboBoxReset( window );
		m_team[ index ] = window;
		return;
	}

	if( strcmp( leaf, "Color" ) == 0 )
	{
		GadgetComboBoxReset( window );
		m_color[ index ].m( (int)window );
		return;
	}

	if( strcmp( leaf, "ReadyButton" ) == 0 )
		m_readyButton[ index ] = window;
}
