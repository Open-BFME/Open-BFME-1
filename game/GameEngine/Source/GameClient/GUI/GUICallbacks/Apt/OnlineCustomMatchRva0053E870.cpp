// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <map>
#include <string>
#include "ascii_string.h"

#include "unicode_string.h"

class GameWindow;
class GameSpyStagingRoom;
class LadderInfo;

void GadgetListBoxGetSelected( GameWindow *listbox, int *selectList );
void *GadgetListBoxGetItemData( GameWindow *listbox, int row, int column );
void GSMessageBoxOk( UnicodeString title, UnicodeString body, void ( *cb )() );
int Rva0009B4B0( int a, int b );

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

struct StagingRoomMapNode
{
	unsigned char m_links[ 0x14 ];
	GameSpyStagingRoom *m_room;
};

typedef _STL::map<int, GameSpyStagingRoom *> StagingRoomMap;

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 );
	virtual StagingRoomMap *getStagingRoomList() = 0;
	GAMESPY_SLOT( 39 ); GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 );
	GAMESPY_SLOT( 43 ); GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 );
	virtual void markAsStagingRoomJoiner( int id ) = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class GameSpyStagingRoom
{
public:
	UnicodeString getGameName();
	AsciiString getLadderIP() const;
	void setLadderIP( AsciiString ip );
	unsigned int getExeCRC() { return m_exeCRC; }
	unsigned int getIniCRC() { return m_iniCRC; }
	unsigned int getExtraCRC() { return m_extraCRC; }
	unsigned short getLadderPort() const { return m_ladderPort; }
    void setLadderPort(unsigned short port) { m_ladderPort=port; }
    int getReportedNumPlayers() const { return m_reportedNumPlayers; }
    int getReportedMaxPlayers() const { return m_reportedMaxPlayers; }
    bool getHasPassword() const { return m_hasPassword; }

	unsigned char m_head[ 0x428 ];
	bool m_hasPassword;
	unsigned char m_mid[ 0x430 - 0x429 ];
	unsigned int m_exeCRC;
	unsigned int m_iniCRC;
	unsigned int m_extraCRC;
	unsigned char m_gap[ 0x450 - 0x43C ];
	unsigned short m_ladderPort;
	unsigned char m_padPort[ 2 ];
	int m_reportedNumPlayers;
	int m_reportedMaxPlayers;
};

class Gen004D4880
{
public:
	void bfmeSet( UnicodeString value );
};

extern GameSpyStagingRoom *TheGameSpyGame;

class GlobalData
{
public:
	unsigned char m_pad[ 0xBC8 ];
	unsigned int m_iniCRC;
	unsigned char m_gap[ 4 ];
	unsigned int m_exeCRC;
	unsigned int m_extraCRC;
};

extern GlobalData *TheWritableGlobalData;
// ?crcEqual0053E870@@YA_NII@Z absent-from-retail
static __forceinline bool crcEqual0053E870(unsigned int left, unsigned int right)
{
    return left == right;
}


class LadderList
{
public:
	const LadderInfo *findLadder( const AsciiString &addr, unsigned short port );
};


extern LadderList *TheLadderList;

class BfmeLevelAN
{
public:
    char *bfmeBuildAN(unsigned int, int, int, int, int, int, int, int);
};

class WindowManager
{
public:
    // ?add@WindowManager@@QAEXPAXPBDH1HHHH@Z absent-from-retail
    __forceinline void add(void *ctx, const char *name, int kind, const char *value, int a, int b, int c, int d)
    {
        ((BfmeLevelAN *)this)->bfmeBuildAN((unsigned int)ctx, (int)name, kind, (int)value, a, b, c, d);
    }
};

// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager

class AptMovieHost
{
public:
	unsigned char m_pad[ 0x250 ];
	void *m_movie;
};

class StlStr
{
public:
	StlStr &operator=( const char *s );
private:
	char m_bytes[ 12 ];
};

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();
	int peerRequestType;
	_STL::string nick;
	_STL::basic_string<unsigned short, _STL::char_traits<unsigned short>, _STL::allocator<unsigned short> > text;
	_STL::string password;
	unsigned char m_mid[ 0xE4 - 0x28 ];
	int m_stagingRoomId;
	unsigned char m_tail[ 0x194 - 0xE8 ];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual int isThreadRunning() = 0;
	virtual int isConnected() = 0;
	virtual int isConnecting() = 0;
	virtual void addRequest( const PeerRequest &request ) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

typedef char PeerRequestSizeCheck[ sizeof( PeerRequest ) == 0x194 ? 1 : -1 ];
class Rva00385F20Room
{
public:
    UnicodeString getGameName() const;
};

typedef char RoomLayoutCheck[ (int)&( (GameSpyStagingRoom *)0 )->m_ladderPort == 0x450 ? 1 : -1 ];

