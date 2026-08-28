// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
    ObjectModule(Thing *, const ModuleData *);
    virtual ~ObjectModule();

protected:
    unsigned int m_04;

private:
    unsigned char m_pad[4];
};

class CritterEmitterUpdateIface1
{
public:
    virtual ~CritterEmitterUpdateIface1();
};

class CritterEmitterUpdateIface2
{
public:
    virtual ~CritterEmitterUpdateIface2();
};

class CritterEmitterUpdateBase : public ObjectModule,
    public CritterEmitterUpdateIface1,
    public CritterEmitterUpdateIface2
{
public:
    CritterEmitterUpdateBase(Thing *thing, const ModuleData *moduleData)
        : ObjectModule(thing, moduleData), m_14(0), m_18(-1), m_1c(-1)
    {
    }

    virtual ~CritterEmitterUpdateBase();

private:
    unsigned int m_14;
    int m_18;
    int m_1c;
};

class CritterEmitterUpdateIface3
{
public:
    virtual ~CritterEmitterUpdateIface3();
};

class CritterEmitterUpdate : public CritterEmitterUpdateBase,
    public CritterEmitterUpdateIface3
{
public:
    CritterEmitterUpdate(Thing *, const ModuleData *);

private:
    unsigned char m_24;
    unsigned char m_25;
};

// ??0CritterEmitterUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
CritterEmitterUpdate::CritterEmitterUpdate(Thing *thing, const ModuleData *moduleData)
    : CritterEmitterUpdateBase(thing, moduleData)
{
    m_24 = 0;
    m_25 = 1;
}
