// ?SendStatsToOtherPlayers@@YAXPBVGameInfo@@@Z
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseunicode /Ireference/shims/campaignmanagerascii /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include "GameNetwork/GameSpy/PeerThread.h"

#include <map>
#include <string>

// The BFME GameSpyInfo vtable has the APT menu layout: getLocalName is slot
// 0x68 and getLocalProfileID is slot 0x70.  This view deliberately names only
// the retail slots needed by this body.
class GameSpyInfoInterface
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
	virtual AsciiString getLocalName( void );
	virtual void slot27( void );
	virtual Int getLocalProfileID( void );
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSlot
{
public:
	Bool isHuman( void ) const;
	UnicodeString getName( void ) const;
};

// BFME inserts two Int-returning virtuals before the Generals GameInfo
// methods.  The local-slot call consequently lands at +0x14.
class GameInfo
{
public:
	virtual Int _bfme_gi_slot0( void );
	virtual Int _bfme_gi_slot1( void );
	virtual void reset( void );
	virtual void startGame( Int gameID );
	virtual Bool amIHost( void ) const;
	virtual Int getLocalSlotNum( void ) const;
	const GameSlot *getConstSlot( Int slotNum ) const;
};

typedef std::map<Int, UnsignedInt> PerGeneralMap;

// This is the retail PSPlayerStats member order used by the matched BFME
// constructors/destructor.  The current common shim is 0x1c4 bytes; BFME's
// SendStats compiland has the 0x1e8 view, so retain the additional retail tail
// without inventing any member reads.
class PSPlayerStats
{
public:
	PSPlayerStats( void );
	PSPlayerStats( const PSPlayerStats &other );
	~PSPlayerStats( void );

	Int id;
	PerGeneralMap wins;
	PerGeneralMap losses;
	PerGeneralMap games;
	PerGeneralMap duration;
	PerGeneralMap unitsKilled;
	PerGeneralMap unitsLost;
	PerGeneralMap unitsBuilt;
	PerGeneralMap buildingsKilled;
	PerGeneralMap buildingsLost;
	PerGeneralMap buildingsBuilt;
	PerGeneralMap earnings;
	PerGeneralMap techCaptured;
	PerGeneralMap discons;
	PerGeneralMap desyncs;
	PerGeneralMap surrenders;
	PerGeneralMap gamesOf2p;
	PerGeneralMap gamesOf3p;
	PerGeneralMap gamesOf4p;
	PerGeneralMap gamesOf5p;
	PerGeneralMap gamesOf6p;
	PerGeneralMap gamesOf7p;
	PerGeneralMap gamesOf8p;
	PerGeneralMap customGames;
	PerGeneralMap QMGames;
	PerGeneralMap _bfme_hole_mapA;
	PerGeneralMap _bfme_hole_mapB;
	PerGeneralMap _bfme_hole_mapC;
	Int locale;
	std::string _bfme_hole_string;
	Int gamesAsRandom;
	std::string options;
	std::string systemSpec;
	Real lastFPS;
	Int lastGeneral;
	Int gamesInRowWithLastGeneral;
	Int builtParticleCannon;
	Int builtNuke;
	Int builtSCUD;
	Int challengeMedals;
	Int battleHonors;
	Int winsInARow;
	Int maxWinsInARow;
	Int lossesInARow;
	Int maxLossesInARow;
	Int disconsInARow;
	Int maxDisconsInARow;
	Int desyncsInARow;
	Int maxDesyncsInARow;
	Int lastLadderPort;
	std::string lastLadderHost;
};

char PSPlayerStatsSizeProbe[ sizeof( PSPlayerStats ) ];

class PSRequest;
class PSResponse;

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface() {}
	virtual void startThread( void ) = 0;
	virtual void endThread( void ) = 0;
	virtual Bool isThreadRunning( void ) = 0;
	virtual void addRequest( const PSRequest &req ) = 0;
	virtual Bool getRequest( PSRequest &req ) = 0;
	virtual void addResponse( const PSResponse &resp ) = 0;
	virtual Bool getResponse( PSResponse &resp ) = 0;
	virtual void trackPlayerStats( PSPlayerStats stats ) = 0;
	virtual PSPlayerStats findPlayerStatsByID( Int id ) = 0;
	static std::string formatPlayerKVPairs( PSPlayerStats stats );
};

extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
extern void GetAdditionalDisconnectsFromUserFile( PSPlayerStats *stats );

void SendStatsToOtherPlayers( const GameInfo *game )
{
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
	req.UTM.isStagingRoom = TRUE;
	req.id = "STATS/";
	AsciiString fullStr;
	PSPlayerStats fullStats = TheGameSpyPSMessageQueue->findPlayerStatsByID( TheGameSpyInfo->getLocalProfileID() );
	PSPlayerStats subStats;
	subStats.id = fullStats.id;
	subStats.wins = fullStats.wins;
	subStats.losses = fullStats.losses;
	subStats.discons = fullStats.discons;
	subStats.desyncs = fullStats.desyncs;
	subStats.games = fullStats.games;
	subStats.locale = fullStats.locale;
	subStats.gamesAsRandom = fullStats.gamesAsRandom;
	GetAdditionalDisconnectsFromUserFile( &subStats );
	fullStr.format( "%d %s", TheGameSpyInfo->getLocalProfileID(), TheGameSpyPSMessageQueue->formatPlayerKVPairs( subStats ) );
	req.options = fullStr.str();

	Int localIndex = game->getLocalSlotNum();
	for ( Int i = 0; i < MAX_SLOTS; ++i )
	{
		const GameSlot *slot = game->getConstSlot( i );
		if ( slot->isHuman() && i != localIndex )
		{
			AsciiString hostName;
			hostName.translate( slot->getName() );
			req.nick = hostName.str();
			DEBUG_LOG(( "SendStatsToOtherPlayers() - sending to '%s', data of\n\t'%s'\n", hostName.str(), req.options.c_str() ));
			TheGameSpyPeerMessageQueue->addRequest( req );
		}
	}
}
