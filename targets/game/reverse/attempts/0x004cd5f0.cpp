// ?rva004CD5F0@GameInfo@@QBEEHH@Z
// partial score=0.24 date=2026-09-21
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x004CD5F0, 157 bytes. A GameInfo helper (calls getMap()/getConstSlot()
// on its own `this`) that checks whether a given map-cache player-position
// record at MapMetaData+0x54 (see MapMetaData_assign.cpp / the +0x54
// Rva000C0C60 eight-record body) allows the game slot at a given index:
// human/computer flag must match GameSlot::isAI(), and if the record's
// faction set is non-empty and the slot has a valid player-template index,
// that template's name must be a member of the faction set.
//
// No named caller (?d_004cdf20@@YAXXZ, itself unlandable) and no vtable slot
// prove the real method name, so this keeps the address token.

#define _STLP_NO_EXCEPTIONS 1
#include <set>
#include "ascii_string.h"

typedef int Int;
typedef unsigned char Bool;

class PlayerTemplate
{
public:
	AsciiString getName() const;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(Int i);
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
// Field order/offsets proven by the matched MapMetaData_assign.cpp (+0x54
// MapPlayers) and its Rva000C0C60MapPlayersAssign.cpp record body.
struct Rva004CD5F0PlayerRecord
{
	Bool m_human;
	Bool m_computer;
	Bool m_loadAIScripts;
	Int m_forcePlayerTeam;
	std::set<AsciiString> m_factionSet;
};

struct MapPlayers
{
	Rva004CD5F0PlayerRecord m_items[8];
};

class MapMetaData
{
public:
	unsigned char m_prefix[0x54];
	MapPlayers m_players;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	Bool isAI() const;					///< ILT 0x000422DF

private:
	unsigned char m_prefix[0x14];

public:
	Int m_playerTemplate;				///< +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	AsciiString getMap() const;						///< ILT 0x0002F28E
	const GameSlot *getConstSlot(Int index) const;		///< ILT 0x00029460

	Bool rva004CD5F0(Int mapPlayerIndex, Int slotIndex) const;
};

Bool GameInfo::rva004CD5F0(Int mapPlayerIndex, Int slotIndex) const
{
	const MapMetaData *md = TheMapCache->findMap(getMap());
	if (!md)
		return 1;

	const Rva004CD5F0PlayerRecord &pr = md->m_players.m_items[mapPlayerIndex];
	const GameSlot *slot = getConstSlot(slotIndex);

	if (slot->isAI())
	{
		if (!pr.m_computer)
			return 0;
	}
	else
	{
		if (!pr.m_human)
			return 0;
	}

	if (pr.m_factionSet.empty())
		return 1;

	if (slot->m_playerTemplate < 0)
		return 1;

	const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(slot->m_playerTemplate);

	// pt->getName() returns AsciiString (a type with a real destructor) by
	// value; capturing it into a POD local keeps the compiler from installing
	// automatic SEH unwind protection for it (retail has none). The member
	// function pointer union preserves the real declared signature so the
	// call still mangles/links against the already-matched
	// ?getName@PlayerTemplate@@QBE?AVAsciiString@@XZ.
	struct RawAsciiString { void *m_text; };
	RawAsciiString name;
	{
		typedef RawAsciiString (PlayerTemplate::*RawFn)() const;
		typedef AsciiString (PlayerTemplate::*RealFn)() const;
		union { RealFn real; RawFn raw; } fn;
		fn.real = &PlayerTemplate::getName;
		name = (pt->*fn.raw)();
	}

	bool found = pr.m_factionSet.find(*(const AsciiString *)&name) != pr.m_factionSet.end();
	((AsciiString *)&name)->~AsciiString();
	return found;
}
