// ?d_005ce090@@YAXXZ
// partial score=0.25 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc

class ParticleSystem;
ParticleSystem *Make00001B18();

namespace FXParticleSystem {
class __declspec(novtable) ParticleSystemInfo {
public:
    virtual ~ParticleSystemInfo();
};
}

class ParticleSystemHandle {
public:
    ParticleSystemHandle(ParticleSystem *system = 0);
    ParticleSystemHandle &operator=(const ParticleSystemHandle &) throw();
    ~ParticleSystemHandle() throw();
    operator bool() const {
        return m_system != 0;
    }
    ParticleSystem *operator->() const {
        ParticleSystem *system = m_system;
        if (!system)
            system = Make00001B18();
        return system;
    }
    ParticleSystem *m_system;
    ParticleSystemHandle *m_previous;
    ParticleSystemHandle *m_next;
};

class BFMERetailAsciiString {
public:
    ~BFMERetailAsciiString() { releaseBuffer(); }
    void clear() { releaseBuffer(); }

private:
    void releaseBuffer();
    unsigned char m_pad[8];
};

class BfmeThingOF {
public:
    void bfmeUnlinkOF();
};

class Particle {
public:
    virtual ~Particle();
    void deleteInstance() { delete this; }
};

class Gen_uwm_00031692 {
public:
    ~Gen_uwm_00031692();
    unsigned int m_0;
    unsigned int m_4;
};

struct Rva005C6730Key {
    ParticleSystem *m_system;
};

class Rva005C6730List {
public:
    void erase(Rva005C6730Key *key);

private:
    unsigned char m_pad[0x80];
    void *m_sentinel;
    unsigned char m_tail[8];
    int m_count;
};

class ParticleSystemManager : public Rva005C6730List {
};

extern ParticleSystemManager *TheParticleSystemManager;

class __declspec(novtable) ParticleSystem : public FXParticleSystem::ParticleSystemInfo {
public:
    friend class ParticleSystemHandle;
    unsigned int getSystemID() const {
        return *reinterpret_cast<const unsigned int *>(
            reinterpret_cast<const unsigned char *>(this) + 0xac);
    }

    void setSlave(ParticleSystem *slave);
    void setMaster(ParticleSystem *master);

protected:
    virtual ~ParticleSystem();

private:
    unsigned char m_pad_04[0x94];
    ParticleSystemHandle *m_firstHandle;
    ParticleSystemHandle *m_lastHandle;
    Particle *m_systemParticlesHead;
    Particle *m_systemParticlesTail;
    unsigned char m_pad_ac[0x0c];
    unsigned int m_attachedToDrawableID;
    unsigned int m_attachedToObjectID;
    BFMERetailAsciiString m_attachedSystemName;
    unsigned char m_pad_c4[0x9c];
    ParticleSystemHandle m_slaveSystem;
    unsigned int m_slaveSystemID;
    ParticleSystemHandle m_masterSystem;
    unsigned int m_masterSystemID;
    unsigned char m_pad_180[0x20];
    BfmeThingOF *m_controlParticle;
    unsigned char m_pad_1a4[0x0c];
    Gen_uwm_00031692 m_member;
};

ParticleSystemHandle::ParticleSystemHandle(ParticleSystem *system)
    : m_system(system), m_previous(0), m_next(0) {
    if (m_system) {
        m_previous = m_system->m_lastHandle;
        m_system->m_lastHandle = this;
        if (m_previous)
            m_previous->m_next = this;
        else
            m_system->m_firstHandle = this;
    }
}

void ParticleSystem::setSlave(ParticleSystem *slave) {
    m_slaveSystem = slave;
    m_slaveSystemID = slave ? slave->getSystemID() : 0;
}

void ParticleSystem::setMaster(ParticleSystem *master) {
    m_masterSystem = master;
    m_masterSystemID = master ? master->getSystemID() : 0;
}

ParticleSystem::~ParticleSystem() {
    *(volatile void **)this = (void *)0x0110FE48;
    if (m_slaveSystem) {
        {
            ParticleSystemHandle empty(0);
            ParticleSystem *slave = m_slaveSystem.operator->();
            slave->m_masterSystem = empty;
            slave->m_masterSystemID = 0;
        }
        {
            ParticleSystemHandle empty(0);
            m_slaveSystem = empty;
            m_slaveSystemID = 0;
        }
    }
    if (m_masterSystem) {
        {
            ParticleSystemHandle empty(0);
            ParticleSystem *master = m_masterSystem.operator->();
            master->m_slaveSystem = empty;
            master->m_slaveSystemID = 0;
        }
        {
            ParticleSystemHandle empty(0);
            m_masterSystem = empty;
            m_masterSystemID = 0;
        }
    }
    while (m_systemParticlesHead)
        m_systemParticlesHead->deleteInstance();
    m_attachedToDrawableID = 0;
    m_attachedToObjectID = 0;
    m_attachedSystemName.clear();
    if (m_controlParticle)
        m_controlParticle->bfmeUnlinkOF();
    m_controlParticle = 0;
    ParticleSystemHandle key(this);
    TheParticleSystemManager->erase(
        reinterpret_cast<Rva005C6730Key *>(&key));
}
