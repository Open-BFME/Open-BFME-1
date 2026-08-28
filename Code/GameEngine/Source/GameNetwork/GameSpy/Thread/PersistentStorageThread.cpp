// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/psplayerstats /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: PersistentStorageThread.cpp //////////////////////////////////////////////////////
// GameSpy Persistent Storage thread
// This thread communicates with GameSpy's persistent storage server
// and talks through a message queue with the rest of
// the game.
// Author: Matthew D. Campbell, July 2002

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/UserPreferences.h"
#include "Common/PlayerTemplate.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/PeerDefs.h"

#include "mutex.h"
#include "thread.h"

#include "Common/StackDump.h"
#include "Common/SubsystemInterface.h"

// Retail's STLport leaves _String_base::_M_allocate_block's rejection path
// empty -- a request for zero, or for more than max_size(), just leaves the
// string unallocated. The vendored 4.5.3 copy calls _M_throw_length_error()
// there instead, and that throw is the entire remaining difference in the
// return-value copy of formatPlayerKVPairs below. Specialise the one
// instantiation this file needs so it matches what shipped; the guard itself
// is unchanged, so a rejected size still allocates nothing.
_STLP_BEGIN_NAMESPACE
template <> void _String_base<char, allocator<char> >::_M_allocate_block(size_t __n)
{
	if ((__n <= (max_size() + 1)) && (__n > 0))
	{
		_M_start = _M_end_of_storage.allocate(__n);
		_M_finish = _M_start;
		_M_end_of_storage._M_data = _M_start + __n;
	}
}
_STLP_END_NAMESPACE

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------

// ??0PSRequest@@ present-unmatched
PSRequest::PSRequest()
{
	player.reset();
	requestType = PSREQUEST_READPLAYERSTATS;
	addDiscon = addDesync = FALSE;
	lastHouse = -1;
}

//-------------------------------------------------------------------------

