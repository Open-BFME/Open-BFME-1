// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Callback used while inspecting contained objects.  The retail body walks
// the object's final template, checks the BFME upgrade-broadcast flag, and
// marks the callback state when the contained upgrade sink rejects the test.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Overridable
{
public:
    virtual ~Overridable();
    const Overridable *getFinalOverride() const;
    Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
    unsigned char m_pad[0xc8];
    UnsignedInt m_kindof;
    UnsignedInt m_flags;
};

class Rva004A41D0UpgradeSink
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual Bool predicate() const;
};

class Rva004A41D0ContainModule
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual Rva004A41D0UpgradeSink *getUpgradeSink();
};

void __cdecl Rva004A41D0UpgradeSinkCallback(void *object, void *userData)
{
    ThingTemplate *thingTemplate =
        *(ThingTemplate **)((char *)object + 4);
    if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
        thingTemplate = (ThingTemplate *)
            thingTemplate->m_nextOverride->getFinalOverride();

    if ((thingTemplate->m_flags & 0x1000) == 0)
        return;

    Rva004A41D0ContainModule *contain =
        *(Rva004A41D0ContainModule **)((char *)object + 0x1fc);
    if (contain == 0)
        return;

    Rva004A41D0UpgradeSink *sink = contain->getUpgradeSink();
    if (sink == 0)
        return;

    if (!sink->predicate())
        *(unsigned char *)((char *)userData + 4) = 1;
}
