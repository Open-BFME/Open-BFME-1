// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// The six ScoreKeeper bodies that move a counter and its per-template map:
//
//   0x000EA5A0  addObjectBuilt(Object *, Int)   built totals    map at +0x144
//   0x000EA730  removeObjectBuilt(Object *)     built totals    map at +0x144
//   0x000EA910  addObjectDestroyed(Object *)    destroyed[idx]  map at +0x150
//   0x000EAA90  addObjectDestroyedCount(...)    destroyed[idx]  map at +0x150
//   0x000EAB00  addObjectBuilt(Object *)        LOST totals     map at +0x2D0
//   0x000EAC60  addObjectCount(...)             LOST total      map at +0x2D0
//
// Six files each declared its own ScoreKeeper, padded blindly up to whichever
// fields its own body touched. Laid against ScoreKeeper::reset -- which is the
// one body that writes nearly all of them, and which stays in ScoreKeeperReset.cpp
// for the reason at the bottom -- the six partial layouts agree exactly, and
// together they cover the whole object. It is written out once here.
//
// AND THEY DISAGREE ABOUT ONE THING, WHICH IS THE POINT OF MERGING THEM.
// Two rows are named addObjectBuilt. The two-argument one at 0x000EA5A0 reaches
// +0x8C, +0x114 and +0x144, and removeObjectBuilt reaches the same three; those
// are the built totals and the built map. The one-argument one at 0x000EAB00
// reaches +0x90, +0x118 and +0x2D0 -- which in reset's layout are
// m_totalUnitsLost, m_totalBuildingsLost and m_objectsLost. So the body called
// addObjectBuilt(Object *) does not increment anything built; it increments the
// LOST counters. addObjectCount at 0x000EAC60 touches the same pair, +0x90 and
// +0x2D0, so it is the lost counter too.
//
// In six files that was invisible: each spelled its own members m_totalUnitsBuilt
// and m_objectsBuilt from the ZH name of the row it held, and padding did the
// rest. Written against one layout the two cannot both be called built, and the
// bodies below use the names their offsets actually land on. The ROW NAMES ARE
// UNCHANGED -- ?addObjectBuilt@ScoreKeeper@@QAEXPAVObject@@@Z stays exactly as
// it is, because renaming it would delete it, and because what retail's symbol
// was called is a separate question from what the body does.
//
// The callers were looked at, and they do not decide it: 0x000EAB00 has exactly
// ONE direct caller in the whole image, the unidentified dump at 0x001C9490,
// reached through no thunk that anything else uses. The caller-profile argument
// that settles this kind of question elsewhere -- a hundred and ten attack-and-
// weapon callers against eighteen that name no single class -- has nothing to
// work with here.
//
// The field attribution is settled, though, and from a source independent of
// reset's layout: declaration order. Zero Hour's ScoreKeeper.h declares
// m_totalUnitsBuilt immediately before m_totalUnitsLost, and
// m_totalBuildingsBuilt immediately before m_totalBuildingsLost, so in any
// layout built comes first and lost sits four bytes after it. Retail's pairs are
// adjacent exactly that way -- +0x8C beside +0x90, +0x114 beside +0x118 -- and
// reset touches both of each pair. The two-argument body takes the LOWER of each
// pair and the one-argument body takes the HIGHER, so the two-argument one is
// incrementing built and the one-argument one is incrementing lost. That is the
// same answer reset's layout gave, reached without it.
//
// So the ZH name did NOT survive a change of meaning: it was put on a body that
// counts losses. The row still stays as it is -- retracting it would empty
// nothing but would delete the only identity these bytes have, and no better
// name has been recovered, only the knowledge that this one is wrong.
//
// One trap this merge had to step around, the same shape as the Bool typedef in
// PlayerRankAndScience.cpp but on a local instead of a signature: two of these
// files defined a type called Bool and defined it differently -- int in
// addObjectDestroyed, bool in addObjectBuilt(Object *, Int) -- and each declared
// its addToCount flag with it. int and bool are not the same local. Both are
// written out as the concrete type they were and there is no Bool typedef here.
//
// ScoreKeeperReset.cpp stays separate: it declares the three scoring masks as
// file-static objects of a bitset-backed BitFlags it defines itself, where all
// six of these read them as extern of a BitFlags that only declares
// testSetAndClear. Those are different objects with different linkage, and one
// TU cannot hold both spellings.

