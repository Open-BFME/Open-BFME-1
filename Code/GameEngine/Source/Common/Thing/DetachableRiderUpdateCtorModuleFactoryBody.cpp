// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor body through ILT 0x0004773F. The
// registration string and 0x24-byte allocation independently identify the
// retail-only DetachableRiderUpdate class.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class DRU_DeepBase
{
public:
    DRU_DeepBase(Thing *, const ModuleData *);
    virtual ~DRU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class DRU_Iface1 { public: virtual void slot(); };
class DRU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public DRU_DeepBase, public DRU_Iface1, public DRU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : DRU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class DetachableRiderUpdate : public UpdateModule
{
public:
    DetachableRiderUpdate(Thing *, const ModuleData *);

private:
    bool m_flag20;
    bool m_flag21;
};

// ??0DetachableRiderUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DetachableRiderUpdate::DetachableRiderUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_flag20(false), m_flag21(false)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
