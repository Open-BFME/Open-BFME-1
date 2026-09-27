// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /I. /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native BFME persistent-storage response callback. Derived from the EA
// PersistentStorageThread.cpp reference (GPL-3.0-or-later); BFME contracts and
// identity are recorded in reverse/identity_evidence/0065c260-storage-callback.md.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"
#include "Common/UserPreferences.h"
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// GameSpy 2004 gpersist.h callback type; the vendor networking header requires
// Platform SDK socket types absent from the engine sweep shim.
typedef enum { pd_private_ro, pd_private_rw, pd_public_ro, pd_public_rw } persisttype_t;
typedef std::map<int,unsigned int> PerGeneralMap;
class PSPlayerStats
{
public:
 PSPlayerStats();PSPlayerStats(const PSPlayerStats&);~PSPlayerStats();PSPlayerStats&operator=(const PSPlayerStats&);
	Int id;                             // +0x000
	PerGeneralMap wins;                 // +0x004
	PerGeneralMap losses;               // +0x010
	PerGeneralMap currentWinStreaks;    // +0x01c
	PerGeneralMap currentLossStreaks;   // +0x028
	PerGeneralMap worstLossStreaks;     // +0x034
	PerGeneralMap bestWinStreaks;       // +0x040
	PerGeneralMap games;                // +0x04c
	PerGeneralMap duration;             // +0x058
	PerGeneralMap unitsKilled;          // +0x064
	PerGeneralMap unitsLost;            // +0x070
	PerGeneralMap unitsBuilt;           // +0x07c
	PerGeneralMap buildingsKilled;      // +0x088
	PerGeneralMap buildingsLost;        // +0x094
	PerGeneralMap buildingsBuilt;       // +0x0a0
	PerGeneralMap earnings;             // +0x0ac
	PerGeneralMap discons;              // +0x0b8
	PerGeneralMap desyncs;              // +0x0c4
	PerGeneralMap surrenders;           // +0x0d0
	PerGeneralMap gamesOf2p;            // +0x0dc
	PerGeneralMap gamesOf3p;            // +0x0e8
	PerGeneralMap gamesOf4p;            // +0x0f4
	PerGeneralMap gamesOf5p;            // +0x100
	PerGeneralMap gamesOf6p;            // +0x10c
	PerGeneralMap gamesOf7p;            // +0x118
	PerGeneralMap gamesOf8p;            // +0x124
	PerGeneralMap customGames;          // +0x130
	PerGeneralMap QMGames;              // +0x13c
	Int locale;                         // +0x148
	std::string dateCreated;            // +0x14c
	Int gamesAsRandom;                  // +0x158
	std::string options;                // +0x15c
	std::string systemSpec;             // +0x168
	Real lastFPS;                       // +0x174
	Int lastSide;                       // +0x178
	Int gamesInRowWithLastSide;         // +0x17c
	Int challengeMedals;                // +0x180
	Int battleHonors;                   // +0x184
	Int winsInARow;                     // +0x188
	Int maxWinsInARow;                  // +0x18c
	Int lossesInARow;                   // +0x190
	Int maxLossesInARow;                // +0x194
	Int gamesOn1_1_Ladder;              // +0x198
	Int gamesOn2_2_Ladder;              // +0x19c
	Int disconsInARow;                  // +0x1a0
	Int maxDisconsInARow;               // +0x1a4
	Int desyncsInARow;                  // +0x1a8
	Int maxDesyncsInARow;               // +0x1ac
	Int best1v1LadderRank;              // +0x1b0
	Int best2v2LadderRank;              // +0x1b4
	std::string lastLadderPlayed;       // +0x1b8
};


class PSRequest {public:
 PSRequest();~PSRequest();
 enum RequestType {PSREQUEST_READPLAYERSTATS,PSREQUEST_UPDATEPLAYERSTATS,PSREQUEST_UPDATEPLAYERLOCALE,PSREQUEST_READCDKEYSTATS};
 RequestType requestType;PSPlayerStats player;std::string cdkey,nick,password,email;bool addDiscon,addDesync;int lastHouse,rva200;std::string results;
};
typedef char RequestExtent[sizeof(PSRequest)==0x210?1:-1];