#include <map>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef int Int;

class ThingTemplate;
class BfmeRvaA760Object;
class Overridable;

typedef _STL::map<const ThingTemplate *, Int> ObjectCountMap;
typedef ObjectCountMap::iterator ObjectCountMapIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int Bits>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags<Bits> &mustBeSet, const BitFlags<Bits> &mustBeClear) const;
	unsigned int m_bits[4];
};

typedef BitFlags<116> KindOfMaskType;

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_INFANTRY = 8,
	KINDOF_VEHICLE = 9,
	KINDOF_SCORE = 39,
	KINDOF_SCORE_CREATE = 40
};

extern const KindOfMaskType KINDOFMASK_NONE;
extern KindOfMaskType scoringBuildingMask;
extern KindOfMaskType scoringBuildingCreateMask;
extern KindOfMaskType scoringBuildingDestroyMask;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType kind) const;
	bool hasKind(KindOfType kind) const
	{
		return (m_kindOf.m_bits[(unsigned int)kind >> 5] & (1 << ((unsigned int)kind & 31))) != 0;
	}

	bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const
	{
		return m_kindOf.testSetAndClear(mustBeSet, mustBeClear);
	}

private:
	unsigned char m_pad[0xC0];
	KindOfMaskType m_kindOf;					// +0xC0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex(void) const { return m_playerIndex; }

private:
	unsigned char m_pad[0x24];
	Int m_playerIndex;						// +0x24
};

// getTemplate and isKindOf belong to Thing, not to Object, and that is
// load-bearing rather than tidiness. removeObjectBuilt is large enough that
// MSVC declines to inline getTemplate at two of its call sites and emits a
// call instead; that call has to land on ?getTemplate@Thing@@QBEPBVThingTemplate@@XZ,
// which is a real matched row at 0x00098E50. Five of these six bodies inline it
// everywhere and never care where it is declared -- which is exactly why five
// files could put it on Object and still match, and why the sixth could not.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}
	bool isKindOf(KindOfType kind) const { return getTemplate()->isKindOf(kind); }
	unsigned int getStatusBits(void) const { return m_status; }

private:
	void *m_vptr;
	const ThingTemplate *m_template;				// +0x04
	unsigned char m_pad[0x90];
	unsigned int m_status;						// +0x98
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Player *getControllingPlayer(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	bool isScoringEnabled(void) const { return m_isScoringEnabled != 0; }

private:
	unsigned char m_pad[0x90];
	unsigned char m_isScoringEnabled;				// +0x90
};

// Address-derived: the unit-score filter BFME uses where Zero Hour tested the
// infantry and vehicle KindOfs directly.
class BfmeRvaA760ProbeInterface
{
public:
	bool accepts(BfmeRvaA760Object *obj, Int arg);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_pad[0x121C];
	BfmeRvaA760ProbeInterface m_unitScoreFilter;			// +0x121C
};

