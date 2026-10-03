// cl: /DNDEBUG /MD /EHsc
// Open-BFME: PopupHostGameSystem, retail 0x004D6EE0, 764 bytes.
// Identity: FunctionLexicon entry 0x012A9618 pairs the string
// "PopupHostGameSystem" (0x01087458) with ILT 0x0043F684 -> 0x004D6EE0.
// ZH twin: PopupHostGame.cpp PopupHostGameSystem, kept line for line.
// Message values follow inputs/reference/shims/sweep/GameClient/Gadget.h
// (GCM_*/GEM_* shifted +2 against ZH). The window statics sit in ZH
// declaration order from 0x012F3EEC (parentPopupID, stored by
// PopupHostGameInit) matching the pinned textEntryGameName 0x012F3F14 and
// comboBoxLadderName 0x012F3F28; they are defined by PopupHostGame.cpp.

typedef unsigned short WideChar;

extern "C" __declspec(dllimport) int __cdecl iswspace( WideChar c );
extern const char g_bfmeEmptyUnicode[];

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
	~StringBase() { releaseBuffer(); }

public:
	void set( const StringBase<T> &other );
	void trim();

private:
	void releaseBuffer();

	Header *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<WideChar>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	UnicodeString &operator=( const UnicodeString &other )
	{
		StringBase<WideChar>::set( *(const StringBase<WideChar> *)&other );
		return *this;
	}

	void set( const UnicodeString &other )
	{
		StringBase<WideChar>::set( *(const StringBase<WideChar> *)&other );
	}

	void trim() { StringBase<WideChar>::trim(); }

	void translate( const AsciiString &src );

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	const WideChar *str() const
	{
		return m_data ? m_data->m_text : (const WideChar *)g_bfmeEmptyUnicode;
	}
};

class GameWindow
{
public:
	int winGetWindowId();
};

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
typedef unsigned int WindowMsgData;

// GameWindow.h GameWindowMessage / sweep Gadget.h GadgetGameMessage values
enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 23,
	GBM_SELECTED = 0x4008,
	GCM_SELECTED = 0x4025,
	GEM_UPDATE_TEXT = 0x4031
};

enum GSOverlayType
{
	GSOVERLAY_PLAYERINFO,
	GSOVERLAY_MAPSELECT,
	GSOVERLAY_BUDDY,
	GSOVERLAY_PAGE,
	GSOVERLAY_GAMEOPTIONS,
	GSOVERLAY_GAMEPASSWORD,
	GSOVERLAY_LADDERSELECT
};

void GameSpyOpenOverlay( GSOverlayType );
void GameSpyCloseOverlay( GSOverlayType );
void SetLobbyAttemptHostJoin( bool start );

UnicodeString GadgetTextEntryGetText( GameWindow *window );
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
void GadgetComboBoxGetSelectedPos( GameWindow *combo, int *pos );
void *GadgetComboBoxGetItemData( GameWindow *combo, int index );

#define GSI_SLOT( n ) virtual void gsiSlot##n() = 0
class GameSpyInfo
{
public:
	GSI_SLOT( 0 ); GSI_SLOT( 1 ); GSI_SLOT( 2 ); GSI_SLOT( 3 );
	GSI_SLOT( 4 ); GSI_SLOT( 5 ); GSI_SLOT( 6 ); GSI_SLOT( 7 );
	GSI_SLOT( 8 ); GSI_SLOT( 9 ); GSI_SLOT( 10 ); GSI_SLOT( 11 );
	GSI_SLOT( 12 ); GSI_SLOT( 13 ); GSI_SLOT( 14 ); GSI_SLOT( 15 );
	GSI_SLOT( 16 ); GSI_SLOT( 17 ); GSI_SLOT( 18 ); GSI_SLOT( 19 );
	GSI_SLOT( 20 ); GSI_SLOT( 21 ); GSI_SLOT( 22 ); GSI_SLOT( 23 );
	GSI_SLOT( 24 ); GSI_SLOT( 25 );
	virtual AsciiString getLocalName() = 0;
};
#undef GSI_SLOT

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

void createGame( void );
void PopulateCustomLadderComboBox( void );

enum NameKeyType { NAMEKEY_INVALID = 0 };

extern NameKeyType textEntryGameNameID;
extern NameKeyType buttonCreateGameID;
extern NameKeyType buttonCancelID;
extern NameKeyType comboBoxLadderNameID;
extern GameWindow *parentPopup;
extern GameWindow *textEntryGameName;
extern bool isPopulatingLadderBox;

WindowMsgHandledType PopupHostGameSystem( GameWindow *window, unsigned int msg, WindowMsgData mData1, WindowMsgData mData2 )
{
	switch ( msg )
	{
		case GWM_CREATE:
		{
			break;
		}

		case GWM_DESTROY:
		{
			parentPopup = 0;
			break;
		}

		case GWM_INPUT_FOCUS:
		{
			if ( mData1 == 1 )
				*(bool *)mData2 = true;
			break;
		}

		case GEM_UPDATE_TEXT:
		{
			GameWindow *control = (GameWindow *)mData1;
			int controlID = control->winGetWindowId();

			if ( controlID == textEntryGameNameID )
			{
				UnicodeString txtInput;

				txtInput.set( GadgetTextEntryGetText( textEntryGameName ) );

				const WideChar *c = txtInput.str();
				while ( c && ( iswspace( *c ) ) )
					c++;

				if ( c )
					txtInput = UnicodeString( c );
				else
					txtInput = UnicodeString::TheEmptyString;

				GadgetTextEntrySetText( textEntryGameName, txtInput );
			}
			break;
		}

		case GCM_SELECTED:
		{
			GameWindow *control = (GameWindow *)mData1;
			int controlID = control->winGetWindowId();
			int pos = -1;
			GadgetComboBoxGetSelectedPos( control, &pos );

			if ( controlID == comboBoxLadderNameID && !isPopulatingLadderBox )
			{
				if ( pos >= 0 )
				{
					int ladderID = (int)GadgetComboBoxGetItemData( control, pos );
					if ( ladderID < 0 )
					{
						PopulateCustomLadderComboBox();
						GameSpyOpenOverlay( GSOVERLAY_LADDERSELECT );
					}
				}
			}
			break;
		}

		case GBM_SELECTED:
		{
			GameWindow *control = (GameWindow *)mData1;
			int controlID = control->winGetWindowId();

			if ( controlID == buttonCancelID )
			{
				parentPopup = 0;
				GameSpyCloseOverlay( GSOVERLAY_GAMEOPTIONS );
				SetLobbyAttemptHostJoin( false );
			}
			else if ( controlID == buttonCreateGameID )
			{
				UnicodeString name;
				name = GadgetTextEntryGetText( textEntryGameName );
				name.trim();
				if ( name.getLength() <= 0 )
				{
					name.translate( reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getLocalName() );
					GadgetTextEntrySetText( textEntryGameName, name );
				}
				createGame();
				parentPopup = 0;
				GameSpyCloseOverlay( GSOVERLAY_GAMEOPTIONS );
			}
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
