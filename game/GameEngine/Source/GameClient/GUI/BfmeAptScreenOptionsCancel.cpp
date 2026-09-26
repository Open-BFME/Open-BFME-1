// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenOptions::_bfme_cancel, retail 0x0055DCB0, 756 bytes. The
// matched Options constructor at 0x00563370 binds thunk 0x0003D811 to the
// selector string "AptOptions::Cancel", and that thunk jumps here. The body
// puts every control back to the value stored in the screen's own
// OptionPreferences at this+0x260. State 4 restores the video page, and any
// other state restores the five audio volumes.

class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	virtual ~OptionPreferences();

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

private:
	unsigned char m_unmodelled_04[ 0x10 ];
};

// The retail call site hands this setter a one-byte value with no bool
// conversion, so the parameter is spelled one byte wide. The body it reaches
// is GadgetCheckBoxSetChecked at 0x004B31D0.
void bfmeSetCheckBoxChecked( GameWindow *window, unsigned char checked );
void GadgetComboBoxSetSelectedPos( GameWindow *window, int position, bool notify );

#define BFME_SLOT( n ) virtual void _bfme_slot##n( void ) = 0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	BFME_SLOT( 0 ); BFME_SLOT( 1 ); BFME_SLOT( 2 ); BFME_SLOT( 3 );
	BFME_SLOT( 4 ); BFME_SLOT( 5 ); BFME_SLOT( 6 ); BFME_SLOT( 7 );
	BFME_SLOT( 8 ); BFME_SLOT( 9 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 ); BFME_SLOT( 18 ); BFME_SLOT( 19 );
	BFME_SLOT( 20 ); BFME_SLOT( 21 ); BFME_SLOT( 22 ); BFME_SLOT( 23 );
	BFME_SLOT( 24 ); BFME_SLOT( 25 ); BFME_SLOT( 26 ); BFME_SLOT( 27 );
	BFME_SLOT( 28 ); BFME_SLOT( 29 ); BFME_SLOT( 30 ); BFME_SLOT( 31 );
	BFME_SLOT( 32 ); BFME_SLOT( 33 ); BFME_SLOT( 34 ); BFME_SLOT( 35 );
	BFME_SLOT( 36 ); BFME_SLOT( 37 ); BFME_SLOT( 38 ); BFME_SLOT( 39 );
	BFME_SLOT( 40 ); BFME_SLOT( 41 ); BFME_SLOT( 42 ); BFME_SLOT( 43 );
	BFME_SLOT( 44 ); BFME_SLOT( 45 ); BFME_SLOT( 46 ); BFME_SLOT( 47 );
	BFME_SLOT( 48 ); BFME_SLOT( 49 ); BFME_SLOT( 50 ); BFME_SLOT( 51 );
	BFME_SLOT( 52 );
	virtual int winSendSystemMsg( GameWindow *window, unsigned int msg,
		unsigned int mData1, unsigned int mData2 ) = 0;
};

// Display::setShroudLevel sits at vtable slot 20 in this build.
class Display
{
public:
	BFME_SLOT( 0 ); BFME_SLOT( 1 ); BFME_SLOT( 2 ); BFME_SLOT( 3 );
	BFME_SLOT( 4 ); BFME_SLOT( 5 ); BFME_SLOT( 6 ); BFME_SLOT( 7 );
	BFME_SLOT( 8 ); BFME_SLOT( 9 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 ); BFME_SLOT( 18 ); BFME_SLOT( 19 );
	virtual void slot20( void *movie, int flag, float value, int unused ) = 0;
};

// The audio client the Apt screens drive. Only the six slots this body
// reaches are named.
class Rva005A00B0AudioClient
{
public:
	BFME_SLOT( 0 ); BFME_SLOT( 1 ); BFME_SLOT( 2 ); BFME_SLOT( 3 );
	BFME_SLOT( 4 ); BFME_SLOT( 5 ); BFME_SLOT( 6 ); BFME_SLOT( 7 );
	BFME_SLOT( 8 ); BFME_SLOT( 9 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 ); BFME_SLOT( 18 ); BFME_SLOT( 19 );
	virtual void stopAudioEvent( void *handle ) = 0;
	BFME_SLOT( 21 ); BFME_SLOT( 22 ); BFME_SLOT( 23 ); BFME_SLOT( 24 );
	BFME_SLOT( 25 ); BFME_SLOT( 26 ); BFME_SLOT( 27 ); BFME_SLOT( 28 );
	BFME_SLOT( 29 ); BFME_SLOT( 30 ); BFME_SLOT( 31 ); BFME_SLOT( 32 );
	BFME_SLOT( 33 ); BFME_SLOT( 34 ); BFME_SLOT( 35 ); BFME_SLOT( 36 );
	BFME_SLOT( 37 ); BFME_SLOT( 38 ); BFME_SLOT( 39 ); BFME_SLOT( 40 );
	BFME_SLOT( 41 ); BFME_SLOT( 42 ); BFME_SLOT( 43 ); BFME_SLOT( 44 );
	BFME_SLOT( 45 ); BFME_SLOT( 46 ); BFME_SLOT( 47 );
	virtual void setSoundVolume( float volume ) = 0;
	virtual void setSpeechVolume( float volume ) = 0;
	virtual void setMusicVolume( float volume ) = 0;
	virtual void setMovieVolume( float volume ) = 0;
	virtual void setAmbientVolume( float volume ) = 0;
};

#undef BFME_SLOT

// The registry singleton at 0x012F19E8 that the Options screen tells to
// republish once the quit menu layout is live.
class Rva00465B80
{
public:
	void apply( void );
};

