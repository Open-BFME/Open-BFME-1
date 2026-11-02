// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// GameSortStruct::operator(), retail 0x0053EDD0 (864 B, jump table included),
// the staging-room list comparator Zero Hour keeps in LobbyUtils.cpp. The
// staging-room tree insert reaches it through the ILT at 0x000317D7.
//
// Rooms whose exe/ini CRCs disagree with ours sort last, then full rooms; the
// rest order by up to two keys read from the custom-match screen (+0x1E8,
// +0x1EC): the low bits pick the column (1 name, 2 non-observer players,
// 4 the field at +0x44C, 8 the GameInfo query at 0x006233E0) and bit 0x10000
// makes it ascending. With no custom-match screen the name decides.
//
// The CRC test is a per-room inline helper: written inline twice, MSVC
// stopped sharing the TheWritableGlobalData load between the two tests.
// The fields at +0x44C and +0x1E8 have no witnessed name, so they keep
// their offsets.
#include <wchar.h>
#include "unicode_string.h"

// Retail inlines ~UnicodeString at every scope exit and calls
// StringBase<unsigned short>::releaseBuffer (0x008881D0) directly, never
// the 0x0005EEA0 jmp body the out-of-line declaration would bind to.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

int Rva0009B4B0( int a, int b );					///< ILT thunk 0x000019F6

class GameInfo
{
public:
	int getNumPlayers( void ) const;
	int getNumNonObserverPlayers( void ) const;
	int _bfme_getMapIsOfficial( void ) const;
};

class GameSpyStagingRoom : public GameInfo
{
public:
	UnicodeString getGameName();
	unsigned int getIniCRC() { return m_iniCRC; }

	unsigned char m_head[ 0x430 ];
	unsigned int m_exeCRC;
	unsigned int m_iniCRC;
	unsigned char m_gap[ 0x44C - 0x438 ];
	int m_i44c;
};

class GlobalData
{
public:
	unsigned char m_pad[ 0xBC8 ];
	unsigned int m_iniCRC;
	unsigned char m_gap[ 4 ];
	unsigned int m_exeCRC;
};
extern GlobalData *TheWritableGlobalData;

class BfmeAptScreenOnlineCustomMatch
{
public:
	unsigned char m_pad[ 0x1E8 ];
	int m_key1e8[ 2 ];
};
extern BfmeAptScreenOnlineCustomMatch *TheBfmeOnlineCustomMatch;

static inline bool crcMismatch( GameSpyStagingRoom *g )
{
	unsigned int exe = g->m_exeCRC;
	return exe != (unsigned int)Rva0009B4B0( TheWritableGlobalData->m_exeCRC, TheWritableGlobalData->m_exeCRC )
		|| g->getIniCRC() != TheWritableGlobalData->m_iniCRC;
}

class GameSortStruct
{
public:
	bool operator()( GameSpyStagingRoom *g1, GameSpyStagingRoom *g2 );
};

bool GameSortStruct::operator()( GameSpyStagingRoom *g1, GameSpyStagingRoom *g2 )
{
	bool g1Bad = crcMismatch( g1 );
	bool g2Bad = crcMismatch( g2 );
	if( g1Bad ^ g2Bad )
		return g1Bad;

	int g1n = g1->getNumNonObserverPlayers();
	bool g1Full = g1n == g1->_bfme_getMapIsOfficial() || g1->getNumPlayers() == 8;
	int g2n = g2->getNumNonObserverPlayers();
	bool g2Full = g2n == g2->_bfme_getMapIsOfficial() || g2->getNumPlayers() == 8;
	if( g1Full ^ g2Full )
		return g2Full;

	int nameCmp = _wcsicmp( g1->getGameName().str(), g2->getGameName().str() );
	int diff44c = g1->m_i44c - g2->m_i44c;
	int diffNonObs = g1->getNumNonObserverPlayers() - g2->getNumNonObserverPlayers();
	int diffOfficial = g1->_bfme_getMapIsOfficial() - g2->_bfme_getMapIsOfficial();

	BfmeAptScreenOnlineCustomMatch *match = TheBfmeOnlineCustomMatch;
	if( !match )
		return nameCmp > 0;

	int key = match->m_key1e8[ 0 ];
	for( int i = 0; i < 2; ++i )
	{
		bool ascending = ( key & 0x10000 ) == 0x10000;
		switch( key & ~0x10000 )
		{
		case 1:
			if( nameCmp ) return ascending ? nameCmp > 0 : nameCmp < 0;
			break;
		case 2:
			if( diffNonObs ) return ascending ? diffNonObs > 0 : diffNonObs < 0;
			break;
		case 4:
			if( diff44c ) return ascending ? diff44c > 0 : diff44c < 0;
			break;
		case 8:
			if( diffOfficial ) return ascending ? diffOfficial > 0 : diffOfficial < 0;
			break;
		}
		key = match->m_key1e8[ 1 ];
	}
	return true;
}
