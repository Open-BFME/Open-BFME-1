// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnBehaviorModuleData constructor lifted from the retail body.

class SpawnBehaviorModuleDataMemberAFirst
{
public:
	SpawnBehaviorModuleDataMemberAFirst()
	{
		m_begin = 0;
		m_end = 0;
	}

	public:
	unsigned int *m_begin;
	unsigned int *m_end;
};

class SpawnBehaviorModuleDataMemberAEnd
{
public:
	SpawnBehaviorModuleDataMemberAEnd()
		: m_capacity(0)
	{
	}

private:
	unsigned int *m_capacity;
};

class SpawnBehaviorModuleDataMemberA
{
public:
	SpawnBehaviorModuleDataMemberA()
	{
	}

	~SpawnBehaviorModuleDataMemberA();

	void clear()
	{
		erase(m_first.m_begin, m_first.m_end);
	}

	void erase(unsigned int *first, unsigned int *last);

private:
	SpawnBehaviorModuleDataMemberAFirst m_first;
	SpawnBehaviorModuleDataMemberAEnd m_end;
};

class SpawnBehaviorModuleDataMemberC
{
public:
	SpawnBehaviorModuleDataMemberC();

private:
	unsigned char m_pad[0x2c];
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_pad[0x68];
};

class SpawnBehaviorModuleDataBase
{
public:
	virtual ~SpawnBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnBehavior.h
class SpawnBehaviorModuleData : public SpawnBehaviorModuleDataBase
{
public:
	SpawnBehaviorModuleData();
	virtual ~SpawnBehaviorModuleData();

private:
	unsigned int m_spawnNumberData;
	unsigned int m_spawnStartNumberData;
	unsigned int m_spawnReplaceDelayData;
	unsigned char m_isOneShotData;
	unsigned char m_canReclaimOrphans;
	unsigned char m_aggregateHealth;
	unsigned char m_exitByBudding;
	unsigned char m_spawnedRequireSpawner;
	unsigned char m_slavesHaveFreeWill;
	unsigned int m_alignment;
	SpawnBehaviorModuleDataMemberA m_spawnTemplateNameData;
	SpawnBehaviorModuleDataMemberC m_damageTypesToPropagateToSlaves;
	UpgradeModuleDataSub m_dieMuxData;
};

// ??0SpawnBehaviorModuleData@@QAE@XZ
SpawnBehaviorModuleData::SpawnBehaviorModuleData()
	: m_spawnTemplateNameData(),
	  m_damageTypesToPropagateToSlaves(),
	  m_dieMuxData()
{
	m_spawnNumberData = 0;
	m_spawnStartNumberData = 0;
	m_spawnReplaceDelayData = 0;
	m_isOneShotData = 0;
	m_canReclaimOrphans = 0;
	m_aggregateHealth = 0;
	m_exitByBudding = 0;
	m_spawnTemplateNameData.clear();
	m_spawnedRequireSpawner = 0;
	m_slavesHaveFreeWill = 0;
}
