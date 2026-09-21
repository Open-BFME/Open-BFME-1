// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.3 date=2026-09-18
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /O2 /Ob2 /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// stlport
// OpenContain's ExitInterface view is this+0x10.  The vtable slot and the
// processNested caller prove this is the real OpenContain method; the narrow
// declarations below retain only the BFME offsets witnessed by this body.

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include <vector>
#include <stdlib.h>

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
	MODELCONDITION_DOOR_1_OPENING = 0x00200000,
	MODELCONDITION_DOOR_1_CLOSING = 0x00400000
};

struct Coord3DBase
{
	Real x;
	Real y;
	Real z;

	Coord3DBase &operator=(const Coord3DBase &other)
	{
		struct Raw
		{
			UnsignedInt x;
			UnsignedInt y;
			UnsignedInt z;
		};
		*(Raw *)this = *(const Raw *)&other;
		return *this;
	}
};

struct Coord3D : public Coord3DBase
{
	Coord3D() {}
	~Coord3D() {}
	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	Coord3D &operator=(const Coord3D &other)
	{
		Coord3DBase *base = this;
		*base = other;
		return *this;
	}
};

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

class ExitInterface : public Rva002284D0VirtualSlots<36>
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
		UnsignedInt condition = m_conditionFlags;
		if (condition & clearFlags)
			goto set_flags;
		if (condition & setFlags)
			return;
	set_flags:
		UnsignedInt flags = m_conditionFlags;
		flags &= ~((UnsignedInt)clearFlags);
		volatile UnsignedInt *conditionFlags = &m_conditionFlags;
		*conditionFlags = flags;
		*conditionFlags = flags | (UnsignedInt)setFlags;
		notifyModelConditionChanged();
	}

private:
	char m_padding[0x110];
	UnsignedInt m_conditionFlags;
};

class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
	void removeUnitFromPathfindMap(Object *object);
	void updatePos(Object *object, const Coord3D *position);
	void updateGoal(Object *object, const Coord3D *position,
		PathfindLayerEnum layer, const char *file, Int line);
	Bool adjustToPossibleDestination(Object *object,
		const LocomotorSet &locomotorSet, Coord3D *destination);
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
		ExitInterface *contain = (ExitInterface *)((char *)this - 0x10);
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

template <typename T>
class StringBase
{
public:
	void concat(const T *text, Int length);

private:
	void *m_data;
};

struct BfmeStringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	const char *str() const
	{
		BfmeStringData *data = (BfmeStringData *)m_data;
		return data ? data->m_text : (const char *)0x0107388B;
	}

	void concat(const char *text, Int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	void concat(const char *text)
	{
		const char *scan = text;
		const char *base = text + 1;
		while (*scan++)
			;
		((StringBase<char> *)this)->concat(text, (Int)(scan - base));
	}

	void concat(char character)
	{
		char one = character;
		((StringBase<char> *)this)->concat(&one, 1);
	}

private:
	void releaseBuffer();
	void *m_data;
};

#define TheAI (*(AI **)0x012EF214)
#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheBfmeGameLogic (*(Rva002284D0GameLogic **)0x012F0898)

#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?getSingleLogicalBonePosition@Object@@QBE_NPBDPAUCoord3D@@PAVMatrix3D@@@Z=?j_00019f42@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayer@Object@@QBEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?setLayer@Object@@QAEXW4PathfindLayerEnum@@@Z=?j_00035e0e@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosition@Thing@@QAEXPBUCoord3D@@@Z=?j_0003a1a7@@YAXXZ")
#pragma comment(linker, "/alternatename:?setOrientation@Thing@@QAEXM@Z=?j_000399a5@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?addObjectToPathfindMap@Pathfinder@@QAEXPAVObject@@@Z=?j_0000b81b@@YAXXZ")
#pragma comment(linker, "/alternatename:?removeUnitFromPathfindMap@Pathfinder@@QAEXPAVObject@@@Z=?j_0001d9da@@YAXXZ")
#pragma comment(linker, "/alternatename:?updatePos@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@@Z=?j_00013647@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@W4PathfindLayerEnum@@PBDH@Z=?j_000294e2@@YAXXZ")
#pragma comment(linker, "/alternatename:?adjustToPossibleDestination@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@@Z=?j_00011252@@YAXXZ")
#pragma comment(linker, "/alternatename:?ignoreObstacle@AIUpdateInterface@@QAEXPAVObject@@@Z=?j_0000315c@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PAVObject@@PBUCoord3D@@@Z=?j_0001c675@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiBfmeCommand9FollowPath@AICommandInterface@@QAEXPBV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@PAVObject@@W4CommandSourceType@@@Z=?j_0001022b@@YAXXZ")

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
		BFMERetailAsciiString startBone("ExitStart");
		BFMERetailAsciiString endBone("ExitEnd");
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
				TheAI->pathfinder()->removeUnitFromPathfindMap(me);
				TheAI->pathfinder()->updatePos(me, me->getPosition());
#line 1443 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp"
				TheAI->pathfinder()->updateGoal(me, me->getPosition(),
					TheTerrainLogic->getLayerForDestination(me,
						me->getPosition()), __FILE__, __LINE__);
			}

			ai->ignoreObstacle(exitObj);
			*(UnsignedInt *)((char *)ai + 0x178) =
				TheBfmeGameLogic->m_frame + 5;
			TheAI->pathfinder()->adjustToPossibleDestination(exitObj,
				ai->getLocomotorSet(), &endPosition);
		}

		std::vector<Coord3D> exitPath;
		exitPath.push_back(endPosition);
		exitPath.push_back(endPosition);
		if (self->rallyPointExists())
			exitPath.push_back(self->rallyPoint());

		if (ai)
		{
			((AICommandInterface *)((char *)ai + 0x20))
				->aiBfmeCommand9FollowPath(&exitPath, me, CMD_FROM_AI);
#line 1461 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp"
			TheAI->pathfinder()->updateGoal(exitObj, &endPosition,
				TheTerrainLogic->getLayerForDestination(exitObj,
					&endPosition), __FILE__, __LINE__);
		}
	}
	else
	{
		TheAI->pathfinder()->addObjectToPathfindMap(exitObj);
	}
}
