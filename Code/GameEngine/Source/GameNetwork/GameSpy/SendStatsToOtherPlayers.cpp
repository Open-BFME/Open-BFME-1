// ?SendStatsToOtherPlayers@@YAXPBVGameInfo@@@Z
// Clean BFME GameSpy stats request reconstruction.  Retail 0x004F3B10,
// 831 bytes; named callers are StartPressed and WOLQuickMatchMenuUpdate.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include <string>
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include "GameNetwork/GameSpy/PeerThread.h"

#include <map>
#include <stddef.h>

// The BFME GameSpyInfo vtable has the APT menu layout: getLocalName is slot
// 0x68 and getLocalProfileID is slot 0x70.  This view deliberately names only
// the retail slots used by this body.
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
// constructors/destructor.  The SendStats compiland's verified view is 0x1c4
// bytes.
class PSPlayerStats
{
public:
	PSPlayerStats( void );
	PSPlayerStats( const PSPlayerStats &other );
	~PSPlayerStats( void );

	Int id;
	// The BFME WOL compiland names these members at the offsets below.  The
	// three extra map slots are proven by the landed PSPlayerStats copy ctor;
	// the field names used here come from the five retail member copies in this
	// body, not from the differently ordered ZH header.
	PerGeneralMap wins;                 // +0x04
	PerGeneralMap losses;               // +0x10
	PerGeneralMap _bfme_map_1c;         // +0x1c
	PerGeneralMap _bfme_map_28;         // +0x28
	PerGeneralMap _bfme_map_34;         // +0x34
	PerGeneralMap _bfme_map_40;         // +0x40
	PerGeneralMap games;                // +0x4c
	PerGeneralMap _bfme_map_58;         // +0x58
	PerGeneralMap _bfme_map_64;         // +0x64
	PerGeneralMap _bfme_map_70;         // +0x70
	PerGeneralMap _bfme_map_7c;         // +0x7c
	PerGeneralMap _bfme_map_88;         // +0x88
	PerGeneralMap _bfme_map_94;         // +0x94
	PerGeneralMap _bfme_map_a0;         // +0xa0
	PerGeneralMap _bfme_map_ac;         // +0xac
	PerGeneralMap discons;              // +0xb8
	PerGeneralMap desyncs;              // +0xc4
	PerGeneralMap _bfme_map_d0;         // +0xd0
	PerGeneralMap _bfme_map_dc;         // +0xdc
	PerGeneralMap _bfme_map_e8;         // +0xe8
	PerGeneralMap _bfme_map_f4;         // +0xf4
	PerGeneralMap _bfme_map_100;        // +0x100
	PerGeneralMap _bfme_map_10c;        // +0x10c
	PerGeneralMap _bfme_map_118;        // +0x118
	PerGeneralMap _bfme_map_124;        // +0x124
	PerGeneralMap _bfme_map_130;        // +0x130
	PerGeneralMap _bfme_map_13c;        // +0x13c
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

typedef char PSPlayerStatsSizeCheck[ sizeof( PSPlayerStats ) == 0x1c4 ? 1 : -1 ];
typedef char PSPlayerStatsOffset_wins[offsetof(PSPlayerStats, wins) == 0x04 ? 1 : -1];
typedef char PSPlayerStatsOffset_losses[offsetof(PSPlayerStats, losses) == 0x10 ? 1 : -1];
typedef char PSPlayerStatsOffset_games[offsetof(PSPlayerStats, games) == 0x4c ? 1 : -1];
typedef char PSPlayerStatsOffset_discons[offsetof(PSPlayerStats, discons) == 0xb8 ? 1 : -1];
typedef char PSPlayerStatsOffset_desyncs[offsetof(PSPlayerStats, desyncs) == 0xc4 ? 1 : -1];
typedef char PSPlayerStatsOffset_locale[offsetof(PSPlayerStats, locale) == 0x148 ? 1 : -1];
typedef char PSPlayerStatsOffset_gamesAsRandom[offsetof(PSPlayerStats, gamesAsRandom) == 0x158 ? 1 : -1];

class PSRequest;
class PSResponse;

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
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

// ?SendStatsToOtherPlayers@@YAXPBVGameInfo@@@Z
void SendStatsToOtherPlayers( const GameInfo *game )
{
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
	req.UTM.isStagingRoom = TRUE;
	req.id = "STATS/";
	AsciiString fullStr;
	PSPlayerStats fullStats = TheGameSpyPSMessageQueue->findPlayerStatsByID(
		TheGameSpyInfo->getLocalProfileID() );
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
	fullStr.format( "%d %s", TheGameSpyInfo->getLocalProfileID(),
		TheGameSpyPSMessageQueue->formatPlayerKVPairs( subStats ) );
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
			DEBUG_LOG(( "SendStatsToOtherPlayers() - sending to '%s', data of\n\t'%s'\n",
				hostName.str(), req.options.c_str() ));
			TheGameSpyPeerMessageQueue->addRequest( req );
		}
	}
}
