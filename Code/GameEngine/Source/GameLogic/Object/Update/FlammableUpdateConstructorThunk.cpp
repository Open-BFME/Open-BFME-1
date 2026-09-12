// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's 0x50-byte allocation proves the compact BFME layout. Zero
// Hour names the fields through +0x3C; the remaining tail is BFME-only state
// whose initialization order is fixed by the retail constructor.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class FU_DeepBase
{
public:
    FU_DeepBase(Thing *, const ModuleData *);
    virtual ~FU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class FU_Iface1 { public: virtual void slot(); };
class FU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public FU_DeepBase, public FU_Iface1, public FU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : FU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }
    const ModuleData *getModuleData() const { return m_moduleData; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class DamageModuleInterface { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h
class FlammableUpdateModuleData
{
private:
    unsigned char m_pad00[8];
    unsigned int m_burnedDelay;
    unsigned int m_aflameDuration;
    unsigned int m_aflameDamageDelay;
    int m_aflameDamageAmount;
    void *m_burningSoundName;

public:
    float m_flameDamageLimitData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h
class FlammableUpdate : public UpdateModule, public DamageModuleInterface
{
public:
    FlammableUpdate(Thing *, const ModuleData *);

    // 0x00292FA0, 13 bytes: row-less unclaimed-boundary candidate. Tail-jmps
    // into the already-landed ?calcSleepTime@FlammableUpdate@@IAE?AW4UpdateSleepTime@@XZ
    // (0x00292FAD) when m_flag40 is clear; returns UPDATE_SLEEP(1) when set.
    // m_flag40 is BFME-only state (see the header comment above), so the
    // semantic name below is descriptive, not recovered.
    UpdateSleepTime bfmeCalcSleepTimeGate();

protected:
    // Declared only -- defined and byte-verified elsewhere in the build
    // (FlammableUpdate.cpp, 0x00292FAD); calling it here resolves to that
    // existing body.
    UpdateSleepTime calcSleepTime();

private:
    int m_status;
    unsigned int m_aflameEndFrame;
    unsigned int m_burnedEndFrame;
    unsigned int m_damageEndFrame;
    void *m_audioHandle;
    float m_flameDamageLimit;
    unsigned int m_lastFlameDamageDealt;
    bool m_flag40;
    unsigned int m_field44;
    unsigned int m_field48;
    bool m_flag4c;
};

// ??0FlammableUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
FlammableUpdate::FlammableUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_status = 0;
    m_aflameEndFrame = 0;
    m_burnedEndFrame = 0;
    m_damageEndFrame = 0;
    m_audioHandle = 0;
    m_flameDamageLimit =
        ((const FlammableUpdateModuleData *)getModuleData())->m_flameDamageLimitData;
    m_lastFlameDamageDealt = 0;
    m_flag40 = false;
    m_field44 = 0;
    m_field48 = 0;
    m_flag4c = false;
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

// ?bfmeCalcSleepTimeGate@FlammableUpdate@@QAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime FlammableUpdate::bfmeCalcSleepTimeGate()
{
    if ( m_flag40 )
        return (UpdateSleepTime)1;
    return calcSleepTime();
}
