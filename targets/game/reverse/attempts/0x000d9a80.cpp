// ?update@Player@@QAEXXZ
// partial score=0.3 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// Readable BFME reconstruction of ?update@Player@@QAEXXZ.
// The named caller at 0x000DF2D0 reaches the retail body at 0x000D9A80.

#define Matrix4x4 Matrix4
#include "PreRTS.h"

#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Team.h"
#include "Common/MessageStream.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPlayer.h"
#include "GameLogic/GameLogic.h"

// BFME's two small maps occupy Player+0x1D8 and Player+0x1EC.  This is the
// existing typed helper used by BfmeThingEZCMaps.cpp; its insert body is the
// proven retail ILT at 0x0000B271, so this TU only declares the ABI.
class BfmeMapEZC
{
public:
	int *insert(void *key);

private:
	unsigned char m_bytes[0x14];
};

// The pending records are twelve bytes in the update body: an opaque owner,
// one AsciiString key, and a countdown at +8.  The vector itself is the three
// pointer STL layout beginning at Player+0x200.
struct BfmePlayerPendingRecord
{
	void *m_opaque;
	AsciiString m_key;
	UnsignedInt m_count;
};

struct BfmePlayerPendingVector
{
	BfmePlayerPendingRecord **m_first;
	BfmePlayerPendingRecord **m_last;
	BfmePlayerPendingRecord **m_capacity;
};

struct BfmePlayerUpdateFields
{
	unsigned char m_unmodelled_000[0x1D8];
	BfmeMapEZC m_mapAt1D8;
	BfmeMapEZC m_mapAt1EC;
	BfmePlayerPendingVector m_pending;
};

// TeamPrototype's BFME instance-list field is at +0x274.  Keep the advance
// declaration-only and use the already pinned Team instance-list ABI.
class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

struct BfmeTeamPrototypeUpdateView
{
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head) : m_cur(head) {}

	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (Team *)((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

// ?update@Player@@QAEXXZ
void Player::update()
{
	BfmePlayerUpdateFields *fields = (BfmePlayerUpdateFields *)this;

	AIPlayer *ai = *(AIPlayer **)((char *)this + 0x220);
	if (ai)
		ai->update();

	for (BfmePlayerPendingRecord **it = fields->m_pending.m_first;
		it != fields->m_pending.m_last; ++it)
	{
		BfmePlayerPendingRecord *record = *it;
		if (record && record->m_count != 0)
		{
			--record->m_count;
			if (record->m_count == 0)
			{
				AsciiString key(record->m_key);
				fields->m_mapAt1EC.insert(&key);
				int *slot = fields->m_mapAt1D8.insert(&key);
				*slot = (int)this;
			}
		}
	}

	struct BfmePlayerTeamListField
	{
		unsigned char m_unmodelled_000[0x288];
		Player::PlayerTeamList m_teamPrototypes;
	};

	BfmePlayerTeamListField *teamFields = (BfmePlayerTeamListField *)this;
	Player::PlayerTeamList teamPrototypes(teamFields->m_teamPrototypes);
	for (Player::PlayerTeamList::iterator it = teamPrototypes.begin();
		it != teamPrototypes.end(); ++it)
	{
		BfmeTeamPrototypeUpdateView *prototype =
			(BfmeTeamPrototypeUpdateView *)*it;
		for (BfmeTeamInstanceIterator iter(prototype->m_teamInstanceList);
			!iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (team)
				team->updateGenericScripts();
		}
	}

	if (ThePlayerList->getLocalPlayer() == this)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (now % LOGICFRAMES_PER_SECOND == 0 &&
			TheGlobalData->m_clientRetaliationModeEnabled !=
				isLogicalRetaliationModeEnabled())
		{
			GameMessage *msg = TheMessageStream->appendMessage(
				GameMessage::MSG_ENABLE_RETALIATION_MODE);
			if (msg)
			{
				msg->appendIntegerArgument(getPlayerIndex());
				msg->appendBooleanArgument(
					TheGlobalData->m_clientRetaliationModeEnabled);
			}
		}
	}
}
