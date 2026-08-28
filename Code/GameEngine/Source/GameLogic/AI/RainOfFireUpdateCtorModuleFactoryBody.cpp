// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor body through ILT 0x0000A0E2. The
// registration and 0x38-byte allocation identify the retail RainOfFireUpdate.

class Thing;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
    unsigned char m_pad[0x24];
    float m_initialDelay;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
    unsigned int getFrame() const { return m_frame; }

private:
    unsigned char m_pad[0x3c];
    unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class ROFU_DeepBase
{
public:
    ROFU_DeepBase(Thing *, const ModuleData *);
    virtual ~ROFU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class ROFU_Iface1 { public: virtual void slot(); };
class ROFU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ROFU_DeepBase, public ROFU_Iface1, public ROFU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : ROFU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    const ModuleData *getModuleData() const { return m_moduleData; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class ROFU_Interface
{
public:
    virtual void slot();
};

class RainOfFireUpdate : public UpdateModule, public ROFU_Interface
{
public:
    RainOfFireUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_frame;
    unsigned int m_f28;
    float m_f2c;
    unsigned int m_f30;
    float m_f34;
};

// ??0RainOfFireUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
RainOfFireUpdate::RainOfFireUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_frame(0x3fffffff), m_f28(0),
      m_f2c(1.0f), m_f30(0), m_f34(0.0f)
{
    const ModuleData *data = getModuleData();
    if (data)
    {
        m_frame = TheGameLogic->getFrame();
        m_f34 = data->m_initialDelay == 0.0f ? 1.0f : 0.0f;
    }
}