class PSResponse {public:
 enum {PSRESPONSE_PLAYERSTATS,PSRESPONSE_COULDNOTCONNECT};
 int responseType;PSPlayerStats player;bool preorder;char rva1C9[0x27];
};
typedef char ResponseExtent[sizeof(PSResponse)==0x1f0?1:-1];
// Existing retail symbol contract: these complete 32-byte members copy the
// queue strings at +6C/+78/+84. The explicit view preserves their ledger ABI.
class BFMENetwork {public:std::string copyState6C();std::string copyState78();std::string copyState84();};
class GameSpyPSMessageQueue {public:
 virtual void slot0();virtual void slot4();virtual void slot8();virtual void slotC();virtual void addRequest(const PSRequest&);virtual bool getRequest(PSRequest&);virtual void addResponse(const PSResponse&);
 char prefix[0x64];int localID;
 int getLocalPlayerID(){return localID;}
};
class BfmeQueueEUG;extern BfmeQueueEUG*g_bfmeQueueEUG;
#define TheGameSpyPSMessageQueue ((GameSpyPSMessageQueue*)g_bfmeQueueEUG)
#define MESSAGE_QUEUE TheGameSpyPSMessageQueue
class GameSpyPSMessageQueueInterface {public:static PSPlayerStats parsePlayerKVPairs(std::string);};
class PSThreadClass {public:char prefix[0x50];bool loginOK,done;int m_opCount;bool m_sawLocalData;
 void decrOpCount(){--m_opCount;}int getOpCount(){return m_opCount;}bool sawLocalPlayerData(){return m_sawLocalData;}void gotLocalPlayerData(){m_sawLocalData=true;}
};
// Existing 99-byte date-stamp method: GetLocalTime and assignment at +14C.
class BfmeStampVSE{public:void bfmeStampVSE();};
void getPersistentDataCallback(int localid, int profileid, persisttype_t type,
 int index, int success, time_t modified, char *data, int len, void *instance)
{
	PSThreadClass *t = (PSThreadClass *)instance;
	if (!t)
		return;

	t->decrOpCount();

	PSResponse resp;

	if (!success)
	{
		resp.responseType = PSResponse::PSRESPONSE_COULDNOTCONNECT;
		resp.player.id = profileid;
		TheGameSpyPSMessageQueue->addResponse(resp);
		if (!t->getOpCount() && !t->sawLocalPlayerData())
		{
			// we haven't gotten stats for ourselves - try again
			PSRequest req;
			req.requestType = PSRequest::PSREQUEST_READPLAYERSTATS;
			req.player.id = MESSAGE_QUEUE->getLocalPlayerID();
			TheGameSpyPSMessageQueue->addRequest(req);
		}
		return;
	}

	if (profileid == MESSAGE_QUEUE->getLocalPlayerID())
	{
		t->gotLocalPlayerData();

		// check if we have discons we should update on the server
		UserPreferences pref;
		AsciiString userPrefFilename;
		userPrefFilename.format("LoTRB4MEOnline\\MiscPref%d.ini", MESSAGE_QUEUE->getLocalPlayerID());
		pref.load(userPrefFilename);
		Int addedInDesyncs2 = pref.getInt("0", 0);
		if (addedInDesyncs2 < 0)
			addedInDesyncs2 = 10;
		Int addedInDesyncs3 = pref.getInt("1", 0);
		if (addedInDesyncs3 < 0)
			addedInDesyncs3 = 10;
		Int addedInDesyncs4 = pref.getInt("2", 0);
		if (addedInDesyncs4 < 0)
			addedInDesyncs4 = 10;
		Int addedInDiscons2 = pref.getInt("3", 0);
		if (addedInDiscons2 < 0)
			addedInDiscons2 = 10;
		Int addedInDiscons3 = pref.getInt("4", 0);
		if (addedInDiscons3 < 0)
			addedInDiscons3 = 10;
		Int addedInDiscons4 = pref.getInt("5", 0);
		if (addedInDiscons4 < 0)
			addedInDiscons4 = 10;


		if (addedInDesyncs2 || addedInDesyncs3 || addedInDesyncs4 || addedInDiscons2 || addedInDiscons3 || addedInDiscons4)
		{

			PSRequest req;
			req.requestType = PSRequest::PSREQUEST_UPDATEPLAYERSTATS;
			req.email = ((BFMENetwork*)MESSAGE_QUEUE)->copyState6C();
			req.nick = ((BFMENetwork*)MESSAGE_QUEUE)->copyState78();
			req.password = ((BFMENetwork*)MESSAGE_QUEUE)->copyState84();
			req.player = GameSpyPSMessageQueueInterface::parsePlayerKVPairs((len)?data:"");
			req.player.id = profileid;
			req.addDesync = FALSE;
			req.addDiscon = FALSE;
			req.lastHouse = 0;
			TheGameSpyPSMessageQueue->addRequest(req);
		}
	}

	resp.responseType = PSResponse::PSRESPONSE_PLAYERSTATS;
	resp.player = GameSpyPSMessageQueueInterface::parsePlayerKVPairs((len)?data:"");
	resp.player.id = profileid;

	if (resp.player.dateCreated.size() == 0 && profileid == MESSAGE_QUEUE->getLocalPlayerID())
	{
		((BfmeStampVSE *)&resp.player)->bfmeStampVSE();
		PSRequest req;
		req.requestType = PSRequest::PSREQUEST_UPDATEPLAYERSTATS;
		req.email = ((BFMENetwork *)MESSAGE_QUEUE)->copyState6C();
		req.nick = ((BFMENetwork *)MESSAGE_QUEUE)->copyState78();
		req.password = ((BFMENetwork *)MESSAGE_QUEUE)->copyState84();
		req.player = resp.player;
		req.player.id = profileid;
		TheGameSpyPSMessageQueue->addRequest(req);
	}

	TheGameSpyPSMessageQueue->addResponse(resp);
}
