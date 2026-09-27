// ?ScoreScreenSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.6 date=2026-09-27
// ScoreScreenSystem candidate excerpt from the owning ScoreScreen.cpp TU.
// The surrounding ScoreScreen globals and engine declarations remain in that TU.

namespace ScoreScreenRvaString
{
	template <typename T> class Base
	{
	public:
		Base() : m_data( 0 ) {}
		Base( const T *text );
		Base( const Base<T> &other );
		~Base();

		void *m_data;
	};

	class Ascii : private Base<char>
	{
	public:
		Ascii( const char *text ) : Base<char>( text ) {}
		Ascii( const Ascii &other ) : Base<char>( other ) {}
		~Ascii() {}
	};
}

class ScoreScreenRvaTransitionHandlerView
{
public:
	void remove( ScoreScreenRvaString::Ascii groupName, Bool skipPending );
};

class ScoreScreenRvaWindowLayoutView
{
public:
	virtual void runInit( void *userData ) = 0;
	virtual ~ScoreScreenRvaWindowLayoutView() {}
	virtual void runUpdate( void *userData ) = 0;
	virtual void runShutdown( void *userData ) = 0;
	virtual void hide( Bool hidden ) = 0;
	virtual void bringForward( void ) = 0;
};

class ScoreScreenRvaUnicodeString : private ScoreScreenRvaString::Base<WideChar>
{
public:
	ScoreScreenRvaUnicodeString() : ScoreScreenRvaString::Base<WideChar>() {}
	ScoreScreenRvaUnicodeString( const ScoreScreenRvaUnicodeString &other )
		: ScoreScreenRvaString::Base<WideChar>( other ) {}
	~ScoreScreenRvaUnicodeString() {}
	void set( const UnicodeString &source );
	void trim( void );
	Bool isEmpty( void ) const;
	const WideChar *str( void ) const;
};

class ScoreScreenRvaAsciiString : private ScoreScreenRvaString::Base<char>
{
public:
	ScoreScreenRvaAsciiString() : ScoreScreenRvaString::Base<char>() {}
	ScoreScreenRvaAsciiString( const char *text ) : ScoreScreenRvaString::Base<char>( text ) {}
	ScoreScreenRvaAsciiString( const ScoreScreenRvaAsciiString &other )
		: ScoreScreenRvaString::Base<char>( other ) {}
	~ScoreScreenRvaAsciiString() {}
	void __cdecl format( ScoreScreenRvaAsciiString format, Int value );
	Bool isEmpty( void ) const;
	const char *str( void ) const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

class ScoreScreenRvaNameKeyGeneratorView
{
public:
	NameKeyType nameToKey( const char *name );
};

class ScoreScreenRvaCampaignManagerView
{
public:
	static ScoreScreenRvaAsciiString TheEmptyString;
	void setCampaign( ScoreScreenRvaAsciiString campaign );
	ScoreScreenRvaAsciiString getCurrentMap( void );
};

typedef void (*ScoreScreenRvaGameStartCallback)( void );
void ScoreScreenRvaCheckForCDAtGameStart( ScoreScreenRvaGameStartCallback callback,
	ScoreScreenRvaGameStartCallback unused );

class ScoreScreenRvaLanApiView
{
public:
	virtual void slot00( void ) = 0; virtual void slot04( void ) = 0;
	virtual void slot08( void ) = 0; virtual void slot0C( void ) = 0;
	virtual void slot10( void ) = 0; virtual void slot14( void ) = 0;
	virtual void slot18( void ) = 0; virtual void slot1C( void ) = 0;
	virtual void slot20( void ) = 0; virtual void slot24( void ) = 0;
	virtual void slot28( void ) = 0; virtual void slot2C( void ) = 0;
	virtual void slot30( void ) = 0; virtual void slot34( void ) = 0;
	virtual void slot38( void ) = 0; virtual void slot3C( void ) = 0;
	virtual void RequestChat( ScoreScreenRvaUnicodeString message, int format ) = 0;
};

static inline void ScoreScreenRvaGadgetTextEntrySetText(
	GameWindow *window, ScoreScreenRvaUnicodeString text )
{
	TheWindowManager->winSendSystemMsg( window, GEM_SET_TEXT,
		(WindowMsgData)&text, 0 );
}

class ScoreScreenRvaGameSpyInfoView
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0;
	virtual void slot3C() = 0; virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0; virtual void slot50() = 0;
	virtual BuddyInfoMap *getBuddyMap() = 0;
};

class ScoreScreenRvaBuddyRequest
{
public:
	enum { BUDDYREQUEST_ADDBUDDY = 5 };
	int buddyRequestType;
	union
	{
		struct { int id; WideChar text[MAX_BUDDY_CHAT_LEN]; } addbuddy;
		char body[0x2B4];
	} arg;
};
typedef char ScoreScreenRvaBuddyRequestSizeCheck[
	sizeof( ScoreScreenRvaBuddyRequest ) == 0x2B8 ? 1 : -1 ];

class ScoreScreenRvaBuddyMessageQueueView
{
public:
	virtual ~ScoreScreenRvaBuddyMessageQueueView() {}
	virtual void startThread( void ) = 0;
	virtual void endThread( void ) = 0;
	virtual Bool isThreadRunning( void ) = 0;
	virtual Bool isConnected( void ) = 0;
	virtual Bool isConnecting( void ) = 0;
	virtual void addRequest( const ScoreScreenRvaBuddyRequest &request ) = 0;
};

