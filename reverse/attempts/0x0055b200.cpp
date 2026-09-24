// ?_bfme_sendStartQuickMatchRequest@BfmeAptScreenOnlineQuickMatch@@QAEXXZ
// partial score=0.30 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "Common/GlobalData.h"
#include "Common/LadderPreferences.h"
#include "Common/PlayerTemplate.h"
#include "Common/UserPreferences.h"
#include "GameClient/GadgetComboBox.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/PersistentStorageDefs.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"

extern Int CalculateRank( const PSPlayerStats &stats );
static Int maxPingEntries;

class PeerRequest
{
public:
	Int peerRequestType;
	std::string nick;
	std::wstring text;
	std::string password;
	std::string email;
	std::string id;
	std::string options;
	std::string ladderIP;
	std::string hostPingStr;
	std::string gameOptsMapName;
	std::string gameOptsPlayerNames[ 8 ];
	std::vector<bool> qmMaps;
	union
	{
		struct
		{
			Int minPointPercentage, maxPointPercentage, points;
			Int widenTime;
			Int ladderID;
			UnsignedInt ladderPassCRC;
			Int maxPing;
			Int maxDiscons, discons;
			char pings[ 17 ];
			Int numPlayers;
			Int botID;
			Int roomID;
			Int side;
			Int color;
			Int NAT;
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
		} QM;
		Int largestPayload[ 44 ];
	};
};

typedef char PeerRequestSizeCheck[ sizeof( PeerRequest ) == 0x194 ? 1 : -1 ];

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual Bool isThreadRunning() = 0;
	virtual Bool isConnected() = 0;
	virtual Bool isConnecting() = 0;
	virtual void addRequest( const PeerRequest &request ) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class BfmeAptScreenOnlineQuickMatch
{
public:
	void _bfme_sendStartQuickMatchRequest();
	void rva0055AE10PopulateRequest( PeerRequest *request );

private:
	unsigned char m_beforePreferences[ 0x40 ];
	unsigned char m_preferences[ 0x1C ];
	GameWindow *m_color;
	GameWindow *m_numPlayers;
	GameWindow *m_side;
	GameWindow *m_connectionSpeed;
	GameWindow *m_ladder;
	GameWindow *m_unknown70;
	GameWindow *m_unknown74;
	Int m_firewallBehavior;
};

#pragma comment(linker, "/alternatename:?rva0055AE10PopulateRequest@BfmeAptScreenOnlineQuickMatch@@QAEXPAVPeerRequest@@@Z=?j_00048a04@@YAXXZ")

void BfmeAptScreenOnlineQuickMatch::_bfme_sendStartQuickMatchRequest()
{
	PeerRequest request;
	*(Int *)&request.peerRequestType = 0x10;
	rva0055AE10PopulateRequest( &request );

	Int selected;
	GadgetComboBoxGetSelectedPos( m_connectionSpeed, &selected );
	if ( selected < 0 )
		selected = 0;
	if ( selected >= maxPingEntries - 1 )
		request.QM.maxPing = TheGameSpyConfig->getPingTimeoutInMs();
	else
		request.QM.maxPing = (selected + 1) * 100;

	PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(
		TheGameSpyInfo->getLocalProfileID() );
	request.QM.points = CalculateRank( stats );

	GadgetComboBoxGetSelectedPos( m_ladder, &selected );
	Int ladderIndex = (Int)GadgetComboBoxGetItemData( m_ladder, selected );
	const LadderInfo *ladderInfo = 0;
	if ( ladderIndex < 0 )
		ladderIndex = 0;
	if ( ladderIndex != 0 )
	{
		ladderInfo = TheLadderList->findLadderByIndex( ladderIndex );
		if ( ladderInfo == 0 )
			ladderIndex = 0;
	}
	request.QM.ladderID = ladderIndex;

	Int side = -1;
	GadgetComboBoxGetSelectedPos( m_side, &selected );
	if ( selected >= 0 )
		side = (Int)GadgetComboBoxGetItemData( m_side, selected );
	request.QM.side = side;
	if ( ladderInfo != 0 && ladderInfo->randomFactions )
	{
		Int sideNum = GameClientRandomValue(
			0, ladderInfo->validFactions.size() - 1 );
		AsciiStringListConstIterator it = ladderInfo->validFactions.begin();
		while ( sideNum-- > 0 )
			++it;
		if ( it != ladderInfo->validFactions.end() )
		{
			Int count = ThePlayerTemplateStore->getPlayerTemplateCount();
			for ( Int index = 0; index < count; ++index )
			{
				const PlayerTemplate *playerTemplate =
					ThePlayerTemplateStore->getNthPlayerTemplate( index );
				if ( playerTemplate != 0 && playerTemplate->getSide() == *it )
				{
					request.QM.side = index;
					break;
				}
			}
		}
	}

	Int color = 0;
	GadgetComboBoxGetSelectedPos( m_color, &selected );
	if ( selected >= 0 )
		color = (Int)GadgetComboBoxGetItemData( m_color, selected );
	request.QM.color = color;

	OptionPreferences preferences;
	m_firewallBehavior = preferences.getFirewallBehavior();
	request.QM.NAT = m_firewallBehavior;

	if ( ladderIndex != 0 )
		request.QM.numPlayers = ladderInfo != 0 ? ladderInfo->playersPerTeam * 2 : 2;
	else
	{
		GadgetComboBoxGetSelectedPos( m_numPlayers, &selected );
		if ( selected < 0 )
			selected = 0;
		request.QM.numPlayers = (selected + 1) * 2;
	}

	strncpy( request.QM.pings, TheGameSpyInfo->getPingString().str(), 17 );
	request.QM.pings[16] = 0;
	request.QM.botID = TheGameSpyConfig->getQMBotID();
	request.QM.roomID = TheGameSpyConfig->getQMChannel();
	request.QM.exeCRC = TheWritableGlobalData->m_exeCRC;
	request.QM.iniCRC = TheWritableGlobalData->m_iniCRC;
	TheGameSpyPeerMessageQueue->addRequest( request );

	if ( ladderIndex > 0 )
	{
		LadderPreferences ladderPreferences;
		ladderPreferences.loadProfile( TheGameSpyInfo->getLocalProfileID() );
		LadderPref recent;
		recent.lastPlayDate = time( 0 );
		recent.address = ladderInfo->address;
		recent.port = ladderInfo->port;
		recent.name = ladderInfo->name;
		ladderPreferences.addRecentLadder( recent );
		ladderPreferences.write();
	}
}
