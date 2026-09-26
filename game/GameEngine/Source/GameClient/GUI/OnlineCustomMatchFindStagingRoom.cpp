// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// BfmeAptScreenOnlineCustomMatch staging-room lookup, retail 0x0053AB30,
// 65 bytes. TheGameSpyInfo vslot +0x98 returns the StagingRoomMap; find
// the int at this+0x1CC and return the mapped GameSpyStagingRoom* or 0.
// Iterator is a class so find uses the hidden-pointer return (callee pops
// dest + key = 8). A miss compares equal to the map header node.

class GameSpyStagingRoom;

struct StagingRoomMapNode
{
	unsigned char m_links[ 0x14 ];
	GameSpyStagingRoom *m_room;
};

struct StagingRoomMapIterator
{
	StagingRoomMapIterator( const StagingRoomMapIterator &other );
	StagingRoomMapNode *m_node;
};

struct StagingRoomMap
{
	StagingRoomMapNode *m_header;
	StagingRoomMapIterator find( const int &key );
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

class BfmeAptScreenOnlineCustomMatch
{
public:
	GameSpyStagingRoom *findSelectedStagingRoom();

private:
	unsigned char m_pad[ 0x1CC ];
	int m_selectedID;
};

GameSpyStagingRoom *BfmeAptScreenOnlineCustomMatch::findSelectedStagingRoom()
{
	StagingRoomMap *rooms = TheGameSpyInfo->getStagingRoomList();
	if( !rooms )
		return 0;
	StagingRoomMapIterator it = rooms->find( m_selectedID );
	if( it.m_node == rooms->m_header )
		return 0;
	return it.m_node->m_room;
}
