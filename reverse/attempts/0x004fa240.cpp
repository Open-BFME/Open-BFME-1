// ?populateGroupRoomListbox@@YAXPAVGameWindow@@@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// ?populateGroupRoomListbox@@YAXPAVGameWindow@@@Z
// retail 0x004FA240, 310 bytes; second non-folded instance of the ZH
// WOLLobbyMenu.cpp static (another copy already landed at 0x005397D0 as a
// naked lift under WOLLobbyMenu_populateGroupRoomListbox_Thunk.cpp -- this
// repo documents duplicated, non-ICF-folded bodies as expected). Callers here
// are WOLLobbyMenuUpdate (x2) and WOLLobbyMenuInit (x1), matching the ZH
// source's two call sites line for line.
// ZH source: GeneralsMD WOLLobbyMenu.cpp:340 populateGroupRoomListbox(GameWindow*):
// reset combo box, walk TheGameSpyInfo->getGroupRoomList() skipping the QM
// channel, add each room's translated name colored by whether it is the
// current group room, remember that selection, GadgetComboBoxSetSelectedPos
// at the end. BFME widened GameSpyGroupRoom by one trailing dword versus ZH's
// 5-int tail (see AsciiUnicodePairCopyCtor.cpp, matched 0x004F97B0), which is
// why the room's copy ctor there documents a 0x20-byte record.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &o ) : StringBase<char>( o ) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &o ) : StringBase<unsigned short>( o ) {}
	~UnicodeString() {}
};

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
// BFME widens the record by one trailing Int versus ZH's m_groupID/m_numWaiting/
// m_maxWaiting/m_numGames/m_numPlaying (see AsciiUnicodePairCopyCtor.cpp).
struct GameSpyGroupRoom
{
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
	BFME_VSLOT(5) BFME_VSLOT(6)
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

// ?populateGroupRoomListbox@@YAXPAVGameWindow@@@Z
void populateGroupRoomListbox( GameWindow *lb )
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
