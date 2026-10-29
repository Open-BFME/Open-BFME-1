// ??0ParticleSystem@@QAE@PBVParticleSystemTemplate@@W4ParticleSystemID@@_N@Z
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#define _STLP_NO_EXCEPTIONS 1
// stlport
// This unit's local ParticleSystem view defines getSystemID inline at its own offset
// (not +0x268) and emits that COMDAT copy; rename it so only retail's 0x0049C950
// (reads +0x268) carries the name. Inlined calls are unchanged.
#define getSystemID getSystemID_LocalView
#include "ascii_string.h"
#include "game_client_random_variable.h"
#include <list>
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"

typedef unsigned int UnsignedInt;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

namespace FXParticleSystem {
class ParticleSystemInfo {
public:
    ParticleSystemInfo();
    virtual ~ParticleSystemInfo();
    unsigned char m_tail[0x94];
};
class ParticleSystem;
}

class ParticleSystem;
class Particle;
class ParticleInfo;
class Xfer;
enum ParticlePriorityType;
// The null-system accessor (ILT 0x00001B18 -> 0x005CFF50) is defined only as
// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ; its real name is unproven.
class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();

class ParticleSystemHandle {
public:
    ParticleSystemHandle() : m_system(0), m_previous(0), m_next(0) {}
    ParticleSystemHandle(ParticleSystem *system);
    ParticleSystemHandle(const ParticleSystemHandle &that) throw();
    ~ParticleSystemHandle() throw();
    ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw();
    operator bool() const { return m_system != 0; }
    ParticleSystem *operator->() const { return m_system ? m_system : (ParticleSystem *)bfmeNullSystemZA(); }
    ParticleSystem *m_system;
    ParticleSystemHandle *m_previous;
    ParticleSystemHandle *m_next;
};

class BfmeParticleSystemHandle : public ParticleSystemHandle {
public:
    BfmeParticleSystemHandle(ParticleSystem *system) throw();
};

template <class T> class TrackingPtr : public ParticleSystemHandle {
public:
    TrackingPtr() {}
    TrackingPtr(::ParticleSystem *system) : ParticleSystemHandle(system) {}
    __forceinline TrackingPtr(const TrackingPtr &that) throw() : ParticleSystemHandle(that) {}
};

namespace FXParticleSystem {
class ParticleSystemTemplate {
public:
    TrackingPtr<ParticleSystem> createSlaveSystem(bool) const;
};
}

class ParticleTemplateSlotView {
public:
    virtual void unusedSlot();
    virtual void unusedSlot1();
    virtual void *unknownSlot2(const ParticleSystemHandle &system) const;
};

class ParticleSystemTemplate {
public:
    virtual ~ParticleSystemTemplate();
    unsigned char m_fields[0xA0];
};

class U1Supplier_005CF1F0;
class U1Rest_005CF1F0 {
public:
    void collect(void *first, U1Supplier_005CF1F0 *second);
    void *m_values[10];
};

class BigChainVictim {
public:
    virtual ~BigChainVictim();
};

class BigChainHold {
public:
    BigChainHold() : m_p(0) {}
    ~BigChainHold() { if (m_p) delete m_p; }
    BigChainVictim *m_p;
};

class Rva005C6A40 {
public:
    ~Rva005C6A40();
    std::vector<BigChainVictim *> m_values;
};

class Rva005C91C0 : public BigChainHold, public Rva005C6A40 {
public:
    ~Rva005C91C0();
};

class Rva005C9E30 : public BigChainHold, public Rva005C91C0 {
public:
    ~Rva005C9E30();
};

class Rva005CB030 : public BigChainHold, public Rva005C9E30 {
public:
    ~Rva005CB030();
};

class Rva005CBD40 : public BigChainHold, public Rva005CB030 {
public:
    ~Rva005CBD40();
};

class Rva005CC980 : public BigChainHold, public Rva005CBD40 {
public:
    ~Rva005CC980();
};

class Rva005CD660 : public BigChainHold, public Rva005CC980 {
public:
    ~Rva005CD660();
};

class Rva005CDB10 : public BigChainHold, public Rva005CD660 {
public:
    ~Rva005CDB10();
};

class Rva005CDFF0 : public BigChainHold, public Rva005CDB10 {
public:
    ~Rva005CDFF0();
    BigChainVictim *&module() { return *reinterpret_cast<BigChainVictim **>(this); }
};


class GameClient {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual UnsignedInt getFrame();
};
extern GameClient *TheGameClient;

class ParticleSystemManager {
public:
    void friend_addParticleSystem(const TrackingPtr<FXParticleSystem::ParticleSystem> &system);
    unsigned char m_beforeList[0x80];
    std::list<TrackingPtr<FXParticleSystem::ParticleSystem> > m_systemList;
    unsigned int m_particleCount;
    unsigned int m_fieldParticleCount;
    unsigned int m_particleSystemCount;
};
extern ParticleSystemManager *TheParticleSystemManager;

template <typename T>
static inline T &particle_field(void *object, unsigned int offset)
{
	return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(object) + offset);
}

