// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the DestroyEnvironmentUpdate constructor to clean C++.

class Thing;
class ModuleData;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
    unsigned int getFrame() const { return m_frame; }

private:
    unsigned char m_pad[0x3C];
    unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
    ObjectModule(Thing *, const ModuleData *);
    virtual ~ObjectModule();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
    virtual void updateModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
    virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule,
    public UpdateModuleInterface,
    public ModuleInterface
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : ObjectModule(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1)
    {
    }

protected:
    const ModuleData *getModuleData() const { return m_moduleData; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class DestroyEnvironmentUpdate : public UpdateModule
{
public:
    DestroyEnvironmentUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_nextCallFrame;
    unsigned int m_flags;
};

// ??0DestroyEnvironmentUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DestroyEnvironmentUpdate::DestroyEnvironmentUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData),
      m_nextCallFrame(0x3FFFFFFF),
      m_flags(0)
{
    if (getModuleData() != 0)
        m_nextCallFrame = TheGameLogic->getFrame();
}
