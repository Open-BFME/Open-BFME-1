// ?update@BfmeAptScreenOptions@@QAEXXZ
// partial score=0.60 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
//
// BfmeAptScreenOptions destructor, retail 0x0055E320 (255 bytes).
// The Options.apt constructor installs vtables 0x0110912C and 0x01109128,
// and AptOptions::InitGadgets references this destructor's cleanup path.

class AsciiString
{
private:
	void *m_data;
};

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
	char m_unmodelled[ 0x214 ];
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

	unsigned char getAnisotropicTextureFiltering();
	unsigned char getTerrainLighting();
	unsigned char get3DShadows();
	unsigned char get2DShadows();
	unsigned char getSmoothWaterBorder();
	unsigned char getShowProps();
	bool getExtraAnimationsDisabled();
	bool getUseHeatEffects();
	bool getDynamicLODEnabled();
	int getTextureReduction();
	int getParticleCap();
	float getMusicVolume();
	float getSoundVolume();
	float getSpeechVolume();
	float getAmbientVolume();
	float getMovieVolume();

private:
	char m_unmodelled[ 0x10 ];
};

class GameWindow;
extern void GadgetCheckBoxSetChecked( GameWindow *g, unsigned char isChecked );
extern void GadgetComboBoxSetSelectedPos( GameWindow *g, int pos, bool sendMsg );
extern void GadgetSliderSetPosition( GameWindow *g, int pos );

class GlobalData
{
public:
	char m_pad[ 0xc68 ];
	float m_displayGamma;
};
extern GlobalData *TheWritableGlobalData;

class Display
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void setGamma( float gamma, float bright, float contrast, bool calibrate );
};
extern Display *TheDisplay;

struct Rva005A00B0AudioClient
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20( int value ) volatile;
	virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48( float volume ) volatile;
	virtual void s49( float volume ) volatile;
	virtual void s50( float volume ) volatile;
	virtual void s51( float volume ) volatile;
	virtual void s52( float volume ) volatile;
};
extern volatile Rva005A00B0AudioClient * volatile TheAudioClientUpdate;

struct Rva00579160Manager
{
	void notify();
};
extern Rva00579160Manager *Rva00579160TheManager;

extern int g_bfmeOptionsAudioPending;
extern void *g_quitMenuLayout;
extern char g_bfmeD1072;
extern const float g_01076C24;

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
	void update();

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

// BfmeAptScreenOptions per-tick sync, retail 0x0055DCB0, 756 bytes. State 4
// pushes the current OptionPreferences into the Options.apt widgets (combo
// box, 9 checkboxes, 2 sliders) then advances to state 3 (deferred) or 2
// (done); any other state instead reapplies gamma + the 5 audio channel
// volumes every tick and pokes the window manager when the quit-menu layout
// is up.
void BfmeAptScreenOptions::update()
{
	if( g_bfmeOptionsAudioPending )
	{
		TheAudioClientUpdate->s20( g_bfmeOptionsAudioPending );
		g_bfmeOptionsAudioPending = 0;
	}

	if( m_field258 == 4 )
	{
		if( m_fields284[ 1 ] && m_field30C != 5 )
			GadgetComboBoxSetSelectedPos( (GameWindow *)m_fields284[ 1 ], m_field30C, false );

		if( g_bfmeD1072 )
		{
			m_field258 = 3;
			return;
		}

		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 5 ], m_options.getAnisotropicTextureFiltering() );
		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 6 ], m_options.getTerrainLighting() );
		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 7 ], m_options.get3DShadows() );
		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 8 ], m_options.get2DShadows() );
		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 9 ], m_options.getSmoothWaterBorder() );
		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 10 ], m_options.getShowProps() );
		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 11 ], !m_options.getExtraAnimationsDisabled() );
		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 12 ], m_options.getUseHeatEffects() );
		GadgetCheckBoxSetChecked( (GameWindow *)m_fields2A8[ 13 ], !m_options.getDynamicLODEnabled() );

		GadgetSliderSetPosition( (GameWindow *)m_fields2A8[ 21 ], m_options.getTextureReduction() );
		GadgetSliderSetPosition( (GameWindow *)m_fields2A8[ 22 ], m_options.getParticleCap() );

		m_field258 = 2;
		return;
	}

	TheDisplay->setGamma( TheWritableGlobalData->m_displayGamma, 0.0f, 1.0f, false );

	TheAudioClientUpdate->s50( (float)(int)m_options.getMusicVolume() * g_01076C24 );
	TheAudioClientUpdate->s48( (float)(int)m_options.getSoundVolume() * g_01076C24 );
	TheAudioClientUpdate->s49( (float)(int)m_options.getSpeechVolume() * g_01076C24 );
	TheAudioClientUpdate->s52( (float)(int)m_options.getAmbientVolume() * g_01076C24 );
	TheAudioClientUpdate->s51( (float)(int)m_options.getMovieVolume() * g_01076C24 );

	if( g_quitMenuLayout )
		Rva00579160TheManager->notify();
}