template <typename T>
static inline const T &particle_field(const void *object, unsigned int offset)
{
	return *reinterpret_cast<const T *>(reinterpret_cast<const unsigned char *>(object) + offset);
}

template <typename T>
static inline void particle_copy(void *destination, unsigned int destinationOffset,
	const void *source, unsigned int sourceOffset)
{
	particle_field<T>(destination, destinationOffset) = particle_field<const T>(source, sourceOffset);
}


class ParticleSystem : public FXParticleSystem::ParticleSystemInfo {
public:
    ParticleSystem(const ParticleSystemTemplate *systemTemplate, ParticleSystemID id, bool createSlaves);
protected:
    virtual ~ParticleSystem();
    virtual void loadPostProcess();
    virtual const char *Rva005CE3A0_name() const;
public:
    virtual void DoXfer(Xfer &);
    virtual bool update(int);
protected:
    virtual Particle *createParticle(const ParticleInfo *, ParticlePriorityType, bool);
public:
    ParticleSystemID getSystemID() const { return m_systemID; }
    void setSlave(const ParticleSystemHandle &slave) {
        m_slaveSystem = slave;
        m_slaveSystemID = slave.m_system ? slave.m_system->getSystemID() : INVALID_PARTICLE_SYSTEM_ID;
    }
    void setMaster(const ParticleSystemHandle &master) {
        m_masterSystem = master;
        m_masterSystemID = master.m_system ? master.m_system->getSystemID() : INVALID_PARTICLE_SYSTEM_ID;
    }
    ParticleSystemHandle *m_firstHandle;
    ParticleSystemHandle *m_lastHandle;
    void *m_systemParticlesHead;
    void *m_systemParticlesTail;
    UnsignedInt m_particleCount;
    ParticleSystemID m_systemID;
    UnsignedInt m_fieldB0;
    UnsignedInt m_attachedToDrawableID;
    UnsignedInt m_attachedToObjectID;
    AsciiString m_nameBC;
    Matrix3D m_localTransform;
    Matrix3D m_transform;
    unsigned char m_fields120[0x160 - 0x120];
    ParticleSystemHandle m_slaveSystem;
    ParticleSystemID m_slaveSystemID;
    ParticleSystemHandle m_masterSystem;
    ParticleSystemID m_masterSystemID;
    unsigned char m_fields180[0x19C - 0x180];
    const ParticleSystemTemplate *m_template;
    void *m_controlParticle;
    bool m_isLocalIdentity;
    bool m_isIdentity;
    bool m_isForever;
    bool m_isStopped;
    bool m_isDestroyed;
    bool m_isFirstPos;
    bool m_isSaveable;
    bool m_field1AB;
    bool m_skipParentXfrm;
    unsigned char m_fields1AD[3];
    Rva005CDFF0 m_member1B0;
    unsigned char m_fields1DC[4];
};

// ??0ParticleSystemHandle@@QAE@PAVParticleSystem@@@Z absent-from-retail
inline ParticleSystemHandle::ParticleSystemHandle(ParticleSystem *system) : m_system(system) {
    if (m_system) {
        m_previous = m_system->m_lastHandle;
        m_next = 0;
        m_system->m_lastHandle = this;
        if (m_previous) m_previous->m_next = this;
        else m_system->m_firstHandle = this;
    } else {
        m_next = 0;
        m_previous = 0;
    }
}

// ??0ParticleSystemHandle@@QAE@ABV0@@Z absent-from-retail
__forceinline ParticleSystemHandle::ParticleSystemHandle(const ParticleSystemHandle &that) throw() {
    m_system = that.m_system;
    ParticleSystem *system = that.m_system;
    if (system) {
        m_previous = system->m_lastHandle;
        m_next = 0;
        system->m_lastHandle = this;
        if (m_previous) m_previous->m_next = this;
        else m_system->m_firstHandle = this;
    } else {
        m_next = 0;
        m_previous = 0;
    }
}

inline void ParticleSystemManager::friend_addParticleSystem(const TrackingPtr<FXParticleSystem::ParticleSystem> &system) {
    m_systemList.push_back(system);
    ++m_particleSystemCount;
}

struct Rva005CF850Triple { unsigned int a, b, c; };
struct Rva005CF850Quad { unsigned int a, b, c, d; };

