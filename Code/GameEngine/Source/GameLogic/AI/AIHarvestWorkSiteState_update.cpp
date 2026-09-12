// ?update@AIHarvestWorkSiteState@@UAE?AW4StateReturnType@@XZ
// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Rva001601E0HarvestRecord;
class Rva001601E0Locomotor;

class Rva001601E0HarvestTarget
{
public:
	virtual int slot00() = 0;
	virtual int slot01() = 0;
	virtual int slot02() = 0;
	virtual void slot03(int) = 0;
	virtual int slot04() = 0;
	virtual int slot05() = 0;
	virtual int slot06() = 0;
	virtual float getValue(int, int) = 0;
	virtual int slot08() = 0;
	virtual int slot09() = 0;
	virtual int slot10() = 0;
	virtual void slot11(int) = 0;
	virtual int slot12() = 0;
	virtual int slot13() = 0;
	virtual int slot14() = 0;
	virtual int slot15() = 0;
	virtual int slot16() = 0;
	virtual int slot17() = 0;
	virtual int getOwner() = 0;
};

#define RVA001601E0_AI_SLOT(n) virtual void slot##n() = 0;
class Rva001601E0AIUpdate
{
public:
	RVA001601E0_AI_SLOT(000)
	RVA001601E0_AI_SLOT(001)
	RVA001601E0_AI_SLOT(002)
	RVA001601E0_AI_SLOT(003)
	RVA001601E0_AI_SLOT(004)
	RVA001601E0_AI_SLOT(005)
	RVA001601E0_AI_SLOT(006)
	RVA001601E0_AI_SLOT(007)
	RVA001601E0_AI_SLOT(008)
	RVA001601E0_AI_SLOT(009)
	RVA001601E0_AI_SLOT(010)
	RVA001601E0_AI_SLOT(011)
	RVA001601E0_AI_SLOT(012)
	RVA001601E0_AI_SLOT(013)
	RVA001601E0_AI_SLOT(014)
	RVA001601E0_AI_SLOT(015)
	RVA001601E0_AI_SLOT(016)
	RVA001601E0_AI_SLOT(017)
	RVA001601E0_AI_SLOT(018)
	RVA001601E0_AI_SLOT(019)
	RVA001601E0_AI_SLOT(020)
	RVA001601E0_AI_SLOT(021)
	RVA001601E0_AI_SLOT(022)
	RVA001601E0_AI_SLOT(023)
	RVA001601E0_AI_SLOT(024)
	RVA001601E0_AI_SLOT(025)
	RVA001601E0_AI_SLOT(026)
	RVA001601E0_AI_SLOT(027)
	RVA001601E0_AI_SLOT(028)
	RVA001601E0_AI_SLOT(029)
	RVA001601E0_AI_SLOT(030)
	RVA001601E0_AI_SLOT(031)
	RVA001601E0_AI_SLOT(032)
	RVA001601E0_AI_SLOT(033)
	RVA001601E0_AI_SLOT(034)
	RVA001601E0_AI_SLOT(035)
	RVA001601E0_AI_SLOT(036)
	RVA001601E0_AI_SLOT(037)
	RVA001601E0_AI_SLOT(038)
	RVA001601E0_AI_SLOT(039)
	RVA001601E0_AI_SLOT(040)
	RVA001601E0_AI_SLOT(041)
	RVA001601E0_AI_SLOT(042)
	RVA001601E0_AI_SLOT(043)
	RVA001601E0_AI_SLOT(044)
	RVA001601E0_AI_SLOT(045)
	RVA001601E0_AI_SLOT(046)
	RVA001601E0_AI_SLOT(047)
	RVA001601E0_AI_SLOT(048)
	RVA001601E0_AI_SLOT(049)
	RVA001601E0_AI_SLOT(050)
	RVA001601E0_AI_SLOT(051)
	RVA001601E0_AI_SLOT(052)
	RVA001601E0_AI_SLOT(053)
	RVA001601E0_AI_SLOT(054)
	RVA001601E0_AI_SLOT(055)
	RVA001601E0_AI_SLOT(056)
	RVA001601E0_AI_SLOT(057)
	RVA001601E0_AI_SLOT(058)
	RVA001601E0_AI_SLOT(059)
	RVA001601E0_AI_SLOT(060)
	RVA001601E0_AI_SLOT(061)
	RVA001601E0_AI_SLOT(062)
	RVA001601E0_AI_SLOT(063)
	RVA001601E0_AI_SLOT(064)
	RVA001601E0_AI_SLOT(065)
	RVA001601E0_AI_SLOT(066)
	RVA001601E0_AI_SLOT(067)
	RVA001601E0_AI_SLOT(068)
	RVA001601E0_AI_SLOT(069)
	RVA001601E0_AI_SLOT(070)
	RVA001601E0_AI_SLOT(071)
	RVA001601E0_AI_SLOT(072)
	RVA001601E0_AI_SLOT(073)
	RVA001601E0_AI_SLOT(074)
	RVA001601E0_AI_SLOT(075)
	RVA001601E0_AI_SLOT(076)
	RVA001601E0_AI_SLOT(077)
	RVA001601E0_AI_SLOT(078)
	RVA001601E0_AI_SLOT(079)
	RVA001601E0_AI_SLOT(080)
	virtual Rva001601E0HarvestTarget *getHarvestTarget() = 0;
	char m_pad[0x1cc - 4];
	Rva001601E0Locomotor *m_locomotor;
};

class Rva001601E0FlagWord
{
public:
	bool test(int bit) const
	{
		return m_bits.test(bit);
	}

