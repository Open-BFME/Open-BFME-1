// ?rva005397D0PopulateGroupRoomListbox@Rva005397D0AptScreen@@QAEXXZ
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3DE /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Retail 0x005397D0, 329 bytes (ret at 0x00539918, INT3 padding from
// 0x00539919), replacing the 298-byte naked __emit lift
// WOLLobbyMenu_populateGroupRoomListbox_Thunk.cpp.
//
// The lift name ?populateGroupRoomListbox@@YAXPAVGameWindow@@@Z is
// contradicted by the body: the argument arrives in ECX and the body reads a
// GameWindow* member at this+0x190, so retail has a thiscall member here, not
// a static taking a GameWindow*. The owning class is not proven by a matched
// caller, so the class and method keep the address token. Linker locality puts
// the body beside two proven BfmeAptScreenOnlineCustomMatch members
// (0x00539720 scalar-deleting destructor, 0x00539750 leaveStagingRoom) and
// the matched insertGame declares a GameWindow* at +0x190 as well, so the
// owning class is most likely BfmeAptScreenOnlineCustomMatch; that is a hint,
// not a claim.
//
// The algorithm is the proven one from the Zero Hour twin
// (WOLLobbyMenu.cpp:337 populateGroupRoomListbox) and from the already matched
// sibling body 0x0052E990 (OnlineChatRva0052E990.cpp), which is the same loop
// with the +0x1C record field compared against 2 instead of 1 and the combo
// member at +0x4C instead of +0x190.

#include <map>

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	// Retail releases through StringBase::releaseBuffer (<char> 0x00887940,
	// <unsigned short> 0x008881D0) directly, not an out-of-line ~StringBase.
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

// The 0x20-byte group-room record, proven by the independently matched copy
// constructor at 0x004F97B0 (AsciiUnicodePairCopyCtor.cpp).
struct AsciiUnicodePair
{
	AsciiString m_ascii;
	UnicodeString m_unicode;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;

	AsciiUnicodePair( const AsciiUnicodePair &other );
};

typedef std::map<int, AsciiUnicodePair> GroupRoomMap;

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

class GameWindow;

void GadgetComboBoxReset( GameWindow *win );
int GadgetComboBoxAddEntry( GameWindow *win, UnicodeString text, int color );
void GadgetComboBoxSetItemData( GameWindow *win, int index, void *data );
void GadgetComboBoxSetSelectedPos( GameWindow *win, int index, bool dummy );

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyConfigInterface *TheGameSpyConfig;
extern int GameSpyColor[];

class Rva005397D0AptScreen
{
public:
	void rva005397D0PopulateGroupRoomListbox();

private:
	unsigned char m_prefix[ 0x190 ];
	GameWindow *m_comboLobbyGroupRooms;
};

void Rva005397D0AptScreen::rva005397D0PopulateGroupRoomListbox()
{
	GameWindow *lb = m_comboLobbyGroupRooms;
	if( !lb )
		return;

	GadgetComboBoxReset( lb );
	int indexToSelect = -1;
	GroupRoomMap::iterator iter;

	for( iter = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getGroupRoomList()->begin();
		iter != reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getGroupRoomList()->end(); ++iter )
	{
		AsciiUnicodePair room = iter->second;
		if( room.m_a != TheGameSpyConfig->getQMChannel() && room.m_f == 1 )
		{
			if( room.m_a == reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getCurrentGroupRoom() )
			{
				int selected = GadgetComboBoxAddEntry(
					lb, room.m_unicode, GameSpyColor[ 1 ] );
				GadgetComboBoxSetItemData(
					lb, selected, (void *)room.m_a );
				indexToSelect = selected;
			}
			else
			{
				int selected = GadgetComboBoxAddEntry(
					lb, room.m_unicode, GameSpyColor[ 2 ] );
				GadgetComboBoxSetItemData(
					lb, selected, (void *)room.m_a );
			}
		}
	}

	GadgetComboBoxSetSelectedPos( lb, indexToSelect, false );
}
