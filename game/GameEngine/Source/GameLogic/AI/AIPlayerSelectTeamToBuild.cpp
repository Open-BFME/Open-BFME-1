// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?selectTeamToBuild@AIPlayer@@MAE_NXZ: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::selectTeamToBuild, 0x00163220, 953 bytes.
// Identity: slot 22 (+0x58) of the AIPlayer vtable 0x010968B0 routes through
// ILT 0x0001B216 here, the slot Zero Hour's AIPlayer.h gives
// selectTeamToBuild (queueDozer 21, selectTeamToReinforce 23). The body is the
// Zero Hour twin: it calls isAGoodIdeaToBuildTeam (slot 25), then
// selectTeamToReinforce (slot 23) and buildSpecificAITeam (slot 9), and
// carries the "**AI** Selecting team to build" and "Error : team '" ...
// "' has no Home Position (or Origin)." literals and the random pick at
// AIPlayer.cpp line 1754.
//
// Layout: AIPlayer m_player +0x0C, m_readyToBuildTeam +0x10, m_teamTimer
// +0x14, m_teamSeconds +0x1C; Player team-prototype list +0x288, Money at
// +0x48 (amount +0x4C); TeamPrototype name +0x14 (the string Zero Hour's
// getName() reads here, as in checkReadyTeams), production priority +0x1C8,
// has-home-location flag +0x194; TheAI's TAiData at +0x14.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0

enum { LOGICFRAMES_PER_SECOND = 5 };

extern int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// StringBase<char>'s buffer header: refcount, length, capacity, data.
struct BfmeAsciiHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

// Retail inlines AsciiString::concat(const AsciiString &) as
// concat(str(), getLength()) into StringBase<char>::concat(const char *, int),
// each accessor with its own null test.
class BfmeAsciiView
{
public:
	int getLength() const { return m_data ? m_data->m_length : 0; }
	const char *str() const { return m_data ? m_data->m_data : ""; }
private:
	const BfmeAsciiHeader *m_data;
};

static inline void bfmeConcat(AsciiString &dst, const AsciiString &src)
{
	const BfmeAsciiView &s = *(const BfmeAsciiView *)&src;
	((StringBase<char> *)&dst)->concat(s.str(), s.getLength());
}

struct GlobalData
{
	char m_unmodelled000[0xa88];
	Int m_debugAI;							// +0xA88
};

extern GlobalData *TheGlobalData;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct TAiData
{
	char m_unmodelled000[0x0c];
	UnsignedInt m_resourcesWealthy;					// +0x0C
	UnsignedInt m_resourcesPoor;					// +0x10
	char m_unmodelled014[0x1c - 0x14];
	Real m_teamWealthyMod;						// +0x1C
	char m_unmodelled020[0x24 - 0x20];
	Real m_teamPoorMod;						// +0x24
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
private:
	char m_unmodelled000[0x14];
	TAiData *m_aiData;						// +0x14
};

extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	const AsciiString &getName(void) const { return m_rva14Name; }

	char m_unmodelled000[0x14];
	AsciiString m_rva14Name;					// +0x14
	char m_unmodelled018[0x194 - 0x18];
	Bool m_hasHomeLocation;						// +0x194
	char m_unmodelled195[0x1c8 - 0x195];
	Int m_productionPriority;					// +0x1C8
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	UnsignedInt countMoney() const { return m_money; }
private:
	void *m_vptr;
	UnsignedInt m_money;						// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	typedef _STL::list<TeamPrototype *> PlayerTeamList;
	Money *getMoney() { return &m_money; }
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }

private:
	char m_unmodelled000[0x48];
	Money m_money;							// +0x48
	char m_unmodelled050[0x288 - 0x50];
	PlayerTeamList m_playerTeamPrototypes;				// +0x288
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	BFME_VIRTUAL_SLOT(00) BFME_VIRTUAL_SLOT(01) BFME_VIRTUAL_SLOT(02)
	BFME_VIRTUAL_SLOT(03) BFME_VIRTUAL_SLOT(04) BFME_VIRTUAL_SLOT(05)
	BFME_VIRTUAL_SLOT(06) BFME_VIRTUAL_SLOT(07) BFME_VIRTUAL_SLOT(08)
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);	// slot 9
	BFME_VIRTUAL_SLOT(10)
	virtual Bool isSkirmishAI(void);				// slot 11
	BFME_VIRTUAL_SLOT(12) BFME_VIRTUAL_SLOT(13) BFME_VIRTUAL_SLOT(14)
	BFME_VIRTUAL_SLOT(15) BFME_VIRTUAL_SLOT(16) BFME_VIRTUAL_SLOT(17)
	BFME_VIRTUAL_SLOT(18) BFME_VIRTUAL_SLOT(19) BFME_VIRTUAL_SLOT(20)
	BFME_VIRTUAL_SLOT(21)

