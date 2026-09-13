// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor through ILT 0x0000FA38. The
// registration string and 0x44-byte allocation identify the retail-only
// RespawnUpdate class.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class RU_DeepBase
{
public:
    RU_DeepBase(Thing *, const ModuleData *);
    virtual ~RU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class RU_Iface1 { public: virtual void slot(); };
class RU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public RU_DeepBase, public RU_Iface1, public RU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : RU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class RespawnUpdate : public UpdateModule
{
public:
    RespawnUpdate(Thing *, const ModuleData *);

private:
    float m_f20;
    unsigned int m_f24;
    int m_f28;
    unsigned int m_f2c;
    unsigned int m_f30;
    int m_f34;
    int m_f38;
    int m_f3c;
    bool m_f40;
    bool m_f41;
};

// ??0RespawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
RespawnUpdate::RespawnUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_f34 = -1;
    m_f38 = -1;
    m_f3c = -1;
    m_f28 = -1;
    m_f2c = 0;
    m_f30 = 0;
    m_f40 = false;
    m_f20 = -1.0f;
    m_f41 = false;
    m_f24 = 0;
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
