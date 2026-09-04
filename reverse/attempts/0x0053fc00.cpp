// ?applyStagingRoomRefresh@BfmeAptScreenOnlineCustomMatch@@QAEXXZ
// partial score=0.88 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BfmeAptScreenOnlineCustomMatch::applyStagingRoomRefresh, retail 0x0053FC00,
// 622 bytes. Apt-hosted RefreshGameListBox: listbox at this+0x18C, no buddy
// sort, then Enable/DisableButtonJoinGame via CallChild on the movie at
// [this+0x34]+0x250. Matched caller refreshStagingRoomList (0x00544DD0)
// names this method through ILT 0x00022999.

#include <map>
#include <set>

class GameWindow;
class GameSpyStagingRoom;

void GadgetListBoxGetSelected( GameWindow *listbox, int *selectList );
void *GadgetListBoxGetItemData( GameWindow *listbox, int row, int column );
int GadgetListBoxGetTopVisibleEntry( GameWindow *listbox );
void GadgetListBoxReset( GameWindow *listbox );
void GadgetListBoxSetSelected( GameWindow *listbox, int index );
void GadgetListBoxSetTopVisibleEntry( GameWindow *listbox, int index );

struct GameSortStruct
{
	bool operator()( GameSpyStagingRoom *left, GameSpyStagingRoom *right ) const;
};

typedef _STL::multiset<GameSpyStagingRoom *, GameSortStruct> SortedGameList;
typedef _STL::map<int, GameSpyStagingRoom *> StagingRoomMap;

class GameSpyStagingRoom
{
public:
	int getID() const { return m_id; }
	int getReportedNumPlayers() const { return m_reportedNumPlayers; }
	int getReportedMaxPlayers() const { return m_reportedMaxPlayers; }

private:
	unsigned char m_pad[ 0x41C ];
	int m_id;
	unsigned char m_mid[ 0x454 - 0x420 ];
	int m_reportedNumPlayers;
	int m_reportedMaxPlayers;
};

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
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class GameWindowManager
{
public:
	virtual void s00() = 0; virtual void s01() = 0; virtual void s02() = 0;
	virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
	virtual void s06() = 0; virtual void s07() = 0; virtual void s08() = 0;
	virtual void s09() = 0; virtual void s10() = 0; virtual void s11() = 0;
	virtual void s12() = 0; virtual void s13() = 0; virtual void s14() = 0;
	virtual void s15() = 0; virtual void s16() = 0; virtual void s17() = 0;
	virtual void s18() = 0; virtual void s19() = 0; virtual void s20() = 0;
	virtual void s21() = 0; virtual void s22() = 0; virtual void s23() = 0;
	virtual void s24() = 0; virtual void s25() = 0; virtual void s26() = 0;
	virtual void s27() = 0; virtual void s28() = 0; virtual void s29() = 0;
	virtual void s30() = 0; virtual void s31() = 0; virtual void s32() = 0;
	virtual void s33() = 0; virtual void s34() = 0; virtual void s35() = 0;
	virtual void s36() = 0; virtual void s37() = 0; virtual void s38() = 0;
	virtual void s39() = 0; virtual void s40() = 0; virtual void s41() = 0;
	virtual void s42() = 0; virtual void s43() = 0; virtual void s44() = 0;
	virtual void s45() = 0; virtual void s46() = 0;
	virtual void winSetLoneWindow( GameWindow *window ) = 0;
};

extern GameWindowManager *TheWindowManager;

class WindowManager
{
public:
	void add( void *ctx, const char *name, int kind, const char *value,
	          int a, int b, int c, int d );
};

extern WindowManager *g_theWindowManager;

class AptMovieHost
{
public:
	unsigned char m_pad[ 0x250 ];
	void *m_movie;
};

class Gen00038951
{
public:
	void handle( int value );
};

class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyStagingRoomRefresh();
	int insertGame( GameSpyStagingRoom *game );

private:
	unsigned char m_head[ 0x34 ];
	AptMovieHost *m_host;
	unsigned char m_gap[ 0x40 - 0x38 ];
	Gen00038951 m_setup;
	unsigned char m_mid[ 0x18C - 0x44 ];
	GameWindow *m_listbox;
	unsigned char m_tail[ 0x1D4 - 0x190 ];
	unsigned char m_joinEnabled;
};

void BfmeAptScreenOnlineCustomMatch::applyStagingRoomRefresh()
{
	GameWindow *win = m_listbox;
	if( !win )
		return;

	int selectedIndex = -1;
	int indexToSelect = -1;
	int selectedID = 0;
	GadgetListBoxGetSelected( win, &selectedIndex );
	if( selectedIndex != -1 )
		selectedID = (int)GadgetListBoxGetItemData( win, selectedIndex, 0 );
	int prevPos = GadgetListBoxGetTopVisibleEntry( win );
	GadgetListBoxReset( win );

	SortedGameList sgl;
	StagingRoomMap *srm = TheGameSpyInfo->getStagingRoomList();
	for( StagingRoomMap::iterator srmIt = srm->begin(); srmIt != srm->end(); ++srmIt )
		sgl.insert( srmIt->second );

	for( SortedGameList::iterator sglIt = sgl.begin(); sglIt != sgl.end(); ++sglIt )
	{
		GameSpyStagingRoom *game = *sglIt;
		if( game )
		{
			int index = insertGame( game );
			if( game->getID() == selectedID )
			{
				indexToSelect = index;
				m_setup.handle( (int)game );
			}
		}
	}

	GadgetListBoxSetSelected( win, indexToSelect );
	GadgetListBoxSetTopVisibleEntry( win, prevPos );

	const char *btn = 0;
	void *movie = 0;
	if( indexToSelect < 0 )
	{
		if( selectedID )
			TheWindowManager->winSetLoneWindow( 0 );
		m_setup.handle( 0 );
		if( m_joinEnabled )
		{
			m_joinEnabled = 0;
			movie = m_host->m_movie;
			btn = "DisableButtonJoinGame";
		}
	}
	else
	{
		srm = TheGameSpyInfo->getStagingRoomList();
		int id = (int)GadgetListBoxGetItemData( win, indexToSelect, 0 );
		StagingRoomMap::iterator it = srm->find( id );
		if( it != srm->end() )
		{
			GameSpyStagingRoom *game = it->second;
			if( game->getReportedNumPlayers() == game->getReportedMaxPlayers() )
			{
				if( m_joinEnabled )
				{
					m_joinEnabled = 0;
					movie = m_host->m_movie;
					btn = "DisableButtonJoinGame";
				}
			}
			else if( !m_joinEnabled )
			{
				m_joinEnabled = 1;
				movie = m_host->m_movie;
				btn = "EnableButtonJoinGame";
			}
		}
		else if( m_joinEnabled )
		{
			m_joinEnabled = 0;
			movie = m_host->m_movie;
			btn = "DisableButtonJoinGame";
		}
	}
	if( btn )
		g_theWindowManager->add( movie, "CallChild", 1, btn, 0, 0, 0, 0 );
}
