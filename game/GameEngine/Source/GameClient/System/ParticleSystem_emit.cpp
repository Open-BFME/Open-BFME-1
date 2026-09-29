// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// The matched ParticleSystem::update at 0x005D1140 calls emit through ILT 0x0003E59F.
// The body recurses through the same ILT when it emits a slave system.
// The retail ret at +0x33F proves the 834-byte extent.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include "game_client_random_variable.h"

struct Coord3D { float x, y, z; void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; } };
class ParticleSystem;
class ParticleSystemTemplate;
extern ParticleSystem *Make00001B18();

class BfmeParticleSystemHandle {
public:
    ~BfmeParticleSystemHandle() throw();
    ParticleSystem *operator->() const { return m_system ? m_system : Make00001B18(); }
    operator bool() const { return m_system != 0; }
    ParticleSystem *m_system;
    void *m_previous;
    void *m_next;
};
class U1CachedHolder;
class U1Sub { public: U1Sub &apply(U1CachedHolder *other); };
class Particle {
public:
    void controlParticleSystem(const BfmeParticleSystemHandle &sys) { m_destroySystem.apply((U1CachedHolder *)&sys); }
    unsigned char m_head[0x7c];
    U1Sub m_destroySystem;
};
class ParticleInfo {
public:
    virtual ~ParticleInfo();
    Coord3D m_value04;
    Coord3D m_vel;
    Coord3D m_pos;
};
class Rva005D0950Module {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual bool slot14();
};
class TerrainLogic {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual float getGroundHeight(float x, float y, void *normal);
};
extern TerrainLogic *TheTerrainLogic;
class AsciiString {
public:
    struct Header { int refs; unsigned short length, capacity; } *m_data;
    bool isEmpty() const { return !m_data || !m_data->length; }
};
namespace rts { template<class T> struct hash { unsigned int operator()(T value) const; }; }
bool operator==(const AsciiString &, const AsciiString &);
typedef _STL::hash_map<AsciiString, ParticleSystemTemplate *, rts::hash<AsciiString>, _STL::equal_to<AsciiString> > BfmeParticleHash;
class ParticleSystemManager {
public:
    BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *, bool);
    unsigned char m_head[0x9c];
    BfmeParticleHash m_templates;
    const ParticleSystemTemplate *findTemplate(const AsciiString &name) const {
        BfmeParticleHash::const_iterator it = m_templates.find(name);
        return it != m_templates.end() ? it->second : 0;
    }
};
extern ParticleSystemManager *TheParticleSystemManager;

class ParticleSystem {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10();
    virtual Particle *createParticle(const ParticleInfo *, int, bool);
    void emit(const Coord3D *pos, int priority, bool isIdentity, const Matrix3D *transform);
protected:
    ParticleInfo *generateParticleInfo(int, int);
public:
    void setControlParticle(Particle *p) { *(Particle **)((char *)this + 0x1a0) = p; }
    bool m_field04;
    unsigned char m_pad05[0x44-5];
    GameClientRandomVariable m_burstDelay;
    GameClientRandomVariable m_burstCount;
    unsigned char m_pad5c[0x6c-0x5c];
    Coord3D m_slavePosOffset;
    AsciiString m_attachedSystemName;
    int m_priority;
    bool m_isGroundAligned;
    bool m_isEmitAboveGroundOnly;
    unsigned char m_pad82[0xf0-0x82];
    Matrix3D m_transform;
    unsigned int m_burstDelayLeft;
    unsigned char m_pad124[0x140-0x124];
    float m_countCoeff;
    float m_delayCoeff;
    Coord3D m_pos;
    Coord3D m_lastPos;
    BfmeParticleSystemHandle m_slaveSystem;
    unsigned char m_pad16c[4];
    BfmeParticleSystemHandle m_masterSystem;
    unsigned char m_pad17c[0x1a4-0x17c];
    bool m_isLocalIdentity;
    bool m_isIdentity;
    unsigned char m_pad1a6[5];
    bool m_field1ab;
    unsigned char m_pad1ac[0x1c4-0x1ac];
    Rva005D0950Module *m_module1c4;
};

void ParticleSystem::emit(const Coord3D *pos, int priority, bool isIdentity, const Matrix3D *transform)
{
    if (m_masterSystem) {
        m_isIdentity = isIdentity;
        if (!isIdentity) m_transform = *transform;
        m_pos = *pos;
        m_pos.add(&m_slavePosOffset);
    }
    if (m_burstDelayLeft == 0) {
        int count = (int)m_burstCount.getValue();
        count *= m_countCoeff;
        int i;
        const ParticleSystemTemplate *tmp;
        if (!m_attachedSystemName.isEmpty() && (tmp = TheParticleSystemManager->findTemplate(m_attachedSystemName)) != 0) {
            for (i = 0; i < count; ++i) {
                ParticleInfo *info = generateParticleInfo(i, count);
                if (!m_isEmitAboveGroundOnly || info->m_pos.z >= TheTerrainLogic->getGroundHeight(info->m_pos.x, info->m_pos.y, 0)) {
                    Particle *p = createParticle(info, priority, false);
                    if (p) {
                        BfmeParticleSystemHandle sys = TheParticleSystemManager->createParticleSystem(tmp, true);
                        sys->setControlParticle(p);
                        p->controlParticleSystem(sys);
                    }
                }
                delete info;
            }
        } else {
            for (i = 0; i < count; ++i) {
                ParticleInfo *info = generateParticleInfo(i, count);
                if (m_isEmitAboveGroundOnly) {
                    if (m_module1c4 && m_module1c4->slot14() && m_field1ab) {
                        if (info->m_pos.z < TheTerrainLogic->getGroundHeight(info->m_pos.x, info->m_pos.y, 0))
                            createParticle(info, priority, false);
                    } else if (info->m_pos.z >= TheTerrainLogic->getGroundHeight(info->m_pos.x, info->m_pos.y, 0)) {
                        createParticle(info, priority, false);
                    }
                } else {
                    createParticle(info, priority, false);
                }
                delete info;
            }
        }
        m_burstDelayLeft = (unsigned int)m_burstDelay.getValue();
        m_burstDelayLeft *= m_delayCoeff;
    } else {
        if (m_field04) m_burstDelayLeft = 1;
        else --m_burstDelayLeft;
    }
    if (m_slaveSystem)
        m_slaveSystem->emit(&m_pos, priority, isIdentity, transform);
}
