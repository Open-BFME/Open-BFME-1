// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's 0x44-byte allocation and retail interface stores preserve
// the BFME fields missing from the Zero Hour StructureCollapseUpdate layout.

class Thing;
class ModuleData;
class Object;
class BodyModuleInterface;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class Module
{
public:
    virtual ~Module();
protected:
    const ModuleData *m_moduleData;
};

class ObjectModule : public Module
{
public:
    ObjectModule(Thing *, const ModuleData *);
protected:
    Object *m_object;
};

class BehaviorModuleInterface { public: virtual BodyModuleInterface *getBody(); };
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
    BehaviorModule(Thing *thing, const ModuleData *moduleData)
        : ObjectModule(thing, moduleData) {}
    virtual ~BehaviorModule() {}
};

class UpdateModuleInterface { public: virtual UpdateSleepTime update(); };
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : BehaviorModule(thing, moduleData), m_bfmeField14(0),
          m_bfmeField18(-1), m_bfmeField1c(-1) {}
    virtual ~UpdateModule() {}
protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }
private:
    unsigned int m_bfmeField14;
    int m_bfmeField18;
    int m_bfmeField1c;
};

class DieModuleInterface { public: virtual void onDie(); };
class StructureCollapseUpdate : public UpdateModule, public DieModuleInterface
{
public:
    StructureCollapseUpdate(Thing *, const ModuleData *);
protected:
    virtual ~StructureCollapseUpdate();
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

StructureCollapseUpdate::~StructureCollapseUpdate()
{
}
