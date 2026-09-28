// cl: /DNDEBUG /MD /EHsc
// finishSinglePlayerInit, retail 0x004E4790 (989 bytes).
//
// Identity: the matched ScoreScreenUpdate (0x004E5020) calls it through ILT
// 0x0001F78F when s_needToFinishSinglePlayerInit is set, exactly as Zero
// Hour's ScoreScreen.cpp does.  BFME's version of the Zero Hour body:
//   - no challenge-campaign branches; the victory path only advances the
//     campaign;
//   - campaign completion only sets the three honors flags (the per-side
//     setXCampaignComplete calls and the CHALLENGE_%d loop are gone);
//   - the low-res movie rule keeps two of the three Zero Hour tests;
//   - the academy windows are not hidden and setGroup is unconditional.
//
// Local ABI-slice replica like ReplayMenuDeleteCopy.cpp (retail 0x004E1090,
// the ScoreScreen region's neighbour): the string model is StringBase-backed,
// with isEmpty inline and isNotEmpty/compareNoCase out of line as retail calls
// them; the SkirmishPreferences/SkirmishBattleHonors pair follows the matched
// _bfme_updateSkirmishBattleHonors (BfmeUpdateSkirmishBattleHonors.cpp).
// ScoreScreen.cpp's window statics are mirrored here as TU statics (DIR32
// relocations to file statics are patched to retail's addresses).

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

#define TRUE true
#define FALSE false

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
	bool isNotEmpty() const throw();
	int compareNoCase( const T *text ) const;
	void set( const StringBase<T> &other );

private:
	Header *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	AsciiString &operator=( const AsciiString &other )
	{
		StringBase<char>::set( other );
		return *this;
	}

	Bool isEmpty() const { return StringBase<char>::isEmpty(); }
	Bool isNotEmpty() const { return StringBase<char>::isNotEmpty(); }
	Int compareNoCase( const char *text ) const { return StringBase<char>::compareNoCase( text ); }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}
};

class GameWindow
{
public:
	Int winHide( Bool hide );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void slot00();
	virtual ~WindowLayout();								///< +0x04
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void destroyWindows( void );					///< +0x20
};

class GameWindowManager
{
public:
#define BFME_WM_PAD( N ) virtual void unused##N();
	BFME_WM_PAD( 00 ) BFME_WM_PAD( 01 ) BFME_WM_PAD( 02 ) BFME_WM_PAD( 03 )
	BFME_WM_PAD( 04 ) BFME_WM_PAD( 05 ) BFME_WM_PAD( 06 ) BFME_WM_PAD( 07 )
	BFME_WM_PAD( 08 ) BFME_WM_PAD( 09 ) BFME_WM_PAD( 10 ) BFME_WM_PAD( 11 )
	BFME_WM_PAD( 12 ) BFME_WM_PAD( 13 ) BFME_WM_PAD( 14 ) BFME_WM_PAD( 15 )
	BFME_WM_PAD( 16 ) BFME_WM_PAD( 17 ) BFME_WM_PAD( 18 ) BFME_WM_PAD( 19 )
	BFME_WM_PAD( 20 ) BFME_WM_PAD( 21 ) BFME_WM_PAD( 22 ) BFME_WM_PAD( 23 )
	BFME_WM_PAD( 24 ) BFME_WM_PAD( 25 ) BFME_WM_PAD( 26 ) BFME_WM_PAD( 27 )
	BFME_WM_PAD( 28 ) BFME_WM_PAD( 29 ) BFME_WM_PAD( 30 ) BFME_WM_PAD( 31 )
	BFME_WM_PAD( 32 ) BFME_WM_PAD( 33 ) BFME_WM_PAD( 34 ) BFME_WM_PAD( 35 )
	BFME_WM_PAD( 36 ) BFME_WM_PAD( 37 ) BFME_WM_PAD( 38 ) BFME_WM_PAD( 39 )
	BFME_WM_PAD( 40 ) BFME_WM_PAD( 41 ) BFME_WM_PAD( 42 ) BFME_WM_PAD( 43 )
#undef BFME_WM_PAD
	virtual Int winSetFocus( GameWindow *window );			///< +0xB0
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );	///< +0x28
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class Campaign
{
public:
	AsciiString getFinalVictoryMovie( void );

	char m_unmodelled_00[4];
	AsciiString m_name;									///< retail this+0x04
};

class Mission;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class CampaignManager
{
public:
	Campaign *getCurrentCampaign( void );
	AsciiString getCurrentMap( void );
	Mission *gotoNextMission( void );
	Bool isVictorious( void ) { return m_victorious; }

private:
	char m_unmodelled_00[0x10];
	Bool m_victorious;									///< retail this+0x10
};

class GameLODManager
{
public:
	Bool didMemPass( void );

	char m_unmodelled_00[0x16C4];
	Int m_fieldAt16C4;									///< retail this+0x16C4, compared against 1
};

enum SaveCode
{
	SC_INVALID = -1
};

class GameState
{
public:
	SaveCode missionSave( void );
};

class InGameUI
{
public:
	void freeMessageResources( void );
};

class GameWindowTransitionsHandler
{
public:
	void setGroup( AsciiString groupName, Bool immediate = FALSE );
};

