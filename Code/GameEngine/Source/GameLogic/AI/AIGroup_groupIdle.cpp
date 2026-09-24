// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_0003add7();

static NameKeyType nameKeyViaIlt(const char *name)
{
	typedef NameKeyType (NameKeyGenerator::*NameKeyCall)(const char *);
	union
	{
		void *asVoid;
		NameKeyCall asMember;
	} nameKeyCast;
	nameKeyCast.asVoid = (void *)j_0003add7;
	return (TheNameKeyGenerator->*nameKeyCast.asMember)(name);
}

#define NAMEKEY(name) nameKeyViaIlt(name)

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_unreconstructed_000[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int low, int high, const char *file, int line);

class AIUpdateModuleData
{
public:
	char m_unreconstructed_000[0x20];
	UnsignedInt m_autoAcquireEnemiesWhenIdle;
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType commandSource);
};

extern void j_00024d70();

static void aiIdleViaIlt(AICommandInterface *commands,
	CommandSourceType commandSource)
{
	typedef void (AICommandInterface::*AIIdleCall)(CommandSourceType);
	union
	{
		void *asVoid;
		AIIdleCall asMember;
	} aiIdleCast;
	aiIdleCast.asVoid = (void *)j_00024d70;
	(commands->*aiIdleCast.asMember)(commandSource);
}

class AIUpdateInterface
{
public:
	char m_unreconstructed_000[4];
	AIUpdateModuleData *m_moduleData;
	char m_unreconstructed_008[0x20 - 0x08];
	AICommandInterface m_commands;
	char m_unreconstructed_021[0x33A - 0x21];
	unsigned char m_playerIdle;

	Bool canAutoAcquire() const
	{
		AIUpdateModuleData *moduleData = m_moduleData;
		return moduleData->m_autoAcquireEnemiesWhenIdle != 0;
	}

	Bool canAutoAcquireWhileStealthed() const
	{
		AIUpdateModuleData *moduleData = m_moduleData;
		return moduleData->m_autoAcquireEnemiesWhenIdle & 0x02;
	}
};

extern void j_00006ece();

static void setNextMoodCheckTimeViaIlt(AIUpdateInterface *ai,
	UnsignedInt frame)
{
	typedef void (AIUpdateInterface::*SetMoodFrameCall)(UnsignedInt);
	union
	{
		void *asVoid;
		SetMoodFrameCall asMember;
	} setMoodFrameCast;
	setMoodFrameCast.asVoid = (void *)j_00006ece;
	(ai->*setMoodFrameCast.asMember)(frame);
}

class StealthUpdateModuleData
{
public:
	char m_unreconstructed_000[8];
	UnsignedInt m_stealthDelay;
};

class StealthUpdate
{
public:
	char m_unreconstructed_000[4];
	StealthUpdateModuleData *m_moduleData;

	UnsignedInt getStealthDelay() const
	{
		return m_moduleData->m_stealthDelay;
	}
};

struct BfmeOwnerBUA;
extern void bfmeGoBUA(BfmeOwnerBUA *owner, void **what);
typedef void (*ContainIterateFunc)(BfmeOwnerBUA *owner, void **what);

