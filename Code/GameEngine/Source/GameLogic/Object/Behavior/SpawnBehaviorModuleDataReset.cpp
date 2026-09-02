// cl: /DNDEBUG /MD /EHsc

class SpawnBehaviorModuleDataMemberA
{
public:
	void erase(unsigned int *first, unsigned int *last);
	void clear(void)
	{
		erase(m_begin, m_end);
	}

private:
	unsigned int *m_begin;
	unsigned int *m_end;
	unsigned int *m_capacity;
};

class SpawnBehaviorModuleData
{
public:
	void resetSpawnData(void);

private:
	unsigned char m_beforeSpawnData[0xc4];
	unsigned int m_spawnNumberData;
	unsigned int m_spawnStartNumberData;
	unsigned int m_spawnReplaceDelayData;
	unsigned char m_isOneShotData;
	unsigned char m_canReclaimOrphans;
	unsigned char m_alignment[2];
	SpawnBehaviorModuleDataMemberA m_spawnTemplateNameData;
	unsigned char m_beforeSpawnedRequireSpawner[8];
	unsigned char m_spawnedRequireSpawner;
};

void SpawnBehaviorModuleData::resetSpawnData(void)
{
	m_spawnTemplateNameData.clear();
	m_spawnNumberData = 0;
	m_spawnStartNumberData = 0;
	m_spawnReplaceDelayData = 0;
	m_isOneShotData = 0;
	m_canReclaimOrphans = 0;
	m_spawnedRequireSpawner = 0;
}
