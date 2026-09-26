// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ParticleSystemManager::destroyAttachedSystems, retail
// 0x005C3C80 (299 bytes).

typedef unsigned int ObjectID;

class ParticleSystem;
struct BfmeParticleSystemNode;

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(ParticleSystem *system = 0) :
		m_system(system), m_previous(0), m_next(0) { }
	BfmeParticleSystemHandle(const BfmeParticleSystemNode *node);
	~BfmeParticleSystemHandle() throw();
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const { return m_system; }

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystem
{
public:
	void destroy();
	ObjectID getAttachedObject() const { return m_attachedToObjectID; }

	unsigned char m_unmodelled_000[0x98];
	BfmeParticleSystemHandle *m_firstHandle;
	BfmeParticleSystemHandle *m_lastHandle;
	unsigned char m_unmodelled_0A0[0x18];
	ObjectID m_attachedToObjectID;
};

// ??1BfmeParticleSystemHandle@@QAE@XZ present-unmatched
inline BfmeParticleSystemHandle::~BfmeParticleSystemHandle() throw()
{
	if (m_system)
	{
		if (m_previous)
			m_previous->m_next = m_next;
		else
			m_system->m_firstHandle = m_next;
		if (m_next)
			m_next->m_previous = m_previous;
		else
			m_system->m_lastHandle = m_previous;
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

// ??0BfmeParticleSystemHandle@@QAE@PBUBfmeParticleSystemNode@@@Z absent-from-retail
inline BfmeParticleSystemHandle::BfmeParticleSystemHandle(
	const BfmeParticleSystemNode *node)
{
	m_system = node->m_value.m_system;
	if (m_system)
	{
		m_previous = m_system->m_lastHandle;
		m_next = 0;
		m_system->m_lastHandle = this;
		if (m_previous)
			m_previous->m_next = this;
		else
			m_system->m_firstHandle = this;
	}
	else
	{
		m_next = 0;
		m_previous = 0;
	}
}

class BfmeParticleSystemIterator
{
public:
	BfmeParticleSystemIterator(BfmeParticleSystemNode *node) : m_node(node) { }
	BfmeParticleSystemHandle &operator*() const { return m_node->m_value; }
	BfmeParticleSystemIterator operator++(int)
	{
		BfmeParticleSystemIterator old(*this);
		m_node = m_node->m_next;
		return old;
	}

	BfmeParticleSystemNode *m_node;
};

class BfmeParticleSystemList
{
	friend class ParticleSystemManager;
	BfmeParticleSystemNode *m_node;
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_unmodelled_000[0x74];
	ObjectID m_id;
};

class ParticleSystemManager
{
public:
	void destroyAttachedSystems(Object *obj);

private:
	unsigned char m_unmodelled_000[0x80];
	BfmeParticleSystemList m_systems;
};

// ?destroyAttachedSystems@ParticleSystemManager@@QAEXPAVObject@@@Z
void ParticleSystemManager::destroyAttachedSystems(Object *obj)
{
	if (obj == 0)
		return;

	BfmeParticleSystemIterator it(m_systems.m_node->m_next);
	while (it.m_node != m_systems.m_node)
	{
		BfmeParticleSystemNode *current = it.m_node;
		it++;
		BfmeParticleSystemHandle system(current);
		if (!system)
			continue;

		if (system->getAttachedObject() == obj->getID())
			system->destroy();
	}
}
