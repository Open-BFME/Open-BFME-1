// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

// Retail RVA 0x001F2E80: the DamageModuleInterface subobject is at +0x24.
// Calls to resolveFX and doAreaEffects use the primary BridgeBehavior this.
// The reference callback is in BridgeBehavior.cpp; BFME uses 0x70-byte sound
// records and different TerrainLogic/AudioManager virtual slots. These local
// views describe those witnessed ABIs without changing the shared ZH headers.
// Full identity and boundary evidence: targets/game/reverse/identity_evidence/
// 001f2e80_bridge_body_state.md.

class DamageInfo;
class ObjectCreationList;
class FXList;
class TerrainRoadType;
class AudioEventRTS;
struct Coord3D { float x,y,z; };
enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };
class Object { char prefix[0x38]; public: Coord3D position; };
class Bridge { public: AsciiString getBridgeTemplateName(); };
class TerrainRoadCollection { public: TerrainRoadType *findBridge(AsciiString); };
class TerrainLogic {
public:
    typedef Bridge *(TerrainLogic::*FindBridge)(const Coord3D *);
    typedef void (TerrainLogic::*UpdateBridges)();
    struct Vtable { void *prefix[38]; FindBridge find; void *middle[7]; UpdateBridges update; };
    Vtable *vtable;
    Bridge *findBridgeAt(const Coord3D *p) { return (this->*(vtable->find))(p); }
    void updateBridgeDamageStates() { (this->*(vtable->update))(); }
};
class Radar {
public:
    typedef void (Radar::*QueueRefresh)();
    struct Vtable { void *prefix[5]; QueueRefresh queue; };
    Vtable *vtable;
    void queueTerrainRefresh() { (this->*(vtable->queue))(); }
};
class AudioManager {
public:
    typedef unsigned (AudioManager::*AddEvent)(AudioEventRTS *);
    struct Vtable { void *prefix[17]; AddEvent add; };
    Vtable *vtable;
    unsigned addAudioEvent(AudioEventRTS *p) { return (this->*(vtable->add))(p); }
};
extern TerrainLogic *TheTerrainLogic;
extern TerrainRoadCollection *TheTerrainRoads;
extern Radar *TheRadar;
extern AudioManager *TheAudio;

class BfmeBridgeModuleBase {
public:
    virtual ~BfmeBridgeModuleBase();
    char pad04[4];
    Object *object;
    char pad0c[0x18];
};
class DamageModuleInterface {
public:
    virtual void onDamage(DamageInfo *) = 0;
    virtual void onHealing(DamageInfo *) = 0;
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType) = 0;
};
struct BfmeBridgeSoundRecord { char bytes[0x70]; };
class BridgeBehavior : public BfmeBridgeModuleBase, public DamageModuleInterface {
public:
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType);
protected:
    void resolveFX();
    void doAreaEffects(TerrainRoadType *, Bridge *, const ObjectCreationList *, const FXList *);
    char pad28[0x14];
    const ObjectCreationList *m_damageToOCL[4][3];
    const FXList *m_damageToFX[4][3];
    BfmeBridgeSoundRecord m_damageToSound[4];
    const ObjectCreationList *m_repairToOCL[4][3];
    const FXList *m_repairToFX[4][3];
    BfmeBridgeSoundRecord m_repairToSound[4];
    bool m_fxResolved;
    char pad47d[7];
    unsigned m_deathFrame;
};

void BridgeBehavior::onBodyDamageStateChange(const DamageInfo *, BodyDamageType oldState, BodyDamageType newState)
{
    if (newState != BODY_RUBBLE) m_deathFrame = 0;
    if (!m_fxResolved) resolveFX();
    if (!m_fxResolved) return;
    Object *us = object;
    Bridge *bridge = TheTerrainLogic->findBridgeAt(&us->position);
    if (!bridge) return;
    AsciiString bridgeTemplateName = bridge->getBridgeTemplateName();
    TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge(bridgeTemplateName);
    bool gotRepaired = oldState > newState;
    AsciiString soundString;
    AsciiString oclString[3];
    AsciiString fxString[3];
    if (gotRepaired) {
        TheAudio->addAudioEvent((AudioEventRTS *)&m_repairToSound[newState]);
        for (int i=0; i<3; ++i)
            doAreaEffects(bridgeTemplate, bridge, m_repairToOCL[newState][i], m_repairToFX[newState][i]);
    } else {
        TheAudio->addAudioEvent((AudioEventRTS *)&m_damageToSound[newState]);
        for (int i=0; i<3; ++i)
            doAreaEffects(bridgeTemplate, bridge, m_damageToOCL[newState][i], m_damageToFX[newState][i]);
    }
    TheTerrainLogic->updateBridgeDamageStates();
    if (oldState == BODY_RUBBLE || newState == BODY_RUBBLE)
        TheRadar->queueTerrainRefresh();
}