class CopyProtect
{
public:
	static Bool validate( void );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/SkirmishPreferences.h
class SkirmishPreferences
{
public:
	SkirmishPreferences();
	virtual ~SkirmishPreferences();
	UnicodeString getUserName();

private:
	char m_unmodelled_04[0x14];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/SkirmishBattleHonors.h
class SkirmishBattleHonors
{
public:
	SkirmishBattleHonors( UnicodeString userName );
	virtual ~SkirmishBattleHonors();
	virtual Bool write();
	void setHonors( Int mask );

private:
	char m_unmodelled_04[0x38];
};

enum
{
	BATTLE_HONOR_CAMPAIGN_USA = 0x00000800,
	BATTLE_HONOR_CAMPAIGN_CHINA = 0x00001000,
	BATTLE_HONOR_CAMPAIGN_GLA = 0x00002000
};

extern CampaignManager *TheCampaignManager;
extern GameTextInterface *TheGameText;
extern GameWindowManager *TheWindowManager;
extern GameLODManager *TheGameLODManager;
extern GameState *TheGameState;
extern InGameUI *TheInGameUI;
extern GameWindowTransitionsHandler *TheTransitionHandler;

void GadgetRadioSetText( GameWindow *window, UnicodeString text );
void PlayMovieAndBlock( AsciiString movieTitle );

extern GameWindow *parent;								///< retail [0x012F415C]
extern GameWindow *listboxChatWindowScoreScreen;		///< retail [0x012F417C]
static GameWindow *buttonOk = 0;						///< retail [0x012F4160]
static GameWindow *buttonContinue = 0;					///< retail [0x012F4164]
static GameWindow *textEntryChat = 0;					///< retail [0x012F4168]
static GameWindow *buttonEmote = 0;						///< retail [0x012F416C]
static GameWindow *chatBoxBorder = 0;					///< retail [0x012F4170]
static GameWindow *buttonBuddies = 0;					///< retail [0x012F4174]
static GameWindow *staticTextGameSaved = 0;				///< retail [0x012F4178]
static Bool buttonIsFinishCampaign = FALSE;				///< retail [0x012F4183]
static WindowLayout *s_blankLayout = 0;					///< retail [0x012F4184]

// ?finishSinglePlayerInit@@YAXXZ
void finishSinglePlayerInit( void )
{
	if( CopyProtect::validate() && TheCampaignManager->isVictorious() )
	{
		TheCampaignManager->gotoNextMission();

		if( TheCampaignManager->getCurrentMap().isEmpty() )
		{
			GadgetRadioSetText( buttonContinue, TheGameText->fetch( "GUI:EndCampaign" ) );
			buttonIsFinishCampaign = TRUE;
			// mark us as having completed the campaign
			Campaign *campaign = TheCampaignManager->getCurrentCampaign();
			if( campaign )
			{
				SkirmishPreferences prefs;
				SkirmishBattleHonors stats( prefs.getUserName() );
				if( campaign->m_name.compareNoCase( "USA" ) == 0 )
					stats.setHonors( BATTLE_HONOR_CAMPAIGN_USA );
				if( campaign->m_name.compareNoCase( "China" ) == 0 )
					stats.setHonors( BATTLE_HONOR_CAMPAIGN_CHINA );
				if( campaign->m_name.compareNoCase( "GLA" ) == 0 )
					stats.setHonors( BATTLE_HONOR_CAMPAIGN_GLA );

				stats.write();

				if( buttonOk )
					buttonOk->winHide( TRUE );
				if( buttonContinue )
					buttonContinue->winHide( TRUE );
				if( textEntryChat )
					textEntryChat->winHide( TRUE );
				if( buttonEmote )
					buttonEmote->winHide( TRUE );
				if( listboxChatWindowScoreScreen )
					listboxChatWindowScoreScreen->winHide( TRUE );
				if( chatBoxBorder )
					chatBoxBorder->winHide( TRUE );
				if( buttonBuddies )
					buttonBuddies->winHide( TRUE );

				if( campaign->getFinalVictoryMovie().isNotEmpty() )
				{
					AsciiString vidName;
					vidName = campaign->getFinalVictoryMovie();
					Bool useLowRes = FALSE;
					if( TheGameLODManager )
					{
						if( !TheGameLODManager->didMemPass() )
							useLowRes = TRUE;
						if( TheGameLODManager->m_fieldAt16C4 <= 1 )
							useLowRes = TRUE;
					}
					if( !useLowRes )
						PlayMovieAndBlock( vidName );
				}
			}
		}
		else
		{
			GadgetRadioSetText( buttonContinue, TheGameText->fetch( "GUI:SaveAndContinue" ) );

			// auto save game
			TheGameState->missionSave();
			if( staticTextGameSaved )
				staticTextGameSaved->winHide( FALSE );
		}
	}
	else
	{
		GadgetRadioSetText( buttonContinue, TheGameText->fetch( "GUI:Retry" ) );
	}

	TheInGameUI->freeMessageResources();

	s_blankLayout->destroyWindows();
	delete s_blankLayout;
	s_blankLayout = 0;

	// set keyboard focus to main parent
	TheWindowManager->winSetFocus( parent );

	if( buttonOk )
		buttonOk->winHide( FALSE );
	if( buttonContinue )
		buttonContinue->winHide( FALSE );
	if( textEntryChat )
		textEntryChat->winHide( TRUE );
	if( buttonEmote )
		buttonEmote->winHide( TRUE );
	if( listboxChatWindowScoreScreen )
		listboxChatWindowScoreScreen->winHide( TRUE );
	if( chatBoxBorder )
		chatBoxBorder->winHide( TRUE );
	if( buttonBuddies )
		buttonBuddies->winHide( TRUE );

	TheTransitionHandler->setGroup( "ScoreScreenShow" );
}