extern GameLogic *TheBfmeGameLogic;
extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ScoreKeeper.h
class ScoreKeeper
{
public:
	void addObjectBuilt(Object *o, Int amount);
	void removeObjectBuilt(const Object *o);
	void addObjectDestroyed(const Object *o);
	void addObjectDestroyedCount(const ThingTemplate *tmpl, const Player *player, Int amount);
	void addObjectBuilt(Object *o);
	void addObjectCount(const ThingTemplate *tmpl, Int amount);

private:
	void *m_vtable;							// +0x00
	Int m_totalMoneyEarned;						// +0x04
	Int m_totalMoneySpent;						// +0x08
	Int m_totalUnitsDestroyed[32];					// +0x0C
	Int m_totalUnitsBuilt;						// +0x8C
	Int m_totalUnitsLost;						// +0x90
	Int m_totalBuildingsDestroyed[32];				// +0x94
	Int m_totalBuildingsBuilt;					// +0x114
	Int m_totalBuildingsLost;					// +0x118
	Int m_heroesVetted;						// +0x11C
	Int m_unitsVetted;						// +0x120
	Int m_powerPoints;						// +0x124
	Int m_pad128;							// +0x128
	Int m_regionCommandPoints;					// +0x12C
	Int m_regionResources;						// +0x130
	Int m_regionPowerPoints;					// +0x134
	Int m_currentScore;						// +0x138
	unsigned int m_frameOverride;					// +0x13C
	Int m_myPlayerIdx;						// +0x140
	ObjectCountMap m_objectsBuilt;					// +0x144
	ObjectCountMap m_objectsDestroyed[32];				// +0x150
	ObjectCountMap m_objectsLost;					// +0x2D0
	ObjectCountMap m_objectsCaptured;				// +0x2DC
};

// ?addObjectBuilt@ScoreKeeper@@QAEXPAVObject@@H@Z
void ScoreKeeper::addObjectBuilt(Object *o, Int amount)
{
	if (TheBfmeGameLogic->isScoringEnabled() == false)
		return;

	if (o->getStatusBits() & 0x800)
		return;

	bool addToCount = false;
	if (o->getTemplate()->isKindOfMulti(scoringBuildingMask, KINDOFMASK_NONE))
	{
		m_totalBuildingsBuilt += amount;
		addToCount = true;
	}
	else if (o->getTemplate()->isKindOfMulti(scoringBuildingCreateMask, KINDOFMASK_NONE))
	{
		m_totalBuildingsBuilt += amount;
		addToCount = true;
	}
	else if (TheWritableGlobalData->m_unitScoreFilter.accepts((BfmeRvaA760Object *)o, 0))
	{
		m_totalUnitsBuilt += amount;
		addToCount = true;
	}
	if (!addToCount)
		return;

	int existingCount = 0;
	ObjectCountMapIt it = m_objectsBuilt.find(o->getTemplate());
	if (it != m_objectsBuilt.end())
		existingCount = it->second;
	int newCount = MAX(0, existingCount + amount);
	m_objectsBuilt[o->getTemplate()] = newCount;
}

// ?removeObjectBuilt@ScoreKeeper@@QAEXPBVObject@@@Z
void ScoreKeeper::removeObjectBuilt(const Object *o)
{
	if (TheBfmeGameLogic->isScoringEnabled() == false)
		return;

	if (o->getStatusBits() & 0x800)
		return;

	if (o->getTemplate()->isKindOfMulti(scoringBuildingMask, KINDOFMASK_NONE))
	{
		--m_totalBuildingsBuilt;
	}
	else if (o->getTemplate()->isKindOfMulti(scoringBuildingCreateMask, KINDOFMASK_NONE))
	{
		--m_totalBuildingsBuilt;
	}
	else if (o->getTemplate()->hasKind(KINDOF_INFANTRY) || o->getTemplate()->isKindOf(KINDOF_VEHICLE))
	{
		if (o->getTemplate()->isKindOf(KINDOF_SCORE) || o->getTemplate()->isKindOf(KINDOF_SCORE_CREATE))
			--m_totalUnitsBuilt;
		else
			return;
	}
	else
		return;

	int existingCount = 0;
	ObjectCountMapIt it = m_objectsBuilt.find(o->getTemplate());
	if (it != m_objectsBuilt.end())
		existingCount = it->second;
	m_objectsBuilt[o->getTemplate()] = existingCount - 1;
}

