// cl: /DNDEBUG /MD /EHsc
// readable body of ??1LaserUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp
//
// LaserUpdate::~LaserUpdate — retail 0x00603820 (118B).
// Zero Hour source: GeneralsMD/.../LaserUpdate.cpp
// Destroy the two particle-system IDs at +0x28/+0x2C through
// TheParticleSystemManager, then the ClientUpdateModule base.
// Ctor at 0x00603790 (??0Rva603790Ctor) installs the same vtable
// 0x01115370; name getter at 0x00603810 returns "LaserUpdate".

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class Rva0002B8C8TailBase
{
public:
	virtual ~Rva0002B8C8TailBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ClientUpdateModule.h
class ClientUpdateModule : public Rva0002B8C8TailBase
{
public:
	virtual ~ClientUpdateModule() {}
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
	virtual void clientUpdate();

private:
	char m_pad04[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h
class LaserUpdate : public ClientUpdateModule
{
public:
	virtual ~LaserUpdate();
	virtual void clientUpdate();

private:
	char m_pad0C[0x28 - 0x0C];
	ParticleSystemID m_particleSystemID;
	ParticleSystemID m_targetParticleSystemID;
};

// ??1LaserUpdate@@UAE@XZ
LaserUpdate::~LaserUpdate()
{
	if (m_particleSystemID)
		TheParticleSystemManager->destroyParticleSystemByID(m_particleSystemID);
	if (m_targetParticleSystemID)
		TheParticleSystemManager->destroyParticleSystemByID(m_targetParticleSystemID);
}