// ??0ParticleSystem@@QAE@PBVParticleSystemTemplate@@W4ParticleSystemID@@_N@Z
ParticleSystem::ParticleSystem(const ParticleSystemTemplate *systemTemplate,
	ParticleSystemID id, bool createSlaves)
    : m_firstHandle(0), m_lastHandle(0)
{
	unsigned int zero = 0;
	const float unit = 1.0f;


	m_systemID = id;
	m_systemParticlesTail = 0;
	m_systemParticlesHead = 0;
	m_isFirstPos = true;
	m_template = systemTemplate;
	particle_field<UnsignedInt>(this, 0x154) = zero;
	particle_field<UnsignedInt>(this, 0x158) = zero;
	particle_field<UnsignedInt>(this, 0x15C) = zero;
	particle_field<UnsignedInt>(this, 0x148) = zero;
	particle_field<UnsignedInt>(this, 0x14C) = zero;
	particle_field<UnsignedInt>(this, 0x150) = zero;
	particle_field<UnsignedInt>(this, 0x134) = zero;
	particle_field<UnsignedInt>(this, 0x138) = zero;
	particle_field<UnsignedInt>(this, 0x13C) = zero;
	m_attachedToDrawableID = 0;
	m_attachedToObjectID = 0;

	m_isLocalIdentity = true;
	m_localTransform.Make_Identity();
	m_isIdentity = true;
	m_transform.Make_Identity();
	m_isStopped = false;
	m_isDestroyed = false;
	m_isSaveable = true;
	m_field1AB = false;

	particle_copy<Rva005CF850Triple>(this, 0x6C, systemTemplate, 0x6C);
	particle_field<float>(this, 0x134) = unit;
	particle_field<float>(this, 0x138) = unit;
	particle_field<float>(this, 0x13C) = unit;
	particle_field<float>(this, 0x140) = unit;
	particle_field<float>(this, 0x144) = unit;
	particle_field<float>(this, 0x180) = unit;
	particle_field<float>(this, 0x188) = unit;
	particle_field<UnsignedInt>(this, 0x40) = zero;
	particle_field<UnsignedInt>(this, 0x18C) = zero;
	particle_field<UnsignedInt>(this, 0x190) = zero;
	particle_field<UnsignedInt>(this, 0x194) = zero;
	particle_field<unsigned char>(this, 0x198) = zero;

	particle_copy<Rva005CF850Triple>(this, 0x14, systemTemplate, 0x14);
	particle_copy<Rva005CF850Triple>(this, 0x28, systemTemplate, 0x28);
	particle_copy<Rva005CF850Triple>(this, 0x34, systemTemplate, 0x34);
	particle_copy<Rva005CF850Triple>(this, 0x44, systemTemplate, 0x44);
	particle_field<UnsignedInt>(this, 0x120) = zero;
	particle_copy<Rva005CF850Triple>(this, 0x50, systemTemplate, 0x50);

	particle_field<unsigned char>(this, 0x04) = particle_field<const unsigned char>(systemTemplate, 0x04);

	particle_field<UnsignedInt>(this, 0x124) = static_cast<UnsignedInt>(
		particle_field<const GameClientRandomVariable>(systemTemplate, 0x5C).getValue());
	particle_field<UnsignedInt>(this, 0x128) = TheGameClient->getFrame();
	particle_copy<unsigned int>(this, 0x12C, systemTemplate, 0x20);
    m_isForever = particle_field<const unsigned int>(systemTemplate, 0x20) == 0;
    particle_copy<unsigned int>(this, 0x24, systemTemplate, 0x24);
    particle_field<UnsignedInt>(this, 0x184) = zero;
    particle_copy<unsigned int>(this, 0x7C, systemTemplate, 0x7C);
    particle_copy<unsigned char>(this, 0x80, systemTemplate, 0x80);
    particle_copy<unsigned char>(this, 0x81, systemTemplate, 0x81);
    particle_copy<unsigned char>(this, 0x82, systemTemplate, 0x82);
    particle_copy<unsigned char>(this, 0x83, systemTemplate, 0x83);
    particle_copy<unsigned int>(this, 0x08, systemTemplate, 0x08);
    particle_copy<unsigned int>(this, 0x0C, systemTemplate, 0x0C);
    particle_field<AsciiString>(this, 0x10) = particle_field<const AsciiString>(systemTemplate, 0x10);
    m_isStopped = false;
    m_masterSystemID = INVALID_PARTICLE_SYSTEM_ID;
    m_slaveSystemID = INVALID_PARTICLE_SYSTEM_ID;
    if (createSlaves) {
        TrackingPtr<FXParticleSystem::ParticleSystem> slave =
            reinterpret_cast<const FXParticleSystem::ParticleSystemTemplate *>(systemTemplate)->createSlaveSystem(true);
        if (slave) {
            setSlave(slave);
            m_slaveSystem->setMaster(BfmeParticleSystemHandle(this));
        }
    }
    particle_field<AsciiString>(this, 0x78) = particle_field<const AsciiString>(systemTemplate, 0x78);
	m_particleCount = 0;
	m_fieldB0 = 0;
	particle_field<UnsignedInt>(this, 0x130) = zero;
	m_controlParticle = 0;
	m_skipParentXfrm = false;
    particle_copy<Rva005CF850Quad>(this, 0x84, systemTemplate, 0x84);
    {
        ParticleSystemHandle system(this);
        ParticleTemplateSlotView *provider = particle_field<ParticleTemplateSlotView *>(systemTemplate, 0xA0);
        m_member1B0.module() = static_cast<BigChainVictim *>(provider ? provider->unknownSlot2(system) : 0);
        reinterpret_cast<U1Rest_005CF1F0 *>(reinterpret_cast<unsigned char *>(&m_member1B0) + 4)->collect(&system, (U1Supplier_005CF1F0 *)systemTemplate);
    }
    TheParticleSystemManager->friend_addParticleSystem(TrackingPtr<FXParticleSystem::ParticleSystem>(this));
}
