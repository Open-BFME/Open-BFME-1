// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x005C33E0 creates a particle system and returns an intrusive handle.
// The manager method at 0x005C3A30 calls this helper through ILT 0x000209DC.

class ParticleSystemTemplate;
class ParticleSystemHandle;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem
{
public:
	ParticleSystem(const ParticleSystemTemplate *systemTemplate, ParticleSystemID id,
		bool createSlaves);
	virtual ~ParticleSystem();

	unsigned char m_bfmeHead[0x94];
	ParticleSystemHandle *m_firstHandle;
	ParticleSystemHandle *m_lastHandle;
	unsigned char m_bfmeTail[0x1e0 - 0xa0];
};

class ParticleSystemHandle
{
public:
	ParticleSystemHandle(ParticleSystem *system)
		: m_system(system)
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
	~ParticleSystemHandle();

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

ParticleSystemHandle makeParticleSystemHandle005C33E0(
	const ParticleSystemTemplate *systemTemplate,
	ParticleSystemID id, bool createSlaves)
{
	return ParticleSystemHandle(new ParticleSystem(systemTemplate, id, createSlaves));
}