WindowMsgHandledType ScoreScreenSystem( GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2 )
{
	ScoreScreenRvaUnicodeString txtInput;
	register GameWindow *control = (GameWindow *)mData1;

	switch( msg )
	{
		case GWM_DESTROY:
		{
			break;
		}

		case GWM_INPUT_FOCUS:
		{
			if( mData1 == TRUE )
				*(Bool *)mData2 = TRUE;
			break;
		}

		case GBM_SELECTED:
		{
			((ScoreScreenRvaTransitionHandlerView *)TheTransitionHandler)->remove(
				ScoreScreenRvaString::Ascii("ScoreScreenShow"), TRUE);
			ReplayWasPressed = FALSE;

			Int controlID = control->winGetWindowId();
			if( controlID == buttonOkID )
			{
				TheShell->pop();
				((ScoreScreenRvaCampaignManagerView *)TheCampaignManager)->setCampaign(
					ScoreScreenRvaCampaignManagerView::TheEmptyString);
			}
			else if ( controlID == buttonContinueID )
			{
				if(!buttonIsFinishCampaign)
					ReplayWasPressed = TRUE;
				if( screenType == SCORESCREEN_SINGLEPLAYER)
				{
					ScoreScreenRvaAsciiString mapName =
						((ScoreScreenRvaCampaignManagerView *)TheCampaignManager)->getCurrentMap();
					if( mapName.isEmpty() )
					{
						ReplayWasPressed = FALSE;
						TheShell->pop();
					}
					else
					{
						ScoreScreenRvaCheckForCDAtGameStart( startNextCampaignGame,
							(ScoreScreenRvaGameStartCallback)0x8e25e0 );
					}
				}
			}
			else if ( controlID == buttonBuddiesID )
			{
				GameSpyToggleOverlay( GSOVERLAY_BUDDY );
			}
			else if ( controlID == buttonSaveReplayID )
			{
				ScoreScreenEnableControls(FALSE);
				WindowLayout *saveReplayLayout = TheShell->getPopupReplayLayout();
				DEBUG_ASSERTCRASH( saveReplayLayout, ("Unable to get save replay menu layout.\n") );
				ScoreScreenRvaWindowLayoutView *layout =
					(ScoreScreenRvaWindowLayoutView *)saveReplayLayout;
				layout->runInit( 0 );
				layout->hide( FALSE );
				layout->bringForward();
			}
			else if ( controlID == buttonEmoteID )
			{
				txtInput.set(GadgetTextEntryGetText( textEntryChat ));
				ScoreScreenRvaGadgetTextEntrySetText( textEntryChat,
					*(ScoreScreenRvaUnicodeString *)0x01336E54 );
				txtInput.trim();
				if (!txtInput.isEmpty())
					if(TheLAN)
						((ScoreScreenRvaLanApiView *)TheLAN)->RequestChat(
							(ScoreScreenRvaUnicodeString &)txtInput,
							LANAPIInterface::LANCHAT_EMOTE);
			}
			for(Int i = 0; i < MAX_SLOTS; ++i)
			{
				ScoreScreenRvaAsciiString name;
				name.format("ScoreScreen.wnd:ButtonAdd%d", i);
				if( controlID ==
					((ScoreScreenRvaNameKeyGeneratorView *)TheNameKeyGenerator)->nameToKey(
						name.str()))
				{
					Bool notBuddy = TRUE;
					Int playerID = (Int)GadgetButtonGetData(TheWindowManager->winGetWindowFromId(NULL,controlID));
					BuddyInfoMap *buddies =
						((ScoreScreenRvaGameSpyInfoView *)TheGameSpyInfo)->getBuddyMap();
					BuddyInfoMap::iterator bIt;
					if( playerID > 0)
					{
						bIt = buddies->find(playerID);
						if (bIt != buddies->end())
						{
							notBuddy = FALSE;
						}
					}
					if(notBuddy)
					{
						ScoreScreenRvaBuddyRequest req;
						req.buddyRequestType = ScoreScreenRvaBuddyRequest::BUDDYREQUEST_ADDBUDDY;
						req.arg.addbuddy.id = playerID;
						ScoreScreenRvaUnicodeString buddyAddstr;
						buddyAddstr.set( TheGameText->fetch("GUI:BuddyAddReq") );
						wcsncpy(req.arg.addbuddy.text, buddyAddstr.str(), MAX_BUDDY_CHAT_LEN);
						req.arg.addbuddy.text[MAX_BUDDY_CHAT_LEN-1] = 0;
						((ScoreScreenRvaBuddyMessageQueueView *)TheGameSpyBuddyMessageQueue)->addRequest(req);
					}
					break;
				}
			}
		}

		case GEM_EDIT_DONE:
		{
			Int controlID = control->winGetWindowId();
			if ( controlID == textEntryChatID )
			{
				txtInput.set(GadgetTextEntryGetText( textEntryChat ));
				ScoreScreenRvaGadgetTextEntrySetText( textEntryChat,
					*(ScoreScreenRvaUnicodeString *)0x01336E54 );
				txtInput.trim();
				if (!txtInput.isEmpty())
					if(TheLAN)
					((ScoreScreenRvaLanApiView *)TheLAN)->RequestChat(
						(ScoreScreenRvaUnicodeString &)txtInput,
						LANAPIInterface::LANCHAT_NORMAL);
			}
		}
	}
	return MSG_HANDLED;
}
