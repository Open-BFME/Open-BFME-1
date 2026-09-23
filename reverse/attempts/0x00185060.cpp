// ?d_00185060@@YAXXZ
// partial score=0.44 date=2026-09-24
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00185060: AIChargeTargetState slot-6 update.

typedef unsigned char Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class AIUpdateInterface;

class StateMachine
{
public:
	Object *getGoalObject();

	unsigned char m_pad00[0x10];
	Object *m_owner;
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")

class Pathfinder
{
public:
	void removeGoal003E3D20(Object *object);
};

#pragma comment(linker, "/alternatename:?removeGoal003E3D20@Pathfinder@@QAEXPAVObject@@@Z=?j_00015d02@@YAXXZ")

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;

	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}
};

#define AIUPDATE_SLOT(n) virtual void slot##n() = 0;
class AIUpdateInterface
{
public:
	AIUPDATE_SLOT(000) AIUPDATE_SLOT(001) AIUPDATE_SLOT(002)
	AIUPDATE_SLOT(003) AIUPDATE_SLOT(004) AIUPDATE_SLOT(005)
	AIUPDATE_SLOT(006) AIUPDATE_SLOT(007) AIUPDATE_SLOT(008)
	AIUPDATE_SLOT(009) AIUPDATE_SLOT(010) AIUPDATE_SLOT(011)
	AIUPDATE_SLOT(012) AIUPDATE_SLOT(013) AIUPDATE_SLOT(014)
	AIUPDATE_SLOT(015) AIUPDATE_SLOT(016) AIUPDATE_SLOT(017)
	AIUPDATE_SLOT(018) AIUPDATE_SLOT(019) AIUPDATE_SLOT(020)
	AIUPDATE_SLOT(021) AIUPDATE_SLOT(022) AIUPDATE_SLOT(023)
	AIUPDATE_SLOT(024) AIUPDATE_SLOT(025) AIUPDATE_SLOT(026)
	AIUPDATE_SLOT(027) AIUPDATE_SLOT(028) AIUPDATE_SLOT(029)
	AIUPDATE_SLOT(030) AIUPDATE_SLOT(031) AIUPDATE_SLOT(032)
	AIUPDATE_SLOT(033) AIUPDATE_SLOT(034) AIUPDATE_SLOT(035)
	AIUPDATE_SLOT(036) AIUPDATE_SLOT(037) AIUPDATE_SLOT(038)
	AIUPDATE_SLOT(039) AIUPDATE_SLOT(040) AIUPDATE_SLOT(041)
	AIUPDATE_SLOT(042) AIUPDATE_SLOT(043) AIUPDATE_SLOT(044)
	AIUPDATE_SLOT(045) AIUPDATE_SLOT(046) AIUPDATE_SLOT(047)
	AIUPDATE_SLOT(048) AIUPDATE_SLOT(049) AIUPDATE_SLOT(050)
	AIUPDATE_SLOT(051) AIUPDATE_SLOT(052) AIUPDATE_SLOT(053)
	AIUPDATE_SLOT(054) AIUPDATE_SLOT(055) AIUPDATE_SLOT(056)
	AIUPDATE_SLOT(057) AIUPDATE_SLOT(058) AIUPDATE_SLOT(059)
	AIUPDATE_SLOT(060) AIUPDATE_SLOT(061) AIUPDATE_SLOT(062)
	AIUPDATE_SLOT(063) AIUPDATE_SLOT(064) AIUPDATE_SLOT(065)
	AIUPDATE_SLOT(066) AIUPDATE_SLOT(067) AIUPDATE_SLOT(068)
	AIUPDATE_SLOT(069) AIUPDATE_SLOT(070) AIUPDATE_SLOT(071)
	AIUPDATE_SLOT(072) AIUPDATE_SLOT(073) AIUPDATE_SLOT(074)
	AIUPDATE_SLOT(075) AIUPDATE_SLOT(076) AIUPDATE_SLOT(077)
	AIUPDATE_SLOT(078) AIUPDATE_SLOT(079) AIUPDATE_SLOT(080)
	AIUPDATE_SLOT(081) AIUPDATE_SLOT(082) AIUPDATE_SLOT(083)
	AIUPDATE_SLOT(084) AIUPDATE_SLOT(085) AIUPDATE_SLOT(086)
	AIUPDATE_SLOT(087) AIUPDATE_SLOT(088) AIUPDATE_SLOT(089)
	AIUPDATE_SLOT(090) AIUPDATE_SLOT(091) AIUPDATE_SLOT(092)
	AIUPDATE_SLOT(093) AIUPDATE_SLOT(094) AIUPDATE_SLOT(095)
	AIUPDATE_SLOT(096) AIUPDATE_SLOT(097) AIUPDATE_SLOT(098)
	AIUPDATE_SLOT(099) AIUPDATE_SLOT(100) AIUPDATE_SLOT(101)
	AIUPDATE_SLOT(102) AIUPDATE_SLOT(103) AIUPDATE_SLOT(104)
	AIUPDATE_SLOT(105) AIUPDATE_SLOT(106) AIUPDATE_SLOT(107)
	AIUPDATE_SLOT(108) AIUPDATE_SLOT(109) AIUPDATE_SLOT(110)
	AIUPDATE_SLOT(111) AIUPDATE_SLOT(112) AIUPDATE_SLOT(113)
	AIUPDATE_SLOT(114) AIUPDATE_SLOT(115) AIUPDATE_SLOT(116)
	AIUPDATE_SLOT(117) AIUPDATE_SLOT(118) AIUPDATE_SLOT(119)
	AIUPDATE_SLOT(120) AIUPDATE_SLOT(121) AIUPDATE_SLOT(122)
	AIUPDATE_SLOT(123) AIUPDATE_SLOT(124) AIUPDATE_SLOT(125)
	AIUPDATE_SLOT(126)
	virtual void slot127(int value) = 0;

