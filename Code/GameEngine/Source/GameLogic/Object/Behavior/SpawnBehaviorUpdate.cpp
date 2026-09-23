// SpawnBehavior::update, RVA 0x0020C750..0x0020C93C (492 bytes).
// Constructor 0x0020AE30 installs vtable VA 0x010A6BFC at owner+0x10;
// slot zero reaches this body through ILT 0x00012995. The compiler uses
// that secondary receiver for update and the primary receiver for helpers.
// The constructor and ZH SpawnBehavior.h witness the member names below.
// Upgrade activation is a BFME addition: 192-bit masks at module data+0x58.
// The two native list operations use the pooled STLport node allocator.
// Callees: computeAggregateStates -> 0x0020BAE0; createSpawn -> 0x0020C3B0;
// getUpgradeActivationMasks -> 0x002D9FF0 (six dwords per output mask).

// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

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
	UnsignedInt m_status;
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

class Rva0020C750Primary
{
public:
    virtual void slot00();
    SpawnBehaviorModuleData *m_module;
    Object *m_object;
    void *m_interface0C;
};

class Rva0020C750UpdateInterface
{
public:
    virtual UpdateSleepTime update() = 0;
};

class SpawnBehavior : public Rva0020C750Primary, public Rva0020C750UpdateInterface
{
public:
	virtual UpdateSleepTime update();
	void computeAggregateStates();
private:
	Bool createSpawn();

	Object *getObject() const
	{
		return m_object;
	}

	UnsignedInt getStatus() const
	{
		return getObject()->m_status;
	}

	Bool shouldTryToSpawn() const
	{
		if (!m_active)
			return false;
		UnsignedInt status = getStatus();
		if ((status & 0x200000) != 0 &&
			m_module->m_isOneShotData == (Bool)1)
		{
			((SpawnBehavior *)this)->m_active = false;
			return false;
		}
		if ((status & 4) != 0 || (status & 0x80000) != 0)
			return false;
		return true;
	}


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
		computeAggregateStates();
	}

	Bool runtimeProduced;
	UpgradeMaskType activation;
	UpgradeMaskType conflicting;
	SpawnBehaviorModuleData *md = m_module;
	md->m_upgradeMuxData.getUpgradeActivationMasks(activation, conflicting);
	if (activation.any())
	{
		SpawnBehaviorFourthBase *gate =
			(SpawnBehaviorFourthBase *)((char *)this + 0x2c);
		if (!gate->slot00())
			return UPDATE_SLEEP_NONE;
	}

	if (!m_initialBurstTimesInited)
	{
		m_initialBurstTimesInited = true;
		Object *object = m_object;
		runtimeProduced = object->m_producerID != (ObjectID)0;
		Int burstInitCount = m_initialBurstCountdown;
		Int listIndex;
		listIndex = 0;
		for (; listIndex < md->m_spawnNumberData; ++listIndex)
		{
			if (md->m_initialBurst > 0)
			{
				if (runtimeProduced && burstInitCount > 0)
					--burstInitCount;
				m_replacementTimes.push_back(runtimeProduced);
			}
			else
				m_replacementTimes.push_back(listIndex);
		}
	}

	if (--m_framesToWait > 0)
		return UPDATE_SLEEP_NONE;

	m_framesToWait = 2;
	if (!shouldTryToSpawn())
		return UPDATE_SLEEP_NONE;
	_STL::list<Int>::iterator iterator = m_replacementTimes.begin();
	while (iterator != m_replacementTimes.end())
	{
		Int replacementTime = *iterator;
		UnsignedInt currentTime = TheBfmeGameLogic->m_frame;
		if (currentTime > (UnsignedInt)replacementTime)
		{
			if (createSpawn())
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


