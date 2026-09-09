// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// byte-exact reconstruction of WOLLobbyMenu::populateGroupRoomListbox at retail 0x004FA240

#include <map>

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &o ) : StringBase<char>( o ) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &o ) : StringBase<unsigned short>( o ) {}
	~UnicodeString() {}
};

class GameWindow;

class GameSpyGroupRoom
{
	public:
	AsciiString m_name;
	UnicodeString m_translatedName;
	int m_groupID;
	int m_numWaiting;
	int m_maxWaiting;
	int m_numGames;
	int m_numPlaying;
	int m_bfmeExtra;
};

typedef std::map<int, GameSpyGroupRoom> GroupRoomMap;

#define BFME_VSLOT(n) virtual void slot##n();

class GameSpyInfo
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2)
	virtual GroupRoomMap *getGroupRoomList();
	BFME_VSLOT(4) BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7)
	BFME_VSLOT(8) BFME_VSLOT(9) BFME_VSLOT(10)
	virtual int getCurrentGroupRoom();
};

class GameSpyConfigInterface
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7)
	virtual int getQMChannel();
};

void GadgetComboBoxReset( GameWindow *win );
int GadgetComboBoxAddEntry( GameWindow *win, UnicodeString text, int color );
void GadgetComboBoxSetItemData( GameWindow *win, int index, void *data );
void GadgetComboBoxSetSelectedPos( GameWindow *win, int index, bool dummy );

extern GameSpyInfo *TheGameSpyInfo;
extern GameSpyConfigInterface *TheGameSpyConfig;

static int g_colorCurrentRoom;
static int g_colorRoom;

static void populateGroupRoomListbox( GameWindow *lb )
{
	if ( !lb )
		return;

	GadgetComboBoxReset( lb );
	int indexToSelect = -1;
	GroupRoomMap::iterator iter;

	for ( iter = TheGameSpyInfo->getGroupRoomList()->begin(); iter != TheGameSpyInfo->getGroupRoomList()->end(); ++iter )
	{
		GameSpyGroupRoom room = iter->second;
		if ( room.m_groupID != TheGameSpyConfig->getQMChannel() )
		{
			if ( room.m_groupID == TheGameSpyInfo->getCurrentGroupRoom() )
			{
				int selected = GadgetComboBoxAddEntry( lb, room.m_translatedName, g_colorCurrentRoom );
				GadgetComboBoxSetItemData( lb, selected, (void *) room.m_groupID );
				indexToSelect = selected;
			}
			else
			{
				int selected = GadgetComboBoxAddEntry( lb, room.m_translatedName, g_colorRoom );
				GadgetComboBoxSetItemData( lb, selected, (void *) room.m_groupID );
			}
		}
	}

	GadgetComboBoxSetSelectedPos( lb, indexToSelect, false );
}

void keepPopulateGroupRoomListbox( GameWindow *lb )
{
	populateGroupRoomListbox( lb );
}