struct Rva006C9270GlobalData
{
	unsigned char m_head[ 0xc68 ];
	void *m_movieC68;									///< retail this+0xc68
};

extern char g_bfmeD1072;
extern void *g_quitMenuLayout;
extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;
extern Rva005A00B0AudioClient *TheAudioClientUpdate;
extern Rva006C9270GlobalData *TheWritableGlobalData;

enum
{
	GSM_SET_SLIDER = 0x400d
};

// Options.apt screen, retail object 0x310 bytes.
class BfmeAptScreenOptions
{
public:
	void _bfme_cancel( const char *name );

private:
	unsigned char m_unmodelled_00[ 0x258 ];
	int m_page;											///< retail this+0x258
	unsigned char m_unmodelled_25C[ 4 ];
	OptionPreferences m_options;						///< retail this+0x260
	unsigned char m_unmodelled_274[ 0x14 ];
	GameWindow *m_comboResolution;						///< retail this+0x288
	unsigned char m_unmodelled_28C[ 0x30 ];
	GameWindow *m_checkAnisotropic;						///< retail this+0x2bc
	GameWindow *m_checkTerrainLighting;					///< retail this+0x2c0
	GameWindow *m_check3DShadows;						///< retail this+0x2c4
	GameWindow *m_check2DShadows;						///< retail this+0x2c8
	GameWindow *m_checkSmoothWater;						///< retail this+0x2cc
	GameWindow *m_checkShowProps;						///< retail this+0x2d0
	GameWindow *m_checkExtraAnimations;					///< retail this+0x2d4
	GameWindow *m_checkHeatEffects;						///< retail this+0x2d8
	GameWindow *m_checkDynamicLOD;						///< retail this+0x2dc
	unsigned char m_unmodelled_2E0[ 0x1c ];
	GameWindow *m_sliderTextureReduction;				///< retail this+0x2fc
	GameWindow *m_sliderParticleCap;					///< retail this+0x300
	unsigned char m_unmodelled_304[ 8 ];
	int m_resolutionIndex;								///< retail this+0x30c
};

// ?_bfme_cancel@BfmeAptScreenOptions@@QAEXPBD@Z
void BfmeAptScreenOptions::_bfme_cancel( const char * )
{
	if( *(void **)0x012F4AE4 != 0 )
	{
		TheAudioClientUpdate->stopAudioEvent( *(void **)0x012F4AE4 );
		*(void **)0x012F4AE4 = 0;
	}

	if( m_page == 4 )
	{
		if( m_comboResolution != 0 && m_resolutionIndex != 5 )
		{
			GadgetComboBoxSetSelectedPos( m_comboResolution, m_resolutionIndex, false );
		}

		if( g_bfmeD1072 )
		{
			m_page = 3;
			return;
		}

		{
			unsigned char value = m_options.getAnisotropicTextureFiltering();
			bfmeSetCheckBoxChecked( m_checkAnisotropic, value );
		}
		{
			unsigned char value = m_options.getTerrainLighting();
			bfmeSetCheckBoxChecked( m_checkTerrainLighting, value );
		}
		{
			unsigned char value = m_options.get3DShadows();
			bfmeSetCheckBoxChecked( m_check3DShadows, value );
		}
		{
			unsigned char value = m_options.get2DShadows();
			bfmeSetCheckBoxChecked( m_check2DShadows, value );
		}
		{
			unsigned char value = m_options.getSmoothWaterBorder();
			bfmeSetCheckBoxChecked( m_checkSmoothWater, value );
		}
		{
			unsigned char value = m_options.getShowProps();
			bfmeSetCheckBoxChecked( m_checkShowProps, value );
		}
		{
			unsigned char value = m_options.getExtraAnimationsDisabled();
			bfmeSetCheckBoxChecked( m_checkExtraAnimations, !value );
		}
		{
			unsigned char value = m_options.getUseHeatEffects();
			bfmeSetCheckBoxChecked( m_checkHeatEffects, value );
		}
		{
			unsigned char value = m_options.getDynamicLODEnabled();
			bfmeSetCheckBoxChecked( m_checkDynamicLOD, !value );
		}

		{
			int position = m_options.getTextureReduction();
			TheWindowManager->winSendSystemMsg( m_sliderTextureReduction, GSM_SET_SLIDER,
				(unsigned int)position, 0 );
		}
		{
			int position = m_options.getParticleCap();
			TheWindowManager->winSendSystemMsg( m_sliderParticleCap, GSM_SET_SLIDER,
				(unsigned int)position, 0 );
		}

		m_page = 2;
		return;
	}

	TheDisplay->slot20( TheWritableGlobalData->m_movieC68, 0, 1.0f, 0 );

	{
		int volume = (int)m_options.getMusicVolume();
		TheAudioClientUpdate->setMusicVolume( volume * 0.01f );
	}
	{
		int volume = (int)m_options.getSoundVolume();
		TheAudioClientUpdate->setSoundVolume( volume * 0.01f );
	}
	{
		int volume = (int)m_options.getSpeechVolume();
		TheAudioClientUpdate->setSpeechVolume( volume * 0.01f );
	}
	{
		int volume = (int)m_options.getAmbientVolume();
		TheAudioClientUpdate->setAmbientVolume( volume * 0.01f );
	}
	{
		int volume = (int)m_options.getMovieVolume();
		TheAudioClientUpdate->setMovieVolume( volume * 0.01f );
	}

	if( g_quitMenuLayout != 0 )
	{
		( (Rva00465B80 *)TheWindowManager )->apply();
	}
}
