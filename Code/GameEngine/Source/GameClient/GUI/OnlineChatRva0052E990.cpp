// ?rva0052E990@BfmeAptScreenOnlineChat@@QAEXXZ
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3DE /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include <map>

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();

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

extern GameSpyInfo *TheGameSpyInfo;
extern GameSpyConfigInterface *TheGameSpyConfig;
extern int GameSpyColor[];

class Rva0052E990BfmeAptScreenOnlineChat
{
public:
	void rva0052E990();

private:
	unsigned char m_prefix[ 0x4c ];
	GameWindow *m_chatLobbies;
};

// ?rva0052E990@BfmeAptScreenOnlineChat@@QAEXXZ
void Rva0052E990BfmeAptScreenOnlineChat::rva0052E990()
{
	if( !m_chatLobbies )
		return;

	GadgetComboBoxReset( m_chatLobbies );
	int indexToSelect = -1;
	GroupRoomMap::iterator iter;

	for( iter = TheGameSpyInfo->getGroupRoomList()->begin();
		iter != TheGameSpyInfo->getGroupRoomList()->end(); ++iter )
	{
		AsciiUnicodePair room = iter->second;
		if( room.m_a != TheGameSpyConfig->getQMChannel() && room.m_f == 2 )
		{
			if( room.m_a == TheGameSpyInfo->getCurrentGroupRoom() )
			{
				int selected = GadgetComboBoxAddEntry(
					m_chatLobbies, room.m_unicode, GameSpyColor[ 1 ] );
				GadgetComboBoxSetItemData(
					m_chatLobbies, selected, (void *)room.m_a );
				indexToSelect = selected;
			}
			else
			{
				int selected = GadgetComboBoxAddEntry(
					m_chatLobbies, room.m_unicode, GameSpyColor[ 2 ] );
				GadgetComboBoxSetItemData(
					m_chatLobbies, selected, (void *)room.m_a );
			}
		}
	}

	GadgetComboBoxSetSelectedPos( m_chatLobbies, indexToSelect, false );
}
