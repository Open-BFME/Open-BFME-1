// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Include
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <bitset>

#include "../../../../../Include/Common/ScalarTypes.h"



#include "../../../../../Include/Common/Enums/StateReturnType.h"





#include "../../../command_source_type.h"

#include "Lib/Coord3D.h"

class Object;
class Player;
class AIUpdateInterface002B9970;
class DozerAIInterface002B9970;

class StateMachine002B9970
{
public:
	virtual void slot000();
	unsigned char m_beforeOwner[0xc];
	Object *m_owner;
};

class State002B9970
{
public:
	virtual StateReturnType update() = 0;

	Object *getMachineOwner()
	{
		return m_machine->m_owner;
	}

protected:
	unsigned char m_beforeMachine[0x18];
	StateMachine002B9970 *m_machine;
	unsigned char m_afterMachine[4];
};

class Player
{
public:
	virtual void slot000();
	unsigned char m_beforePlayerIndex[0x20];
	int m_playerIndex;

	int getPlayerIndex() const
	{
		return m_playerIndex;
	}
};

class Object
{
public:
	virtual void slot000();

	AIUpdateInterface002B9970 *getAIUpdateInterface() const
	{
		return m_ai;
	}

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	Player *getControllingPlayer() const;



	unsigned char m_beforeAI[0x200];
	AIUpdateInterface002B9970 *m_ai;
	unsigned char m_beforePrivateStatus[0x13c];
	unsigned char m_privateStatus;
};

// Retail call to Object::getControllingPlayer goes through ILT 0x20824.
extern void j_00020824();

// Retail call to AICommandInterface::aiRepair goes through ILT 0x29c08.
extern void j_00029c08();

class AICommandInterface
{
public:
	virtual void aiDoCommand() = 0;
};

class DozerAIInterface002B9970
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual float getBoredTime() const;
	virtual float getBoredRange() const;
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual bool isAnyTaskPending() const;
};

class AIUpdatePrimary002B9970
{
public:
	virtual void slot000();
	unsigned char m_afterVtable[0x1c];
};

class AIUpdateInterface002B9970 : public AIUpdatePrimary002B9970, public AICommandInterface
{
public:
	virtual void slot004(); virtual void slot008();
	virtual void slot00c(); virtual void slot010();
	virtual void slot014(); virtual void slot018();
	virtual void slot01c(); virtual void slot020();
	virtual void slot024(); virtual void slot028();
	virtual void slot02c(); virtual void slot030();
	virtual void slot034(); virtual void slot038();
	virtual void slot03c(); virtual void slot040();
	virtual void slot044(); virtual void slot048();
	virtual void slot04c(); virtual void slot050();
	virtual void slot054(); virtual void slot058();
	virtual void slot05c(); virtual void slot060();
	virtual void slot064(); virtual void slot068();
	virtual void slot06c(); virtual void slot070();
	virtual void slot074(); virtual void slot078();
	virtual void slot07c(); virtual void slot080();
	virtual void slot084(); virtual void slot088();
	virtual void slot08c(); virtual void slot090();
	virtual void slot094(); virtual void slot098();
	virtual void slot09c(); virtual void slot0a0();
	virtual void slot0a4(); virtual void slot0a8();
	virtual void slot0ac(); virtual void slot0b0();
	virtual void slot0b4(); virtual void slot0b8();
	virtual void slot0bc(); virtual void slot0c0();
	virtual void slot0c4(); virtual void slot0c8();
	virtual void slot0cc(); virtual void slot0d0();
	virtual void slot0d4(); virtual void slot0d8();
	virtual void slot0dc(); virtual void slot0e0();
	virtual void slot0e4(); virtual void slot0e8();
	virtual void slot0ec(); virtual void slot0f0();
	virtual void slot0f4(); virtual void slot0f8();
	virtual void slot0fc(); virtual void slot100();
	virtual void slot104(); virtual void slot108();
	virtual void slot10c(); virtual void slot110();
	virtual void slot114(); virtual void slot118();
	virtual void slot11c(); virtual void slot120();
	virtual void slot124(); virtual void slot128();
	virtual void slot12c(); virtual void slot130();
	virtual void slot134(); virtual void slot138();
	virtual DozerAIInterface002B9970 *getDozerAIInterface();
	virtual void slot13c(); virtual void slot140();
	virtual void slot144(); virtual void slot148();
	virtual void slot14c(); virtual void slot150();
	virtual void slot154(); virtual void slot158();
	virtual void slot15c(); virtual void slot160();
	virtual void slot164(); virtual void slot168();
	virtual void slot16c(); virtual void slot170();
	virtual void slot174(); virtual void slot178();
	virtual bool isIdle() const;
};

