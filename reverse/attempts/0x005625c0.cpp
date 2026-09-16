// ?d_005625c0@@YAXXZ
// partial score=0.996 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenOptions::_bfme_onInitGadget, retail 0x005625C0, 2797 bytes.
// The matched Options constructor at 0x00563370 pushes the selector string
// "AptOptions::InitGadgets" at 0x005636AF and loads this body's ILT thunk, so
// the constructor names the body. Apt calls the handler once per gadget with
// the gadget name, the movie, and the GameWindow. The screen stores the window
// in its own member and pushes the stored preference back into the control.
// m_page picks the chain: page 4 is the video page and pages 2 and 3 share the
// audio and network page.
//
// The body compiles to retail's 2797 bytes. Every instruction matches retail's
// shape. Twelve bytes still differ and all twelve are stack displacements.
// Retail keeps this function-scope UnicodeString in the window argument slot
// and storedHeight in the lowest local, and this build swaps the two. Retail
// keeps prefs in the slot it shares with the Resolution AsciiString and the
// getIPstring temporary in the slot it shares with the Resolution selected
// index, and this build swaps those.

extern "C" int __cdecl strcmp( const char *left, const char *right );

extern "C" __declspec( dllimport ) int __cdecl bfmeScanDYG(
	const char *source, const char *format, ... );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
template <typename T> struct BfmeStringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[ 1 ];
};

// The by-value string shape of reference/shims/stringinline/StringInline.h:
// a private StringBase base owns the out-of-line copy constructor and
// destructor, and the string class forwards to it inline.
template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	BfmeStringHeader<T> *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	bool isEmpty( void ) const { return m_data == 0 || m_data->m_length == 0; }
	const char *str( void ) const { return m_data->m_text; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text )
		: StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	void format( UnicodeString format, ... );
	void translate( const AsciiString &text );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class PreferenceMap
{
public:
	AsciiString &operator[]( const AsciiString &key );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	unsigned char getAnisotropicTextureFiltering( void );
	unsigned char getTerrainLighting( void );
	unsigned char get3DShadows( void );
	unsigned char get2DShadows( void );
	unsigned char getSmoothWaterBorder( void );
	unsigned char getShowProps( void );
	bool getExtraAnimationsDisabled( void );
	bool getUseHeatEffects( void );
	bool getDynamicLODEnabled( void );
	int getTextureReduction( void );
	int getParticleCap( void );

	float getMusicVolume( void );
	float getSoundVolume( void );
	float getSpeechVolume( void );
	float getAmbientVolume( void );
	float getMovieVolume( void );
	float getBrightness( void );
	float getScrollFactor( void );

	unsigned char getAllHealthBars( void );
	unsigned char getAlternateMouseSetup( void );
	unsigned char getUnitDecals( void );
	unsigned char getSendDelay( void );
	unsigned char getDisplayForeignLanguage( void );
	unsigned char getTurnOffMessengerInGame( void );
	unsigned char getLanguageFilter( void );
	unsigned char getUseEAX3( void );
	int getAudioLOD( void );

	unsigned int getOnlineIPAddress( void );
	void setOnlineIPAddress( AsciiString address );

	// The ideal-detail chooser reads GameLODManager, not the preferences, so
	// retail calls it with TheGameLODManager in ecx. The ledger already carries
	// the body under this decorated name.
	int getIdealStaticGameDetail( void );

	unsigned char m_vtable[ 4 ];						///< retail this+0x00
	PreferenceMap m_map;								///< retail this+0x04
};

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winEnable( bool enable );
};

void GadgetComboBoxReset( GameWindow *comboBox );
int GadgetComboBoxAddEntry( GameWindow *comboBox, UnicodeString text, int color );
void GadgetComboBoxSetSelectedPos( GameWindow *comboBox, int selected, bool notify );
void GadgetComboBoxSetItemData( GameWindow *comboBox, int index, void *data );
void GadgetSliderSetPosition( GameWindow *slider, int position );

// The retail call site hands this setter a one-byte value with no bool
// conversion, so the parameter is spelled one byte wide. The body it reaches is
// GadgetCheckBoxSetChecked at 0x004B31D0.
void bfmeSetCheckBoxChecked( GameWindow *checkBox, unsigned char checked );

