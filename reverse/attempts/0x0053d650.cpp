// ?applySelectedMap@BfmeAptScreenOnlineCustomMatch@@QAE_NVAsciiString@@@Z
// partial score=0.72 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch apply-map, retail 0x0053D650, 304 bytes.
// Requires TheGameSpyInfo and TheGameSpyGame. Lowercases the map name, setMap,
// then on a MapCache hit copies CRC/size/official and calls slot 0
// setMapAvailability(true), adjustSlotsForMap, resetAccepted, resetStartSpots,
// and GameSpyInfo vslot +0xCC.

template <typename T> class StringBase
{
	friend class AsciiString;

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
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void toLower();
};

class GameSlot
{
public:
	void setMapAvailability( bool hasMap );
};

class GameSpyStagingRoom
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void reset();
	virtual void slot0C();
	virtual bool amIHost() const;
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();
	virtual void resetStartSpots();
	virtual void adjustSlotsForMap();
	GameSlot *getSlot( int index );
	void setMap( AsciiString mapName );
	void setMapCRC( unsigned int crc );
	void setMapSize( unsigned int size );

	unsigned char m_pad[ 0x50 ];
	int m_officialMap;
};

struct MapCacheNode
{
	unsigned char m_pad[ 0x39 ];
	unsigned char m_isOfficial;
	unsigned char m_pad3A[ 0x3C - 0x3A ];
	unsigned int m_fileSize;
	unsigned int m_crc;
};

class MapCache
{
public:
	MapCacheNode *m_header;
	MapCacheNode *find( const AsciiString &key );
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
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 ); GAMESPY_SLOT( 47 );
	GAMESPY_SLOT( 48 ); GAMESPY_SLOT( 49 ); GAMESPY_SLOT( 50 );
	virtual void notifyStagingRoomMapChanged() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;
extern GameSpyStagingRoom *TheGameSpyGame;
extern MapCache *TheMapCache;

class BfmeAptScreenOnlineCustomMatch
{
public:
	bool applySelectedMap( AsciiString mapName );
};

bool BfmeAptScreenOnlineCustomMatch::applySelectedMap( AsciiString mapName )
{
	if( !TheGameSpyInfo || !TheGameSpyGame )
		return false;
	mapName.toLower();
	TheGameSpyGame->setMap( mapName );
	MapCache *cache = TheMapCache;
	MapCacheNode *node = cache->find( mapName );
	if( node != cache->m_header )
	{
		TheGameSpyGame->getSlot( 0 )->setMapAvailability( true );
		TheGameSpyGame->setMapCRC( node->m_crc );
		TheGameSpyGame->setMapSize( node->m_fileSize );
		TheGameSpyGame->m_officialMap = node->m_isOfficial ? 1 : 0;
	}
	TheGameSpyGame->adjustSlotsForMap();
	TheGameSpyGame->resetAccepted();
	TheGameSpyGame->resetStartSpots();
	TheGameSpyInfo->notifyStagingRoomMapChanged();
	return true;
}
