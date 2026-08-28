// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the PointDefenseLaserUpdate constructor to clean C++.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1
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

class PB_Iface1
{
public:
    virtual void slot();
};

class PB_Iface2
{
public:
    virtual void slot();
};

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

class PointDefenseLaserUpdateIface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PointDefenseLaserUpdate.h
class PointDefenseLaserUpdate : public UpdateModule,
    public PointDefenseLaserUpdateIface
{
public:
    PointDefenseLaserUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_bestTargetID;
    unsigned int m_inRange;
    unsigned int m_nextScanFrames;
};

// ??0PointDefenseLaserUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
PointDefenseLaserUpdate::PointDefenseLaserUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData),
      m_bestTargetID(0), m_inRange(0), m_nextScanFrames(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
