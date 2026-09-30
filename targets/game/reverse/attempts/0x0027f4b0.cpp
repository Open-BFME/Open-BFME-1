// ??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=1.0 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <string.h>
#include <bitset>
#include <vector>
#include "ascii_string.h"
#include "coord3d.h"
// Retail 0x0027F4B0, 1237 bytes. Constructor identity: factory and derived
// constructors through ILT, final vtables 010BA8A8/7E0/7D4/7D0/7B4.
// PARTIAL: 1233/1237 bytes; +0x471 string-reference lifetime remains.
// Existing AIUpdate.cpp uses a ZH layout; this isolated BFME view follows
// retail construction and seven unwind states, including the Coord3D array.
class Thing;
class ModuleData;
class Object;

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

private:
	protected:
	const ModuleData *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113d40
{
public:
	ObjectModule(Thing *thing, const ModuleData *data);

protected:
	Object *m_object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data) : ObjectModule(thing, data) {}
	virtual ~BehaviorModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data) :
		BehaviorModule(thing, data),
		m_nextCallFrameAndPhase(0),
		m_indexInLogic(-1),
		m_updateState(-1)
	{
	}
	virtual ~UpdateModule();

	void setWakeFrame(Object *object, unsigned int frame);

protected:

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};


class AIUpdateCommandInterface { public: virtual void commandInterfaceAnchor() = 0; };
class AIUpdateExtraInterface { public: virtual void extraInterfaceAnchor() = 0; };
class Gen_001B98B0 { public: void bfmeClear(); };
class Gen_001BA9E0 { public: virtual ~Gen_001BA9E0(); };
class Rva001B7450 {
public:
    Rva001B7450();
    ~Rva001B7450() { reinterpret_cast<Gen_001BA9E0 *>(this)->Gen_001BA9E0::~Gen_001BA9E0(); }
    void clear() { reinterpret_cast<Gen_001B98B0 *>(this)->bfmeClear(); }
    virtual void keep();
    char m_004[0x20];
};
class GiantBirdMemberA { public: ~GiantBirdMemberA(); };
class Gen_0027AE50 {
public:
    // Retail does not advance from EH state 1 before this call.
    Gen_0027AE50() throw();
    ~Gen_0027AE50() throw();
    char m_000[0xa0];
};
// This constructor installs VA 010BA790; the base-only vtable 01073744
// would be wrong here. The owning embedded type remains address-derived.
class Rva010BA790Head { public: virtual ~Rva010BA790Head() {} };
class Rva0027EED0 {
public:
    ~Rva0027EED0();
    Rva010BA790Head m_000;
    _STL::vector<int> m_004;
};
enum WhichTurretType { TURRET_MAIN, TURRET_ALT };
class TurretAIData;
class TurretAI {
public:
    TurretAI(Object *, const TurretAIData *, WhichTurretType);
    char m_000[0xac];
};
enum LocomotorSetType { LOCOMOTORSET_INVALID=-1, LOCOMOTORSET_NORMAL, LOCOMOTORSET_NORMAL_UPGRADED };
class Overridable {
public:
    virtual ~Overridable();
    const Overridable *getFinalOverride() const {
        if (m_nextOverride) return m_nextOverride->getFinalOverride();
        return this;
    }
    Overridable *m_nextOverride;
};
template<class T> class OVERRIDE {
public:
    const T *operator*() const {
        if (!m_overridable) return 0;
        return (T *)m_overridable->getFinalOverride();
    }
    operator const T *() const { return operator*(); }
private: const T *m_overridable;
};
class Gen_001418F0 : public Overridable { public: float bfmeFindFloat(const void *); };
class Object {
public:
    virtual ~Object();
    const Gen_001418F0 *getTemplate() const { return m_template; }
    OVERRIDE<Gen_001418F0> m_template;
};
class AttackPriorityInfo;
class ScriptEngine { public: const AttackPriorityInfo *getAttackInfo(const AsciiString &); };
extern ScriptEngine *TheScriptEngine;
class LuaScriptEngine { public: int rva002EBF60(const AsciiString &); };
extern LuaScriptEngine *TheLuaScriptEngine;
struct Rva0027F4B0ModuleData {
    char m_000[0x14];
    const TurretAIData *m_turretData[2];
    char m_01c[0x30-0x1c];
    AsciiString m_030;
    char m_034[0x44-0x34];
    AsciiString m_044;
};
// Inline definition from StringBase.cpp; avoids an out-of-line emptiness test.
template<> inline bool StringBase<char>::isEmpty() const {
    return !m_data || m_data->length == 0;
}
struct Rva0027F4B0Position : public Coord3DBase { void zero() { x=0.0f; y=0.0f; z=0.0f; } };
class AIUpdateInterface : public UpdateModule,
    public AIUpdateCommandInterface, public AIUpdateExtraInterface {
public:
    AIUpdateInterface(Thing *, const ModuleData *);
    virtual ~AIUpdateInterface();
private:
    bool chooseLocomotorSetExplicit(LocomotorSetType);
protected:
    void chooseGoodLocomotorFromCurrentSet();
private:
    bool chooseLocomotorSet(LocomotorSetType wst) {
        if (wst == LOCOMOTORSET_NORMAL && m_upgradedLocomotors)
            wst = LOCOMOTORSET_NORMAL_UPGRADED;
        if (wst == m_curLocomotorSet) return true;
        if (!m_337 && chooseLocomotorSetExplicit(wst)) {
            chooseGoodLocomotorFromCurrentSet();
            m_1d4 = const_cast<Gen_001418F0 *>(m_object->getTemplate())->bfmeFindFloat((const void *)m_curLocomotorSet);
            return true;
        }
        return false;
    }
    Object *getObject() const { return m_object; }
    const Rva0027F4B0ModuleData *getAIUpdateModuleData() const {
        return reinterpret_cast<const Rva0027F4B0ModuleData *>(m_moduleData);
    }
    int m_028; // +0x028
    int m_02c; // +0x02c
    int m_stateMachine; // +0x030
    int m_034; // +0x034
    int m_038; // +0x038
    int m_03c; // +0x03c
    int m_currentVictimID; // +0x040
    float m_desiredSpeed; // +0x044
    int m_lastCommandSource; // +0x048
    int m_guardMode; // +0x04c
    int m_guardTargetType[2]; // +0x050
    Rva0027F4B0Position m_position058;
    int m_objectToGuard; // +0x064
    int m_areaToGuard; // +0x068
    int m_nextEnemyScanTime; // +0x06c
    const AttackPriorityInfo * m_attackInfo; // +0x070
    Coord3D m_waypoints[16]; // +0x074
    int m_134; // +0x134
    int m_138; // +0x138
    int m_13c; // +0x13c
    int m_path; // +0x140
    int m_requestedVictimID; // +0x144
    Rva0027F4B0Position m_requestedDestination;
    Rva0027F4B0Position m_position154;
    int m_160; // +0x160
    int m_164; // +0x164
    float m_pathExtraDistance; // +0x168
    int m_blockedFrames; // +0x16c
    float m_170; // +0x170
    float m_bumpSpeedLimit; // +0x174
    int m_ignoreCollisionsUntil; // +0x178
    int m_queueForPathFrame; // +0x17c
    Rva0027F4B0Position m_position180;
    int m_18c; // +0x18c
    int m_190; // +0x190
    int m_194; // +0x194
    int m_198; // +0x198
    int m_19c; // +0x19c
    int m_1a0; // +0x1a0
    int m_1a4; // +0x1a4
    Rva001B7450 m_locomotorSet; // +0x1a8
    int m_curLocomotor; // +0x1cc
    LocomotorSetType m_curLocomotorSet; // +0x1d0
    float m_1d4; // +0x1d4
    int m_locomotorGoalType; // +0x1d8
    Rva0027F4B0Position m_position1dc;
    TurretAI *m_turretAI[2]; // +0x1e8
    int m_turretSyncFlag;
    AsciiString m_1f4;
    int m_1f8, m_1fc, m_200;
    Rva0027EED0 m_204;
    int m_214, m_218, m_21c;
    _STL::bitset<304> m_220;
    _STL::bitset<304> m_248;
    // Three zero-initialized words. Bit count is not established by the ctor.
    _STL::bitset<96> m_270;
    Gen_0027AE50 m_27c;
    bool m_31c; // +0x31c
    bool m_31d; // +0x31d
    bool m_31e; // +0x31e
    bool m_isAttackPath; // +0x31f
    bool m_320; // +0x320
    bool m_321; // +0x321
    bool m_isSafePath; // +0x322
    bool m_323; // +0x323
    bool m_324; // +0x324
    bool m_isBlocked; // +0x325
    bool m_isBlockedAndStuck; // +0x326
    bool m_upgradedLocomotors; // +0x327
    bool m_328; // +0x328
    bool m_329; // +0x329
    bool m_32a; // +0x32a
    bool m_isAiDead; // +0x32b
    bool m_32c; // +0x32c
    bool m_32d; // +0x32d
    bool m_32e; // +0x32e
    bool m_32f; // +0x32f
    bool m_isInUpdate; // +0x330
    bool m_331; // +0x331
    bool m_332; // +0x332
    bool m_333; // +0x333
    bool m_334; // +0x334
    bool m_335; // +0x335
    bool m_336; // +0x336
    bool m_337; // +0x337
    bool m_338; // +0x338
    bool m_339; // +0x339
    bool m_33a; // +0x33a
    bool m_33b; // +0x33b
    int m_33c;
};
AIUpdateInterface::AIUpdateInterface(Thing *thing, const ModuleData *data) :
    UpdateModule(thing, data), m_1a0(0), m_200(0), m_214(0),
    m_31c(false), m_32f(false), m_33b(false), m_33c(0)
{
    m_stateMachine = 0;
    m_034 = 0;
    m_038 = 0;
    m_03c = 0;
    m_currentVictimID = 0;
    m_lastCommandSource = 2;
    m_guardMode = 0;
    m_028 = 0xfacade;
    m_02c = 0xfacade;
    m_desiredSpeed = 999999.0f;
    m_guardTargetType[0] = m_guardTargetType[1] = 4;
    m_position058.zero();
    m_objectToGuard = 0;
    m_areaToGuard = 0;
    m_nextEnemyScanTime = 0;
    m_attackInfo = 0;
    m_134 = 0;
    m_138 = 0;
    m_13c = 0;
    m_path = 0;
    m_requestedVictimID = 0;
    m_requestedDestination.zero();
    m_position154.zero();
    m_160 = 0;
    m_164 = 0;
    m_pathExtraDistance = 0;
    m_blockedFrames = 0;
    m_170 = 0;
    m_bumpSpeedLimit = 999999.0f;
    m_ignoreCollisionsUntil = 0;
    m_queueForPathFrame = 0;
    m_position180.zero();
    m_18c = 0;
    m_190 = 0;
    m_194 = -1;
    m_198 = 0;
    m_19c = 0;
    m_locomotorSet.clear();
    m_curLocomotor = 0;
    m_curLocomotorSet = LOCOMOTORSET_INVALID;
    m_locomotorGoalType = 0;
    m_position1dc.zero();
    memset(m_turretAI, 0, sizeof(m_turretAI));
    m_turretSyncFlag = -1;
    m_1f8 = 0;
    m_1fc = 0;
    m_218 = 0;
    m_21c = 0;
    m_31d = false;
    m_31e = false;
    m_isAttackPath = false;
    m_320 = false;
    m_321 = false;
    m_isSafePath = false;
    m_323 = false;
    m_324 = false;
    m_isBlocked = false;
    m_isBlockedAndStuck = false;
    m_upgradedLocomotors = false;
    m_328 = false;
    m_329 = false;
    m_32a = false;
    m_isAiDead = false;
    m_32c = true;
    m_32d = false;
    m_32e = false;
    m_isInUpdate = false;
    m_331 = false;
    m_1a4 = 0;
    m_332 = false;
    m_335 = false;
    m_333 = false;
    m_334 = false;
    m_336 = true;
    m_337 = false;
    m_338 = false;
    m_220.reset();
    m_339 = false;
    m_33a = false;
    const Rva0027F4B0ModuleData *d = getAIUpdateModuleData();
    for (int i=0; i<2; ++i) {
        if (getAIUpdateModuleData()->m_turretData[i])
            m_turretAI[i] = new TurretAI(getObject(), d->m_turretData[i], (WhichTurretType)i);
    }
    chooseLocomotorSet(LOCOMOTORSET_NORMAL);
    if (!d->m_044.isEmpty()) {
        ScriptEngine *engine = TheScriptEngine;
        m_attackInfo = engine->getAttackInfo(d->m_044);
        const AsciiString * volatile retainedName = &d->m_044;
    }
    setWakeFrame(getObject(), 1);
    m_200 = TheLuaScriptEngine->rva002EBF60(d->m_030);
}