class GameLogic
{
public:
	virtual void slot000();
	unsigned char m_beforeFrame[0x38];
	unsigned int m_frame;

	unsigned int getFrame() const
	{
		return m_frame;
	}
};

class InGameUI
{
public:
	virtual void slot000(); virtual void slot004();
	virtual void slot008(); virtual void slot00c();
	virtual void slot010(); virtual void slot014();
	virtual void slot018(); virtual void slot01c();
	virtual void slot020(); virtual void slot024();
	virtual void slot028(); virtual void slot02c();
	virtual void slot030(); virtual void slot034();
	virtual void slot038(); virtual void slot03c();
	virtual void slot040(); virtual void slot044();
	virtual void slot048(); virtual void slot04c();
	virtual void slot050(); virtual void slot054();
	virtual void slot058(); virtual void slot05c();
	virtual void slot060(); virtual void slot064();
	virtual void slot068(); virtual void slot06c();
	virtual void slot070(); virtual void slot074();
	virtual void slot078(); virtual void slot07c();
	virtual void slot080(); virtual void slot084();
	virtual void slot088(); virtual void slot08c();
	virtual void slot090(); virtual void slot094();
	virtual void slot098(); virtual void slot09c();
	virtual void slot0a0(); virtual void slot0a4();
	virtual void slot0a8(); virtual void slot0ac();
	virtual void slot0b0(); virtual void slot0b4();
	virtual void slot0b8(); virtual void slot0bc();
	virtual void slot0c0(); virtual void slot0c4();
	virtual void slot0c8(); virtual void slot0cc();
	virtual void slot0d0(); virtual void slot0d4();
	virtual void slot0d8(); virtual void slot0dc();
	virtual void slot0e0(); virtual void slot0e4();
	virtual void slot0e8(); virtual void slot0ec();
	virtual void slot0f0(); virtual void slot0f4();
	virtual void slot0f8(); virtual void slot0fc();
	virtual void slot100(); virtual void slot104();
	virtual void slot108(); virtual void slot10c();
	virtual void slot110(); virtual void slot114();
	virtual void slot118(); virtual void slot11c();
	virtual void slot120(); virtual void slot124();
	virtual void slot128(); virtual void slot12c();
	virtual void slot130(); virtual void slot134();
	virtual void slot138(); virtual void slot13c();
	virtual void slot140(); virtual void slot144();
	virtual void slot148(); virtual void slot14c();
	virtual void slot150(); virtual void slot154();
	virtual void slot158(); virtual void slot15c();
	virtual void slot160(); virtual void slot164();
	virtual void slot168(); virtual void slot16c();
	virtual void slot170(); virtual void slot174();
	virtual void slot178(); virtual void addIdleWorker(Object *object);
	virtual void removeIdleWorker(Object *object, int playerNumber);
};

extern GameLogic *TheGameLogic;
extern InGameUI *TheInGameUI;


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *obj) = 0;
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterSamePlayer : public PartitionFilter
{
public:
	PartitionFilterSamePlayer(const Player *player) : m_player(player) {}
	virtual ~PartitionFilterSamePlayer() {}
	virtual Bool allow(Object *obj);

private:
	const Player *m_player;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags(BogusInitType, Int idx)
	{
		m_bits._Unchecked_set((size_t)idx);
	}
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	// 0x000C3DD0 (ILT 0x000382FD). Visible but out of line, as in
	// Weapon_bfmeCanAffect.cpp: seeing that the masks are only copied lets
	// VC7.1 reuse the STRUCTURE mask's stack slot for the SamePlayer filter
	// built after it, which is retail's 0x68-byte frame.
	__declspec(noinline) PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *obj);

private:
	KindOfMaskType m_mustBeSet, m_mustBeClear;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *obj) : m_obj(obj) {}
	virtual ~PartitionFilterSameMapStatus() {}
	virtual Bool allow(Object *obj);

private:
	const Object *m_obj;
};

struct SimpleObjectIteratorClump
{
	Object *m_obj;
	float m_numeric;
};

