// cl: /DNDEBUG /MD /EHsc
// readable body of ??0StructureCollapseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/StructureCollapseUpdate.cpp
// ModuleFactory reaches this constructor through ILT 0x0004A345. Its
// independently verified 0x44-byte allocation includes the BFME tail absent
// from the Zero Hour header.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class SCU_DeepBase
{
public:
    SCU_DeepBase(Thing *, const ModuleData *);
    virtual ~SCU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class SCU_Iface1 { public: virtual void slot(); };
class SCU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public SCU_DeepBase, public SCU_Iface1, public SCU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : SCU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
    virtual void onDie();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureCollapseUpdate.h
class StructureCollapseUpdate : public UpdateModule, public DieModuleInterface
{
public:
    StructureCollapseUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_collapseFrame;
    unsigned int m_burstFrame;
    unsigned int m_collapseState;
    float m_collapseVelocity;
    float m_currentHeight;
    unsigned int m_bfmeTail38;
    unsigned int m_bfmeTail3c;
    unsigned int m_bfmeTail40;
};

// ??0StructureCollapseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
StructureCollapseUpdate::StructureCollapseUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_collapseFrame = 0;
    m_collapseState = 0;
    m_collapseVelocity = 0.0f;
    m_burstFrame = 0;
    m_currentHeight = 0.0f;
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
    m_bfmeTail38 = 0;
    m_bfmeTail3c = 0;
    m_bfmeTail40 = 0;
}
