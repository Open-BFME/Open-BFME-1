// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: ParticleSystem::setMaster, retail 0x005C3590 (56 bytes).
// The public BFME ParticleSystem is an intrusive handle: its first pointer
// selects the implementation object whose system ID is at +0xAC.  The master
// handle and saved ID occupy +0x170 and +0x17C in the owning implementation.
// Identity: the reference ParticleSys.cpp names this exact method and field
// update; the ILT at 0x0002D4BB targets this body, while its only call targets
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
	void setMaster(ParticleSystem *master);
	ParticleSystemID getSystemID() const
	{
		return m_system->m_systemID;
	}

private:
	unsigned char m_beforeMasterSystem[0x170 - sizeof(ParticleSystemHandle)];
	ParticleSystemHandle m_masterSystem;
	ParticleSystemID m_masterSystemID;
};

void ParticleSystem::setMaster(ParticleSystem *master)
{
	m_masterSystem = *master;
	m_masterSystemID = master->m_system ? master->getSystemID() : 0;
}