class ContainModuleInterface
{
#define CONTAIN_SLOT(name) virtual void slot##name();
public:
	CONTAIN_SLOT(00) CONTAIN_SLOT(04) CONTAIN_SLOT(08) CONTAIN_SLOT(0C)
	CONTAIN_SLOT(10) CONTAIN_SLOT(14) CONTAIN_SLOT(18) CONTAIN_SLOT(1C)
	CONTAIN_SLOT(20) CONTAIN_SLOT(24) CONTAIN_SLOT(28) CONTAIN_SLOT(2C)
	CONTAIN_SLOT(30) CONTAIN_SLOT(34) CONTAIN_SLOT(38) CONTAIN_SLOT(3C)
	CONTAIN_SLOT(40) CONTAIN_SLOT(44) CONTAIN_SLOT(48) CONTAIN_SLOT(4C)
	CONTAIN_SLOT(50) CONTAIN_SLOT(54) CONTAIN_SLOT(58) CONTAIN_SLOT(5C)
	CONTAIN_SLOT(60) CONTAIN_SLOT(64) CONTAIN_SLOT(68) CONTAIN_SLOT(6C)
	CONTAIN_SLOT(70) CONTAIN_SLOT(74) CONTAIN_SLOT(78) CONTAIN_SLOT(7C)
	CONTAIN_SLOT(80) CONTAIN_SLOT(84) CONTAIN_SLOT(88) CONTAIN_SLOT(8C)
	CONTAIN_SLOT(90) CONTAIN_SLOT(94) CONTAIN_SLOT(98) CONTAIN_SLOT(9C)
	CONTAIN_SLOT(A0) CONTAIN_SLOT(A4) CONTAIN_SLOT(A8) CONTAIN_SLOT(AC)
	CONTAIN_SLOT(B0) CONTAIN_SLOT(B4) CONTAIN_SLOT(B8) CONTAIN_SLOT(BC)
	CONTAIN_SLOT(C0) CONTAIN_SLOT(C4) CONTAIN_SLOT(C8) CONTAIN_SLOT(CC)
	CONTAIN_SLOT(D0) CONTAIN_SLOT(D4) CONTAIN_SLOT(D8) CONTAIN_SLOT(DC)
	CONTAIN_SLOT(E0) CONTAIN_SLOT(E4) CONTAIN_SLOT(E8) CONTAIN_SLOT(EC)
	CONTAIN_SLOT(F0) CONTAIN_SLOT(F4) CONTAIN_SLOT(F8)
	virtual void iterateContained(ContainIterateFunc func, void *userData,
		Bool reverse);
#undef CONTAIN_SLOT
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void orderSlavesToGoIdle(CommandSourceType commandSource);
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	UnsignedInt getStatusBits() const { return m_statusBits; }
	ContainModuleInterface *getContain() const { return m_contain; }
	StealthUpdate *findUpdateModule(NameKeyType key);
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;

private:
	char m_unreconstructed_000[0x90];
	UnsignedInt m_statusBits;
	char m_unreconstructed_094[0x1FC - 0x94];
	ContainModuleInterface *m_contain;
	char m_unreconstructed_200[4];
	AIUpdateInterface *m_ai;
};

extern void j_00044201();

static SpawnBehaviorInterface *getSpawnBehaviorInterfaceViaIlt(
	const Object *obj)
{
	typedef SpawnBehaviorInterface *(Object::*GetSpawnBehaviorCall)() const;
	union
	{
		void *asVoid;
		GetSpawnBehaviorCall asMember;
	} getSpawnBehaviorCast;
	getSpawnBehaviorCast.asVoid = (void *)j_00044201;
	return (obj->*getSpawnBehaviorCast.asMember)();
}

enum
{
	OBJECT_STATUS_STEALTHED = 0x00008000,
	OBJECT_STATUS_DETECTED = 0x00020000,
	OBJECT_STATUS_CAN_STEALTH = 0x00040000
};

#define BitTest(value, mask) (((value) & (mask)) != 0)

class AIGroup
{
public:
	void groupIdle(Int commandSource);

private:
	std::list<Object *> m_memberList;
};

void AIGroup::groupIdle(Int commandSource)
{
	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (obj == 0)
			continue;

		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai)
		{
			aiIdleViaIlt(&ai->m_commands, (CommandSourceType)commandSource);

			if (commandSource == CMD_FROM_PLAYER)
				ai->m_playerIdle = 1;

			if (commandSource == CMD_FROM_PLAYER &&
				BitTest(obj->getStatusBits(), OBJECT_STATUS_CAN_STEALTH) &&
				ai->canAutoAcquire())
			{
				if (!BitTest(obj->getStatusBits(), OBJECT_STATUS_STEALTHED) &&
					!BitTest(obj->getStatusBits(), OBJECT_STATUS_DETECTED))
				{
					if (!ai->canAutoAcquireWhileStealthed())
					{
						static NameKeyType key_StealthUpdate =
							NAMEKEY("StealthUpdate");
						StealthUpdate *stealth =
							(StealthUpdate *)obj->findUpdateModule(
								key_StealthUpdate);
						if (stealth)
						{
							UnsignedInt stealthFrames = stealth->getStealthDelay();
							UnsignedInt randomFrames = GetGameLogicRandomValue(
								0, 5,
								"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIGroup.cpp",
								0x951);
							setNextMoodCheckTimeViaIlt(
								ai, TheGameLogic->getFrame() + stealthFrames +
									randomFrames);
						}
					}
				}
			}
		}
		else
		{
			ContainModuleInterface *contain = obj->getContain();
			if (contain)
				contain->iterateContained(bfmeGoBUA,
					(void *)&commandSource, true);
		}

		SpawnBehaviorInterface *spawnInterface =
			getSpawnBehaviorInterfaceViaIlt(obj);
		if (spawnInterface)
			spawnInterface->orderSlavesToGoIdle(
				(CommandSourceType)commandSource);
	}
}
