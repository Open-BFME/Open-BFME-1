// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: lift the HordeUpdate constructor dump to clean C++.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_DUMMY
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HordeUpdate.h
class HordeUpdateInterface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HordeUpdate.h
class HordeUpdate : public UpdateModule, public HordeUpdateInterface
{
public:
    HordeUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_lastHordeRefreshFrame;
    unsigned int m_flags;
};

// ??0HordeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
HordeUpdate::HordeUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData),
      m_lastHordeRefreshFrame(0),
      m_flags(0)
{
    setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
}
