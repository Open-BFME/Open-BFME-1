// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
    static AsciiString TheEmptyString;
};

enum ObjectID
{
    INVALID_OBJECT_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
    void init(const AsciiString &, ObjectID);

private:
    void *m_vtable;
    unsigned char m_data[0x6c];
};

class SlowDeathBehaviorPrimary
{
public:
    virtual void slowDeathBehaviorPrimaryAnchor();

private:
    unsigned char m_data[8];
};

class SlowDeathBehaviorSecondary
{
public:
    virtual void slowDeathBehaviorSecondaryAnchor();
};

class SlowDeathBehaviorTertiary
{
public:
    virtual void slowDeathBehaviorTertiaryAnchor();

private:
    unsigned char m_data[0xc];
};

class SlowDeathBehaviorDieInterface
{
public:
    virtual void slowDeathBehaviorDieAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h
class SlowDeathBehaviorInterface
{
public:
    virtual void slowDeathBehaviorAnchor();
};

class SlowDeathBehavior : public SlowDeathBehaviorPrimary,
    public SlowDeathBehaviorSecondary,
    public SlowDeathBehaviorTertiary,
    public SlowDeathBehaviorDieInterface,
    public SlowDeathBehaviorInterface
{
public:
    SlowDeathBehavior(Thing *, const ModuleData *);
    virtual ~SlowDeathBehavior();

private:
    unsigned char m_data[0x28];
};

class GiantBirdSlowDeathBehavior : public SlowDeathBehavior
{
public:
    GiantBirdSlowDeathBehavior(Thing *, const ModuleData *);

private:
    unsigned int m_acceleratedTimeScale;
    AudioEventRTS m_deathSound;
    unsigned char m_pad[0xc];
    unsigned int m_unknownD0;
    unsigned char m_unknownD4;
};

// ??0GiantBirdSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
GiantBirdSlowDeathBehavior::GiantBirdSlowDeathBehavior(Thing *thing, const ModuleData *moduleData)
    : SlowDeathBehavior(thing, moduleData)
{
    unsigned int zero = 0;
    m_deathSound.init(AsciiString::TheEmptyString, (ObjectID)zero);
    m_acceleratedTimeScale = zero;
    m_unknownD0 = zero;
    m_unknownD4 = (unsigned char)zero;
}
