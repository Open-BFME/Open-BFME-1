// ?bfmeMapChanged@BfmeAptScreenSkirmish@@QAE_NPBVAsciiString@@@Z
// partial score=0.98 date=2026-09-05
// Near match. MSVC assigns the incoming AsciiString pointer to EDI and the
// MapMetaData pointer to ESI. Retail assigns those registers in the opposite
// order.
// cl: /O2 /DNDEBUG /MD /EHsc /G5 /Ireference/shims/stringinline

#include "StringInline.h"

class GameInfo
{
public:
	void setMap( AsciiString mapName );
	void setMapCRC( unsigned int mapCRC );
	void setMapSize( unsigned int mapSize );
};

extern GameInfo *g_bfmeCurrentCB;

class MapMetaData
{
private:
	char m_unmodelled[ 0x28 ];

public:
	unsigned int m_filesize;
	unsigned int m_CRC;
};

class MapCache
{
public:
	const MapMetaData *findMap( AsciiString mapName );
};

extern MapCache *TheMapCache;

class LANPreferences
{
public:
	virtual void _bfme_slot0( void );
	virtual void _bfme_slot1( void );
	virtual void _bfme_slot2( void );
	virtual void _bfme_slot3( void );
	virtual void _bfme_slot4( void );
	virtual void _bfme_slot5( void );
	virtual void _bfme_slot6( void );
	virtual void setAsciiString( AsciiString key, AsciiString value );

	void setPreferredMap( AsciiString mapName );
};

class SkirmishBattleHonors
{
public:
	virtual void _bfme_slot0( void );
	virtual void _bfme_slot1( void );
	virtual bool _bfme_load( void );
	virtual bool write( void );
};

class BfmeAptScreenSkirmish
{
public:
	bool bfmeMapChanged( const AsciiString *mapName ) throw();

private:
	char m_unmodelled[ 0x16c ];
	SkirmishBattleHonors m_honors;
};

bool BfmeAptScreenSkirmish::bfmeMapChanged( const AsciiString *mapName ) throw()
{
	const MapMetaData *map;
	const AsciiString *name = mapName;
	g_bfmeCurrentCB->setMap( *name );
	map = TheMapCache->findMap( *name );
	if( map )
	{
		unsigned int crc = map->m_CRC;
		g_bfmeCurrentCB->setMapCRC( crc );
		unsigned int size = map->m_filesize;
		g_bfmeCurrentCB->setMapSize( size );
	}
	( (LANPreferences *)&m_honors )->setPreferredMap( *name );
	SkirmishBattleHonors *honors = (SkirmishBattleHonors *)&m_honors;
	honors->write();
	return true;
}
