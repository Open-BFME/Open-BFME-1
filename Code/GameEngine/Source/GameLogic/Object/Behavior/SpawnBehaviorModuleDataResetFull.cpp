// cl: /DNDEBUG /MD /EHsc

void *bfmeMakeBNG(void *one, void *two);

class SpawnBehaviorModuleDataMemberA
{
public:
	void erase(unsigned int *first, unsigned int *last);
	void clear(void)
	{
		erase(m_begin, m_end);
	}

	unsigned int *m_begin;
	unsigned int *m_end;
	unsigned int *m_capacity;
};

class SpawnBehaviorModuleData
{
public:
	void resetSpawnDataFull(void);

private:
	unsigned char m_beforeFlag[0xa8];
	unsigned char m_flagA8;
	unsigned char m_padA9[0xb];
	void *m_madeBNG;
	unsigned char m_beforeSpawnData[0x0c];
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

void SpawnBehaviorModuleData::resetSpawnDataFull(void)
{
	unsigned int z = 0;
	m_flagA8 = (unsigned char)z;
	m_madeBNG = bfmeMakeBNG((void *)z, (void *)z);
	m_spawnTemplateNameData.clear();
	m_spawnNumberData = z;
	m_spawnStartNumberData = z;
	m_spawnReplaceDelayData = z;
	m_isOneShotData = (unsigned char)z;
	m_canReclaimOrphans = (unsigned char)z;
	m_spawnedRequireSpawner = (unsigned char)z;
}
