// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's 0x58-byte allocation proves the BFME layout. The fields
// through +0x50 follow the Zero Hour source; +0x54 is BFME-only state that
// retail initializes in the same zeroing run.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class TU_DeepBase
{
public:
    TU_DeepBase(Thing *, const ModuleData *);
    virtual ~TU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class TU_Iface1 { public: virtual void slot(); };
class TU_Iface2 { public: virtual void slot(); };

class UpdateModule : public TU_DeepBase, public TU_Iface1, public TU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : TU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class BfmeToppleCollideModuleInterface { public: virtual void slot(); };

class ToppleUpdate : public UpdateModule, public BfmeToppleCollideModuleInterface
{
public:
    ToppleUpdate(Thing *, const ModuleData *);

private:
    float m_angularVelocity;
    float m_angularAcceleration;
    float m_toppleDirectionX;
    float m_toppleDirectionY;
    float m_toppleDirectionZ;
    int m_toppleState;
    float m_angularAccumulation;
    float m_angleDeltaX;
    int m_numAngleDeltaX;
    bool m_doBounceFX;
    unsigned int m_options;
    unsigned int m_stumpID;
    unsigned int m_bfmeState;
};

// ??0ToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
ToppleUpdate::ToppleUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_angleDeltaX = 0.0f;
    m_doBounceFX = false;
    m_numAngleDeltaX = 0;
    m_angularVelocity = 0.0f;
    m_angularAccumulation = 0.0f;
    m_angularAcceleration = 0.0f;
    m_toppleDirectionX = 0.0f;
    m_toppleDirectionY = 0.0f;
    m_toppleDirectionZ = 0.0f;
    m_toppleState = 0;
    m_options = 0;
    m_stumpID = 0;
    m_bfmeState = 0;
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