protected:
	virtual Bool selectTeamToBuild( void );				// slot 22
	virtual Bool selectTeamToReinforce( Int minPriority );		// slot 23
	BFME_VIRTUAL_SLOT(24)
	virtual Bool isAGoodIdeaToBuildTeam( TeamPrototype *proto );	// slot 25

private:
	void *m_dlinkhead_TeamBuildQueue;				// +0x04
	void *m_dlinkhead_TeamReadyQueue;				// +0x08
	Player *m_player;						// +0x0C
	Bool m_readyToBuildTeam;					// +0x10
	Int m_teamTimer;						// +0x14
	char m_unmodelled018[0x1c - 0x18];
	Int m_teamSeconds;						// +0x1C
};

#undef BFME_VIRTUAL_SLOT

Bool AIPlayer::selectTeamToBuild( void )
{

	// find the highest priority of all teams
	Player::PlayerTeamList::const_iterator t;
	const Int invalidPri = -99999;
	Int hiPri = invalidPri;
	// collect all teams that are possible to build, and are at the highest priority
	Player::PlayerTeamList candidateList1;
	for (t = m_player->getPlayerTeams()->begin(); t != m_player->getPlayerTeams()->end(); ++t)
	{
		if (isAGoodIdeaToBuildTeam(*t))
		{
			candidateList1.push_back( (*t) );
			Int pri = (*t)->m_productionPriority;

			if (pri > hiPri)
			{
				hiPri = pri;
			}
		}
	}

	if (selectTeamToReinforce(hiPri)) {
		return true;
	}

	// check if no team prototypes are valid for production
	if (hiPri == invalidPri)
		return false;

	if (TheGlobalData->m_debugAI) {
		TheScriptEngine->AppendDebugMessage("**AI** Selecting team to build", false);
	}

	// collect all teams that are possible to build, and are at the highest priority
	Player::PlayerTeamList candidateList;
	Int count = 0;
	for (t = candidateList1.begin(); t != candidateList1.end(); ++t)
	{
		if ((*t)->m_productionPriority == hiPri)
		{
			candidateList.push_back( (*t) );
			count++;
		}
	}

	// pick a random team from the hi-priority set
	Int which = GetGameLogicRandomValue( 0, count-1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIPlayer.cpp", 1754 );

	TeamPrototype *teamProto = NULL;
	Int i = 0;
	for (t = candidateList.begin(); t != candidateList.end(); ++t)
	{
		if (i == which)
		{
			teamProto = (*t);
			break;
		}

		i++;
	}
	if (teamProto) {
		if (!teamProto->m_hasHomeLocation && !isSkirmishAI()) {
			AsciiString teamStr = "Error : team '";
			bfmeConcat(teamStr, teamProto->getName());
			// StringBase<char>::concat(const char *, int) at 0x00887D60, length folded.
			((StringBase<char> *)&teamStr)->concat("' has no Home Position (or Origin).", 35);
			TheScriptEngine->AppendDebugMessage(teamStr, false);
		}
		// Build it at low priority, as we have selected it automagically.
		buildSpecificAITeam(teamProto, false);
		m_readyToBuildTeam = false;
		m_teamTimer = m_teamSeconds*LOGICFRAMES_PER_SECOND;
		if (m_player->getMoney()->countMoney() < TheAI->getAiData()->m_resourcesPoor) {
			m_teamTimer = m_teamTimer/TheAI->getAiData()->m_teamPoorMod;
		}	else if (m_player->getMoney()->countMoney() > TheAI->getAiData()->m_resourcesWealthy) {
			m_teamTimer = m_teamTimer/TheAI->getAiData()->m_teamWealthyMod;
		}
		return true;
	}
	return false;
}