	void requestPath(Coord3D *destination, Bool isFinalGoal);
};
#undef AIUPDATE_SLOT

#pragma comment(linker, "/alternatename:?requestPath@AIUpdateInterface@@QAEXPAUCoord3D@@_N@Z=?j_0003bcff@@YAXXZ")

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual const void *getTemplate() const = 0;
	unsigned char m_pad04[0x34];
	Coord3D m_position;
	unsigned char m_pad44[0x11c - 0x44];
	unsigned int m_modelConditionWord;
	unsigned char m_pad120[0x204 - 0x120];
	AIUpdateInterface *m_ai;

	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	class Weapon *getCurrentWeapon(WeaponSlotType *slot);
	void notifyModelConditionChanged();
};

#pragma comment(linker, "/alternatename:?getCurrentWeapon@Object@@QAEPAVWeapon@@PAW4WeaponSlotType@@@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")

class Weapon
{
public:
	WeaponStatus bfmeComputeStatus(Bool *valid) const;
};

#pragma comment(linker, "/alternatename:?bfmeComputeStatus@Weapon@@ABE?AW4WeaponStatus@@PA_N@Z=?j_0001e6a0@@YAXXZ")

class Rva000D3F10StatusView
{
public:
	Bool test(unsigned int bit) const;
};

#pragma comment(linker, "/alternatename:?test@Rva000D3F10StatusView@@QBE_NI@Z=?j_0003ab20@@YAXXZ")

class AIInternalMoveToState
{
public:
	virtual StateReturnType update();

	void setAdjustsDestination(bool value)
	{
		m_adjustDestinations = value;
	}

protected:
	unsigned char m_statePrefix[0x18];
	StateMachine *m_machine;
	unsigned char m_goalPrefix[0x04];
	Coord3D m_goalPosition;
	unsigned char m_moveFields[0x1c];
	unsigned char m_adjustDestinations;
};

#pragma comment(linker, "/alternatename:?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ=?j_000488f6@@YAXXZ")

class AIChargeTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
	Bool rva0016F4A0();
	Bool rva0016FD30();
	void rva0016F4F0(Object *source, Object *victim, AIUpdateInterface *ai);

private:
	unsigned char m_field50;
	unsigned char m_pad51[3];
	int m_field54;
};

#pragma comment(linker, "/alternatename:?rva0016F4A0@AIChargeTargetState@@QAE_NXZ=?j_0000d689@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0016FD30@AIChargeTargetState@@QAE_NXZ=?j_00035d3c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0016F4F0@AIChargeTargetState@@QAEXPAVObject@@0PAVAIUpdateInterface@@@Z=?j_000126f7@@YAXXZ")

static __forceinline void clearAdjustDestinationFlag(AIChargeTargetState *state)
{
	(reinterpret_cast<unsigned char *>(state))[0x4c] = 0;
}

#define BFME_THE_AI (*(AI **)0x012EF214)

void __stdcall Rva0017EEE0WeaponCondition(Object *object);
#pragma comment(linker, "/alternatename:?Rva0017EEE0WeaponCondition@@YGXPAVObject@@@Z=?j_000413df@@YAXXZ")

StateReturnType AIChargeTargetState::update()
{
	WeaponSlotType slot;
	Weapon *weapon;
	StateMachine *machine = m_machine;
	Object *source = machine->m_owner;
	AIUpdateInterface *ai;
	Object *victim;
	victim = machine->getGoalObject();
	ai = source->getAI();
	if (ai != 0 && (victim != 0 ||
		(source->m_modelConditionWord & 0x10000000) != 0) && m_field54 > 0)
	{
		if (victim && rva0016F4A0())
		{
			if (!((Rva000D3F10StatusView *)source)->test(0x7c))
			{
				BFME_THE_AI->pathfinder()->removeGoal003E3D20(source);

				Coord3D goalPosition = victim->m_position;
				m_goalPosition = goalPosition;
				clearAdjustDestinationFlag(this);
				ai = source->getAI();
				ai->requestPath(&m_goalPosition, true);
			}
		}

		slot = PRIMARY_WEAPON;
		weapon = 0;
		weapon = source->getCurrentWeapon(&slot);
		if (weapon)
		{
			if (victim && rva0016FD30())
			{
				if (!((Rva000D3F10StatusView *)victim)->test(0x7c) &&
					weapon->bfmeComputeStatus(0) == READY_TO_FIRE)
				{
					rva0016F4F0(source, victim, ai);
					unsigned int modelCondition = source->m_modelConditionWord;
					const unsigned int modelMask = 0x10000000;
					if ((modelCondition & modelMask) == 0)
					{
						modelCondition |= modelMask;
						source->m_modelConditionWord = modelCondition;
						source->notifyModelConditionChanged();
					}
					ai->slot127(4);
					Rva0017EEE0WeaponCondition(source);
				}
			}

			if (m_field50)
				return STATE_SUCCESS;
			return AIInternalMoveToState::update();
		}
	}
	return STATE_FAILURE;
}