#define DEBUG_MAP(x) for (it = stats.x.begin(); it != stats.x.end(); ++it) \
{ \
	if (it->second > 0) \
	{ \
		DEBUG_LOG(("%s(%d): %d\n", #x, it->first, it->second)); \
	} \
}

static void debugDumpPlayerStats( const PSPlayerStats& stats )
{
	DEBUG_LOG(("-----------------------------------------\n"));
	DEBUG_LOG(("Tracking player stats for player %d:\n", stats.id));
	PerGeneralMap::const_iterator it;
	DEBUG_MAP(wins);
	DEBUG_MAP(losses);
	DEBUG_MAP(games);
	DEBUG_MAP(duration);
	DEBUG_MAP(unitsKilled);
	DEBUG_MAP(unitsLost);
	DEBUG_MAP(unitsBuilt);
	DEBUG_MAP(buildingsKilled);
	DEBUG_MAP(buildingsLost);
	DEBUG_MAP(buildingsBuilt);
	DEBUG_MAP(earnings);
	DEBUG_MAP(techCaptured);
	DEBUG_MAP(discons);
	DEBUG_MAP(desyncs);
	DEBUG_MAP(surrenders);
	DEBUG_MAP(gamesOf2p);
	DEBUG_MAP(gamesOf3p);
	DEBUG_MAP(gamesOf4p);
	DEBUG_MAP(gamesOf5p);
	DEBUG_MAP(gamesOf6p);
	DEBUG_MAP(gamesOf7p);
	DEBUG_MAP(gamesOf8p);
	DEBUG_MAP(customGames);
	DEBUG_MAP(QMGames);
	
	if (stats.locale > 0)
	{
		DEBUG_LOG(("Locale: %d\n", stats.locale));
	}
	
	if (stats.gamesAsRandom > 0)
	{
		DEBUG_LOG(("gamesAsRandom: %d\n", stats.gamesAsRandom));
	}

	if (stats.options.length())
	{
		DEBUG_LOG(("Options: %s\n", stats.options.c_str()));
	}

	if (stats.systemSpec.length())
	{
		DEBUG_LOG(("systemSpec: %s\n", stats.systemSpec.c_str()));
	}

	if (stats.lastFPS > 0.0f)
	{
		DEBUG_LOG(("lastFPS: %g\n", stats.lastFPS));
	}

	if (stats.battleHonors > 0)
	{
		DEBUG_LOG(("battleHonors: %x\n", stats.battleHonors));
	}
	if (stats.challengeMedals > 0)
	{
		DEBUG_LOG(("challengeMedals: %x\n", stats.challengeMedals));
	}
	if (stats.lastGeneral >= 0)
	{
		DEBUG_LOG(("lastGeneral: %d\n", stats.lastGeneral));
	}
	if (stats.gamesInRowWithLastGeneral >= 0)
	{
		DEBUG_LOG(("gamesInRowWithLastGeneral: %d\n", stats.gamesInRowWithLastGeneral));
	}
	if (stats.builtSCUD >= 0)
	{
		DEBUG_LOG(("builtSCUD: %d\n", stats.builtSCUD));
	}
	if (stats.builtNuke >= 0)
	{
		DEBUG_LOG(("builtNuke: %d\n", stats.builtNuke));
	}
	if (stats.builtParticleCannon >= 0)
	{
		DEBUG_LOG(("builtParticleCannon: %d\n", stats.builtParticleCannon));
	}

	if (stats.winsInARow >= 0)
	{
		DEBUG_LOG(("winsInARow: %d\n", stats.winsInARow));
	}
	if (stats.maxWinsInARow >= 0)
	{
		DEBUG_LOG(("maxWinsInARow: %d\n", stats.maxWinsInARow));
	}
	if (stats.disconsInARow >= 0)
	{
		DEBUG_LOG(("disconsInARow: %d\n", stats.disconsInARow));
	}
	if (stats.maxDisconsInARow >= 0)
	{
		DEBUG_LOG(("maxDisconsInARow: %d\n", stats.maxDisconsInARow));
	}
	if (stats.lossesInARow >= 0)
	{
		DEBUG_LOG(("lossesInARow: %d\n", stats.lossesInARow));
	}
	if (stats.maxLossesInARow >= 0)
	{
		DEBUG_LOG(("maxLossesInARow: %d\n", stats.maxLossesInARow));
	}
	if (stats.desyncsInARow >= 0)
	{
		DEBUG_LOG(("desyncsInARow: %d\n", stats.desyncsInARow));
	}
	if (stats.maxDesyncsInARow >= 0)
	{
		DEBUG_LOG(("maxDesyncsInARow: %d\n", stats.maxDesyncsInARow));
	}

	if (stats.lastLadderPort >= 0)
	{
		DEBUG_LOG(("lastLadderPort: %d\n", stats.lastLadderPort));
	}

	if (stats.lastLadderHost.length())
	{
		DEBUG_LOG(("lastLadderHost: %s\n", stats.lastLadderHost.c_str()));
	}



}

//-------------------------------------------------------------------------

// The psplayerstats shim header labels PSPlayerStats with Zero Hour's field
// names. BFME kept Zero Hour's *shape* -- same member count, same stride, which
// is why the copy constructor at 0x6577D0 byte-matches through that shim -- but
// moved the labels: four streak maps take map slots 2-5, pushing games..QMGames
// down by four, and the scalar tail is relabelled outright. Below is what the
// retail body at 0x655360 actually reads, at the offsets it reads it from.
// Relabelling the shim would touch four translation units and cost a full-tree
// gate; this view keeps the change TU-local until that is worth paying for.
struct BfmePlayerStats
{
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

// fails the build loudly if the shim's layout ever stops agreeing with the view
typedef char BfmePlayerStatsMatchesShim[sizeof(BfmePlayerStats) == sizeof(PSPlayerStats) ? 1 : -1];

#define BFME_OTHER them
#define BFME_THIS  me

#define INCORPORATE_MAP(x) for (it = BFME_OTHER.x.begin(); it != BFME_OTHER.x.end(); ++it) \
{ \
	if (it->second > 0) \
	{ \
		BFME_THIS.x[it->first] = it->second; \
	} \
}

// A current streak of zero is meaningful -- it has to overwrite the old non-zero
// value when the streak breaks -- so these two copy unguarded.
#define INCORPORATE_MAP_ALWAYS(x) for (it = BFME_OTHER.x.begin(); it != BFME_OTHER.x.end(); ++it) \
{ \
	BFME_THIS.x[it->first] = it->second; \
}

void PSPlayerStats::incorporate( const PSPlayerStats& other )
{
	BfmePlayerStats &me = (BfmePlayerStats &)*this;
	const BfmePlayerStats &them = (const BfmePlayerStats &)other;
	PerGeneralMap::const_iterator it;
	INCORPORATE_MAP(wins);
	INCORPORATE_MAP(losses);
	INCORPORATE_MAP(games);
	INCORPORATE_MAP(duration);
	INCORPORATE_MAP(unitsKilled);
	INCORPORATE_MAP(unitsLost);
	INCORPORATE_MAP(unitsBuilt);
	INCORPORATE_MAP(buildingsKilled);
	INCORPORATE_MAP(buildingsLost);
	INCORPORATE_MAP(buildingsBuilt);
	INCORPORATE_MAP(earnings);
	INCORPORATE_MAP(discons);
	INCORPORATE_MAP(desyncs);
	INCORPORATE_MAP(surrenders);
	INCORPORATE_MAP(gamesOf2p);
	INCORPORATE_MAP(gamesOf3p);
	INCORPORATE_MAP(gamesOf4p);
	INCORPORATE_MAP(gamesOf5p);
	INCORPORATE_MAP(gamesOf6p);
	INCORPORATE_MAP(gamesOf7p);
	INCORPORATE_MAP(gamesOf8p);
	INCORPORATE_MAP(customGames);
	INCORPORATE_MAP(QMGames);
	INCORPORATE_MAP_ALWAYS(currentWinStreaks);
	INCORPORATE_MAP_ALWAYS(currentLossStreaks);
	INCORPORATE_MAP(worstLossStreaks);
	INCORPORATE_MAP(bestWinStreaks);

	if (BFME_OTHER.locale > 0)
	{
		BFME_THIS.locale = BFME_OTHER.locale;
	}

	if (BFME_OTHER.gamesAsRandom > 0)
	{
		BFME_THIS.gamesAsRandom = BFME_OTHER.gamesAsRandom;
	}

	if (BFME_OTHER.options.length())
	{
		BFME_THIS.options = BFME_OTHER.options;
	}

	if (BFME_OTHER.systemSpec.length())
	{
		BFME_THIS.systemSpec = BFME_OTHER.systemSpec;
	}

	if (BFME_OTHER.lastFPS > 0.0f)
	{
		BFME_THIS.lastFPS = BFME_OTHER.lastFPS;
	}

	// honours and medals are bit sets, so they merge rather than overwrite
	if (BFME_OTHER.battleHonors > 0)
	{
		BFME_THIS.battleHonors |= BFME_OTHER.battleHonors;
	}
	if (BFME_OTHER.challengeMedals > 0)
	{
		BFME_THIS.challengeMedals |= BFME_OTHER.challengeMedals;
	}
	if (BFME_OTHER.lastSide >= 0)
	{
		BFME_THIS.lastSide = BFME_OTHER.lastSide;
	}
	if (BFME_OTHER.gamesInRowWithLastSide >= 0)
	{
		BFME_THIS.gamesInRowWithLastSide = BFME_OTHER.gamesInRowWithLastSide;
	}
	if (BFME_OTHER.winsInARow >= 0)
	{
		BFME_THIS.winsInARow = BFME_OTHER.winsInARow;
	}
	if (BFME_OTHER.maxWinsInARow >= 0)
	{
		BFME_THIS.maxWinsInARow = BFME_OTHER.maxWinsInARow;
	}
	if (BFME_OTHER.lossesInARow >= 0)
	{
		BFME_THIS.lossesInARow = BFME_OTHER.lossesInARow;
	}
	if (BFME_OTHER.maxLossesInARow >= 0)
	{
		BFME_THIS.maxLossesInARow = BFME_OTHER.maxLossesInARow;
	}
	if (BFME_OTHER.disconsInARow >= 0)
	{
		BFME_THIS.disconsInARow = BFME_OTHER.disconsInARow;
	}
	if (BFME_OTHER.maxDisconsInARow >= 0)
	{
		BFME_THIS.maxDisconsInARow = BFME_OTHER.maxDisconsInARow;
	}
	if (BFME_OTHER.desyncsInARow >= 0)
	{
		BFME_THIS.desyncsInARow = BFME_OTHER.desyncsInARow;
	}
	if (BFME_OTHER.maxDesyncsInARow >= 0)
	{
		BFME_THIS.maxDesyncsInARow = BFME_OTHER.maxDesyncsInARow;
	}

	if (BFME_OTHER.dateCreated.length())
	{
		BFME_THIS.dateCreated = BFME_OTHER.dateCreated;
	}
	if (BFME_OTHER.gamesOn1_1_Ladder >= 0)
	{
		BFME_THIS.gamesOn1_1_Ladder = BFME_OTHER.gamesOn1_1_Ladder;
	}
	if (BFME_OTHER.gamesOn2_2_Ladder >= 0)
	{
		BFME_THIS.gamesOn2_2_Ladder = BFME_OTHER.gamesOn2_2_Ladder;
	}
	if (BFME_OTHER.best1v1LadderRank > 0)
	{
		BFME_THIS.best1v1LadderRank = BFME_OTHER.best1v1LadderRank;
	}
	if (BFME_OTHER.best2v2LadderRank > 0)
	{
		BFME_THIS.best2v2LadderRank = BFME_OTHER.best2v2LadderRank;
	}
	if (BFME_OTHER.lastLadderPlayed.length())
	{
		BFME_THIS.lastLadderPlayed = BFME_OTHER.lastLadderPlayed;
	}
}

PSPlayerStats::PSPlayerStats( const PSPlayerStats& other )
{
	incorporate(other);
	id = other.id;
	locale = other.locale;
	gamesAsRandom = other.gamesAsRandom;
	options = other.options;
	systemSpec = other.systemSpec;
	lastFPS = other.lastFPS;
	lastGeneral = other.lastGeneral;
	gamesInRowWithLastGeneral = other.gamesInRowWithLastGeneral;
	builtParticleCannon = other.builtParticleCannon;
	builtNuke = other.builtNuke;
	builtSCUD = other.builtSCUD;
	challengeMedals = other.challengeMedals;
	battleHonors = other.battleHonors;
	winsInARow = other.winsInARow;
	maxWinsInARow = other.maxWinsInARow;
	lossesInARow = other.lossesInARow;
	maxLossesInARow = other.maxLossesInARow;
	disconsInARow = other.disconsInARow;
	maxDisconsInARow = other.maxDisconsInARow;
	desyncsInARow = other.desyncsInARow;
	// BFME copies a fourth string here, between desyncsInARow and
	// maxDesyncsInARow; see the shimmed header for where it lives.
	_bfme_hole_string = other._bfme_hole_string;
	maxDesyncsInARow = other.maxDesyncsInARow;
	lastLadderPort = other.lastLadderPort;
	lastLadderHost = other.lastLadderHost;
}

//-------------------------------------------------------------------------

typedef std::queue<PSRequest> RequestQueue;
typedef std::queue<PSResponse> ResponseQueue;
class PSThreadClass;

class GameSpyPSMessageQueue : public GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueue();
	GameSpyPSMessageQueue();
	virtual void startThread( void );
	virtual void endThread( void );
	virtual Bool isThreadRunning( void );

	virtual void addRequest( const PSRequest& req );
	virtual Bool getRequest( PSRequest& req );

	virtual void addResponse( const PSResponse& resp );
	virtual Bool getResponse( PSResponse& resp );

	virtual void trackPlayerStats( PSPlayerStats stats );
	virtual PSPlayerStats findPlayerStatsByID( Int id );

	PSThreadClass* getThread( void );

	Int getLocalPlayerID(void) { return m_localPlayerID; }
	void setLocalPlayerID(Int localPlayerID) { m_localPlayerID = localPlayerID; }

	std::string getEmail() { return m_email; }
	std::string getNick() { return m_nick; }
	std::string getPassword() { return m_password; }

	void setEmail(std::string email) { m_email = email; }
	void setNick(std::string nick) { m_nick = nick; }
	void setPassword(std::string password) { m_password = password; }

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	PSThreadClass *m_thread;
	Int m_localPlayerID;

	std::string m_email;
	std::string m_nick;
	std::string m_password;

	std::map<Int, PSPlayerStats> m_playerStats;
};

GameSpyPSMessageQueueInterface* GameSpyPSMessageQueueInterface::createNewMessageQueue( void )
{
	return NEW GameSpyPSMessageQueue;
}

GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue = NULL;
#define MESSAGE_QUEUE ((GameSpyPSMessageQueue *)TheGameSpyPSMessageQueue)

//-------------------------------------------------------------------------

class PSThreadClass : public ThreadClass
{

public:
	PSThreadClass() : ThreadClass() 
	{ 
		m_loginOK = m_sawLocalData = m_doneTryingToLogin = false; 
		m_opCount = 0; 
	}

	void Thread_Function();

	void persAuthCallback( Bool val ) { m_loginOK = val; m_doneTryingToLogin = true; }
	void decrOpCount( void ) { --m_opCount; }
	void incrOpCount( void ) { ++m_opCount; }
	Int getOpCount( void ) { return m_opCount; }
	Bool sawLocalPlayerData( void ) { return m_sawLocalData; }
	void gotLocalPlayerData( void ) { m_sawLocalData = TRUE; }

private:
	Bool tryConnect( void );
	Bool tryLogin( Int id, std::string nick, std::string password, std::string email );
	Bool m_loginOK;
	Bool m_doneTryingToLogin;
	Int m_opCount;
	Bool m_sawLocalData;
};


//-------------------------------------------------------------------------

// ??0GameSpyPSMessageQueue@@ present-unmatched
GameSpyPSMessageQueue::GameSpyPSMessageQueue()
{
	m_thread = NULL;
	m_localPlayerID = 0;
}

// ??1GameSpyPSMessageQueue@@ present-unmatched
GameSpyPSMessageQueue::~GameSpyPSMessageQueue()
{
	endThread();
}

// ?startThread@GameSpyPSMessageQueue@@ present-unmatched
void GameSpyPSMessageQueue::startThread( void )
{
	if (!m_thread)
	{
		m_thread = NEW PSThreadClass;
		m_thread->Execute();
	}
	else
	{
		if (!m_thread->Is_Running())
		{
			m_thread->Execute();
		}
	}
}

// ?endThread@GameSpyPSMessageQueue@@ present-unmatched
void GameSpyPSMessageQueue::endThread( void )
{
	if (m_thread)
		delete m_thread;
	m_thread = NULL;
}

Bool GameSpyPSMessageQueue::isThreadRunning( void )
{
	return (m_thread) ? m_thread->Is_Running() : false;
}

// ?addRequest@GameSpyPSMessageQueue@@ present-unmatched
void GameSpyPSMessageQueue::addRequest( const PSRequest& req )
{
	MutexClass::LockClass m(m_requestMutex);
	if (m.Failed())
		return;

	m_requests.push(req);
}

Bool GameSpyPSMessageQueue::getRequest( PSRequest& req )
{
	MutexClass::LockClass m(m_requestMutex, 0);
	if (m.Failed())
		return false;

	if (m_requests.empty())
		return false;
	req = m_requests.front();
	m_requests.pop();
	return true;
}

// ?addResponse@GameSpyPSMessageQueue@@ present-unmatched
void GameSpyPSMessageQueue::addResponse( const PSResponse& resp )
{
	MutexClass::LockClass m(m_responseMutex);
	if (m.Failed())
		return;

	m_responses.push(resp);
}

// ?getResponse@GameSpyPSMessageQueue@@ present-unmatched
Bool GameSpyPSMessageQueue::getResponse( PSResponse& resp )
{
	MutexClass::LockClass m(m_responseMutex, 0);
	if (m.Failed())
		return false;

	if (m_responses.empty())
		return false;
	resp = m_responses.front();
	m_responses.pop();
	return true;
}

PSThreadClass* GameSpyPSMessageQueue::getThread( void )
{
	return m_thread;
}

void GameSpyPSMessageQueue::trackPlayerStats( PSPlayerStats stats )
{
#ifdef DEBUG_LOGGING
	debugDumpPlayerStats( stats );
	DEBUG_ASSERTCRASH(stats.id != 0, ("Tracking stats with ID of 0\n"));
#endif
	MutexClass::LockClass m(m_requestMutex);
	PSPlayerStats newStats;
	std::map<Int, PSPlayerStats>::iterator it = m_playerStats.find(stats.id);
	if (it != m_playerStats.end())
	{
		newStats = it->second;
		newStats.incorporate(stats);
		m_playerStats[stats.id] = newStats;
	}
	else
	{
		m_playerStats[stats.id] = stats;
	}
}

PSPlayerStats GameSpyPSMessageQueue::findPlayerStatsByID( Int id )
{
	MutexClass::LockClass m(m_requestMutex);
	std::map<Int, PSPlayerStats>::iterator it = m_playerStats.find(id);
	if (it != m_playerStats.end())
	{
		return it->second;
	}

	PSPlayerStats empty;
	empty.id = 0;
	return empty;
}

//-------------------------------------------------------------------------

Bool PSThreadClass::tryConnect( void )
{
	Int result;

	DEBUG_LOG(("m_opCount = %d - opening connection\n", m_opCount));

	if (IsStatsConnected())
	{
		DEBUG_LOG(("connection already open!\n"));
		return true;
	}

	// this may block for 1-2 seconds (according to GS) so it's nice we're not in the UI thread :)
	result = InitStatsConnection(0);

	if (result != GE_NOERROR)
	{
		DEBUG_LOG(("InitStatsConnection() returned %d\n", result));
		return false;
	}

	return true;
}

static void persAuthCallback(int localid, int profileid, int authenticated, char *errmsg, void *instance)
{
	PSThreadClass *t = (PSThreadClass *)instance;
	DEBUG_LOG(("Auth callback: localid: %d profileid: %d auth: %d err: %s\n",localid, profileid, authenticated, errmsg));
	if (t)
		t->persAuthCallback(authenticated != 0);
}

// ?tryLogin@PSThreadClass@@ present-unmatched
Bool PSThreadClass::tryLogin( Int id, std::string nick, std::string password, std::string email )
{
	char validate[33];
	DEBUG_LOG(("PSThreadClass::tryLogin id = %d, nick = %s, password = %s, email = %s\n", id, nick.c_str(), password.c_str(), email.c_str()));
	/***********
	We'll go ahead and start the authentication, using a Presence & Messaging SDK
	profileid / password.  To generate the new validation token, we'll need to pass
	in the password for the profile we are authenticating.
	Again, if this is done in a client/server setting, with the Persistent Storage
	access being done on the server, and the P&M SDK is used on the client, the
	server will need to send the challenge (GetChallenge(NULL)) to the client, the
	client will create the validation token using GenerateAuth, and send it
	back to the server for use in PreAuthenticatePlayerPM
	***********/
	char *munkeeHack = strdup(password.c_str()); // GenerateAuth takes a char*, not a const char* :P
	GenerateAuth(GetChallenge(NULL), munkeeHack, validate);
	free (munkeeHack);

	/************
	After we get the validation token, we pass it and the profileid of the user
	we are authenticating into PreAuthenticatePlayerPM.
	We pass the same authentication callback as for the first user, but a different
	localid this time.
	************/
	m_loginOK = false;
	m_doneTryingToLogin = false;
	PreAuthenticatePlayerPM(id, id, validate, ::persAuthCallback, this);
	while (!m_doneTryingToLogin && IsStatsConnected())
		PersistThink();
	DEBUG_LOG(("Persistant Storage Login success %d\n", m_loginOK));
	return m_loginOK;
}

static void getPersistentDataCallback(int localid, int profileid, persisttype_t type, int index, int success, char *data, int len, void *instance)
{
	DEBUG_LOG(("Data get callback: localid: %d profileid: %d success: %d len: %d data: %s\n",localid, profileid, success, len, data));
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

	if (profileid == MESSAGE_QUEUE->getLocalPlayerID() && TheGameSpyGame && TheGameSpyGame->getUseStats())
	{
		t->gotLocalPlayerData();
		DEBUG_LOG(("getPersistentDataCallback() - got local player info\n"));

		// check if we have discons we should update on the server
		UserPreferences pref;
		AsciiString userPrefFilename;
		userPrefFilename.format("GeneralsOnline\\MiscPref%d.ini", MESSAGE_QUEUE->getLocalPlayerID());
		DEBUG_LOG(("using the file %s\n", userPrefFilename.str()));
		pref.load(userPrefFilename);
		Int addedInDesyncs2 = pref.getInt("0", 0);
		DEBUG_LOG(("addedInDesyncs2 = %d\n", addedInDesyncs2));
		if (addedInDesyncs2 < 0)
			addedInDesyncs2 = 10;
		Int addedInDesyncs3 = pref.getInt("1", 0);
		DEBUG_LOG(("addedInDesyncs3 = %d\n", addedInDesyncs3));
		if (addedInDesyncs3 < 0)
			addedInDesyncs3 = 10;
		Int addedInDesyncs4 = pref.getInt("2", 0);
		DEBUG_LOG(("addedInDesyncs4 = %d\n", addedInDesyncs4));
		if (addedInDesyncs4 < 0)
			addedInDesyncs4 = 10;
		Int addedInDiscons2 = pref.getInt("3", 0);
		DEBUG_LOG(("addedInDiscons2 = %d\n", addedInDiscons2));
		if (addedInDiscons2 < 0)
			addedInDiscons2 = 10;
		Int addedInDiscons3 = pref.getInt("4", 0);
		DEBUG_LOG(("addedInDiscons3 = %d\n", addedInDiscons3));
		if (addedInDiscons3 < 0)
			addedInDiscons3 = 10;
		Int addedInDiscons4 = pref.getInt("5", 0);
		DEBUG_LOG(("addedInDiscons4 = %d\n", addedInDiscons4));
		if (addedInDiscons4 < 0)
			addedInDiscons4 = 10;

		DEBUG_LOG(("addedInDesync=%d,%d,%d, addedInDiscon=%d,%d,%d\n",
			addedInDesyncs2, addedInDesyncs3, addedInDesyncs4,
			addedInDiscons2, addedInDiscons3, addedInDiscons4));

		if (addedInDesyncs2 || addedInDesyncs3 || addedInDesyncs4 || addedInDiscons2 || addedInDiscons3 || addedInDiscons4)
		{
			DEBUG_LOG(("We have a previous discon we can attempt to update!  Bummer...\n"));

			PSRequest req;
			req.requestType = PSRequest::PSREQUEST_UPDATEPLAYERSTATS;
			req.email = MESSAGE_QUEUE->getEmail();
			req.nick = MESSAGE_QUEUE->getNick();
			req.password = MESSAGE_QUEUE->getPassword();
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

	TheGameSpyPSMessageQueue->addResponse(resp);
}

static void setPersistentDataLocaleCallback(int localid, int profileid, persisttype_t type, int index, int success, void *instance)
{
	DEBUG_LOG(("Data save callback: localid: %d profileid: %d success: %d\n", localid, profileid, success));

	PSThreadClass *t = (PSThreadClass *)instance;
	if (!t)
		return;

	t->decrOpCount();
}

static void setPersistentDataCallback(int localid, int profileid, persisttype_t type, int index, int success, void *instance)
{
	DEBUG_LOG(("Data save callback: localid: %d profileid: %d success: %d\n", localid, profileid, success));

	PSThreadClass *t = (PSThreadClass *)instance;
	if (!t)
		return;

	if (success)
	{
		UserPreferences pref;
		AsciiString userPrefFilename;
		userPrefFilename.format("GeneralsOnline\\MiscPref%d.ini", profileid);
		DEBUG_LOG(("setPersistentDataCallback - writing stats to file %s\n", userPrefFilename.str()));
		pref.load(userPrefFilename);
		pref.clear();
		pref.write();
	}
	t->decrOpCount();
}

struct CDAuthInfo
{
	Bool success;
	Bool done;
	Int id;
};

void preAuthCDCallback(int localid, int profileid, int authenticated, char *errmsg, void *instance)
{
	DEBUG_LOG(("preAuthCDCallback(): profileid: %d auth: %d err: %s\n", profileid, authenticated, errmsg));

	CDAuthInfo *authInfo = (CDAuthInfo *)instance;
	authInfo->success = authenticated;
	authInfo->done = TRUE;
	authInfo->id = profileid;
}

static void getPreorderCallback(int localid, int profileid, persisttype_t type, int index, int success, char *data, int len, void *instance)
{
	PSThreadClass *t = (PSThreadClass *)instance;
	if (!t)
		return;

	t->decrOpCount();

	PSResponse resp;

	if (!success)
	{
		DEBUG_LOG(("Failed getPreorderCallback()\n"));
		return;
	}

	resp.responseType = PSResponse::PSRESPONSE_PREORDER;
	resp.preorder = (data && strcmp(data, "\\preorder\\1") == 0);
	DEBUG_LOG(("getPreorderCallback() - data was '%s'\n", data));

	TheGameSpyPSMessageQueue->addResponse(resp);
}

// ?Thread_Function@PSThreadClass@@ present-unmatched
void PSThreadClass::Thread_Function()
{
	try {
	_set_se_translator( DumpExceptionInfo ); // Hook that allows stack trace.
	/*********
	First step, set our game authentication info
	We could do:
		strcpy(gcd_gamename,"ccgenzh");
		strcpy(gcd_secret_key,"D6s9k3");
	or
		strcpy(gcd_gamename,"ccgeneralsb");
		strcpy(gcd_secret_key,"whatever the key is");
	...but this is more secure:
	**********/
	/**
	gcd_gamename[0]='c';gcd_gamename[1]='c';gcd_gamename[2]='g';gcd_gamename[3]='e';
	gcd_gamename[4]='n';gcd_gamename[5]='e';gcd_gamename[6]='r';gcd_gamename[7]='a';
	gcd_gamename[8]='l';gcd_gamename[9]='s';gcd_gamename[10]='b';gcd_gamename[11]='\0';
	gcd_secret_key[0]='g';gcd_secret_key[1]='3';gcd_secret_key[2]='T';gcd_secret_key[3]='9';
	gcd_secret_key[4]='s';gcd_secret_key[5]='2';gcd_secret_key[6]='\0';
	/**/
	gcd_gamename[0]='c';gcd_gamename[1]='c';gcd_gamename[2]='g';gcd_gamename[3]='e';
	gcd_gamename[4]='n';gcd_gamename[5]='z';gcd_gamename[6]='h';gcd_gamename[7]='\0';
	gcd_secret_key[0]='D';gcd_secret_key[1]='6';gcd_secret_key[2]='s';gcd_secret_key[3]='9';
	gcd_secret_key[4]='k';gcd_secret_key[5]='3';gcd_secret_key[6]='\0';
	/**/
	
	//strcpy(StatsServerHostname, "sdkdev.gamespy.com");

	PSRequest req;
	while ( running )
	{
		// deal with requests
		if (TheGameSpyPSMessageQueue->getRequest(req))
		{
			switch (req.requestType)
			{
			case PSRequest::PSREQUEST_SENDGAMERESTOGAMESPY:
				{
					if (tryConnect())
					{
						NewGame(0);
#ifdef DEBUG_LOGGING
						Int res = 
#endif // DEBUG_LOGGING
							SendGameSnapShot(NULL, req.results.c_str(), SNAP_FINAL);
						DEBUG_LOG(("Just sent game results - res was %d\n", res));
						FreeGame(NULL);
					}
				}
				break;
			case PSRequest::PSREQUEST_READPLAYERSTATS:
				{
					if (!MESSAGE_QUEUE->getLocalPlayerID())
					{
						MESSAGE_QUEUE->setLocalPlayerID(req.player.id); // first request is for ourselves
						MESSAGE_QUEUE->setEmail(req.email);
						MESSAGE_QUEUE->setNick(req.nick);
						MESSAGE_QUEUE->setPassword(req.password);
						DEBUG_LOG(("Setting email/nick/password = %s/%s/%s\n", req.email.c_str(), req.nick.c_str(), req.password.c_str()));
					}
					DEBUG_LOG(("Processing PSRequest::PSREQUEST_READPLAYERSTATS\n"));
					if (tryConnect())
					{
						incrOpCount();
						GetPersistDataValues(0, req.player.id, pd_public_rw, 0, "", getPersistentDataCallback, this);
					}
				}
				break;
			case PSRequest::PSREQUEST_UPDATEPLAYERLOCALE:
				{
					DEBUG_LOG(("Processing PSRequest::PSREQUEST_UPDATEPLAYERLOCALE\n"));
					if (tryConnect() && tryLogin(req.player.id, req.nick, req.password, req.email))
					{
						char kvbuf[256];
						sprintf(kvbuf, "\\locale\\%d", req.player.locale);
						incrOpCount();
						SetPersistDataValues(0, req.player.id, pd_public_rw, 0, kvbuf, setPersistentDataLocaleCallback, this);
					}
				}
				break;
			case PSRequest::PSREQUEST_UPDATEPLAYERSTATS:
				{
					/*
					** NOTE THAT THIS IS HIGHLY DEPENDENT ON INI ORDERING FOR THE PLAYERTEMPLATES!!!
					*/
					DEBUG_LOG(("Processing PSRequest::PSREQUEST_UPDATEPLAYERSTATS\n"));
					UserPreferences pref;
					AsciiString userPrefFilename;
					userPrefFilename.format("GeneralsOnline\\MiscPref%d.ini", MESSAGE_QUEUE->getLocalPlayerID());
					DEBUG_LOG(("using the file %s\n", userPrefFilename.str()));
					pref.load(userPrefFilename);
					Int addedInDesyncs2 = pref.getInt("0", 0);
					DEBUG_LOG(("addedInDesyncs2 = %d\n", addedInDesyncs2));
					if (addedInDesyncs2 < 0)
						addedInDesyncs2 = 10;
					Int addedInDesyncs3 = pref.getInt("1", 0);
					DEBUG_LOG(("addedInDesyncs3 = %d\n", addedInDesyncs3));
					if (addedInDesyncs3 < 0)
						addedInDesyncs3 = 10;
					Int addedInDesyncs4 = pref.getInt("2", 0);
					DEBUG_LOG(("addedInDesyncs4 = %d\n", addedInDesyncs4));
					if (addedInDesyncs4 < 0)
						addedInDesyncs4 = 10;
					Int addedInDiscons2 = pref.getInt("3", 0);
					DEBUG_LOG(("addedInDiscons2 = %d\n", addedInDiscons2));
					if (addedInDiscons2 < 0)
						addedInDiscons2 = 10;
					Int addedInDiscons3 = pref.getInt("4", 0);
					DEBUG_LOG(("addedInDiscons3 = %d\n", addedInDiscons3));
					if (addedInDiscons3 < 0)
						addedInDiscons3 = 10;
					Int addedInDiscons4 = pref.getInt("5", 0);
					DEBUG_LOG(("addedInDiscons4 = %d\n", addedInDiscons4));
					if (addedInDiscons4 < 0)
						addedInDiscons4 = 10;

					DEBUG_LOG(("req.addDesync=%d, req.addDiscon=%d, addedInDesync=%d,%d,%d, addedInDiscon=%d,%d,%d\n",
						req.addDesync, req.addDiscon, addedInDesyncs2, addedInDesyncs3, addedInDesyncs4,
						addedInDiscons2, addedInDiscons3, addedInDiscons4));

					if (req.addDesync || req.addDiscon)
					{
						AsciiString val;
						if (req.lastHouse == 2)
						{
							val.format("%d", addedInDesyncs2 + req.addDesync);
							pref["0"] = val;
							val.format("%d", addedInDiscons2 + req.addDiscon);
							pref["3"] = val;
							DEBUG_LOG(("house 2 req.addDesync || req.addDiscon: %d %d\n",
								addedInDesyncs2 + req.addDesync, addedInDiscons2 + req.addDiscon));
						}
						else if (req.lastHouse == 3)
						{
							val.format("%d", addedInDesyncs3 + req.addDesync);
							pref["1"] = val;
							val.format("%d", addedInDiscons3 + req.addDiscon);
							pref["4"] = val;
							DEBUG_LOG(("house 3 req.addDesync || req.addDiscon: %d %d\n",
								addedInDesyncs3 + req.addDesync, addedInDiscons3 + req.addDiscon));
						}
						else
						{
							val.format("%d", addedInDesyncs4 + req.addDesync);
							pref["2"] = val;
							val.format("%d", addedInDiscons4 + req.addDiscon);
							pref["5"] = val;
							DEBUG_LOG(("house 4 req.addDesync || req.addDiscon: %d %d\n",
								addedInDesyncs4 + req.addDesync, addedInDiscons4 + req.addDiscon));
						}
						pref.write();
						if (req.password.size() == 0)
							return;
					}
					if (!req.player.id)
					{
						DEBUG_LOG(("Bailing because ID is NULL!\n"));
						return;
					}
					req.player.desyncs[2] += addedInDesyncs2;
					req.player.games[2] += addedInDesyncs2;
					req.player.discons[2] += addedInDiscons2;
					req.player.games[2] += addedInDiscons2;
					req.player.desyncs[3] += addedInDesyncs3;
					req.player.games[3] += addedInDesyncs3;
					req.player.discons[3] += addedInDiscons3;
					req.player.games[3] += addedInDiscons3;
					req.player.desyncs[4] += addedInDesyncs4;
					req.player.games[4] += addedInDesyncs4;
					req.player.discons[4] += addedInDiscons4;
					req.player.games[4] += addedInDiscons4;
					DEBUG_LOG(("House2: %d/%d/%d, House3: %d/%d/%d, House4: %d/%d/%d\n",
						req.player.desyncs[2], req.player.discons[2], req.player.games[2],
						req.player.desyncs[3], req.player.discons[3], req.player.games[3],
						req.player.desyncs[4], req.player.discons[4], req.player.games[4]
						));
					if (tryConnect() && tryLogin(req.player.id, req.nick, req.password, req.email))
					{
						DEBUG_LOG(("Logged in!\n"));
						if (TheGameSpyPSMessageQueue)
							TheGameSpyPSMessageQueue->trackPlayerStats(req.player);

						char *munkeeHack = strdup(GameSpyPSMessageQueueInterface::formatPlayerKVPairs(req.player).c_str()); // GS takes a char* for some reason
						incrOpCount();
						DEBUG_LOG(("Setting values %s\n", munkeeHack));
						SetPersistDataValues(0, req.player.id, pd_public_rw, 0, munkeeHack, setPersistentDataCallback, this);
						free(munkeeHack);
					}
					else
					{
						DEBUG_LOG(("Cannot connect!\n"));
						//if (IsStatsConnected())
							//CloseStatsConnection();
					}
				}
				break;
			case PSRequest::PSREQUEST_READCDKEYSTATS:
				{
					DEBUG_LOG(("Processing PSRequest::PSREQUEST_READCDKEYSTATS\n"));
					if (tryConnect())
					{
						incrOpCount();
						CDAuthInfo cdAuthInfo;
						cdAuthInfo.done = FALSE;
						cdAuthInfo.success = FALSE;
						cdAuthInfo.id = 0;
						char cdkeyHash[33] = "";
						char validationToken[33] = "";
						char *munkeeHack = strdup(req.cdkey.c_str()); // GenerateAuth takes a char*, not a const char* :P

						GenerateAuth(GetChallenge(NULL), munkeeHack, validationToken); // validation token
						GenerateAuth("", munkeeHack, cdkeyHash); // cdkey hash

						free (munkeeHack);

						PreAuthenticatePlayerCD( 0, "preorder", cdkeyHash, validationToken, preAuthCDCallback , &cdAuthInfo);

						while (running && IsStatsConnected() && !cdAuthInfo.done)
							PersistThink();

						DEBUG_LOG(("Looking for preorder status for %d (success=%d, done=%d) from CDKey %s with hash %s\n",
							cdAuthInfo.id, cdAuthInfo.success, cdAuthInfo.done, req.cdkey.c_str(), cdkeyHash));
						if (cdAuthInfo.done && cdAuthInfo.success)
							GetPersistDataValues(0, cdAuthInfo.id, pd_public_ro, 0, "\\preorder", getPreorderCallback, this);
						else
							decrOpCount();
					}
				}
				break;
			}
		}

		// update the network
		if (IsStatsConnected())
		{
			PersistThink();
			if (m_opCount <= 0)
			{
				DEBUG_ASSERTCRASH(m_opCount == 0, ("Negative operations pending!!!"));
				DEBUG_LOG(("m_opCount = %d - closing connection\n", m_opCount));
				CloseStatsConnection();
				m_opCount = 0;
			}
		}

		// end our timeslice
		Switch_Thread();
	}

	if (IsStatsConnected())
		CloseStatsConnection();
	} catch ( ... ) {
		DEBUG_CRASH(("Exception in storage thread!"));
	}
}

//-------------------------------------------------------------------------
PSPlayerStats::PSPlayerStats( void )
{
	reset();
}

void PSPlayerStats::reset( void )
{
	BfmePlayerStats &me = (BfmePlayerStats &)*this;
	me.id = 0;
	me.locale = 0;
	me.gamesAsRandom = 0;
	me.lastFPS = 0;
	me.lastSide = 1;                 // no side chosen yet reads as side 1, not 0
	me.gamesInRowWithLastSide = 0;
	me.battleHonors = 0;
	me.challengeMedals = 0;
	me.winsInARow = 0;
	me.maxWinsInARow = 0;
	me.lossesInARow = 0;
	me.maxLossesInARow = 0;
	me.gamesOn1_1_Ladder = 0;
	me.gamesOn2_2_Ladder = 0;
	me.disconsInARow = 0;
	me.maxDisconsInARow = 0;
	me.desyncsInARow = 0;
	me.maxDesyncsInARow = 0;
	me.lastLadderPlayed = "";
	me.best1v1LadderRank = -1;       // unranked
	me.best2v2LadderRank = -1;
	me.dateCreated = "";
}

//-------------------------------------------------------------------------
#define CHECK(x) if (k == #x && generalMarker >= 0) { s.x[generalMarker] = atoi(v.c_str()); continue; }

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/GameSpyParsePlayerKVPairsThunk.cpp
// ?parsePlayerKVPairs@GameSpyPSMessageQueueInterface@@ present-unmatched
PSPlayerStats GameSpyPSMessageQueueInterface::parsePlayerKVPairs( std::string kvPairs )
{
	PSPlayerStats s;
	kvPairs.append("\\");

	Int offset = 0;
	while (1)
	{
		Int firstMarker = kvPairs.find_first_of('\\', offset);
		if (firstMarker < 0)
			break;
		Int secondMarker = kvPairs.find_first_of('\\', firstMarker + 1);
		if (secondMarker < 0)
			break;
		Int thirdMarker = kvPairs.find_first_of('\\', secondMarker + 1);
		if (thirdMarker < 0)
			break;
		Int generalMarker = kvPairs.find_last_not_of("0123456789", secondMarker - 1);
		std::string k, v, g;
		if (generalMarker == secondMarker - 1)
		{
			k = kvPairs.substr(firstMarker + 1, secondMarker - firstMarker - 1);
			generalMarker = -1;
		}
		else
		{
			k = kvPairs.substr(firstMarker + 1, generalMarker - firstMarker);
			g = kvPairs.substr(generalMarker + 1, secondMarker - generalMarker - 1);
			generalMarker = atoi(g.c_str());
		}
		v = kvPairs.substr(secondMarker + 1, thirdMarker - secondMarker - 1);
		//DEBUG_LOG(("%d [%s] [%s]\n", generalMarker, k.c_str(), v.c_str()));
		offset = thirdMarker - 1;

		CHECK(wins);
		CHECK(losses);
		CHECK(games);
		CHECK(duration);
		CHECK(unitsKilled);
		CHECK(unitsLost);
		CHECK(unitsBuilt);
		CHECK(buildingsKilled);
		CHECK(buildingsLost);
		CHECK(buildingsBuilt);
		CHECK(earnings);
		CHECK(techCaptured);
		CHECK(discons);
		CHECK(desyncs);
		CHECK(surrenders);
		CHECK(gamesOf2p);
		CHECK(gamesOf3p);
		CHECK(gamesOf4p);
		CHECK(gamesOf5p);
		CHECK(gamesOf6p);
		CHECK(gamesOf7p);
		CHECK(gamesOf8p);
		CHECK(customGames);
		CHECK(QMGames);
		
		if (k == "locale" && generalMarker < 0)
		{
			s.locale = atoi(v.c_str());
			continue;
		}

		if (k == "random" && generalMarker < 0)
		{
			s.gamesAsRandom = atoi(v.c_str());
			continue;
		}

		if (k == "options" && generalMarker < 0)
		{
			s.options = v;
			continue;
		}

		if (k == "systemSpec" && generalMarker < 0)
		{
			s.systemSpec = v;
			continue;
		}

		if (k == "fps" && generalMarker < 0)
		{
			s.lastFPS = atof(v.c_str());
			continue;
		}
		
		if (k == "lastGeneral" && generalMarker < 0)
		{
			s.lastGeneral = atoi(v.c_str());
			continue;
		}
		if (k == "genInRow" && generalMarker < 0)
		{
			s.gamesInRowWithLastGeneral = atoi(v.c_str());
			continue;
		}
		if (k == "builtNuke" && generalMarker < 0)
		{
			s.builtNuke = atoi(v.c_str());
			continue;
		}
		if (k == "builtSCUD" && generalMarker < 0)
		{
			s.builtSCUD = atoi(v.c_str());
			continue;
		}
		if (k == "builtCannon" && generalMarker < 0)
		{
			s.builtParticleCannon = atoi(v.c_str());
			continue;
		}
		if (k == "challenge" && generalMarker < 0)
		{
			s.challengeMedals = atoi(v.c_str());
			continue;
		}
		if (k == "battle" && generalMarker < 0)
		{
			s.battleHonors = atoi(v.c_str());
			continue;
		}

		if (k == "WinRow" && generalMarker < 0)
		{
			s.winsInARow = atoi(v.c_str());
			continue;
		}
		if (k == "WinRowMax" && generalMarker < 0)
		{
			s.maxWinsInARow = atoi(v.c_str());
			continue;
		}

		if (k == "LossRow" && generalMarker < 0)
		{
			s.lossesInARow = atoi(v.c_str());
			continue;
		}
		if (k == "LossRowMax" && generalMarker < 0)
		{
			s.maxLossesInARow = atoi(v.c_str());
			continue;
		}

		if (k == "DSRow" && generalMarker < 0)
		{
			s.desyncsInARow = atoi(v.c_str());
			continue;
		}
		if (k == "DSRowMax" && generalMarker < 0)
		{
			s.maxDesyncsInARow = atoi(v.c_str());
			continue;
		}

		if (k == "DCRow" && generalMarker < 0)
		{
			s.disconsInARow = atoi(v.c_str());
			continue;
		}
		if (k == "DCRowMax" && generalMarker < 0)
		{
			s.maxDisconsInARow = atoi(v.c_str());
			continue;
		}

		if (k == "ladderPort" && generalMarker < 0)
		{
			s.lastLadderPort = atoi(v.c_str());
			continue;
		}
		if (k == "ladderHost" && generalMarker < 0)
		{
			s.lastLadderHost = v;
			continue;
		}

		//DEBUG_ASSERTCRASH(generalMarker >= 0, ("Unknown KV Pair in persistent storage: [%s] = [%s]\n", k.c_str(), v.c_str()));
		//DEBUG_ASSERTCRASH(generalMarker  < 0, ("Unknown KV Pair in persistent storage for PlayerTemplate %d: [%s] = [%s]\n", generalMarker, k.c_str(), v.c_str()));
	}

	return s;
}
#define BFME_STATS ((BfmePlayerStats &)stats)

#define ITERATE_OVER(x) for (it = BFME_STATS.x.begin(); it != BFME_STATS.x.end(); ++it) \
{ \
	if (it->second > 0) \
	{ \
		sprintf(kvbuf, "\\" #x "%d\\%d", it->first, it->second); \
		s.append(kvbuf); \
	} \
}

#include "Common/PlayerTemplate.h"

std::string GameSpyPSMessageQueueInterface::formatPlayerKVPairs( PSPlayerStats stats )
{
	char kvbuf[256];
	std::string s = "";
	PerGeneralMap::iterator it;

	ITERATE_OVER(wins);
	ITERATE_OVER(losses);
	ITERATE_OVER(games);
	ITERATE_OVER(duration);
	ITERATE_OVER(unitsKilled);
	ITERATE_OVER(unitsLost);
	ITERATE_OVER(unitsBuilt);
	ITERATE_OVER(buildingsKilled);
	ITERATE_OVER(buildingsLost);
	ITERATE_OVER(buildingsBuilt);
	ITERATE_OVER(earnings);
	ITERATE_OVER(discons);
	ITERATE_OVER(desyncs);
	ITERATE_OVER(surrenders);
	ITERATE_OVER(gamesOf2p);
	ITERATE_OVER(gamesOf3p);
	ITERATE_OVER(gamesOf4p);
	ITERATE_OVER(gamesOf5p);
	ITERATE_OVER(gamesOf6p);
	ITERATE_OVER(gamesOf7p);
	ITERATE_OVER(gamesOf8p);
	ITERATE_OVER(customGames);
	ITERATE_OVER(QMGames);
	ITERATE_OVER(currentWinStreaks);
	ITERATE_OVER(currentLossStreaks);
	ITERATE_OVER(worstLossStreaks);
	ITERATE_OVER(bestWinStreaks);

	if (BFME_STATS.locale > 0)
	{
		sprintf(kvbuf, "\\locale\\%d", BFME_STATS.locale);
		s.append(kvbuf);
	}

	if (BFME_STATS.gamesAsRandom > 0)
	{
		sprintf(kvbuf, "\\random\\%d", BFME_STATS.gamesAsRandom);
		s.append(kvbuf);
	}

	if (BFME_STATS.options.length())
	{
		_snprintf(kvbuf, 256, "\\options\\%s", BFME_STATS.options.c_str());
		kvbuf[255] = 0;
		s.append(kvbuf);
	}

	if (BFME_STATS.systemSpec.length())
	{
		_snprintf(kvbuf, 256, "\\systemSpec\\%s", BFME_STATS.systemSpec.c_str());
		kvbuf[255] = 0;
		s.append(kvbuf);
	}

	if (BFME_STATS.lastFPS > 0.0f)
	{
		sprintf(kvbuf, "\\fps\\%g", BFME_STATS.lastFPS);
		s.append(kvbuf);
	}
	if (BFME_STATS.lastSide >= 0)
	{
		sprintf(kvbuf, "\\lastSide\\%d", BFME_STATS.lastSide);
		s.append(kvbuf);
	}
	if (BFME_STATS.gamesInRowWithLastSide >= 0)
	{
		sprintf(kvbuf, "\\genInRow\\%d", BFME_STATS.gamesInRowWithLastSide);
		s.append(kvbuf);
	}
	if (BFME_STATS.challengeMedals > 0)
	{
		sprintf(kvbuf, "\\challenge\\%d", BFME_STATS.challengeMedals);
		s.append(kvbuf);
	}
	if (BFME_STATS.battleHonors > 0)
	{
		sprintf(kvbuf, "\\battle\\%d", BFME_STATS.battleHonors);
		s.append(kvbuf);
	}

	// the streak counters themselves are reported every time, only their maxima are guarded
	{
		sprintf(kvbuf, "\\WinRow\\%d", BFME_STATS.winsInARow);
		s.append(kvbuf);
	}
	if (BFME_STATS.maxWinsInARow > 0)
	{
		sprintf(kvbuf, "\\WinRowMax\\%d", BFME_STATS.maxWinsInARow);
		s.append(kvbuf);
	}

	{
		sprintf(kvbuf, "\\LossRow\\%d", BFME_STATS.lossesInARow);
		s.append(kvbuf);
	}
	if (BFME_STATS.maxLossesInARow > 0)
	{
		sprintf(kvbuf, "\\LossRowMax\\%d", BFME_STATS.maxLossesInARow);
		s.append(kvbuf);
	}

	{
		sprintf(kvbuf, "\\DCRow\\%d", BFME_STATS.disconsInARow);
		s.append(kvbuf);
	}
	if (BFME_STATS.maxDisconsInARow > 0)
	{
		sprintf(kvbuf, "\\DCRowMax\\%d", BFME_STATS.maxDisconsInARow);
		s.append(kvbuf);
	}

	{
		sprintf(kvbuf, "\\DSRow\\%d", BFME_STATS.desyncsInARow);
		s.append(kvbuf);
	}
	if (BFME_STATS.maxDesyncsInARow > 0)
	{
		sprintf(kvbuf, "\\DSRowMax\\%d", BFME_STATS.maxDesyncsInARow);
		s.append(kvbuf);
	}

	if (BFME_STATS.best1v1LadderRank > 0)
	{
		sprintf(kvbuf, "\\best1v1LadderRank\\%d", BFME_STATS.best1v1LadderRank);
		s.append(kvbuf);
	}
	if (BFME_STATS.best2v2LadderRank > 0)
	{
		sprintf(kvbuf, "\\best2v2LadderRank\\%d", BFME_STATS.best2v2LadderRank);
		s.append(kvbuf);
	}
	if (BFME_STATS.lastLadderPlayed.length())
	{
		_snprintf(kvbuf, 256, "\\lastLadderPlayed\\%s", BFME_STATS.lastLadderPlayed.c_str());
		kvbuf[255] = 0;
		s.append(kvbuf);
	}
	if (BFME_STATS.dateCreated.length())
	{
		_snprintf(kvbuf, 256, "\\dateCreated\\%s", BFME_STATS.dateCreated.c_str());
		kvbuf[255] = 0;
		s.append(kvbuf);
	}
	if (BFME_STATS.gamesOn1_1_Ladder > 0)
	{
		sprintf(kvbuf, "\\gamesOn1_1_Ladder\\%d", BFME_STATS.gamesOn1_1_Ladder);
		s.append(kvbuf);
	}
	if (BFME_STATS.gamesOn2_2_Ladder > 0)
	{
		sprintf(kvbuf, "\\gamesOn2_2_Ladder\\%d", BFME_STATS.gamesOn2_2_Ladder);
		s.append(kvbuf);
	}

	// One DEBUG_LOG call cannot carry the whole KV string, so it goes out in
	// 511-character chunks. A release build drops the log call but keeps the
	// walk, which is how the chunk size was read back off retail.
	Int charsLeft = s.length();
	const char *chunk = s.c_str();
	while (charsLeft > 0)
	{
		Int thisChunk = std::min(511, charsLeft);
		DEBUG_LOG(("%.*s", thisChunk, chunk));
		chunk += thisChunk;
		charsLeft -= thisChunk;
	}

	return s;
}

//-------------------------------------------------------------------------
