// ?findParticleSystemByID@ParticleSystemManager@@AAE?AVBfmeParticleSystemHandle@@W4ParticleSystemID@@@Z
// Open-BFME: ParticleSystemManager::findParticleSystemByID, retail 0x005C3B30 (171 bytes).
// The list is the 12-byte intrusive-handle list at this+0x80. A returned
// handle is inserted into the particle system's handle chain before return.
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem;
ParticleSystem *Make00001B18();

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(ParticleSystem *system = 0) :
		m_system(system), m_previous(0), m_next(0) { }
	BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that);
	~BfmeParticleSystemHandle() throw();
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make00001B18();
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

__forceinline BfmeParticleSystemHandle::BfmeParticleSystemHandle(
	const BfmeParticleSystemHandle &that )
{
	ParticleSystem *system = that.m_system;
	m_system = system;
	if (system)
	{
		m_previous = system->m_lastHandle;
		m_next = 0;
		system->m_lastHandle = this;
		if (m_previous)
			m_previous->m_next = this;
		else
			m_system->m_firstHandle = this;
	}
	else
	{
		m_previous = 0;
		m_next = 0;
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
