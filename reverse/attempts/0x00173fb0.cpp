// ?update@AIFearState@@UAE?AW4StateReturnType@@XZ
// partial score=0.592 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath
// AIFearState::update, retail RVA 0x00173FB0 (402 bytes).
// The constructor, its vtable, and the matched onEnter body establish the class and slot.

#include "coord3d.h"

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

inline void Coord3D::set(const Coord3DBase *that)
{
	y = that->y;
	x = that->x;
	z = that->z;
}

enum StateReturnType
{
	STATE_FAILURE = -2
};

enum StateExitType
{
	STATE_EXIT_NORMAL = 0,
	STATE_EXIT_RESET = 1
};

class StateMachine;
class AIUpdateInterface;
class CRCParameterCheck;
class GameLogic;

template <int N>
class AIFearVirtualSlots : public AIFearVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class AIFearVirtualSlots<0>
{
};

class AIFearAIUpdateInterfaceVTable : public AIFearVirtualSlots<122>
{
public:
	virtual void slot1e8() = 0;
	virtual void slot1ec() = 0;
	virtual void slot1f0() = 0;
	virtual void slot1f4() = 0;
	virtual void slot1f8() = 0;
	virtual void chooseLocomotorSet(UnsignedInt set) = 0;
};

struct Rva00173FB0ConfigView
{
	unsigned char m_pad00[0x34];
	int m_field34;
	UnsignedInt m_field38;
};

struct Rva00173FB0PathView
{
	unsigned char m_pad00[0x08];
	void *m_field08;
};

class AIUpdateInterface : public AIFearAIUpdateInterfaceVTable
{
public:
	Rva00173FB0ConfigView *m_field04;
	unsigned char m_pad008[0x140 - 0x008];
	Rva00173FB0PathView *m_path;
	unsigned char m_pad144[0x180 - 0x144];
	Coord3D m_field180;
	unsigned char m_pad18c[0x31d - 0x18c];
	Bool m_flag31d;
	Bool m_flag31e;
	unsigned char m_pad31f[0x332 - 0x31f];
	Bool m_flag332;
};

class Thing
{
private:
	unsigned char m_pad00[0x38];

public:
	Coord3D m_cachedPos;
	Real m_cachedAngle;

	Real bfmeRelativeAngleTo(const Coord3D *point) const;
	void setOrientation(Real angle);
};

class Object : public Thing
{
private:
	unsigned char m_pad48[0x110 - 0x48];

public:
	UnsignedInt m_modelConditionFlags[10];

private:
	unsigned char m_pad138[0x204 - 0x138];

public:
	AIUpdateInterface *m_ai;

private:
	unsigned char m_pad208[0x344 - 0x208];

public:
	unsigned char m_privateStatus;

	void notifyModelConditionChanged();
};

class StateMachine
{
private:
	unsigned char m_pad00[0x10];

public:
	Object *m_owner;
	Object *getGoalObject();
};

struct Rva00173FB0FrameView
{
	unsigned char m_pad00[0x3c];
	UnsignedInt m_field3c;
};

extern GameLogic *TheGameLogic;
extern Bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern void j_0003a17a();
extern int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

typedef void (__cdecl *CritterDesyncLog)(CRCParameterCheck *, const char *, ...);

class Rva0026F110
{
public:
	void set();
};

class AIInternalMoveToState
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();

protected:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[0x04];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x1c];
	Bool m_adjustDestinations;
	unsigned char m_pad04d[0x03];
};

class AIFearState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();

private:
	UnsignedInt m_okToRepathTimes;
	Bool m_checkForPath;
	unsigned char m_pad55[0x03];
	Bool m_extra;
	unsigned char m_pad59[0x03];
	UnsignedInt m_field5c;
};

// ?update@AIFearState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIFearState::update()
{
	Bool extra = m_extra;
	StateMachine *machine = m_machine;
	Object *owner = machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;

	if (extra)
	{
		Object *goal = machine->getGoalObject();
		if (goal == 0)
			return (StateReturnType)-1;
		if ((goal->m_privateStatus & 1) != 0)
			return (StateReturnType)-1;

		UnsignedInt currentFrame = ((Rva00173FB0FrameView *)TheGameLogic)->m_field3c;
		if (currentFrame > m_field5c)
			return (StateReturnType)-1;

		ai->slot1e8();
		if ((owner->m_modelConditionFlags[1] & 0x10000000u) != 0)
		{
			owner->m_modelConditionFlags[1] &= 0xEFFFFFFFu;
			owner->notifyModelConditionChanged();
		}

		Real angle = owner->bfmeRelativeAngleTo(&goal->m_cachedPos);
		angle += owner->m_cachedAngle;
		owner->setOrientation(angle);
		return (StateReturnType)0;
	}

	if (m_checkForPath)
	{
		Rva00173FB0PathView *path = ai->m_path;
		if (path != 0 && !ai->m_flag31e)
		{
			const Coord3DBase *position =
				(const Coord3DBase *)((const unsigned char *)path->m_field08 + 0x0c);
			m_goalPosition.set(position);

			if (Glo012F0239 && TheCRCParameterCheck)
				((CritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
					"CritterDesync: setAdjustDestination(FALSE) 14");

			m_adjustDestinations = false;
			m_checkForPath = false;
		}
	}

	if (AIInternalMoveToState::update() != (StateReturnType)0)
	{
		m_extra = true;
		if (ai != 0)
		{
			ai->slot1e8();
			((Rva0026F110 *)ai)->set();
			ai->m_field180.set(&m_goalPosition);
			ai->m_flag31d = false;
		}

		if (ai->m_flag332)
		{
			UnsignedInt delay = ai->m_field04->m_field38 >> 2;
			UnsignedInt frame = ((Rva00173FB0FrameView *)TheGameLogic)->m_field3c;
			m_field5c = frame + delay;
		}
		else
		{
			UnsignedInt frame = ((Rva00173FB0FrameView *)TheGameLogic)->m_field3c;
			m_field5c = frame + GetGameLogicRandomValue(
				(int)ai->m_field04->m_field38,
				ai->m_field04->m_field34,
				"F:\bfme\Code\gameengine\Source\GameLogic\Ai\AIStates.cpp",
				3509);
		}
	}

	return (StateReturnType)0;
}
