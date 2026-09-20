// ?d_0020c750@@YAXXZ
// partial score=0.88 date=2026-09-20
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1
};

template <int NUMBITS>
class BitFlags
{
private:
	_STL::bitset<NUMBITS> m_bits;

	public:
	BitFlags()
	{
	}

	bool any() const
	{
		return m_bits.any();
	}
};

typedef BitFlags<192> UpgradeMaskType;

class UpgradeMuxData
{
public:
	void getUpgradeActivationMasks(UpgradeMaskType &activation,
		UpgradeMaskType &conflicting) const;
};

class SpawnBehaviorModuleData
{
public:
	char m_pad00[8];
	Int m_spawnNumberData;
	char m_pad0c[4];
	Int m_initialBurst;
	Bool m_isOneShotData;
	char m_pad15[0x43];
	UpgradeMuxData m_upgradeMuxData;
};

class Object
{
public:
	char m_pad00[0x78];
	ObjectID m_producerID;
	char m_pad7c[0x14];
	UnsignedInt m_status90;
};

class Rva00367E30Logic
{
public:
	char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class SpawnBehaviorFourthBase
{
public:
	virtual Bool slot00();
};

class SpawnBehaviorPrimary
{
public:
	virtual void slot00();
	SpawnBehaviorModuleData *m_module;
	Object *m_object;
	char m_pad0c[0x40];
	Bool m_active;

	Object *getObject() const
	{
		return m_object;
	}

	UnsignedInt getStatus() const
	{
		return getObject()->m_status90;
	}

	Bool shouldTryToSpawn() const
	{
		if (!m_active)
			return false;
		UnsignedInt status = getStatus();
		if ((status & 0x200000) != 0 &&
			m_module->m_isOneShotData == (Bool)1)
		{
			((SpawnBehaviorPrimary *)this)->m_active = false;
			return false;
		}
		if ((status & 4) != 0 || (status & 0x80000) != 0)
			return false;
		return true;
	}
};

class SpawnBehavior
{
public:
	virtual UpdateSleepTime update();
	void computeAggregateStates();
	Bool createSpawn();

private:
	char m_pad04[0x24];
	Int m_oneShotCountdown;
	Int m_framesToWait;
	Int m_firstBatchCount;
	_STL::list<Int> m_replacementTimes;
	_STL::list<ObjectID> m_spawnIDs;
	Bool m_active;
	Bool m_aggregateHealth;
	Bool m_initialBurstTimesInited;
	Int m_spawnCount;
	UnsignedInt m_selfTaskingSpawnCount;
	UnsignedInt m_initialBurstCountdown;
	void *m_templateNameIterator;
};

// ?update@SpawnBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SpawnBehavior::update()
{
	if (m_aggregateHealth)
	{
		((SpawnBehavior *)((char *)this - 0x10))->computeAggregateStates();
	}

	Bool runtimeProduced;
	UpgradeMaskType activation;
	UpgradeMaskType conflicting;
	SpawnBehaviorModuleData *md = *(SpawnBehaviorModuleData **)((char *)this - 0x0c);
	md->m_upgradeMuxData.getUpgradeActivationMasks(activation, conflicting);
	if (activation.any())
	{
		SpawnBehaviorFourthBase *gate =
			(SpawnBehaviorFourthBase *)((char *)this + 0x1c);
		if (!gate->slot00())
			return UPDATE_SLEEP_NONE;
	}

	if (!m_initialBurstTimesInited)
	{
		m_initialBurstTimesInited = true;
		Object *object = *(Object **)((char *)this - 0x08);
		runtimeProduced = object->m_producerID != (ObjectID)0;
		Int burstInitCount = m_initialBurstCountdown;
		Int listIndex[2];
		listIndex[0] = 0;
		for (; listIndex[0] < md->m_spawnNumberData; ++listIndex[0])
		{
			if (md->m_initialBurst > 0)
			{
				if (runtimeProduced && burstInitCount > 0)
					--burstInitCount;
				m_replacementTimes.push_back(runtimeProduced);
			}
			else
				m_replacementTimes.push_back(listIndex[0]);
		}
	}

	if (--m_framesToWait > 0)
		return UPDATE_SLEEP_NONE;

	m_framesToWait = 2;
	if (!((SpawnBehaviorPrimary *)((char *)this - 0x10))->shouldTryToSpawn())
		return UPDATE_SLEEP_NONE;
	_STL::list<Int>::iterator iterator = m_replacementTimes.begin();
	while (iterator != m_replacementTimes.end())
	{
		Int replacementTime = *iterator;
		UnsignedInt currentTime = TheBfmeGameLogic->m_frame;
		if (currentTime > (UnsignedInt)replacementTime)
		{
			if (((SpawnBehavior *)((char *)this - 0x10))->createSpawn())
				iterator = m_replacementTimes.erase(iterator);
			else
				++iterator;
		}
		else
			++iterator;
	}

	if (md->m_isOneShotData && m_oneShotCountdown <= 0)
		m_active = false;
	return UPDATE_SLEEP_NONE;
}
