class ParticleSystemHandle;
class ParticleSystem
{
public:
	char m_pad[0x98];
	ParticleSystemHandle *m_firstHandle;
	ParticleSystemHandle *m_lastHandle;
};
class ParticleSystemHandle
{
public:
	ParticleSystemHandle() : m_system(0), m_previous(0), m_next(0) {}
	ParticleSystemHandle(const ParticleSystemHandle &that);
	~ParticleSystemHandle() throw();
	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};
// ??0ParticleSystemHandle@@QAE@ABV0@@Z absent-from-retail
// The copy helper is emitted to keep the by-value getter's member-copy ABI;
// retail contains the helper inline in this body and has no separate claim.
inline ParticleSystemHandle::ParticleSystemHandle(const ParticleSystemHandle &that)
{
	ParticleSystem *system = that.m_system;
	m_system = system;
	if (system)
	{
		m_previous = system->m_lastHandle;
		m_next = 0;
		system->m_lastHandle = this;
		if (m_previous) m_previous->m_next = this;
		else m_system->m_firstHandle = this;
	}
	else { m_next = 0; m_previous = 0; }
}
class Gen0060C510Target {
public: ParticleSystemHandle getParticleSystem();
private: char m_pad[0x14]; ParticleSystemHandle m_particleSystem;
};
ParticleSystemHandle Gen0060C510Target::getParticleSystem() { return m_particleSystem; }
