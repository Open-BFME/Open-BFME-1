// ?applyStagingRoomRefresh@BfmeAptScreenOnlineCustomMatch@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Retail RVA 0053FC00, complete 622 bytes through RET at 0053FE6D.
// Matched caller OnlineCustomMatchRefreshStagingList.cpp names this entry.
// Existing direct-callee bindings are retained. The local dispatch/host views
// and unknown fields retain offsets; the supplied GameSpy header does not
// model retail slot 98 or the dwords at 454/458. See identity evidence.

#define Matrix4x4 Matrix4
class INI;
#include "GameNetwork/GameSpy/StagingRoomGameInfo.h"
#include "GameClient/GameWindowManager.h"
#include <map>
#include <set>


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

// Only pointer accesses use these views; no replacement GameSpy type is declared.
static int field41c(GameSpyStagingRoom *p) { return *(int*)((char*)p+0x41c); }
static int field454(GameSpyStagingRoom *p) { return *(int*)((char*)p+0x454); }
static int field458(GameSpyStagingRoom *p) { return *(int*)((char*)p+0x458); }

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class Rva0053FC00GameSpySlots
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
	virtual StagingRoomMap *slot98() = 0;
};
#undef GAMESPY_SLOT

class GameSpyInfo;
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

class BfmeLevelAN {
public: char *bfmeBuildAN(unsigned int,int,int,int,int,int,int,int);
};
class WindowManager;
extern WindowManager *g_theWindowManager;

class Rva0053FC00Host
{
public:
	unsigned char m_pad[ 0x250 ];
	unsigned int m_250;
};

class MpGameSetup
{
public:
	void bfmeSetSecondGame(GameInfo *game);
};

class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyStagingRoomRefresh();
	int insertGame( GameSpyStagingRoom *game );

private:
	unsigned char m_head[ 0x34 ];
	Rva0053FC00Host *m_034;
	unsigned char m_gap[ 0x40 - 0x38 ];
	MpGameSetup m_040;
	unsigned char m_mid[ 0x18C - 0x44 ];
	GameWindow *m_18c;
	unsigned char m_tail[ 0x1D4 - 0x190 ];
	unsigned char m_1d4;
};

void BfmeAptScreenOnlineCustomMatch::applyStagingRoomRefresh()
{
	GameWindow *win = m_18c;
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
	StagingRoomMap *srm = reinterpret_cast<Rva0053FC00GameSpySlots*>(TheGameSpyInfo)->slot98();
	for( StagingRoomMap::iterator srmIt = srm->begin(); srmIt != srm->end(); ++srmIt )
		sgl.insert( srmIt->second );

	for( SortedGameList::iterator sglIt = sgl.begin(); sglIt != sgl.end(); ++sglIt )
	{
		GameSpyStagingRoom *game = *sglIt;
		if( game )
		{
			int index = insertGame( game );
			if( field41c(game) == selectedID )
			{
				indexToSelect = index;
				m_040.bfmeSetSecondGame(game);
			}
		}
	}

	GadgetListBoxSetSelected( win, indexToSelect );
	GadgetListBoxSetTopVisibleEntry( win, prevPos );

	const char *btn = 0;
	unsigned int movie = 0;
	if( indexToSelect < 0 )
	{
		if( selectedID )
			TheWindowManager->winSetLoneWindow( 0 );
		m_040.bfmeSetSecondGame(0);
		if( m_1d4 )
		{
			m_1d4 = 0;
			movie = m_034->m_250;
			btn = "DisableButtonJoinGame";
		}
	}
	else
	{
		srm = reinterpret_cast<Rva0053FC00GameSpySlots*>(TheGameSpyInfo)->slot98();
		int id = (int)GadgetListBoxGetItemData( win, indexToSelect, 0 );
		StagingRoomMap::iterator it = srm->find( id );
		if( it != srm->end() )
		{
			GameSpyStagingRoom *game = it->second;
			if( field454(game) != field458(game) )
			{
				if( !m_1d4 ) {
					m_1d4 = 1;
					movie = m_034->m_250;
					reinterpret_cast<BfmeLevelAN*>(g_theWindowManager)->bfmeBuildAN((unsigned)movie,(int)"CallChild",1,(int)"EnableButtonJoinGame",0,0,0,0);
				}
			}
			else if( m_1d4 ) {
				m_1d4=0;
				movie=m_034->m_250;
				btn="DisableButtonJoinGame";
			}
		}
		else if( m_1d4 )
		{
			m_1d4 = 0;
			movie = m_034->m_250;
			btn = "DisableButtonJoinGame";
		}
	}
	if( btn )
		reinterpret_cast<BfmeLevelAN*>(g_theWindowManager)->bfmeBuildAN((unsigned)movie,(int)"CallChild",1,(int)btn,0,0,0,0);
}
