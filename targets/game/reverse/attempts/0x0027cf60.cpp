// ?attackOrdinaryTarget@AIStateTargetDispatch@@QAEXPAVThing@@@Z
// partial score=0.997 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
#include "../command_source_type.h"

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Thing;
class AIUpdateInterface;

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AICommandInterface
{
public:
	void aiMoveAwayFromUnit(Object *object, CommandSourceType commandSource);
	void aiMoveToPosition(const Coord3D *position, CommandSourceType commandSource);

private:
	char m_unmodelled_00[4];
};

class UpdateModule : public BfmeVirtualSlots<96>
{
public:
	char m_unmodelled_04[4];
	Object *m_object;
	char m_unmodelled_0c[0x20 - 0x0c];
};

class StateMachine
{
public:
	unsigned int getCurrentStateID() const;
};

class Path;
class Rva001B7200Locomotor;

struct Rva001B7200PathPoint
{
	Real m_real00;
	Coord3D m_coord04;
	Real m_real10[3];
	int m_layer;
	int m_int20;
};

class Path
{
public:
	void computePointOnPath(Object *object, Rva001B7200Locomotor *locomotor,
		Rva001B7200PathPoint *out, Bool flag);
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	virtual Bool isIdle() const = 0;
	virtual Bool bfmeCurrentWeaponTemplateFlag4() const = 0;
	virtual void slot98() = 0;
	virtual void slot99() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual void slot119() = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void slot122() = 0;
	virtual Bool Rva0027CF60Slot123() const = 0;
	Bool bfmeBlocksFormationRefresh();
	Bool blockedBy(Object *object);
	Bool hasHigherPathPriority(AIUpdateInterface *other) const;
	unsigned int getCurrentStateID() const;
	Real Rva0026EED0(Thing *target);

	char m_unmodelled_24[0x30 - 0x24];
	StateMachine *m_stateMachine;
	char m_unmodelled_34[0x140 - 0x34];
	Path *m_path;
	char m_unmodelled_144[0x16c - 0x144];
	int m_blockedFrames;
	char m_unmodelled_170[0x1cc - 0x170];
	Rva001B7200Locomotor *m_curLocomotor;
	char m_unmodelled_1d0[0x31e - 0x1d0];
	unsigned char m_waitingForPath;
	char m_unmodelled_31f[0x325 - 0x31f];
	unsigned char m_isBlocked;
	unsigned char m_isBlockedAndStuck;
	char m_unmodelled_327[0x32b - 0x327];
	unsigned char m_isAiDead;
};

