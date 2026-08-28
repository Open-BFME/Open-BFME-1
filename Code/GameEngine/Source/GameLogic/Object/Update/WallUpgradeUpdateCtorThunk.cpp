// cl: /DNDEBUG /MD /EHsc
// The ModuleFactory registration and 0x34-byte allocation identify this
// constructor. Two extra interface bases account for the vftable slots at
// +0x20 and +0x24 after the common UpdateModule layout.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_DUMMY };

class WUU_DeepBase
{
public:
    WUU_DeepBase(Thing *, const ModuleData *);
    virtual ~WUU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class WUU_Iface1 { public: virtual void slot(); };
class WUU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public WUU_DeepBase, public WUU_Iface1, public WUU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : WUU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class WUU_Iface3 { public: virtual void slot(); };
class WUU_Iface4 { public: virtual void slot(); };

class WallUpgradeUpdate
    : public UpdateModule, public WUU_Iface3, public WUU_Iface4
{
public:
    WallUpgradeUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_f28;
    unsigned int m_f2c;
    bool m_f30;
};

// ??0WallUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
WallUpgradeUpdate::WallUpgradeUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_f28(0), m_f2c(0), m_f30(true)
{
    setWakeFrame(getObject(), (UpdateSleepTime)1);
}
