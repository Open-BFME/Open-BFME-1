// ?findParticleSystemByID@ParticleSystemManager@@AAE?AVBfmeParticleSystemHandle@@W4ParticleSystemID@@@Z
// partial score=0.9 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem;
ParticleSystem *bfmeInvalidParticleSystemHandle();

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(ParticleSystem *system = 0) :
		m_system(system), m_previous(0), m_next(0) { }
	BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that);
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : bfmeInvalidParticleSystemHandle();
	}

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystem
{
public:
	unsigned char m_unmodelled_000[0x98];
	BfmeParticleSystemHandle *m_firstHandle;
	BfmeParticleSystemHandle *m_lastHandle;
	unsigned char m_unmodelled_0A0[0x0C];
	ParticleSystemID m_id;
};

BfmeParticleSystemHandle::BfmeParticleSystemHandle(
	const BfmeParticleSystemHandle &that ) :
	m_system(that.m_system), m_previous(0), m_next(0)
{
	if (m_system)
	{
		m_previous = m_system->m_lastHandle;
		m_system->m_lastHandle = this;
		if (m_previous)
			m_previous->m_next = this;
		else
			m_system->m_firstHandle = this;
	}
}

struct BfmeParticleSystemNode
{
	BfmeParticleSystemNode *m_next;
	BfmeParticleSystemNode *m_previous;
	BfmeParticleSystemHandle m_value;
};

class BfmeParticleSystemIterator
{
public:
	BfmeParticleSystemIterator(BfmeParticleSystemNode *node) : m_node(node) { }
	BfmeParticleSystemHandle &operator*() const { return m_node->m_value; }
	BfmeParticleSystemHandle *operator->() const { return &m_node->m_value; }
	BfmeParticleSystemIterator &operator++()
	{
		m_node = m_node->m_next;
		return *this;
	}
	bool operator!=(const BfmeParticleSystemIterator &that) const
	{
		return m_node != that.m_node;
	}

private:
	BfmeParticleSystemNode *m_node;
};

class BfmeParticleSystemList
{
public:
	BfmeParticleSystemIterator begin()
	{
		return BfmeParticleSystemIterator(m_node->m_next);
	}
	BfmeParticleSystemIterator end()
	{
		return BfmeParticleSystemIterator(m_node);
	}

private:
	BfmeParticleSystemNode *m_node;
};

class ParticleSystemManager
{
private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);

	unsigned char m_unmodelled_000[0x80];
	BfmeParticleSystemList m_systems;
};

// ?findParticleSystemByID@ParticleSystemManager@@AAE?AVBfmeParticleSystemHandle@@W4ParticleSystemID@@@Z
BfmeParticleSystemHandle ParticleSystemManager::findParticleSystemByID(
	ParticleSystemID id )
{
	if (id == INVALID_PARTICLE_SYSTEM_ID)
		return 0;

	for (BfmeParticleSystemIterator it = m_systems.begin();
		it != m_systems.end(); ++it)
	{
		if (*it && (*it)->m_id == id)
			return *it;
	}

	return 0;
}