class AIStateTargetDispatch : public AIUpdateInterface
{
public:
	void attackOrdinaryTarget(Thing *target);

protected:
	Bool needToRotate();
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum KindOfType
{
	KINDOF_INFANTRY = 8,
	KINDOF_BFME_6C = 0x6c
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum CrushSquishTestType
{
	TEST_CRUSH_OR_SQUISH = 2
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;

	char m_unmodelled_00[0x38];
	Coord3D m_cachedPos;
	char m_unmodelled_44[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class Object : public Thing
{
public:
	Relationship getRelationship(const Object *that) const;
	int getLayer() const;
	unsigned char getCrushableLevel() const;
	Bool testStatus(int status) const;
	Bool crushPolicy(Object *object, CrushSquishTestType test) const;
	void notifyModelConditionChanged();
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual Bool probePosition(const Coord3D *position);
};

struct Rva007EAC80Helper
{
	unsigned int Rva007EAC80(Object *object, void *context, Coord3D *position);
};

struct AIContext
{
	char m_unmodelled_00[0xb5];
	unsigned char m_unmodelled_b5;
};

class AI
{
public:
	char m_unmodelled_00[0x0c];
	Rva007EAC80Helper *m_unmodelled_0c;
	char m_unmodelled_10[4];
	AIContext *m_unmodelled_14;
};

class BfmeThingEP;

class Gen_0026F630
{
public:
	Bool bfmeMatches(const BfmeThingEP *thing) const;
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;
extern "C" void j_0000a407();
extern "C" void j_00011252();

#pragma comment(linker, "/alternatename:?Rva0026EED0@AIUpdateInterface@@QAEMPAVThing@@@Z=?j_0000a407@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva007EAC80@Rva007EAC80Helper@@QAEIPAVObject@@PAXPAUCoord3D@@@Z=?j_00011252@@YAXXZ")

void AIStateTargetDispatch::attackOrdinaryTarget(Thing *target)
{
	AIUpdateInterface *otherAI = target->m_ai;
	Object *self = m_object;
	if (otherAI == 0)
		return;

	if (self->getRelationship(reinterpret_cast<Object *>(target)) != ALLIES)
		return;

	Bool selfBlocks = bfmeBlocksFormationRefresh();
	Bool otherBlocks = otherAI->bfmeBlocksFormationRefresh() != 0;
	if (self->isKindOf((KindOfType)0x5c) &&
		(*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(self) + 0x94) & 0x04000000) != 0)
		return;
	if ((reinterpret_cast<const unsigned char *>(self)[0x94] & 0x20) != 0)
		return;
	if ((reinterpret_cast<const unsigned char *>(target)[0x94] & 0x20) != 0)
		return;
	if (target->isKindOf(KINDOF_BFME_6C))
	{
		if (reinterpret_cast<Object *>(target)->getLayer() != LAYER_GROUND)
			return;
		if (TheTerrainLogic->probePosition(&target->m_cachedPos))
			return;
	}
	if (!Rva0027CF60Slot123())
		return;
	if (!otherAI->Rva0027CF60Slot123())
		return;

	if (selfBlocks)
	{
		if (getCurrentStateID() == 0x36 && !TheAI->m_unmodelled_14->m_unmodelled_b5)
			return;
		if (!blockedBy(reinterpret_cast<Object *>(target)))
			return;
		if (target->isKindOf(KINDOF_INFANTRY) && m_stateMachine->getCurrentStateID() == 0x13)
			return;

		m_isBlocked = 1;
		if (otherBlocks && otherAI->m_waitingForPath)
			return;

		Real distance = Rva0026EED0(target);
		Real *closestDistance = reinterpret_cast<Real *>(reinterpret_cast<char *>(this) + 0x170);
		if (distance < *closestDistance)
			*closestDistance = distance;

		if (!reinterpret_cast<Gen_0026F630 *>(otherAI)->bfmeMatches(reinterpret_cast<const BfmeThingEP *>(self)) &&
			target->isKindOf(KINDOF_INFANTRY) &&
			static_cast<signed char>(reinterpret_cast<Object *>(target)->getCrushableLevel()) <
			static_cast<signed char>(self->getCrushableLevel()))
		{
			static_cast<AICommandInterface *>(otherAI)->aiMoveAwayFromUnit(self, CMD_FROM_AI);
			return;
		}

		if (m_blockedFrames == 0)
			m_blockedFrames = 1;
		if (!needToRotate())
		{
			if (!otherBlocks)
			{
				m_isBlockedAndStuck = 1;
				if (m_path != 0)
				{
					Rva001B7200PathPoint point;
					m_path->computePointOnPath(self, m_curLocomotor, &point, false);
					if (point.m_int20 != 0x7fffffff)
						m_isBlockedAndStuck = 0;
				}
				if (m_isBlockedAndStuck &&
					(*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(self) + 0x114) & 0x10000000) != 0)
				{
					*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(self) + 0x114) &= 0xefffffff;
					self->notifyModelConditionChanged();
				}
			}
			else
			{
				if (!otherAI->blockedBy(self))
					return;
				if (reinterpret_cast<AIStateTargetDispatch *>(otherAI)->needToRotate())
					return;
				if (hasHigherPathPriority(otherAI))
					return;
				static_cast<AICommandInterface *>(this)->aiMoveAwayFromUnit(otherAI->m_object, CMD_FROM_AI);
			}
		}
		else
		{
			m_blockedFrames = 1;
			return;
		}
	}
	else
	{
		if (m_isAiDead && self->isKindOf(KINDOF_INFANTRY))
		{
			Object *currentSelf = m_object;
			if (reinterpret_cast<Object *>(target)->crushPolicy(
				currentSelf,
				(CrushSquishTestType)1))
				return;
		}

		Coord3D targetPosition;
		targetPosition.x = target->m_cachedPos.x;
		targetPosition.y = target->m_cachedPos.y;
		targetPosition.z = target->m_cachedPos.z;
		if (otherBlocks)
			return;
		if (getCurrentStateID() == 0x2a)
			return;
		if (self->testStatus(0x45))
			return;
		if ((reinterpret_cast<const unsigned char *>(target)[0x344] & 8) != 0)
			return;
		if ((reinterpret_cast<const unsigned char *>(self)[0x344] & 8) != 0)
			return;

		if (isIdle())
		{
			Coord3D selfPosition;
			selfPosition.x = self->m_cachedPos.x;
			selfPosition.y = self->m_cachedPos.y;
			selfPosition.z = self->m_cachedPos.z;
			TheAI->m_unmodelled_0c->Rva007EAC80(self,
				reinterpret_cast<char *>(this) + 0x1a8, &selfPosition);
			static_cast<AICommandInterface *>(this)->aiMoveToPosition(&selfPosition, CMD_FROM_AI);
		}
		if (otherAI->isIdle())
		{
			TheAI->m_unmodelled_0c->Rva007EAC80(reinterpret_cast<Object *>(target),
				reinterpret_cast<char *>(otherAI) + 0x1a8, &targetPosition);
			static_cast<AICommandInterface *>(otherAI)->aiMoveToPosition(&targetPosition, CMD_FROM_AI);
		}
	}
}
