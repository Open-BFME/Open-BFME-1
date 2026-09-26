// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString
{
public:
	bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}

	void *m_data;
};

namespace FXParticleSystem { class ParticleSystem; }

class ParticleSystemHandle;

namespace FXParticleSystem {
class ParticleSystem
{
public:
	unsigned char m_pad[0x98];
	ParticleSystemHandle *m_firstHandle;
	ParticleSystemHandle *m_lastHandle;
};
}

class ParticleSystemHandle
{
public:
	ParticleSystemHandle() : m_system(0), m_previous(0), m_next(0) {}
	ParticleSystemHandle(const ParticleSystemHandle &that) throw()
		: m_system(that.m_system)
	{
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
	ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw();
	~ParticleSystemHandle() throw();

	FXParticleSystem::ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

template <class T>
class TrackingPtr : public ParticleSystemHandle
{
public:
	TrackingPtr() {}
	TrackingPtr(const TrackingPtr &that) throw() : ParticleSystemHandle(that) {}
	TrackingPtr(const ParticleSystemHandle &that) throw() : ParticleSystemHandle(that) {}
	TrackingPtr &operator=(const ParticleSystemHandle &that) throw()
	{
		ParticleSystemHandle::operator=(that);
		return *this;
	}
};

namespace FXParticleSystem {

class ParticleSystemTemplate;

class TemplateMap
{
public:
	struct Node { void *unused0; void *unused1; ParticleSystemTemplate *value; };
	Node *find(const AsciiString *name);
};

class ParticleSystemManager
{
public:
	ParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves) throw();

	unsigned char m_pad[0x9c];
	TemplateMap m_templates;
};

extern ParticleSystemManager *TheParticleSystemManager;

class ParticleSystemTemplate
{
public:
	TrackingPtr<ParticleSystem> createSlaveSystem(bool createSlaves) const;

private:
	virtual ~ParticleSystemTemplate();
	unsigned char m_pad0[0x64];
	AsciiString m_slaveSystemName;
	unsigned char m_pad1[0x30];
	mutable ParticleSystemTemplate *m_slaveTemplate;
};

TrackingPtr<ParticleSystem> ParticleSystemTemplate::createSlaveSystem(bool createSlaves) const
{
	TrackingPtr<ParticleSystem> slave;
	if (m_slaveTemplate == 0)
	{
		void *nameData = m_slaveSystemName.m_data;
		unsigned int slaveSystemNameAddress = (unsigned int)this + 0x68;
		if (nameData != 0 && *(const unsigned short *)((const char *)nameData + 4) != 0)
		{
			ParticleSystemTemplate *resolvedTemplate = 0;
			ParticleSystemManager *manager = TheParticleSystemManager;
			TemplateMap *templates = &manager->m_templates;
			TemplateMap::Node *node = templates->find((const AsciiString *)slaveSystemNameAddress);
			if (node)
				resolvedTemplate = node->value;
			m_slaveTemplate = resolvedTemplate;
			if (m_slaveTemplate)
				slave = TheParticleSystemManager->createParticleSystem(m_slaveTemplate, createSlaves);
		}
	}
	return slave;
}

}
