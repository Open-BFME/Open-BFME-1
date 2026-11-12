// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <string.h>
#include <bitset>
#include <vector>
#include "ascii_string.h"
#include "coord3d.h"
// ??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0027F4B0,
// 1237 bytes (ret 8 at +0x4D2, INT3 at +0x4D5).
//
// Identity: the factory and the derived AI constructors (GiantBird, Dozer,
// Worker...) reach this body through ILT 0x000292A3, and it installs the
// final vtables 010BA8A8/7E0/7D4/7D0/7B4 that the matched destructor
// 0x0027EF60 (AIUpdateInterfaceDestructors.cpp) restores.
//
// Zero Hour AIUpdate.cpp AIUpdateInterface::AIUpdateInterface on BFME 1's
// layout, read from this body and its seven native unwind states: the
// UpdateModule base (out-of-line ObjectModule ctor), the sixteen waypoint
// coordinates at +0x74, the LocomotorSet at +0x1A8 (constructor 0x001B7450,
// reset 0x001B98B0, destructor 0x001BA9E0: the ledger keeps three
// placeholder class names for that one class, bridged below), the +0x1F4
// string, the +0x204 embedded vector owner (vtable 010BA790), the 304-bit
// masks at +0x220/+0x248, the +0x270 words and the 0xA0-byte member at +0x27C
// (0x0027AE50). The body then resets the scalars in ZH order, builds the
// turret AIs (TurretAI ctor 0x0018DED0), picks LOCOMOTORSET_NORMAL, looks up
// the attack priority by the module data's +0x44 name, wakes the module and
// asks the Lua engine for the +0x30 name (0x002EBF60) into +0x200.
// AIUpdate.cpp keeps the Zero Hour layout and its own copy of this
// constructor marked present-unmatched; this unit is the retail one.
//
// [BFME 2 donor] open-bfme-2 76f0baefa6
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIUpdateInterfaceCtor.cpp
// (BFME 2 0x0026E9BD, 984 B) follows the same WorldBuilder source order and
// member roles; BFME 1 has two turret slots and a different tail.
//
// Codegen notes: the Coord3D members are zeroed through inline zero()
// methods (direct stores schedule differently); the module data is reached
// through a getObject()-style accessor for the turret loop; TheScriptEngine
// is loaded before getAttackInfo and a volatile pointer to the looked-up name
// is kept after the call, which reproduces retail's stack spill of it.
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

// Vtable spellings. The matched destructor (AIUpdateInterfaceDestructors.cpp)
// names AIUpdateInterface's final vtables after the bases Module,
// AIUpdateBehaviorInterface, UpdateModule, AIUpdateCommandInterface and
// AIUpdateExtraInterface, and dir32_addresses.csv records them so. The
// constructor also stores each interface's own vtable first, recorded as
// BehaviorModuleInterface, UpdateModuleInterface, Rva0026E890 (0x010B9338)
// and Rva001EF440 (0x010A1DE4). The destructor's base names are therefore
// novtable layers over the classes that own those vtables.
class __declspec(novtable) Module : public ObjectModule
{
public:
	Module(Thing *thing, const ModuleData *data) : ObjectModule(thing, data) {}
};

class __declspec(novtable) AIUpdateBehaviorInterface : public BehaviorModuleInterface
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public Module, public AIUpdateBehaviorInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data) : Module(thing, data) {}
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


class Rva0026E890 { public: virtual void commandInterfaceAnchor() = 0; };
class Rva001EF440 { public: virtual void extraInterfaceAnchor() = 0; };
class __declspec(novtable) AIUpdateCommandInterface : public Rva0026E890 {};
class __declspec(novtable) AIUpdateExtraInterface : public Rva001EF440 {};
class Gen_001B98B0 { public: void bfmeClear(); };
class Gen_001BA9E0 { public: virtual ~Gen_001BA9E0(); };
class LocomotorSet {
public:
    LocomotorSet();
    ~LocomotorSet() { reinterpret_cast<Gen_001BA9E0 *>(this)->Gen_001BA9E0::~Gen_001BA9E0(); }
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
// The +0x204 member: its vtable 0x010BA790 is recorded only as the datum
// R2Data010BA790, and its out-of-line constructor 0x0027EE90
// (R2ZeroingConstructors.cpp) stores it the same way; this is that body
// inlined. Destructor 0x0027EED0.
extern int R2Data010BA790;
class Rva0027EED0 {
public:
    Rva0027EED0() { m_000 = &R2Data010BA790; m_004 = 0; m_008 = 0; m_00c = 0; }
    ~Rva0027EED0();
    void *m_000;
    int m_004;
    int m_008;
    int m_00c;
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
    LocomotorSet m_locomotorSet; // +0x1a8
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