// Integration blocker (not a landed constructor): this isolated body probes exact at 1237B with 32 relocations, but must be adopted into official AIUpdate.cpp rather than introducing another AIUpdateInterface class.
// Retail final vptrs are +0/+0x0C/+0x10/+0x20/+0x24; own fields start +0x28. Current aiupdatelayout shim lacks the fifth interface base.
// Retail command source is +0x48 (constructor/privateDock), ignored obstacle +0x164 (named path-state callers), blocked-frame field +0x16C, BFME LocomotorSet +0x1A8..+0x1CB (0x24 bytes), curLocomotor +0x1CC, turrets +0x1E8, attitude +0x1F8, and next mood check +0x1FC.
// The current shim uses a 0x18-byte ZH LocomotorSet at +0x1B4. Padding keeps some later offsets exact while the actual member layout is wrong; two ZH pathfind cells conflict with retail blockedFrames.
// Adding the fifth base and shrinking pre-locomotor padding preserves 61/65 current official-TU rows, but is diagnostic only and does not establish a correct BFME layout.
// Wrong existing AI identities: setLastCommandSource at0x001B49AE stores+0x3C and overlaps retained AnimateWindow::setAnimType; true AI command source is+0x48. setAttitude at0x0045DC60 stores+0x1F4, while seven named callers reach true body0x0027DEF0/128B storing+0x1F8. ignoreObstacleID at0x007F21F0 stores+0x154, whereas named callers use getter0x0026F940 and setter0x0026F930 at+0x164.
// Anonymous seven-byte getter rows0x002B1020/0x004A3AA0 also read+0x154 and must retain anonymous coverage under distinct owners when the AI header is corrected. Do not silently delete them.
// Use durable tombstones, add_match identity corrections, and exact snapshot naming evidence for proven wrong identities. Existing BFME name witnesses have stale conflicting attitude/mood fields and need independent reconciliation, not a broadened baseline.
// Final codegen lever: load TheScriptEngine before getAttackInfo, then retain a volatile pointer to d->m_044 after the call to reproduce the retail stack spill. This local has no gameplay effect and needs integration review.
// Full official-TU/header-dependent byte and relocation gates remain pending. This bank is evidence only; no authored C++ progress is claimed.
