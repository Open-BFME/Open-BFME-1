// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ParticleSystem::~ParticleSystem, retail 0x005CE090 (623 bytes).
// Identity: installs ParticleSystem's vftable 0x0110FE48, and its only caller
// is the matched scalar-deleting destructor ??_GParticleSystem (0x005CEAB0).
// Body is Zero Hour's ParticleSys.cpp destructor on BFME's intrusive
// ParticleSystemHandle (system/prev/next; the system keeps the handle chain at
// +0x98/+0x9C, walked by the final detach loop). Offsets follow the matched
// siblings setSlave/setMaster (0x005C35E0/0x005C3590, handles at +0x160/+0x170,
// system ID at +0xAC) and loadPostProcess (0x005C5100).
// Retail EH map (tools/eh_info.py): members +0xBC string, +0x160, +0x170,
// +0x1B0 in states 1-4; states 5-9 are sibling handle temporaries. The handle
// destructor is throw() (no states before the member handle destructors).
// The call through operator-> stores a constant ID (no reload of the null
// handle across emptyParticleSystem), modelled by the two-argument setter; the
// calls on this keep ZH's one-argument form, whose folded getSystemID branch
// leaves retail's allocated-but-never-stored states 6 and 8.
// +0x1A0 is a pointer detached through 0x005C3010 (matched as
// BfmeThingOF::bfmeUnlinkOF, it releases a handle at +0x7C of the pointee),
// i.e. ZH's m_controlParticle; the name oracle's m_systemLifetimeLeft witness
// for +0x1A0 comes only from a 13-byte store-only setter (0x005BE2E0).
// The +0x9C..+0xB0 and +0xBC names not witnessed elsewhere keep neutral or ZH
// spellings; m_nameBC keeps its offset.
#include "ascii_string.h"

typedef unsigned int ParticleSystemID;
typedef unsigned int DrawableID;
typedef unsigned int ObjectID;

class ParticleSystem;
ParticleSystem *emptyParticleSystem();

class ParticleSystemHandle
{
public:
	ParticleSystemHandle(ParticleSystem *system = 0);
	~ParticleSystemHandle() throw();
	ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw();
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (m_system == 0)
			return emptyParticleSystem();
		return m_system;
	}
	void release();

	ParticleSystem *m_system;
	ParticleSystemHandle *m_prev;
	ParticleSystemHandle *m_next;
};

namespace FXParticleSystem {
class ParticleSystemInfo
{
public:
	virtual ~ParticleSystemInfo();
	unsigned char m_info[0x94];
};
}

class Particle
{
public:
	virtual ~Particle();
	void deleteInstance() { delete this; }
};

class BfmeThingOF
{
public:
	void bfmeUnlinkOF();
};

class Rva005CDFF0
{
public:
	~Rva005CDFF0();
	unsigned char m_data[8];
};

struct Rva005C6730Key;
class Rva005C6730List
{
public:
	void erase(Rva005C6730Key *key);
};

class ParticleSystemManager : public Rva005C6730List
{
public:
	void friend_removeParticleSystem(const ParticleSystemHandle &system)
	{
		erase((Rva005C6730Key *)&system);
	}
};

extern ParticleSystemManager *TheParticleSystemManager;

class ParticleSystem : public FXParticleSystem::ParticleSystemInfo
{
	friend class ParticleSystemHandle;

public:
	ParticleSystemID getSystemID() const { return m_systemID; }
	void setSlave(const ParticleSystemHandle &slave)
	{
		ParticleSystemID slaveID = slave ? slave->getSystemID() : 0;
		m_slaveSystem = slave;
		m_slaveSystemID = slaveID;
	}
	void setMaster(const ParticleSystemHandle &master)
	{
		ParticleSystemID masterID = master ? master->getSystemID() : 0;
		m_masterSystem = master;
		m_masterSystemID = masterID;
	}

	void setSlave(const ParticleSystemHandle &slave, ParticleSystemID slaveID)
	{
		m_slaveSystem = slave;
		m_slaveSystemID = slaveID;
	}
	void setMaster(const ParticleSystemHandle &master, ParticleSystemID masterID)
	{
		m_masterSystem = master;
		m_masterSystemID = masterID;
	}

protected:
	virtual ~ParticleSystem();

private:
	ParticleSystemHandle *m_firstHandle;		// +0x98
	ParticleSystemHandle *m_lastHandle;		// +0x9C
	Particle *m_systemParticlesHead;		// +0xA0
	Particle *m_systemParticlesTail;		// +0xA4
	unsigned int m_particleCount;			// +0xA8
	ParticleSystemID m_systemID;			// +0xAC
	unsigned int m_fieldB0;				// +0xB0
	DrawableID m_attachedToDrawableID;		// +0xB4
	ObjectID m_attachedToObjectID;			// +0xB8
	AsciiString m_nameBC;				// +0xBC
	unsigned char m_padC0[0x160 - 0xC0];
	ParticleSystemHandle m_slaveSystem;		// +0x160
	ParticleSystemID m_slaveSystemID;		// +0x16C
	ParticleSystemHandle m_masterSystem;		// +0x170
	ParticleSystemID m_masterSystemID;		// +0x17C
	unsigned char m_pad180[0x1A0 - 0x180];
	BfmeThingOF *m_controlParticle;			// +0x1A0
	unsigned char m_pad1A4[0x1B0 - 0x1A4];
	Rva005CDFF0 m_member1B0;			// +0x1B0
};

// ??0ParticleSystemHandle@@QAE@PAVParticleSystem@@@Z absent-from-retail
inline ParticleSystemHandle::ParticleSystemHandle(ParticleSystem *system)
	: m_system(system)
{
	if (m_system)
	{
		m_prev = m_system->m_lastHandle;
		m_next = 0;
		m_system->m_lastHandle = this;
		if (m_prev)
			m_prev->m_next = this;
		else
			m_system->m_firstHandle = this;
	}
	else
	{
		m_prev = 0;
		m_next = 0;
	}
}

// ?release@ParticleSystemHandle@@QAEXXZ absent-from-retail
inline void ParticleSystemHandle::release()
{
	if (m_system)
	{
		if (m_prev)
			m_prev->m_next = m_next;
		else
			m_system->m_firstHandle = m_next;
		if (m_next)
			m_next->m_prev = m_prev;
		else
			m_system->m_lastHandle = m_prev;
		m_prev = 0;
		m_next = 0;
		m_system = 0;
	}
}

ParticleSystem::~ParticleSystem()
{
	if (m_slaveSystem)
	{
		m_slaveSystem->setMaster(ParticleSystemHandle(), 0);
		setSlave(0);
	}

	if (m_masterSystem)
	{
		m_masterSystem->setSlave(ParticleSystemHandle(), 0);
		setMaster(0);
	}

	while (m_systemParticlesHead)
		m_systemParticlesHead->deleteInstance();

	m_attachedToDrawableID = 0;
	m_attachedToObjectID = 0;
	m_nameBC.clear();

	if (m_controlParticle)
		m_controlParticle->bfmeUnlinkOF();
	m_controlParticle = 0;

	TheParticleSystemManager->friend_removeParticleSystem(this);

	while (m_firstHandle)
		m_firstHandle->release();
}
