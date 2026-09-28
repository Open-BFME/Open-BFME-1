// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Precompiled
// LaserUpdate::initLaser -- retail RVA 0x00603FE0; 776 bytes.
// Identity: the pinned ILT 0x00024FC3 carries
// ?initLaser@LaserUpdate@@QAEXPBVObject@@PBUCoord3D@@1H@Z, the four-argument
// BFME form called by the matched LaserFXNugget::doFXPos/doFXObj,
// SpecialAbilityUpdate::initLaser (0x002A7010) and
// LaserUpdate::initFromDrawables (0x00604460).  Zero Hour LaserUpdate.cpp
// supplies the spine; BFME drops the bone-name argument and the shroud test,
// takes the fire bone (and its on-turret flag) from module data, adds the
// expiry frame at +0x48, returns particle systems through the handle class,
// and always centres the drawable on the midpoint of the two positions.
// Layout and handle model follow the matched LaserUpdateClientUpdate.cpp.

#include "string_base.h"
#include "coord.h"
#include "matrix3d.h"

template<> inline const char *StringBase<char>::str() const { const char *text=(const char *)m_data; if(text) text+=8; else text=""; return text; }
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
#include "ascii_string.h"

enum WhichTurretType { TURRET_INVALID = -1, TURRET_MAIN = 0 };

class Object {
public:
    bool getSingleLogicalBonePosition(const char *boneName, Coord3D *position, Matrix3D *transform) const;
    bool getSingleLogicalBonePositionOnTurret(WhichTurretType whichTurret, const char *boneName, Coord3D *position, Matrix3D *transform) const;
};
class Drawable {
public:
    void setPosition(const Coord3D *);
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
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class ParticleSystem {
public:
    void setPosition(const Coord3D *);
    ParticleSystemID getSystemID() const { return m_systemID; }
    char m_unmodelled_000[0xac];
    ParticleSystemID m_systemID;
};
class ParticleSystemTemplate;
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
class ParticleSystemManager {
public:
    ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
    BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
private:
    BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);
    friend class LaserUpdate;
};
extern ParticleSystemManager *TheParticleSystemManager;
class LaserUpdateModuleData {
public:
    char m_unmodelled_00[8];
    AsciiString m_particleSystemName;
    AsciiString m_parentFireBoneName;
    bool m_parentFireBoneOnTurret;
    char m_pad11[3];
    AsciiString m_targetParticleSystemName;
    float m_rva00603FE0LifetimeMsec;
};
class LaserUpdate {
public:
    virtual void clientUpdate();
    void initLaser(const Object *parent, const Coord3D *startPos, const Coord3D *endPos, int sizeDeltaFrames);
    const LaserUpdateModuleData *getLaserUpdateModuleData() const { return m_moduleData; }
    Drawable *getDrawable() const { return m_drawable; }
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

void LaserUpdate::initLaser(const Object *parent, const Coord3D *startPos, const Coord3D *endPos, int sizeDeltaFrames)
{
    const LaserUpdateModuleData *data = getLaserUpdateModuleData();
    BfmeParticleSystemHandle system;
    if( sizeDeltaFrames > 0 )
    {
        m_widening = true;
        m_widenStartFrame = TheGameClient->getFrame();
        m_widenFinishFrame = m_widenStartFrame + sizeDeltaFrames;
        m_currentWidthScalar = 0.0f;
    }
    else if( sizeDeltaFrames < 0 )
    {
        m_decaying = true;
        m_decayStartFrame = TheGameClient->getFrame();
        m_decayFinishFrame = m_decayStartFrame - sizeDeltaFrames;
        m_currentWidthScalar = 1.0f;
    }

    m_rva00603BB0ExpiryFrame = (unsigned)((float)TheGameClient->getFrame() + data->m_rva00603FE0LifetimeMsec * 0.03f);

    if( parent && !data->m_parentFireBoneName.isEmpty() )
    {
        if( data->m_parentFireBoneOnTurret )
        {
            if( !parent->getSingleLogicalBonePositionOnTurret( TURRET_MAIN, data->m_parentFireBoneName.str(), &m_startPos, 0 ) )
            {
                TheGameClient->destroyDrawable( getDrawable() );
                return;
            }
        }
        else if( !parent->getSingleLogicalBonePosition( data->m_parentFireBoneName.str(), &m_startPos, 0 ) )
        {
            TheGameClient->destroyDrawable( getDrawable() );
            return;
        }
    }
    else if( startPos )
    {
        m_startPos = *startPos;
    }
    else
    {
        TheGameClient->destroyDrawable( getDrawable() );
        return;
    }

    if( endPos )
    {
        m_endPos = *endPos;
    }
    else
    {
        TheGameClient->destroyDrawable( getDrawable() );
        return;
    }

    if( !m_particleSystemID )
    {
        if( data->m_particleSystemName.isNotEmpty() )
        {
            const ParticleSystemTemplate *tmp = TheParticleSystemManager->findTemplate( data->m_particleSystemName );
            if( tmp )
            {
                system = TheParticleSystemManager->createParticleSystem( tmp, true );
                if( system.m_system )
                    m_particleSystemID = system.m_system->getSystemID();
            }
        }

        if( data->m_targetParticleSystemName.isNotEmpty() )
        {
            const ParticleSystemTemplate *tmp = TheParticleSystemManager->findTemplate( data->m_targetParticleSystemName );
            if( tmp )
            {
                system = TheParticleSystemManager->createParticleSystem( tmp, true );
                if( system.m_system )
                    m_targetParticleSystemID = system.m_system->getSystemID();
            }
        }
    }

    if( m_particleSystemID )
    {
        system = TheParticleSystemManager->findParticleSystemByID( m_particleSystemID );
        if( system.m_system )
            system.m_system->setPosition( &m_startPos );
    }

    if( m_targetParticleSystemID )
    {
        system = TheParticleSystemManager->findParticleSystemByID( m_targetParticleSystemID );
        if( system.m_system )
            system.m_system->setPosition( &m_endPos );
    }

    Coord3D posToUse;
    posToUse.set( startPos );
    posToUse.add( endPos );
    posToUse.scale( 0.5f );
    getDrawable()->setPosition( &posToUse );
    m_dirty = true;
}
