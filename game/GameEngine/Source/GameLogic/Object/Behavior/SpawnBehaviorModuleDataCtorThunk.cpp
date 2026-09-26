// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnBehaviorModuleData constructor lifted from the retail body.

class AsciiString;

class Rva0076F980MidFirst
{
public:
	Rva0076F980MidFirst()
	{
		m_begin = 0;
		m_end = 0;
	}

	public:
	AsciiString *m_begin;
	AsciiString *m_end;
};

class Rva0076F980MidEnd
{
public:
	Rva0076F980MidEnd()
		: m_capacity(0)
	{
	}

private:
	AsciiString *m_capacity;
};

class Rva0076F980Mid
{
public:
	Rva0076F980Mid()
	{
	}

	~Rva0076F980Mid();

	void clear()
	{
		erase(m_first.m_begin, m_first.m_end);
	}

	AsciiString *erase(AsciiString *first, AsciiString *last);

private:
	Rva0076F980MidFirst m_first;
	Rva0076F980MidEnd m_end;
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnBehavior.h
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
	Rva0076F980Mid m_spawnTemplateNameData;
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