	void set(int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<32> m_bits;
};

class Rva001601E0Object
{
public:
	char m_pad00[0x12c];
	Rva001601E0FlagWord m_flags;
	char m_pad130[0xd4];
	Rva001601E0AIUpdate *m_ai;
	void notifyModelConditionChanged();
};

class Rva001601E0StateMachine
{
public:
	char m_pad00[0x10];
	Rva001601E0Object *m_owner;
};

class Rva001601E0Terrain
{
public:
	Rva001601E0HarvestRecord *find(Rva001601E0HarvestRecord *, float);
	bool check(int);
	int adjust(Rva001601E0HarvestRecord *, int);
};

extern void j_000226ab();

class Rva001601E0Locomotor
{
public:
	void action(Rva001601E0Object *, Rva001601E0HarvestRecord *, int);
};

class Rva001601E0HarvestRecord
{
public:
	char m_pad00[0x0c];
	int m_id;

	int getID() const
	{
		return m_id;
	}
	int getAmount() const
	{
		return m_amount;
	}
	int m_owner;
	char m_pad14[0x14];
	int m_amount;
};

class GameLogic
{
public:
	char m_pad00[0x3c];
	unsigned int m_frame;
};


class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;

extern void j_0002b3be();
extern void j_00003166();
extern void j_00002b49();
extern void j_0002191d();

static __forceinline bool bfmeTerrainCheck(Rva001601E0Terrain *terrain, int id)
{
	typedef bool (Rva001601E0Terrain::*Call)(int);
	union { void *asVoid; Call asMember; } cast;
	cast.asVoid = (void *)j_0002b3be;
	return (terrain->*cast.asMember)(id);
}

static __forceinline int bfmeTerrainAdjust(Rva001601E0Terrain *terrain,
	Rva001601E0HarvestRecord *record, int amount)
{
	typedef int (Rva001601E0Terrain::*Call)(Rva001601E0HarvestRecord *, int);
	union { void *asVoid; Call asMember; } cast;
	cast.asVoid = (void *)j_00003166;
	return (terrain->*cast.asMember)(record, amount);
}

static __forceinline void bfmeLocomotorAction(Rva001601E0Locomotor *locomotor,
	Rva001601E0Object *owner, Rva001601E0HarvestRecord *record, int value)
{
	typedef void (Rva001601E0Locomotor::*Call)(Rva001601E0Object *, Rva001601E0HarvestRecord *, int);
	union { void *asVoid; Call asMember; } cast;
	cast.asVoid = (void *)j_00002b49;
	(locomotor->*cast.asMember)(owner, record, value);
}

static __forceinline void bfmeNotifyModelConditionChanged(Rva001601E0Object *owner)
{
	typedef void (Rva001601E0Object::*Call)();
	union { void *asVoid; Call asMember; } cast;
	cast.asVoid = (void *)j_0002191d;
	(owner->*cast.asMember)();
}

class Rva001601E0StateBase
{
public:
	virtual StateReturnType slot00() = 0;
	virtual StateReturnType slot01() = 0;
	virtual StateReturnType slot02() = 0;
	virtual StateReturnType slot03() = 0;
	virtual StateReturnType slot04() = 0;
	virtual StateReturnType slot05() = 0;
};

class AIHarvestWorkSiteState : public Rva001601E0StateBase
{
public:
	virtual StateReturnType update();

	char m_pad00[0x18];
	Rva001601E0StateMachine *m_machine;
	char m_pad20[4];
	unsigned int m_frame;
};

StateReturnType AIHarvestWorkSiteState::update()
{
	register AIHarvestWorkSiteState *self = this;
	Rva001601E0HarvestTarget *target =
		self->m_machine->m_owner->m_ai->getHarvestTarget();
	if (target != 0)
	{
		register Rva001601E0Object *owner = self->m_machine->m_owner;
		typedef Rva001601E0HarvestRecord *(Rva001601E0Terrain::*FindCall)(
			Rva001601E0HarvestRecord *, float);
		union { void *asVoid; FindCall asMember; } findCast;
		findCast.asVoid = (void *)j_000226ab;
		register Rva001601E0HarvestRecord *record =
			(((Rva001601E0Terrain *)TheTerrainLogic)->*findCast.asMember)(
				(Rva001601E0HarvestRecord *)((char *)owner + 0x38),
				target->getValue(0, 2));
		int recordOwner = 0;
		if (record != 0)
		{
			recordOwner = record->m_owner;
		}
		if (record != 0 && recordOwner == target->getOwner() &&
			bfmeTerrainCheck((Rva001601E0Terrain *)TheTerrainLogic, record->getID()))
		{
			GameLogic *gameLogic = TheGameLogic;
			if (gameLogic->m_frame >= self->m_frame)
			{
				int first = target->slot01();
				int second = target->slot00();
				const int previousAmount = record->m_amount;
				int amount = first - second;
				int remaining = bfmeTerrainAdjust((Rva001601E0Terrain *)TheTerrainLogic, record, amount);
				if (remaining > 0)
				{
					for (int count = remaining; count != 0; --count)
					{
						target->slot03(previousAmount - remaining);
					}
					return STATE_SUCCESS;
				}
				return STATE_SUCCESS;
			}

			if (self->m_machine->m_owner->m_ai->m_locomotor != 0)
			{
				bfmeLocomotorAction(self->m_machine->m_owner->m_ai->m_locomotor,
					self->m_machine->m_owner, record, 0);
			}
		}
		else
		{
			target->slot11(1);
			return STATE_FAILURE;
		}
	}

	flags:
	Rva001601E0Object *flagsOwner = self->m_machine->m_owner;
	if (!flagsOwner->m_flags.test(22))
	{
		flagsOwner->m_flags.set(22);
		bfmeNotifyModelConditionChanged(flagsOwner);
	}
	return STATE_CONTINUE;

}