// ?addObjectDestroyed@ScoreKeeper@@QAEXPBVObject@@@Z
void ScoreKeeper::addObjectDestroyed(const Object *o)
{
	ScoreKeeper *keeper = this;
	const Object *object = o;
	if (TheBfmeGameLogic->isScoringEnabled() == false)
		return;

	if (object->getStatusBits() & 0x800)
		return;

	Player *player = object->getControllingPlayer();
	Int playerIdx = player->getPlayerIndex();
	// int, not bool: this file's Bool was a typedef for int.
	int addToCount = false;
	if (object->getTemplate()->isKindOfMulti(scoringBuildingMask, KINDOFMASK_NONE))
	{
		++keeper->m_totalBuildingsDestroyed[playerIdx];
		addToCount = true;
	}
	else if (object->getTemplate()->isKindOfMulti(scoringBuildingDestroyMask, KINDOFMASK_NONE))
	{
		++keeper->m_totalBuildingsDestroyed[playerIdx];
		addToCount = true;
	}
	else if (TheWritableGlobalData->m_unitScoreFilter.accepts((BfmeRvaA760Object *)object, 0))
	{
		++keeper->m_totalUnitsDestroyed[playerIdx];
		addToCount = true;
	}
	if (addToCount)
	{
		Int existingCount = 0;
		ObjectCountMapIt it = keeper->m_objectsDestroyed[playerIdx].find(object->getTemplate());
		if (it != keeper->m_objectsDestroyed[playerIdx].end())
			existingCount = it->second;
		keeper->m_objectsDestroyed[playerIdx][object->getTemplate()] = existingCount + 1;
	}
}

// ?addObjectDestroyedCount@ScoreKeeper@@QAEXPBVThingTemplate@@PBVPlayer@@H@Z
void ScoreKeeper::addObjectDestroyedCount(const ThingTemplate *tmpl, const Player *player, Int amount)
{
	int playerIdx = player->getPlayerIndex();
	m_totalUnitsDestroyed[playerIdx] += amount;
	ObjectCountMap &counts = m_objectsDestroyed[playerIdx];
	int existingCount = 0;
	ObjectCountMapIt it = counts.find(tmpl);
	if (it != counts.end())
		existingCount = it->second;
	counts[tmpl] = existingCount + amount;
}

// ?addObjectBuilt@ScoreKeeper@@QAEXPAVObject@@@Z
// The row keeps its Zero Hour name; the offsets it reaches are the LOST ones.
void ScoreKeeper::addObjectBuilt(Object *o)
{
	if (TheBfmeGameLogic->isScoringEnabled() == false)
		return;

	if (o->getStatusBits() & 0x800)
		return;

	if (o->getTemplate()->isKindOfMulti(scoringBuildingMask, KINDOFMASK_NONE))
		++m_totalBuildingsLost;
	else if (o->getTemplate()->isKindOfMulti(scoringBuildingCreateMask, KINDOFMASK_NONE))
		++m_totalBuildingsLost;
	else if (TheWritableGlobalData->m_unitScoreFilter.accepts((BfmeRvaA760Object *)o, 0))
		++m_totalUnitsLost;
	else
		return;

	int existingCount = 0;
	ObjectCountMapIt it = m_objectsLost.find(o->getTemplate());
	if (it != m_objectsLost.end())
		existingCount = it->second;
	m_objectsLost[o->getTemplate()] = existingCount + 1;
}

// ?addObjectCount@ScoreKeeper@@QAEXPBVThingTemplate@@H@Z
void ScoreKeeper::addObjectCount(const ThingTemplate *tmpl, Int amount)
{
	m_totalUnitsLost += amount;
	int existingCount = 0;
	ObjectCountMapIt it = m_objectsLost.find(tmpl);
	if (it != m_objectsLost.end())
		existingCount = it->second;
	m_objectsLost[tmpl] = existingCount + amount;
}
