// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// readable body of ??0StealthDetectorUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdate.cpp

class Thing;
class ModuleData;
class Object;

extern int GetGameLogicRandomValue(int, int, char *, int);

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();
protected:
    void *m_moduleData;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthDetectorUpdate.h
class StealthDetectorUpdateModuleData
{
public:
    unsigned char m_f00[8];
    unsigned int m_updateRate;
    unsigned char m_f0c[4];
    unsigned char m_initiallyDisabled;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthDetectorUpdate.h
class StealthDetectorUpdate : public UpdateModule
{
public:
    StealthDetectorUpdate(Thing *, const ModuleData *);
private:
    bool m_enabled;
};

#define GameLogicRandomValue(lo, hi) GetGameLogicRandomValue((lo), (hi), __FILE__, __LINE__)

// ??0StealthDetectorUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
StealthDetectorUpdate::StealthDetectorUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    const StealthDetectorUpdateModuleData *data = (const StealthDetectorUpdateModuleData *)m_moduleData;
    m_enabled = !data->m_initiallyDisabled;
#line 77 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StealthDetectorUpdate.cpp"
    setWakeFrame(getObject(), m_enabled ? (UpdateSleepTime)GameLogicRandomValue(1, data->m_updateRate) : UPDATE_SLEEP_FOREVER);
}
