// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Precompiled
// LaserUpdate::clientUpdate -- retail RVA 0x00603BB0; 846 bytes.
// Identity: LaserUpdate constructor 0x00603790 and destructor 0x00603820
// install vtable VA 0x01115370. Its client-update slot +0x28 points through
// ILT 0x0003F2C4 to this body. The name getter 0x00603810 says LaserUpdate.
// Zero Hour LaserUpdate.cpp supplies the widening/decaying spine; BFME adds
// expiry at +0x48 and updates both drawable/particle endpoints here.
// BFME differs from the older constructor/xfer sketches: parent/target IDs
// are +0x4C/+0x50 (also witnessed by initFromDrawables at 0x00604460).
// The module-data fire-bone string at +0x0C and Drawable::m_object at +0xFC
// are independently witnessed by name_oracle. The Object geometry view below
// claims only the call-site offset +0xAC, not a complete Object layout.
// All REL32 declarations reuse existing matched bodies or established pins.
// U1Sub::apply cannot throw: its 84-byte body only unlinks/splices handles.
// That contract suppresses unwind states for the two returned temporaries.
// Shared coordinate/string declarations retain their native inline operations;
// the StringBase specialization keeps the nullable buffer adjustment explicit.

#include "string_base.h"
#include "coord.h"
#include "matrix3d.h"

#include "geometry.h"
class Rva00603BB0ObjectView {
public:
    char m_unmodelled_000[0xac];
    const GeometryInfo &getGeometryInfo() const { return *(const GeometryInfo *)((const char *)this+0xac); }
};
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };
class Drawable {
public:
    bool getCurrentWorldspaceClientBonePositions(const char *, Matrix3D &) const;
    void setPosition(const Coord3D *);
    const Coord3D *getPosition() const { return ((const BFMERopeDrawable *)this)->getPosition(); }
    char m_unmodelled_000[0xfc];
    Rva00603BB0ObjectView *m_object;
    Rva00603BB0ObjectView *getObject() const { return m_object; }
};
class GameClient {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10();
    virtual Drawable *findDrawableByID(unsigned);
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void destroyDrawable(Drawable *);
    virtual void slot25(); virtual unsigned getFrame();
};
extern GameClient *TheGameClient;
class ParticleSystem { public: void setPosition(const Coord3D *); };
class U1CachedHolder;
class U1Sub {
public:
    U1Sub &apply(U1CachedHolder *other) throw();
};
class BfmeParticleSystemHandle {
public:
    BfmeParticleSystemHandle() : m_system(0), m_previous(0), m_next(0) {}
    ~BfmeParticleSystemHandle() throw();
    BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &other) {
        ((U1Sub *)this)->apply((U1CachedHolder *)&other); return *this;
    }
    ParticleSystem *m_system;
    BfmeParticleSystemHandle *m_previous, *m_next;
};
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class ParticleSystemManager {
private: BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);
    friend class LaserUpdate;
};
extern ParticleSystemManager *TheParticleSystemManager;
class LaserUpdateModuleData {
public:
    char m_unmodelled_00[8];
    AsciiString m_particleSystemName;
    AsciiString m_parentFireBoneName;
};
class LaserUpdate {
public:
    virtual void clientUpdate();
    const LaserUpdateModuleData *m_moduleData;
    Drawable *m_drawable;
    Coord3D m_startPos, m_endPos;
    bool m_dirty;
    char m_pad25[3];
    ParticleSystemID m_particleSystemID, m_targetParticleSystemID;
    bool m_widening, m_decaying;
    char m_pad32[2];
    unsigned m_widenStartFrame, m_widenFinishFrame;
    float m_currentWidthScalar;
    unsigned m_decayStartFrame, m_decayFinishFrame;
    unsigned m_rva00603BB0ExpiryFrame;
    unsigned m_parentID, m_targetID;
};

void LaserUpdate::clientUpdate()
{
    const LaserUpdateModuleData *data=m_moduleData;
    unsigned now=TheGameClient->getFrame();
    if(now>m_rva00603BB0ExpiryFrame) goto expired;
    if(m_decaying) {
        m_currentWidthScalar=1.0f-(float)(now-m_decayStartFrame)/(float)(m_decayFinishFrame-m_decayStartFrame);
        m_dirty=true;
        if(m_currentWidthScalar<=0.0f) {
            m_currentWidthScalar=0.0f;
expired:
            TheGameClient->destroyDrawable(m_drawable); return;
        }
    } else if(m_widening) {
        m_currentWidthScalar=(float)(now-m_widenStartFrame)/(float)(m_widenFinishFrame-m_widenStartFrame);
        m_dirty=true;
        if(m_currentWidthScalar>=1.0f) { m_currentWidthScalar=1.0f; m_widening=false; }
    }
    m_dirty=true;
    if(m_parentID && m_targetID) {
        Drawable *parent=TheGameClient->findDrawableByID(m_parentID);
        Drawable *target=TheGameClient->findDrawableByID(m_targetID);
        if(parent && target) {
            if(!data->m_parentFireBoneName.isEmpty()) {
                Matrix3D matrix(true);
                parent->getCurrentWorldspaceClientBonePositions(data->m_parentFireBoneName.str(),matrix);
                m_startPos.set(matrix.Get_X_Translation(),matrix.Get_Y_Translation(),matrix.Get_Z_Translation());
            } else {
                m_startPos.set(parent->getPosition());
                m_startPos.z+=parent->getObject()->getGeometryInfo().getMaxHeightAbovePosition()*0.5f;
            }
            m_endPos.set(target->getPosition());
            m_endPos.z+=target->getObject()->getGeometryInfo().getMaxHeightAbovePosition()*0.83f;
            BfmeParticleSystemHandle system;
            if(m_particleSystemID) {
                system=TheParticleSystemManager->findParticleSystemByID(m_particleSystemID);
                if(system.m_system) system.m_system->setPosition(&m_startPos);
            }
            if(m_targetParticleSystemID) {
                system=TheParticleSystemManager->findParticleSystemByID(m_targetParticleSystemID);
                if(system.m_system) system.m_system->setPosition(&m_endPos);
            }
            Coord3D pos;
            pos.set(&m_startPos);
            pos.add(&m_endPos);
            pos.scale(0.5f);
            m_drawable->setPosition(&pos);
        }
    }
}