struct SimpleObjectIterator
{
	std::vector<SimpleObjectIteratorClump> m_entries;
	SimpleObjectIteratorClump *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	SimpleObjectIterator *m_mpo;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult()
	{
		if (--m_mpo->m_refCount == 0)
			delete m_mpo;
	}
	Object *next() const
	{
		if (m_mpo->m_cursor == m_mpo->m_entries.end())
			return 0;
		return (m_mpo->m_cursor++)->m_obj;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int a, Real b, Int c, Int d, Int e);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

class ActionManager
{
public:
	bool canRepairObject(const Object *obj, const Object *objectToRepair, CommandSourceType commandSource);
};
extern ActionManager *TheActionManager;

static inline Real distanceSquared2D(const Coord3D *a, const Coord3D *b)
{
	Real dx = a->x - b->x;
	Real dy = a->y - b->y;
	return dx * dx + dy * dy;
}

// Retail 0x002B82D0 (505 B). Zero Hour's file-static findObjectToRepair
// (DozerAIUpdate.cpp); retail passes the dozer in EDI, VC7.1's private
// convention for a static called from this TU only, and calls it directly
// from update below. BFME chains the three filters with link as temporaries of
// the range query (they die right after it, the iterator lives on), and
// computes the 2D distance itself. The distance is written in both arms of
// Zero Hour's first/closer test: VC7.1 hoists it and pops dx/dy per arm, as
// retail does; the dozer position is re-read per object through one pointer.
static Object *findObjectToRepair(Object *dozer)
{
	if (dozer == 0)
		return 0;
	if (!dozer->getAIUpdateInterface())
		return 0;
	const DozerAIInterface002B9970 *dozerAI = dozer->getAIUpdateInterface()->getDozerAIInterface();

	Object *closestRepairTarget = 0;
	Real closestRepairTargetDistSqr = 0.0f;
	const BfmeWideResult &iter = ((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
		(Int)dozer->getPosition(), dozerAI->getBoredRange(), 0,
		(Int)PartitionFilterSamePlayer(dozer->getControllingPlayer()).link(
			PartitionFilterAcceptByKindOf(KindOfMaskType(KindOfMaskType::kInit, 7), KINDOFMASK_NONE).link(
				&PartitionFilterSameMapStatus(dozer))),
		0);
	Object *obj;
	while ((obj = iter.next()) != 0)
	{
		if (!TheActionManager->canRepairObject(dozer, obj, CMD_FROM_AI))
			continue;

		const Coord3D *pos = dozer->getPosition();
		if (closestRepairTarget == 0)
		{
			closestRepairTarget = obj;
			closestRepairTargetDistSqr = distanceSquared2D(pos, obj->getPosition());
		}
		else
		{
			Real distSqr = distanceSquared2D(pos, obj->getPosition());
			if (distSqr < closestRepairTargetDistSqr)
			{
				closestRepairTarget = obj;
				closestRepairTargetDistSqr = distSqr;
			}
		}
	}
	return closestRepairTarget;
}

class Rva002B9970DozerPrimaryIdleState : public State002B9970
{
public:
	// ?update@DozerPrimaryIdleState@@UAE?AW4StateReturnType@@XZ
	virtual StateReturnType update();

	unsigned int m_idleTooLongTimestamp;
	int m_idlePlayerNumber;
	bool m_isMarkedAsIdle;
};

// ?update@DozerPrimaryIdleState@@UAE?AW4StateReturnType@@XZ
StateReturnType Rva002B9970DozerPrimaryIdleState::update()
{
	DozerAIInterface002B9970 *dozerAI;
	Object *dozer = getMachineOwner();
	AIUpdateInterface002B9970 *ai = dozer->getAIUpdateInterface();
	if (!ai)
		return STATE_FAILURE;

	dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
		return STATE_FAILURE;

	if (ai->isIdle() && !m_isMarkedAsIdle && !((dozer->m_privateStatus & 1) != 0))
	{
		typedef Player *(Object::*OwningPlayerFn)() const;
		union { void (*fn)(); OwningPlayerFn call; } ownerFn = { j_00020824 };
		Player *owner = (dozer->*ownerFn.call)();
		m_idlePlayerNumber = owner->getPlayerIndex();
		TheInGameUI->addIdleWorker(getMachineOwner());
		m_isMarkedAsIdle = true;
	}

	if (m_isMarkedAsIdle && (!ai->isIdle() || ((dozer->m_privateStatus & 1) != 0)))
	{
		TheInGameUI->removeIdleWorker(getMachineOwner(), m_idlePlayerNumber);
		m_idlePlayerNumber = -1;
		m_isMarkedAsIdle = false;
	}

	if (!ai->isIdle())
		m_idleTooLongTimestamp = TheGameLogic->getFrame();

	if (TheGameLogic->getFrame() - m_idleTooLongTimestamp > dozerAI->getBoredTime() &&
		dozerAI->isAnyTaskPending() == false)
	{
		m_idleTooLongTimestamp = TheGameLogic->getFrame();
		Object *repairTarget = findObjectToRepair(dozer);
		if (repairTarget)
		{
			typedef void (AICommandInterface::*RepairFn)(Object *, CommandSourceType);
			union { void (*fn)(); RepairFn call; } repair = { j_00029c08 };
			(static_cast<AICommandInterface *>(ai)->*repair.call)(repairTarget, CMD_FROM_AI);
		}
	}

	return STATE_CONTINUE;
}
