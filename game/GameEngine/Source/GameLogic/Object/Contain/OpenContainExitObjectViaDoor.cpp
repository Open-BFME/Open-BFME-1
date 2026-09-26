// Retail 0x002284D0: 1039 bytes; ExitInterface receiver module+0x30; ret8.
// Analyst ABI pack: docs/analysis/0x003e9720.md. removeGoal at +022A is required.
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// stlport
// OpenContain's ExitInterface receiver is module+0x30; Contain is receiver-0x10.  The vtable slot and the
// ExitInterface slot 2 and the Zero Hour donor prove the method identity; the narrow
// declarations below retain only the BFME offsets witnessed by this body.

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include "Lib/BaseType.h"
#include "ascii_string.h"
#include <bitset>
#include <vector>
#include <stdlib.h>
#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum ExitDoorType
{
	DOOR_1 = 0
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum KindOfType
{
	KINDOF_VEHICLE = 9
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

enum ModelConditionFlagType
{
	MODELCONDITION_DOOR_1_OPENING = 21,
	MODELCONDITION_DOOR_1_CLOSING = 22
};

// Retain the native vector append cursor across the placement copy.
namespace _STL {
template <> inline void vector<Coord3D>::push_back(const Coord3D &value) {
    Coord3D *finish = _M_finish;
    if (finish != _M_end_of_storage._M_data) {
        _Construct(finish, value);
        _M_finish = finish + 1;
    } else {
        _M_insert_overflow(finish,value,__false_type(),1,true);
    }
}
}
class Object;
class Matrix3D;
class LocomotorSet;
class Pathfinder;
class TerrainLogic;

template <int N>
class Rva002284D0VirtualSlots : public Rva002284D0VirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva002284D0VirtualSlots<0>
{
};

class ContainView002284D0 : public Rva002284D0VirtualSlots<36>
{
public:
	virtual void removeFromContain(Object *object, Bool exposeStealthUnits) = 0;
};

template <int N>
class Rva002284D0AISlots : public Rva002284D0AISlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva002284D0AISlots<0>
{
};

class AIUpdateInterface : public Rva002284D0AISlots<96>
{
public:
	virtual Bool isIdle() const = 0;

	void ignoreObstacle(Object *object);

	const LocomotorSet &getLocomotorSet() const
	{
		return *(const LocomotorSet *)((const char *)this + 0x1A8);
	}
};

class AICommandInterface
{
public:
	void aiBfmeCommand9FollowPath(const std::vector<Coord3D> *path,
		Object *ignoreObject, CommandSourceType commandSource);
};

class Thing
{
public:
	void setPosition(const Coord3D *position);
	void setOrientation(Real angle);
	Bool isKindOf(KindOfType kind) const;
};

class ConditionBits002284D0 {
    std::bitset<320> bits;
public:
    bool test(int n) const { return bits.test(n); }
    void set(int n) { bits.set(n); }
    void reset(int n) { bits.reset(n); }
};
class Object : public Thing
{
public:
	Bool getSingleLogicalBonePosition(const char *boneName,
		Coord3D *position, Matrix3D *transform) const;
	Int getLayer() const;
	void setLayer(PathfindLayerEnum layer);
	void notifyModelConditionChanged();

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x204);
	}

	void clearAndSetModelConditionState(ModelConditionFlagType clearFlags,
		ModelConditionFlagType setFlags)
	{
        if (m_conditionFlags.test(clearFlags) || !m_conditionFlags.test(setFlags)) {
            m_conditionFlags.reset(clearFlags);
            m_conditionFlags.set(setFlags);
            notifyModelConditionChanged();
        }
	}

private:
	char m_padding[0x110];
	ConditionBits002284D0 m_conditionFlags;
};

void j_00011252(); // ILT to 003EAC80; thiscall Object/set/destination; ret12.
class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
	void removePos(Object *object);
	void removeGoal(Object *object);
	void updatePos(Object *object, const Coord3D *position);
	void updateGoal(Object *object, const Coord3D *position,
		PathfindLayerEnum layer, const char *file, Int line);
	Bool adjustToPossibleDestination(Object *object,
        const LocomotorSet &locomotorSet, Coord3D *destination) {
        union { void (*route)(); Bool (Pathfinder::*method)(Object *, const LocomotorSet &, Coord3D *); } call;
        call.route = j_00011252;
        return (this->*call.method)(object, locomotorSet, destination);
    }
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

class AI
{
public:
	char m_padding[0x0C];
	Pathfinder *m_pathfinder;

	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}
};

class Rva002284D0GameLogic
{
public:
	char m_padding[0x3C];
	UnsignedInt m_frame;
};

class OpenContainModuleData
{
public:
	char m_padding[0x144];
	Int m_numberOfExitPaths;
	UnsignedInt m_doorOpenTime;
};

