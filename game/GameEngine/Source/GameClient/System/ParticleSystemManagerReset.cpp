// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ParticleSystemManager::reset, retail 0x005C3740 (117 bytes).

class ParticleSystem
{
public:
	virtual ~ParticleSystem();
};

struct BfmeParticleSystemHandle
{
	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

struct BfmeParticleSystemNode
{
	BfmeParticleSystemNode *m_next;
	BfmeParticleSystemNode *m_previous;
	BfmeParticleSystemHandle m_value;
};

struct BfmeParticleSystemList
{
	bool empty() const
	{
		return m_node->m_next == m_node;
	}

	ParticleSystem *front()
	{
		return m_node->m_next->m_value.m_system;
	}

	BfmeParticleSystemNode *m_node;
};

class ParticleSystemManager
{
public:
	virtual void reset();

private:
	unsigned char m_unmodelled_004[0x08];
	ParticleSystem *m_allParticlesHead[14];
	ParticleSystem *m_allParticlesTail[14];
	unsigned int m_uniqueSystemID;
	BfmeParticleSystemList m_allParticleSystemList;
	unsigned int m_particleCount;
	unsigned int m_fieldParticleCount;
	unsigned int m_particleSystemCount;
	int m_onScreenParticleCount;
	unsigned int m_lastLogicFrameUpdate;
	int m_localPlayerIndex;
};

void ParticleSystemManager::reset()
{
	while (m_particleSystemCount)
	{
		if (!m_allParticleSystemList.empty())
		{
			ParticleSystem *system = m_allParticleSystemList.front();
			if (system)
				delete system;
		}
	}

	for (int i = 0; i < 14; ++i)
	{
		m_allParticlesHead[i] = 0;
		m_allParticlesTail[i] = 0;
	}

	m_particleCount = 0;
	m_fieldParticleCount = 0;
	m_particleSystemCount = 0;
	m_onScreenParticleCount = 0;
	m_lastLogicFrameUpdate = 0;
	m_localPlayerIndex = 0;
	m_uniqueSystemID = 0;
}
