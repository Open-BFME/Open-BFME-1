// cl: /DNDEBUG /MD /EHsc
// readable body of ??0SupplyCenterProductionExitUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdate.cpp

// The BFME UpdateModule/ExitInterface prefix and the zeroed rally point are
// retained locally because the shared ZH declaration has a different prefix.
class Thing;
class ModuleData;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    float x;
    float y;
    float z;

    void zero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
};

enum UpdateSleepTime
{
    UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    void *m_f04;
    Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class SupplyCenterProductionExitUpdateIface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterProductionExitUpdate.h
class SupplyCenterProductionExitUpdate : public UpdateModule,
    public SupplyCenterProductionExitUpdateIface
{
public:
    SupplyCenterProductionExitUpdate(Thing *, const ModuleData *);

private:
    Coord3D m_rallyPoint;
    volatile unsigned char m_rallyPointExists;
};

// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SupplyCenterProductionExitUpdate::SupplyCenterProductionExitUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_rallyPointExists = false;
    m_rallyPoint.zero();
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