class OpenContain
{
public:
	virtual void exitObjectViaDoor(Object *exitObject, ExitDoorType exitDoor);

	void removeFromContain(Object *object)
	{
		ContainView002284D0 *contain = (ContainView002284D0 *)((char *)this - 0x10);
		contain->removeFromContain(object, false);
	}

	OpenContainModuleData *getOpenContainModuleData() const
	{
		return *(OpenContainModuleData **)((const char *)this - 0x2C);
	}

	Object *getObject() const
	{
		return *(Object **)((const char *)this - 0x28);
	}

	Int &whichExitPath()
	{
		return *(Int *)((char *)this + 0x38);
	}

	UnsignedInt &doorCloseCountdown()
	{
		return *(UnsignedInt *)((char *)this + 0x3C);
	}

	Bool rallyPointExists() const
	{
		return *(const Bool *)((const char *)this + 0x84);
	}

	const Coord3D &rallyPoint() const
	{
		return *(const Coord3D *)((const char *)this + 0x78);
	}
};

inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline void StringBase<char>::concat(char c) { concat(&c, 1); }
template <> inline void StringBase<char>::concat(const char *s) { concat(s, (int)strlen(s)); }

#define TheAI (*(AI **)0x012EF214)
#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheBfmeGameLogic (*(Rva002284D0GameLogic **)0x012F0898)


void OpenContain::exitObjectViaDoor(Object *exitObject, ExitDoorType)
{
	register OpenContain *self = this;
	register Object *exitObj = exitObject;
	self->removeFromContain(exitObj);

	Object *me = self->getObject();
	self->doorCloseCountdown() = self->getOpenContainModuleData()->m_doorOpenTime;
	if (self->doorCloseCountdown())
		me->clearAndSetModelConditionState(
			MODELCONDITION_DOOR_1_CLOSING,
			MODELCONDITION_DOOR_1_OPENING);

	Int numberExits = self->getOpenContainModuleData()->m_numberOfExitPaths;
	if (numberExits > 0)
	{
		AsciiString startBone("ExitStart");
		AsciiString endBone("ExitEnd");
		Coord3D startPosition;
		Coord3D endPosition;

		if (numberExits > 1)
		{
			char suffix[8];
			Int &exitPath = self->whichExitPath();
			itoa(exitPath, suffix, 10);
			if (exitPath < 10)
			{
				startBone.concat('0');
				endBone.concat('0');
			}
			exitPath = (exitPath % numberExits) + 1;
			startBone.concat(suffix);
			endBone.concat(suffix);
		}

		me->getSingleLogicalBonePosition(startBone.str(), &startPosition, 0);
		me->getSingleLogicalBonePosition(endBone.str(), &endPosition, 0);

		Real exitAngle = *(const Real *)((const char *)me + 0x44);
		exitObj->setPosition(&startPosition);
		exitObj->setOrientation(exitAngle);
		exitObj->setLayer((PathfindLayerEnum)me->getLayer());

		AIUpdateInterface *ai = exitObj->getAI();
		AIUpdateInterface *myAi = me->getAI();
		TheAI->pathfinder()->addObjectToPathfindMap(exitObj);
		if (ai)
		{
			if (myAi && myAi->isIdle() && me->isKindOf(KINDOF_VEHICLE))
			{
				TheAI->pathfinder()->removePos(me);
				TheAI->pathfinder()->removeGoal(me);
				TheAI->pathfinder()->updatePos(me, me->getPosition());
				TheAI->pathfinder()->updateGoal(me, me->getPosition(),
					TheTerrainLogic->getLayerForDestination(me,
						me->getPosition()), "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp", 0x5A3);
			}

			ai->ignoreObstacle(exitObj);
			{ UnsignedInt frame = TheBfmeGameLogic->m_frame + 5; *(UnsignedInt *)((char *)ai + 0x178) = frame; }
			TheAI->pathfinder()->adjustToPossibleDestination(exitObj,ai->getLocomotorSet(),&endPosition);
		}

		{
		std::vector<Coord3D> exitPath;
		exitPath.push_back(endPosition);
		exitPath.push_back(endPosition);
		if (self->rallyPointExists())
			exitPath.push_back(self->rallyPoint());

		if (ai)
		{
			((AICommandInterface *)((char *)ai + 0x20))
				->aiBfmeCommand9FollowPath(&exitPath, me, CMD_FROM_AI);
			TheAI->pathfinder()->updateGoal(exitObj, &endPosition,
				TheTerrainLogic->getLayerForDestination(exitObj,
					&endPosition), "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp", 0x5B5);
		}
		}
	}
	else
	{
		TheAI->pathfinder()->addObjectToPathfindMap(exitObj);
	}
}