#define BFME_SLOT( n ) virtual void _bfme_slot##n( void ) = 0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	BFME_SLOT( 0 ); BFME_SLOT( 1 ); BFME_SLOT( 2 ); BFME_SLOT( 3 );
	BFME_SLOT( 4 ); BFME_SLOT( 5 ); BFME_SLOT( 6 ); BFME_SLOT( 7 );
	BFME_SLOT( 8 ); BFME_SLOT( 9 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 );
	virtual int getDisplayModeCount( void ) = 0;
	virtual void getDisplayModeDescription( int index, int *width, int *height,
		int *bitDepth ) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameText.h
class GameTextInterface
{
public:
	BFME_SLOT( 0 ); BFME_SLOT( 1 ); BFME_SLOT( 2 ); BFME_SLOT( 3 );
	BFME_SLOT( 4 ); BFME_SLOT( 5 ); BFME_SLOT( 6 ); BFME_SLOT( 7 );
	BFME_SLOT( 8 ); BFME_SLOT( 9 );
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

#undef BFME_SLOT

enum StaticGameLODLevel
{
	STATIC_GAME_LOD_UNKNOWN = -1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameLOD.h
class GameLODManager
{
public:
	bool setStaticLODLevel( StaticGameLODLevel level );
	StaticGameLODLevel getStaticLODLevel( void ) const { return m_staticLODLevel; }

