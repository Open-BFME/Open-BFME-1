// cl: /DNDEBUG /MD /EHs-
// GiveUpgradeUpdate::update, retail RVA 0x0025E4B0.
// The UpdateModuleInterface vtable at this+0x10 points through ILT 0x000154AB.

typedef int ObjectID;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Object;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

#define AI_SLOT(n) virtual void slot##n();
class AIUpdateInterface
{
public:
	AI_SLOT(000) AI_SLOT(001) AI_SLOT(002) AI_SLOT(003)
	AI_SLOT(004) AI_SLOT(005) AI_SLOT(006) AI_SLOT(007)
	AI_SLOT(008) AI_SLOT(009) AI_SLOT(010) AI_SLOT(011)
	AI_SLOT(012) AI_SLOT(013) AI_SLOT(014) AI_SLOT(015)
	AI_SLOT(016) AI_SLOT(017) AI_SLOT(018) AI_SLOT(019)
	AI_SLOT(020) AI_SLOT(021) AI_SLOT(022) AI_SLOT(023)
	AI_SLOT(024) AI_SLOT(025) AI_SLOT(026) AI_SLOT(027)
	AI_SLOT(028) AI_SLOT(029) AI_SLOT(030) AI_SLOT(031)
	AI_SLOT(032) AI_SLOT(033) AI_SLOT(034) AI_SLOT(035)
	AI_SLOT(036) AI_SLOT(037) AI_SLOT(038) AI_SLOT(039)
	AI_SLOT(040) AI_SLOT(041) AI_SLOT(042) AI_SLOT(043)
	AI_SLOT(044) AI_SLOT(045) AI_SLOT(046) AI_SLOT(047)
	AI_SLOT(048) AI_SLOT(049) AI_SLOT(050) AI_SLOT(051)
	AI_SLOT(052) AI_SLOT(053) AI_SLOT(054) AI_SLOT(055)
	AI_SLOT(056) AI_SLOT(057) AI_SLOT(058) AI_SLOT(059)
	AI_SLOT(060) AI_SLOT(061) AI_SLOT(062) AI_SLOT(063)
	AI_SLOT(064) AI_SLOT(065) AI_SLOT(066) AI_SLOT(067)
	AI_SLOT(068) AI_SLOT(069) AI_SLOT(070) AI_SLOT(071)
	AI_SLOT(072) AI_SLOT(073) AI_SLOT(074) AI_SLOT(075)
	AI_SLOT(076) AI_SLOT(077) AI_SLOT(078) AI_SLOT(079)
	AI_SLOT(080) AI_SLOT(081) AI_SLOT(082) AI_SLOT(083)
	AI_SLOT(084) AI_SLOT(085) AI_SLOT(086) AI_SLOT(087)
	AI_SLOT(088) AI_SLOT(089) AI_SLOT(090) AI_SLOT(091)
	AI_SLOT(092) AI_SLOT(093) AI_SLOT(094) AI_SLOT(095)
	AI_SLOT(096) AI_SLOT(097) AI_SLOT(098) AI_SLOT(099)
	AI_SLOT(100) AI_SLOT(101) AI_SLOT(102) AI_SLOT(103)
	AI_SLOT(104) AI_SLOT(105) AI_SLOT(106) AI_SLOT(107)
	AI_SLOT(108) AI_SLOT(109) AI_SLOT(110) AI_SLOT(111)
	AI_SLOT(112) AI_SLOT(113) AI_SLOT(114) AI_SLOT(115)
	AI_SLOT(116) AI_SLOT(117) AI_SLOT(118) AI_SLOT(119)
	AI_SLOT(120) AI_SLOT(121) AI_SLOT(122) AI_SLOT(123)
	AI_SLOT(124) AI_SLOT(125) AI_SLOT(126) AI_SLOT(127)
	virtual CommandSourceType getLastCommandSource() const;
};
#undef AI_SLOT

class Object
{
public:
	virtual void objectSlot00();
	virtual void objectSlot01();
	virtual void objectSlot02();
	virtual void objectSlot03();
	virtual void objectSlot04();
	virtual void objectSlot05();
	virtual void objectSlot06();
	virtual void objectSlot07();
	virtual void objectSlot08();
	virtual void objectSlot09();
	virtual Object *getSpecialObject();
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *object);
};

