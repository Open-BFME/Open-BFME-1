// cl: /DNDEBUG /DWIN32 /MD /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?doNamedSetStoppingDistance@ScriptActions@@IAEXABVAsciiString@@M@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doNamedGuard@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The five actions that look one named unit up and change something about it:
//
//   0x002EF710  doNamedSetStoppingDistance  the locomotor's close-enough distance
//   0x002F0460  doNamedGiveExperiencePoints the experience tracker
//   0x002F1190  doNamedForceEmotion         an emotion, range-checked to [0,10)
//   0x002FEBD0  doNamedSetStatus            one object-status bit
//   0x00301BA0  doNamedGuard                guard where it already stands
//
// All five reach the unit through ScriptEngine slot 26 and then read one of
// Object's three interesting pointers. Written apart, no file could show that
// those three live in the same object.

#include <string.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

enum EmotionType
{
	EMOTION_INVALID = -1
};

enum GuardMode { GUARDMODE_NORMAL = 0 };
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

struct Coord3D { Real x, y, z; };

#include "ascii_string.h"

template<int NUMBITS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	void set(Int idx)
	{
		m_bits[(unsigned)idx >> 5] |= 1u << (idx & 31);
	}

	unsigned m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource);
};

class AIPad20
{
	unsigned char m_pad[0x20];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
public:
	unsigned char m_pad[0x38];
	float m_closeEnoughDist;
};

// The command interface is a base at +0x20 rather than a member, because
// doNamedGuard calls through it and needs `this` adjusted by that much. The
// current locomotor then sits at +0x1CC, which the trailing run reaches whether
// or not the empty base is folded away.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public AIPad20, public AICommandInterface
{
public:
	unsigned char m_afterCommand[0x1CC - 0x21];
	Locomotor *m_curLocomotor;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h
class ExperienceTracker
{
public:
	void addExperiencePoints(float experienceGain, bool canScaleForBonus, bool isShared, bool allowLevelGain, bool provideFeedback);
};

// The three pointers these five actions reach: the position at +0x38, the AI
// update module at +0x204 and the experience tracker at +0x210.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void leaveGroup();
	void forceEmotion(EmotionType emotion, float duration, const Object *source);
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);

	unsigned char m_beforePos[0x38];
	Coord3D m_pos;
	unsigned char m_betweenPosAndAI[0x204 - 0x44];
	AIUpdateInterface *m_ai;
	unsigned char m_betweenAIAndExperience[0x210 - 0x208];
	ExperienceTracker *m_experienceTracker;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _se_0() = 0;
	virtual void _se_1() = 0;
	virtual void _se_2() = 0;
	virtual void _se_3() = 0;
	virtual void _se_4() = 0;
	virtual void _se_5() = 0;
	virtual void _se_6() = 0;
	virtual void _se_7() = 0;
	virtual void _se_8() = 0;
	virtual void _se_9() = 0;
	virtual void _se_10() = 0;
	virtual void _se_11() = 0;
	virtual void _se_12() = 0;
	virtual void _se_13() = 0;
	virtual void _se_14() = 0;
	virtual void _se_15() = 0;
	virtual void _se_16() = 0;
	virtual void _se_17() = 0;
	virtual void _se_18() = 0;
	virtual void _se_19() = 0;
	virtual void _se_20() = 0;
	virtual void _se_21() = 0;
	virtual void _se_22() = 0;
	virtual void _se_23() = 0;
	virtual void _se_24() = 0;
	virtual void _se_25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedSetStoppingDistance(const AsciiString &unit, float stoppingDistance);
	void doNamedGiveExperiencePoints(const AsciiString &unitName, int experience);
	void doNamedForceEmotion(const AsciiString &unitName, EmotionType emotion, float duration);
	void doNamedSetStatus(const AsciiString &unitName, Int bit, Bool set);
	void doNamedGuard(const AsciiString &unitName);
};

void ScriptActions::doNamedSetStoppingDistance(const AsciiString &unit, float stoppingDistance)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	if (theObj)
	{
		AIUpdateInterface *aiUpdate = theObj->m_ai;
		if (!aiUpdate || !aiUpdate->m_curLocomotor)
			return;

		if (stoppingDistance >= 0.5f)
			aiUpdate->m_curLocomotor->m_closeEnoughDist = stoppingDistance;
	}
}

void ScriptActions::doNamedGiveExperiencePoints(const AsciiString &unitName, int experience)
{
	Object *object = TheScriptEngine->getUnitNamed(unitName);
	if (!object)
		return;

	ExperienceTracker *tracker = object->m_experienceTracker;
	if (!tracker)
		return;

	tracker->addExperiencePoints((float)experience, true, true, true, false);
}

void ScriptActions::doNamedForceEmotion(const AsciiString &unitName, EmotionType emotion, float duration)
{
	if (emotion < 0)
		return;
	if (emotion >= 10)
		return;

	Object *object = TheScriptEngine->getUnitNamed(unitName);
	if (object)
		object->forceEmotion(emotion, duration, 0);
}

void ScriptActions::doNamedSetStatus(const AsciiString &unitName, Int bit, Bool set)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theSrcUnit) {
		return;
	}

	ObjectStatusMaskType status;
	status.set(bit);
	theSrcUnit->setStatus(status, set);
}

void ScriptActions::doNamedGuard(const AsciiString &unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit) {
		return;
	}

	AIUpdateInterface *aiUpdate = theUnit->m_ai;
	if (!aiUpdate) {
		return;
	}
	theUnit->leaveGroup();
	Int z = *(Int *)&theUnit->m_pos.z;
	Int x = *(Int *)&theUnit->m_pos.x;
	Int y = *(Int *)&theUnit->m_pos.y;
	Coord3D position;
	*(Int *)&position.z = z;
	*(Int *)&position.x = x;
	*(Int *)&position.y = y;
	aiUpdate->aiGuardPosition(&position, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
}
