// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x004DBBF0, 525 bytes. BFME-only PopupPlayerInfo.cpp helper; its
// only caller is HandlePersistentStorageResponses (0x004DD4DA and 0x004DD7DC
// through ILT 0x0001E24F), which stores the response's two ladder ranks in
// 0x012B9660/0x012B9664 and then passes &player. The body keeps the better
// (lowest positive) rank of the stored stats and those globals and, when one
// improved, posts a PSRequest (type 11) carrying only id and the two ranks.
// PSPlayerStats +0x1B0/+0x1B4 are best1v1LadderRank/best2v2LadderRank per the
// matched formatPlayerKVPairs at 0x00655360. The PSRequest email/nick/password
// assignment is the Zero Hour ScoreScreen.cpp populatePlayerInfo pattern.

#include <string>
#include "Common/AsciiString.h"

typedef int Int;

class PSPlayerStats
{
public:
	PSPlayerStats( void );
	~PSPlayerStats( void );
	PSPlayerStats &operator=( const PSPlayerStats &other );

	Int id;                             // +0x000
	char unmodelled_004[ 0x1ac ];
	Int best1v1LadderRank;              // +0x1b0
	Int best2v2LadderRank;              // +0x1b4
	std::string lastLadderPlayed;       // +0x1b8
};

typedef char PSPlayerStatsSizeCheck[ sizeof( PSPlayerStats ) == 0x1c4 ? 1 : -1 ];

class PSRequest
{
public:
	PSRequest();
	~PSRequest();

	Int requestType;                    // +0x000
	PSPlayerStats player;               // +0x004
	std::string cdkey;                  // +0x1c8
	std::string nick;                   // +0x1d4
	std::string password;               // +0x1e0
	std::string email;                  // +0x1ec
	bool addDiscon;
	bool addDesync;
	Int lastHouse;
	Int dword_200;
	std::string results;
};

typedef char PSRequestSizeCheck[ sizeof( PSRequest ) == 0x210 ? 1 : -1 ];

// BFME GameSpyInfo carries five more virtuals ahead of Zero Hour's
// setLocalName (SendStatsToOtherPlayers.cpp: getLocalName +0x68 and
// getLocalProfileID +0x70), so Zero Hour's getLocalEmail lands at +0x74 and
// getLocalBaseName at +0x88. Only the two slots this body calls are named.
class GameSpyInfo
{
public:
	virtual void slot00( void );
	virtual void slot01( void );
	virtual void slot02( void );
	virtual void slot03( void );
	virtual void slot04( void );
	virtual void slot05( void );
	virtual void slot06( void );
	virtual void slot07( void );
	virtual void slot08( void );
	virtual void slot09( void );
	virtual void slot10( void );
	virtual void slot11( void );
	virtual void slot12( void );
	virtual void slot13( void );
	virtual void slot14( void );
	virtual void slot15( void );
	virtual void slot16( void );
	virtual void slot17( void );
	virtual void slot18( void );
	virtual void slot19( void );
	virtual void slot20( void );
	virtual void slot21( void );
	virtual void slot22( void );
	virtual void slot23( void );
	virtual void slot24( void );
	virtual void slot25( void );
	virtual void slot26( void );
	virtual void slot27( void );
	virtual void slot28( void );
	virtual AsciiString getLocalEmail( void );     // +0x74
	virtual void slot30( void );
	virtual void slot31( void );
	virtual void slot32( void );
	virtual void slot33( void );
	virtual AsciiString getLocalBaseName( void );  // +0x88
};

extern GameSpyInfo *TheGameSpyInfo;

// 0x012F76F0 (TheGameSpyPSMessageQueue); +0x10 is addRequest.
class BfmeQueueEUG
{
public:
	virtual void slot00( void );
	virtual void slot01( void );
	virtual void slot02( void );
	virtual void slot03( void );
	virtual void addRequest( const PSRequest &req );
};

extern BfmeQueueEUG *g_bfmeQueueEUG;
extern Int g_bfmePeerReqE4;
extern Int g_bfmePeerReqE8;

void UpdateBestLadderRanks004DBBF0( PSPlayerStats *stats )
{
	if ( !TheGameSpyInfo || !g_bfmeQueueEUG )
		return;

	Int best1v1;
	if ( g_bfmePeerReqE4 > 0 && ( stats->best1v1LadderRank <= 0 || g_bfmePeerReqE4 < stats->best1v1LadderRank ) )
		best1v1 = g_bfmePeerReqE4;
	else
		best1v1 = stats->best1v1LadderRank;

	Int best2v2;
	if ( g_bfmePeerReqE8 > 0 && ( stats->best2v2LadderRank <= 0 || g_bfmePeerReqE8 < stats->best2v2LadderRank ) )
		best2v2 = g_bfmePeerReqE8;
	else
		best2v2 = stats->best2v2LadderRank;

	if ( best1v1 == stats->best1v1LadderRank && best2v2 == stats->best2v2LadderRank )
		return;

	PSRequest req;
	PSPlayerStats newStats;
	req.requestType = 11;
	req.email = TheGameSpyInfo->getLocalEmail().str();
	req.nick = TheGameSpyInfo->getLocalBaseName().str();
	req.password = "";
	newStats.best1v1LadderRank = best1v1;
	newStats.id = stats->id;
	newStats.best2v2LadderRank = best2v2;
	req.player = newStats;
	g_bfmeQueueEUG->addRequest( req );
}
