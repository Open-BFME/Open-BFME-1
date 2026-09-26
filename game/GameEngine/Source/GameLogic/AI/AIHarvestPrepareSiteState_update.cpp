// cl: /DNDEBUG /MD
// Retail 0x00160050: AIHarvestPrepareSiteState::update.

typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class HarvestRecord;

class HarvestTarget
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03(int) = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual float getValue(int, int) = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11(int) = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void setOwner(int) = 0;
	virtual void slot17(int) = 0;
};

class AIUpdate
{
public:
#define AIUPDATE_SLOT(n) virtual void slot##n() = 0;
	AIUPDATE_SLOT(000)
	AIUPDATE_SLOT(001)
	AIUPDATE_SLOT(002)
	AIUPDATE_SLOT(003)
	AIUPDATE_SLOT(004)
	AIUPDATE_SLOT(005)
	AIUPDATE_SLOT(006)
	AIUPDATE_SLOT(007)
	AIUPDATE_SLOT(008)
	AIUPDATE_SLOT(009)
	AIUPDATE_SLOT(010)
	AIUPDATE_SLOT(011)
	AIUPDATE_SLOT(012)
	AIUPDATE_SLOT(013)
	AIUPDATE_SLOT(014)
	AIUPDATE_SLOT(015)
	AIUPDATE_SLOT(016)
	AIUPDATE_SLOT(017)
	AIUPDATE_SLOT(018)
	AIUPDATE_SLOT(019)
	AIUPDATE_SLOT(020)
	AIUPDATE_SLOT(021)
	AIUPDATE_SLOT(022)
	AIUPDATE_SLOT(023)
	AIUPDATE_SLOT(024)
	AIUPDATE_SLOT(025)
	AIUPDATE_SLOT(026)
	AIUPDATE_SLOT(027)
	AIUPDATE_SLOT(028)
	AIUPDATE_SLOT(029)
	AIUPDATE_SLOT(030)
	AIUPDATE_SLOT(031)
	AIUPDATE_SLOT(032)
	AIUPDATE_SLOT(033)
	AIUPDATE_SLOT(034)
	AIUPDATE_SLOT(035)
	AIUPDATE_SLOT(036)
	AIUPDATE_SLOT(037)
	AIUPDATE_SLOT(038)
	AIUPDATE_SLOT(039)
	AIUPDATE_SLOT(040)
	AIUPDATE_SLOT(041)
	AIUPDATE_SLOT(042)
	AIUPDATE_SLOT(043)
	AIUPDATE_SLOT(044)
	AIUPDATE_SLOT(045)
	AIUPDATE_SLOT(046)
	AIUPDATE_SLOT(047)
	AIUPDATE_SLOT(048)
	AIUPDATE_SLOT(049)
	AIUPDATE_SLOT(050)
	AIUPDATE_SLOT(051)
	AIUPDATE_SLOT(052)
	AIUPDATE_SLOT(053)
	AIUPDATE_SLOT(054)
	AIUPDATE_SLOT(055)
	AIUPDATE_SLOT(056)
	AIUPDATE_SLOT(057)
	AIUPDATE_SLOT(058)
	AIUPDATE_SLOT(059)
	AIUPDATE_SLOT(060)
	AIUPDATE_SLOT(061)
	AIUPDATE_SLOT(062)
	AIUPDATE_SLOT(063)
	AIUPDATE_SLOT(064)
	AIUPDATE_SLOT(065)
	AIUPDATE_SLOT(066)
	AIUPDATE_SLOT(067)
	AIUPDATE_SLOT(068)
	AIUPDATE_SLOT(069)
	AIUPDATE_SLOT(070)
	AIUPDATE_SLOT(071)
	AIUPDATE_SLOT(072)
	AIUPDATE_SLOT(073)
	AIUPDATE_SLOT(074)
	AIUPDATE_SLOT(075)
	AIUPDATE_SLOT(076)
	AIUPDATE_SLOT(077)
	AIUPDATE_SLOT(078)
	AIUPDATE_SLOT(079)
	AIUPDATE_SLOT(080)
	virtual HarvestTarget *getHarvestTarget() = 0;
#undef AIUPDATE_SLOT
	char m_pad[0x1cc - 4];
};

class ModelConditionFlags
{
public:
	bool test(UnsignedInt condition) const
	{
		return (m_bits & condition) != 0;
	}

	void set(UnsignedInt condition)
	{
		m_bits |= condition;
	}

private:
	UnsignedInt m_bits;
};

class Object
{
public:
	char m_pad00[0x12c];
	ModelConditionFlags m_statusFlags;
	char m_pad130[0xd4];
	AIUpdate *m_ai;
	void notifyModelConditionChanged();
};

class StateMachine
{
public:
	char m_pad00[0x10];
	Object *m_owner;
};

class TerrainLogic
{
public:
	HarvestRecord *find(HarvestRecord *, float);
	void process(HarvestRecord *, void *);
};

class HarvestRecord
{
public:
	char m_pad00[0x10];
	int m_owner;
	char m_pad14[4];
	bool m_isFinished;
};

class GameLogic
{
	char m_pad00[0x3c];

public:
	UnsignedInt m_frame;
};

#pragma comment(linker, "/alternatename:?find@TerrainLogic@@QAEPAVHarvestRecord@@PAV2@M@Z=?j_000226ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?process@TerrainLogic@@QAEXPAVHarvestRecord@@PAX@Z=?j_0001acbc@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")

#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheGameLogic (*(GameLogic **)0x012F0898)

class StateBase
{
public:
	virtual StateReturnType slot00() = 0;
	virtual StateReturnType slot01() = 0;
	virtual StateReturnType slot02() = 0;
	virtual StateReturnType slot03() = 0;
	virtual StateReturnType slot04() = 0;
	virtual StateReturnType slot05() = 0;
};

class AIHarvestPrepareSiteState : public StateBase
{
public:
	virtual StateReturnType update();

	char m_pad00[0x18];
	StateMachine *m_machine;
	char m_pad20[4];
	UnsignedInt m_frame;
};

StateReturnType AIHarvestPrepareSiteState::update()
{
	HarvestTarget *target = m_machine->m_owner->m_ai->getHarvestTarget();
	register UnsignedInt condition = 0x200000;
	if (target != 0)
	{
		Object *ownerForFind = m_machine->m_owner;
		HarvestRecord *record = TheTerrainLogic->find(
			(HarvestRecord *)((char *)ownerForFind + 0x38),
			target->getValue(0, 2));
		if (record == 0)
		{
			StateMachine *machineForFind = m_machine;
			HarvestRecord *fallbackRecord =
				(HarvestRecord *)((char *)machineForFind + 0x24);
			record = TheTerrainLogic->find(
				fallbackRecord,
				target->getValue(0, 2));
			if (record == 0)
				target->slot11(1);
			return STATE_FAILURE;
		}

		target->slot17(record->m_owner);
		Object *owner = m_machine->m_owner;
		if (!owner->m_statusFlags.test(condition))
		{
			owner->m_statusFlags.set(condition);
			owner->notifyModelConditionChanged();
		}
		if (record->m_isFinished)
			return STATE_SUCCESS;

		if (TheGameLogic->m_frame >= m_frame)
		{
			TheTerrainLogic->process(record,
				(void *)((char *)m_machine->m_owner + 0x38));
			return STATE_SUCCESS;
		}
	}

	Object *owner = m_machine->m_owner;
	if (!owner->m_statusFlags.test(condition))
	{
		owner->m_statusFlags.set(condition);
		owner->notifyModelConditionChanged();
	}
	return STATE_CONTINUE;
}
