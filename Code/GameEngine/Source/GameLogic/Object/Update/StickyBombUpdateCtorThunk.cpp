// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: lift the StickyBombUpdate constructor dump to clean C++.

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

class StickyBombUpdateInterface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StickyBombUpdate.h
class StickyBombUpdate : public UpdateModule, public StickyBombUpdateInterface
{
public:
    StickyBombUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_targetID;
    unsigned int m_dieFrame;
};

// ??0StickyBombUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
StickyBombUpdate::StickyBombUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_targetID(0), m_dieFrame(0)
{
    setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
}