class SpecialAbilityUpdate
{
public:
	void bfmeAbortAbility();
	void advanceUpdate();
	bool checkTarget(Object *target);
};

class UpdateModuleInterface
{
public:
	UpdateSleepTime update();
};

class GiveUpgradeUpdate
{
public:
	virtual UpdateSleepTime update();
};

class GiveUpgradeUpdateModuleData
{
public:
	unsigned char m_pad[0x26c];
	// The named module-data factory reaches table RVA 0x00CB51F0;
	// its +0x26c entry is FadeOutSpeed with INI::parseReal.
	float m_fadeOutSpeed;
};

extern GameLogic *TheGameLogic;
#define BfmeZeroRange (*(const float *)0x01075350)

#pragma comment(linker, "/alternatename:?update@UpdateModuleInterface@@QAE?AW4UpdateSleepTime@@XZ=?j_00044b0c@@YAXXZ")
#pragma comment(linker, "/alternatename:?advanceUpdate@SpecialAbilityUpdate@@QAEXXZ=?j_0003d0eb@@YAXXZ")
#pragma comment(linker, "/alternatename:?checkTarget@SpecialAbilityUpdate@@QAE_NPAVObject@@@Z=?j_00008995@@YAXXZ")

// ?update@GiveUpgradeUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime GiveUpgradeUpdate::update()
{
	char *rawThis = reinterpret_cast<char *>(this);
	Object *ownerObject = *reinterpret_cast<Object **>(rawThis - 8);
	AIUpdateInterface *ownerAI =
		*reinterpret_cast<AIUpdateInterface **>(reinterpret_cast<char *>(ownerObject) + 0x204);
	CommandSourceType lastCommandSource = ownerAI->getLastCommandSource();
	UpdateSleepTime baseSleepTime =
		reinterpret_cast<UpdateModuleInterface *>(rawThis)->update();

	if (lastCommandSource != CMD_FROM_AI)
	{
		*reinterpret_cast<bool *>(rawThis + 0xd9) = false;
		reinterpret_cast<SpecialAbilityUpdate *>(rawThis - 0x10)->bfmeAbortAbility();
		return baseSleepTime;
	}

	if (*reinterpret_cast<bool *>(rawThis + 0xd9))
		reinterpret_cast<SpecialAbilityUpdate *>(rawThis - 0x10)->advanceUpdate();

	if (!*reinterpret_cast<bool *>(rawThis + 0xd8))
	{
		Object *target = TheGameLogic->findObjectByID(
			*reinterpret_cast<ObjectID *>(rawThis + 0x9c));
		if (target == 0 ||
			(*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(target) + 0x344) & 1) != 0 ||
			!reinterpret_cast<SpecialAbilityUpdate *>(rawThis - 0x10)->checkTarget(target))
		{
			*reinterpret_cast<bool *>(rawThis + 0xd9) = false;
			reinterpret_cast<SpecialAbilityUpdate *>(rawThis - 0x10)->bfmeAbortAbility();
			AICommandInterface *aiCommands =
				reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(ownerAI) + 0x20);
			aiCommands->aiIdle(CMD_FROM_AI);
			return baseSleepTime;
		}
	}

	if (*reinterpret_cast<bool *>(rawThis + 0xd8))
	{
		Object *objectForTimer = *reinterpret_cast<Object **>(rawThis - 8);
		*reinterpret_cast<float *>(rawThis + 0xdc) -=
			(*reinterpret_cast<GiveUpgradeUpdateModuleData **>(rawThis - 0xc))->m_fadeOutSpeed;
		if (*reinterpret_cast<float *>(rawThis + 0xdc) < BfmeZeroRange)
		{
			TheGameLogic->destroyObject(objectForTimer);
			*reinterpret_cast<bool *>(rawThis + 0xd8) = false;
			*reinterpret_cast<float *>(rawThis + 0xdc) = 0.0f;
		}
		else
		{
			Object *specialObject = objectForTimer->getSpecialObject();
			if (specialObject != 0)
				*reinterpret_cast<float *>(reinterpret_cast<char *>(specialObject) + 0xb0) =
					*reinterpret_cast<float *>(rawThis + 0xdc);
		}
	}

	if (*reinterpret_cast<bool *>(rawThis + 0xd9))
		return UPDATE_SLEEP_NONE;
	return baseSleepTime;
}