class BfmeAptScreenOnlineCustomMatch
{
public:
	void rva0053E870();
	void applyPreferredGameNamePassword( bool fromPrefs );

private:
	unsigned char m_head[ 0x34 ];
	AptMovieHost *m_field34;
	unsigned char m_mid[ 0x188 - 0x38 ];
	int m_state;
	GameWindow *m_gameList;
	unsigned char m_gap[ 0x1B4 - 0x190 ];
	unsigned char m_field1B4;
	unsigned char m_pad1B5[ 3 ];
	unsigned char m_gap1B8[ 0x1BC - 0x1B8 ];
	int m_field1BC;
	unsigned char m_gap1C0[ 0x1C4 - 0x1C0 ];
	int m_field1C4;
	unsigned char m_gap1C8[ 0x1CC - 0x1C8 ];
	int m_selectedID;
};

// ?rva0053E870@BfmeAptScreenOnlineCustomMatch@@QAEXXZ
void BfmeAptScreenOnlineCustomMatch::rva0053E870()
{
	if( m_field1B4 )
		return;

	m_state = 1;
	m_field1C4 = 0;
	// Look for a game to join
	int selected;
	GadgetListBoxGetSelected( m_gameList, &selected );
	if( selected >= 0 )
	{
		int selectedID = (int)GadgetListBoxGetItemData( m_gameList, selected, 0 );
		if( selectedID > 0 )
		{
			StagingRoomMap *srm = TheGameSpyInfo->getStagingRoomList();
			StagingRoomMap::iterator srmIt = srm->find( selectedID );
			if( srmIt != srm->end() )
			{
				GameSpyStagingRoom *roomToJoin = srmIt->second;
				bool exeOk = roomToJoin && crcEqual0053E870(roomToJoin->getExeCRC(),(unsigned int)Rva0009B4B0((int)TheWritableGlobalData->m_exeCRC,(int)TheWritableGlobalData->m_exeCRC));
				bool iniOk = roomToJoin && roomToJoin->getIniCRC() == TheWritableGlobalData->m_iniCRC;
				bool extraOk = roomToJoin && roomToJoin->getExtraCRC() == TheWritableGlobalData->m_extraCRC;
				if( !exeOk || !iniOk || !extraOk )
				{
					// bad crc.  don't go.
					GSMessageBoxOk( TheGameText->fetch( "GUI:JoinFailedDefault" ),
						TheGameText->fetch( "GUI:JoinFailedCRCMismatch" ), 0 );
					return;
				}
				bool unknownLadder = ( roomToJoin->getLadderPort() && TheLadderList->findLadder(
					roomToJoin->getLadderIP(), roomToJoin->getLadderPort() ) == 0 );
				if( unknownLadder )
				{
					GSMessageBoxOk( TheGameText->fetch( "GUI:JoinFailedDefault" ),
						TheGameText->fetch( "GUI:JoinFailedUnknownLadder" ), 0 );
					return;
				}
				if( roomToJoin->getReportedNumPlayers() == roomToJoin->getReportedMaxPlayers() )
				{
					GSMessageBoxOk( TheGameText->fetch( "GUI:JoinFailedDefault" ),
						TheGameText->fetch( "GUI:JoinFailedRoomFull" ), 0 );
					return;
				}
				m_field1B4 = 1;
				m_field1BC = -1;
				if( roomToJoin->getHasPassword() )
				{
					m_selectedID = selectedID;
					g_theWindowManager->add(m_field34->m_movie, "CallChild", 1, "EnterPassword", 0, 0, 0, 0);
					applyPreferredGameNamePassword( 0 );
					m_state = 10;
				}
				else
				{
					TheGameSpyInfo->markAsStagingRoomJoiner( selectedID );
					( (Gen004D4880 *)TheGameSpyGame )->bfmeSet( ((const Rva00385F20Room *)roomToJoin)->getGameName() );
					TheGameSpyGame->setLadderIP( roomToJoin->getLadderIP() );
					TheGameSpyGame->setLadderPort( roomToJoin->getLadderPort() );
					// no password - just join it
					PeerRequest req;
					req.peerRequestType = 0xB;
					req.text = ((const Rva00385F20Room *)srmIt->second)->getGameName().str();
					req.m_stagingRoomId = selectedID;
					req.password = "";
					TheGameSpyPeerMessageQueue->addRequest( req );
					m_state = 0xB;
				}
			}
		}
		else
		{
			GSMessageBoxOk( TheGameText->fetch( "GUI:Error" ),
				TheGameText->fetch( "GUI:NoGameInfo" ), 0 );
		}
	}
	else
	{
		GSMessageBoxOk( TheGameText->fetch( "GUI:Error" ),
			TheGameText->fetch( "GUI:NoGameSelected" ), 0 );
	}
}
