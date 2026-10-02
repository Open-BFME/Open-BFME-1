// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
    static AsciiString TheEmptyString;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
    // ??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z (0x000B2CC0); the two-arg
    // positional ctor retail's ILT 0x00025306 routes to.
    AudioEventRTS(const AsciiString &, int);

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h
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
    : SlowDeathBehavior(thing, moduleData), m_deathSound(AsciiString::TheEmptyString, 0)
{
    unsigned int zero = 0;
    m_acceleratedTimeScale = zero;
    m_unknownD0 = zero;
    m_unknownD4 = (unsigned char)zero;
}
