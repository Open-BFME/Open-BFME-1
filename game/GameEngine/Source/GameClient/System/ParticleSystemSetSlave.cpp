// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: ParticleSystem::setSlave, retail 0x005C35E0 (56 bytes).
// The public BFME ParticleSystem is an intrusive handle: its first pointer
// selects the implementation object whose system ID is at +0xAC.  The slave
// handle and saved ID occupy +0x160 and +0x16C in the owning implementation.
// Identity: the reference ParticleSys.cpp names this exact method and field
// update; the ILT at 0x00038B59 targets this body, while its only call targets
// the pinned ParticleSystemHandle assignment ILT at 0x0000FA3D.

typedef unsigned int ParticleSystemID;

class ParticleSystemData
{
public:
	unsigned char m_beforeSystemID[0xAC];
	ParticleSystemID m_systemID;
};

class ParticleSystemHandle
{
public:
	ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw();

	ParticleSystemData *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class ParticleSystem : public ParticleSystemHandle
{
public:
	void setSlave(ParticleSystem *slave);
	ParticleSystemID getSystemID() const
	{
		return m_system->m_systemID;
	}

private:
	unsigned char m_beforeSlaveSystem[0x160 - sizeof(ParticleSystemHandle)];
	ParticleSystemHandle m_slaveSystem;
	ParticleSystemID m_slaveSystemID;
};

void ParticleSystem::setSlave(ParticleSystem *slave)
{
	m_slaveSystem = *slave;
	m_slaveSystemID = slave->m_system ? slave->getSystemID() : 0;
}