	unsigned char m_unmodelled_0000[ 0x16c0 ];
	StaticGameLODLevel m_staticLODLevel;				///< retail this+0x16c0
	unsigned char m_unmodelled_16c4[ 0x1708 - 0x16c4 ];
	int m_resolutionTier;								///< retail this+0x1708
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class EnumeratedIP
{
public:
	AsciiString getIPstring( void );
	unsigned int getIP( void ) const { return m_ip; }
	EnumeratedIP *getNext( void ) const { return m_next; }

private:
	AsciiString m_ipString;
	unsigned int m_ip;
	EnumeratedIP *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	EnumeratedIP *getAddresses( void );

private:
	EnumeratedIP *m_addresses;
	bool m_isWinsockInitialized;
};

// The combo index mapper already landed at 0x0055E070. The Options screen is
// the class that owns it, so the Detail arm calls it on itself.
class BfmeAptScreenSetComboFromIndex
{
public:
	void setComboFromIndex( int index );
};

// The two bytes the shell hands the Options screen when it opens. The screen
// disables its own controls while the byte at 0x012F4AD0 is clear.
extern unsigned char g_optByte12F4AD0;

// The BFME anti-tamper integer helpers. Each one takes two plain ints and
// returns one. Rva0054E860 seals a value, Rva0054E9E0 opens one back to a
// plain int, Rva0054E7E0 advances one by the step constant, and Rva0054E5E0
// hashes a pair to 0x342C2BE0 when the two sealed values are equal.
int __cdecl Rva0054E860( int left, int right );
int __cdecl Rva0054E9E0( int left, int right );
int __cdecl Rva0054E7E0( int left, int right );
int __cdecl Rva0054E5E0( int left, int right );

enum
{
	BFME_SEALED_EQUAL = 0x342C2BE0,
	BFME_SEALED_STEP = 0x352D2FF1
};

extern Display *TheDisplay;
extern GameTextInterface *TheGameText;
extern GameLODManager *TheGameLODManager;

// Options.apt screen, retail object 0x310 bytes. The offsets are the ones
// BfmeAptScreenOptionsCancel.cpp and BfmeAptScreenOptionsRefreshNat.cpp
// already established, extended with the controls only this body touches.
class BfmeAptScreenOptions
{
public:
	void _bfme_onInitGadget( const char *name, void *movie, GameWindow *window );

private:
	unsigned char m_unmodelled_000[ 0x258 ];
	int m_page;											///< retail this+0x258
	unsigned char m_unmodelled_25C[ 4 ];
	OptionPreferences m_options;						///< retail this+0x260
	unsigned char m_unmodelled_268[ 0x284 - 0x268 ];
	GameWindow *m_comboResolution;						///< retail this+0x284
	GameWindow *m_comboDetail;							///< retail this+0x288
	GameWindow *m_comboOnlineIp;						///< retail this+0x28c
	GameWindow *m_checkHealthBars;						///< retail this+0x290
	GameWindow *m_checkAlternateMouse;					///< retail this+0x294
	unsigned char m_unmodelled_298[ 4 ];
	GameWindow *m_checkUnitDecals;						///< retail this+0x29c
	GameWindow *m_sliderSendDelay;						///< retail this+0x2a0
	unsigned char m_unmodelled_2A4[ 4 ];
	GameWindow *m_checkTurnOffMessenger;				///< retail this+0x2a8
	GameWindow *m_checkForeignLanguage;					///< retail this+0x2ac
	GameWindow *m_checkFilterLanguage;					///< retail this+0x2b0
	GameWindow *m_checkEAX3;							///< retail this+0x2b4
	GameWindow *m_checkHighAudioQuality;				///< retail this+0x2b8
	GameWindow *m_checkAnisotropic;						///< retail this+0x2bc
	GameWindow *m_checkTerrainLighting;					///< retail this+0x2c0
	GameWindow *m_check3DShadows;						///< retail this+0x2c4
	GameWindow *m_check2DShadows;						///< retail this+0x2c8
	GameWindow *m_checkSmoothWater;						///< retail this+0x2cc
	GameWindow *m_checkShowProps;						///< retail this+0x2d0
	GameWindow *m_checkExtraAnimations;					///< retail this+0x2d4
	GameWindow *m_checkHeatEffects;						///< retail this+0x2d8
	GameWindow *m_checkDynamicLOD;						///< retail this+0x2dc
	GameWindow *m_sliderMusicVolume;					///< retail this+0x2e0
	GameWindow *m_sliderSoundFxVolume;					///< retail this+0x2e4
	GameWindow *m_sliderVoiceVolume;					///< retail this+0x2e8
	GameWindow *m_sliderAmbientVolume;					///< retail this+0x2ec
	GameWindow *m_sliderMovieVolume;					///< retail this+0x2f0
	GameWindow *m_sliderScrollSpeed;					///< retail this+0x2f4
	GameWindow *m_sliderBrightness;						///< retail this+0x2f8
	GameWindow *m_sliderTextureDetail;					///< retail this+0x2fc
	GameWindow *m_sliderParticleCap;					///< retail this+0x300
	int m_defaultResolutionIndex;						///< retail this+0x304
};

// ?_bfme_onInitGadget@BfmeAptScreenOptions@@QAEXPBDPAXPAVGameWindow@@@Z
void BfmeAptScreenOptions::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window )
{
	if ( window == 0 )
		return;

	GadgetComboBoxReset( window );

	UnicodeString text;
	int storedHeight;

	if ( m_page == 4 )
	{
		if ( strcmp( name, "Options::AnisotropicTextureFiltering" ) == 0 )
		{
			m_checkAnisotropic = window;
			unsigned char value = m_options.getAnisotropicTextureFiltering();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::TerrainLighting" ) == 0 )
		{
			m_checkTerrainLighting = window;
			unsigned char value = m_options.getTerrainLighting();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::3dShadows" ) == 0 )
		{
			m_check3DShadows = window;
			unsigned char value = m_options.get3DShadows();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::2dShadows" ) == 0 )
		{
			m_check2DShadows = window;
			unsigned char value = m_options.get2DShadows();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::SmoothWaterBorder" ) == 0 )
		{
			m_checkSmoothWater = window;
			unsigned char value = m_options.getSmoothWaterBorder();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::ShowProps" ) == 0 )
		{
			m_checkShowProps = window;
			unsigned char value = m_options.getShowProps();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::ShowAnimations" ) == 0 )
		{
			m_checkExtraAnimations = window;
			unsigned char value = m_options.getExtraAnimationsDisabled();
			bfmeSetCheckBoxChecked( window, !value );
		}
		else if ( strcmp( name, "Options::HeatEffects" ) == 0 )
		{
			m_checkHeatEffects = window;
			unsigned char value = m_options.getUseHeatEffects();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::DisableDynamicLOD" ) == 0 )
		{
			m_checkDynamicLOD = window;
			unsigned char value = m_options.getDynamicLODEnabled();
			bfmeSetCheckBoxChecked( window, !value );
		}
		else if ( strcmp( name, "Options::TextureDetail" ) == 0 )
		{
			m_sliderTextureDetail = window;
			GadgetSliderSetPosition( window, m_options.getTextureReduction() );
		}
		else if ( strcmp( name, "Options::ParticleCap" ) == 0 )
		{
			m_sliderParticleCap = window;
			GadgetSliderSetPosition( window, m_options.getParticleCap() );
		}
	}
	else if ( m_page == 2 || m_page == 3 )
	{
		if ( strcmp( name, "Options::Resolution" ) == 0 )
		{
			m_comboResolution = window;
			AsciiString stored = m_options.m_map[ AsciiString( "Resolution" ) ];

			int storedWidth;
			int defaultWidth;
			int defaultHeight;
			if ( TheGameLODManager->m_resolutionTier <= 2 )
			{
				storedWidth = defaultWidth = 800;
				storedHeight = defaultHeight = 600;
			}
			else
			{
				storedWidth = defaultWidth = 1024;
				storedHeight = defaultHeight = 768;
			}
			int selected = -1;

			if ( !stored.isEmpty() )
			{
				if ( bfmeScanDYG( stored.str(), "%d%d", &storedWidth,
					&storedHeight ) != 2 )
				{
					storedWidth = defaultWidth;
					storedHeight = defaultHeight;
				}
			}

			int count = TheDisplay->getDisplayModeCount();
			int limit[ 2 ];
			limit[ 1 ] = Rva0054E860( count, count );
			int cursor = Rva0054E860( 0, 0 );
			while ( Rva0054E5E0( cursor, limit[ 1 ] ) != BFME_SEALED_EQUAL )
			{
				int index = Rva0054E9E0( cursor, cursor );
				int modeWidth;
				int modeHeight;
				int modeBitDepth;
				TheDisplay->getDisplayModeDescription( index, &modeWidth,
					&modeHeight, &modeBitDepth );

				text.format( UnicodeString( L"%dx%d" ), modeWidth, modeHeight );
				GadgetComboBoxAddEntry( window, text, -1 );

				if ( modeWidth == defaultWidth && modeHeight == defaultHeight )
					m_defaultResolutionIndex = index;
				if ( modeWidth == storedWidth && modeHeight == storedHeight )
					selected = index;

				cursor = Rva0054E7E0( cursor, BFME_SEALED_STEP );
			}

			GadgetComboBoxSetSelectedPos( window, selected, false );
			if ( !g_optByte12F4AD0 )
				window->winEnable( false );
		}
		else if ( strcmp( name, "Options::Detail" ) == 0 )
		{
			GadgetComboBoxAddEntry( window, TheGameText->fetch( "GUI:UltraHigh" ), -1 );
			GadgetComboBoxAddEntry( window, TheGameText->fetch( "GUI:High" ), -1 );
			GadgetComboBoxAddEntry( window, TheGameText->fetch( "GUI:Medium" ), -1 );
			GadgetComboBoxAddEntry( window, TheGameText->fetch( "GUI:Low" ), -1 );
			GadgetComboBoxAddEntry( window, TheGameText->fetch( "GUI:VeryLow" ), -1 );
			GadgetComboBoxAddEntry( window, TheGameText->fetch( "GUI:Custom" ), -1 );
			m_comboDetail = window;

			if ( TheGameLODManager->getStaticLODLevel() == STATIC_GAME_LOD_UNKNOWN )
			{
				TheGameLODManager->setStaticLODLevel( (StaticGameLODLevel)
					( (OptionPreferences *)TheGameLODManager )->getIdealStaticGameDetail() );
			}
			( (BfmeAptScreenSetComboFromIndex *)this )->setComboFromIndex(
				TheGameLODManager->getStaticLODLevel() );

			if ( !g_optByte12F4AD0 )
				window->winEnable( false );
			return;
		}
		else if ( strcmp( name, "Options::MusicVolume" ) == 0 )
		{
			m_sliderMusicVolume = window;
			GadgetSliderSetPosition( window, (int)m_options.getMusicVolume() );
		}
		else if ( strcmp( name, "Options::SoundFxVolume" ) == 0 )
		{
			m_sliderSoundFxVolume = window;
			GadgetSliderSetPosition( window, (int)m_options.getSoundVolume() );
		}
		else if ( strcmp( name, "Options::VoiceVolume" ) == 0 )
		{
			m_sliderVoiceVolume = window;
			GadgetSliderSetPosition( window, (int)m_options.getSpeechVolume() );
		}
		else if ( strcmp( name, "Options::AmbientVolume" ) == 0 )
		{
			m_sliderAmbientVolume = window;
			GadgetSliderSetPosition( window, (int)m_options.getAmbientVolume() );
		}
		else if ( strcmp( name, "Options::MovieVolume" ) == 0 )
		{
			m_sliderMovieVolume = window;
			GadgetSliderSetPosition( window, (int)m_options.getMovieVolume() );
		}
		else if ( strcmp( name, "Options::Brightness" ) == 0 )
		{
			m_sliderBrightness = window;
			GadgetSliderSetPosition( window, (int)m_options.getBrightness() );
		}
		else if ( strcmp( name, "Options::ScrollSpeed" ) == 0 )
		{
			m_sliderScrollSpeed = window;
			GadgetSliderSetPosition( window,
				(int)( m_options.getScrollFactor() * 50.0f ) );
		}
		else if ( strcmp( name, "Options::HealthBars" ) == 0 )
		{
			m_checkHealthBars = window;
			unsigned char value = m_options.getAllHealthBars();
			bfmeSetCheckBoxChecked( window, value );
			if ( TheGameLODManager->getStaticLODLevel() <= 1 )
			{
				bfmeSetCheckBoxChecked( window, 1 );
				m_checkHealthBars->winEnable( false );
			}
			else
			{
				bfmeSetCheckBoxChecked( window, value );
			}
		}
		else if ( strcmp( name, "Options::AlternateMouseSetUp" ) == 0 )
		{
			m_checkAlternateMouse = window;
			unsigned char value = !m_options.getAlternateMouseSetup();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::ShowUnitDecals" ) == 0 )
		{
			m_checkUnitDecals = window;
			unsigned char value = m_options.getUnitDecals();
			bfmeSetCheckBoxChecked( window, value );
			if ( TheGameLODManager->getStaticLODLevel() <= 1 )
			{
				bfmeSetCheckBoxChecked( window, 0 );
				m_checkUnitDecals->winEnable( false );
			}
			else
			{
				bfmeSetCheckBoxChecked( window, value );
			}
		}
		else if ( strcmp( name, "Options::OnlineIp" ) == 0 )
		{
			m_comboOnlineIp = window;
			OptionPreferences *prefs = &m_options;
			unsigned int storedIP = prefs->getOnlineIPAddress();
			UnicodeString address;

			IPEnumeration addresses;
			EnumeratedIP *ip = addresses.getAddresses();
			int selected = -1;

			while ( ip != 0 )
			{
				address.translate( ip->getIPstring() );
				int index = GadgetComboBoxAddEntry( m_comboOnlineIp, address, -1 );
				GadgetComboBoxSetItemData( m_comboOnlineIp, index,
					(void *)ip->getIP() );
				if ( storedIP == ip->getIP() )
					selected = index;
				ip = ip->getNext();
			}

			if ( selected >= 0 )
			{
				GadgetComboBoxSetSelectedPos( m_comboOnlineIp, selected, false );
			}
			else
			{
				GadgetComboBoxSetSelectedPos( m_comboOnlineIp, 0, false );
				if ( addresses.getAddresses() != 0 )
					prefs->setOnlineIPAddress(
						addresses.getAddresses()->getIPstring() );
			}
		}
		else if ( strcmp( name, "Options::Firewall" ) == 0 )
		{
		}
		else if ( strcmp( name, "Options::SendDelay" ) == 0 )
		{
			m_sliderSendDelay = window;
			unsigned char value = m_options.getSendDelay();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::DisplayForeignLanguage" ) == 0 )
		{
			m_checkForeignLanguage = window;
			unsigned char value = m_options.getDisplayForeignLanguage();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::TurnOffMessengerInGame" ) == 0 )
		{
			m_checkTurnOffMessenger = window;
			unsigned char value = m_options.getTurnOffMessengerInGame();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::FilterLanguage" ) == 0 )
		{
			m_checkFilterLanguage = window;
			unsigned char value = m_options.getLanguageFilter();
			bfmeSetCheckBoxChecked( window, value );
		}
		else if ( strcmp( name, "Options::EAX3" ) == 0 )
		{
			m_checkEAX3 = window;
			bfmeSetCheckBoxChecked( window, m_options.getUseEAX3() );
		}
		else if ( strcmp( name, "Options::HighAudioQuality" ) == 0 )
		{
			m_checkHighAudioQuality = window;
			if ( m_options.getAudioLOD() == 1 )
				bfmeSetCheckBoxChecked( window, 1 );
			else
				bfmeSetCheckBoxChecked( window, 0 );
		}
	}
}
