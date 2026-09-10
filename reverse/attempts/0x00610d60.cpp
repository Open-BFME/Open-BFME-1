// ?d_00610d60@@YAXXZ
// partial score=0.8 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Walks the manager's two target lists and gives every target that has no
// particle system yet one built from the matching template name.

typedef bool Bool;

enum { FALSE = 0, TRUE = 1 };

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Gen0060CBB0Coord3D
{
	float x;
	float y;
	float z;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	char *m_data;

private:
	void releaseBuffer();
};

class AsciiString
{
public:
	char *m_data;
};

class ParticleSystemTemplate;

class ParticleSystemHandle;

class ParticleSystem
{
public:
	void setPosition(const Coord3D *position);
	void setField94(void *value);
	void start();

	unsigned char m_pad00[0x98];
	ParticleSystemHandle *m_firstHandle;
	ParticleSystemHandle *m_lastHandle;
};

ParticleSystem *Make00001B18(void);

class ParticleSystemHandle
{
public:
	~ParticleSystemHandle() throw()
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

	operator Bool() const
	{
		return m_system != 0;
	}

	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make00001B18();
	}

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class BfmeParticleSystemHandle : public ParticleSystemHandle
{
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *sysTemplate, Bool createSlaves) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

class Gen0060C510Target
{
public:
	ParticleSystemHandle getParticleSystem();
	void getPosition(Gen0060CBB0Coord3D *position);
	void attachParticleSystem(BfmeParticleSystemHandle *handle, Coord3D origin);
	void adoptParticleSystem(BfmeParticleSystemHandle *handle);
};

struct Gen0060C510TargetVector
{
	unsigned int size(void) const
	{
		return (unsigned int)(m_finish - m_start);
	}

	Gen0060C510Target *operator[](unsigned int index) const
	{
		return m_start[index];
	}

	Gen0060C510Target **m_start;
	Gen0060C510Target **m_finish;
	Gen0060C510Target **m_endOfStorage;
};

class Gen_00609320
{
public:
	unsigned char m_pad[8];
	volatile unsigned char m_enabled;
};

extern Gen_00609320 *g_bfmeStateDF;

class BfmeLivingWorldManager
{
public:
	void rva00610d60();

private:
	unsigned char m_pad00[0xC4];
	BFMERetailAsciiString m_secondaryName;
	Coord3D m_origin;
	unsigned char m_padD4[0x2C];
	BFMERetailAsciiString m_primaryName;
	unsigned char m_pad104[0x13C];
	Gen0060C510TargetVector m_primaryTargets;
	Gen0060C510TargetVector m_secondaryTargets;
};

void BfmeLivingWorldManager::rva00610d60()
{
	register unsigned char enabled = g_bfmeStateDF->m_enabled;
	if (enabled != FALSE)
	{
		for (unsigned int i = 0; i < m_secondaryTargets.size(); ++i)
		{
			if (!m_secondaryTargets[i]->getParticleSystem())
			{
				ParticleSystemTemplate *sysTemplate;
				{
					const char *name = m_secondaryName.m_data
						? m_secondaryName.m_data + 8
						: "";
					BFMERetailAsciiString particleSystemName(name);
					sysTemplate = TheParticleSystemManager->findTemplate(
						*(const AsciiString *)&particleSystemName);
				}
				if (sysTemplate)
				{
					BfmeParticleSystemHandle created =
						TheParticleSystemManager->createParticleSystem(
							sysTemplate, TRUE);
					if (created)
					{
						Gen0060CBB0Coord3D position;
						m_secondaryTargets[i]->getPosition(&position);
						created->setPosition((const Coord3D *)&position);
						created->setField94((void *)1);
						created->start();
						m_secondaryTargets[i]->attachParticleSystem(
							&created, m_origin);
					}
				}
			}
		}

		for (unsigned int i = 0; i < m_primaryTargets.size(); ++i)
		{
			if (!m_primaryTargets[i]->getParticleSystem())
			{
				ParticleSystemTemplate *sysTemplate;
				{
					const char *name = m_primaryName.m_data
						? m_primaryName.m_data + 8
						: "";
					BFMERetailAsciiString particleSystemName(name);
					sysTemplate = TheParticleSystemManager->findTemplate(
						*(const AsciiString *)&particleSystemName);
				}
				if (sysTemplate)
				{
					BfmeParticleSystemHandle created =
						TheParticleSystemManager->createParticleSystem(
							sysTemplate, TRUE);
					if (created)
					{
						Gen0060CBB0Coord3D position;
						m_primaryTargets[i]->getPosition(&position);
						created->setPosition((const Coord3D *)&position);
						created->setField94((void *)1);
						created->start();
						m_primaryTargets[i]->adoptParticleSystem(
							&created);
					}
				}
			}
		}
	}
}
