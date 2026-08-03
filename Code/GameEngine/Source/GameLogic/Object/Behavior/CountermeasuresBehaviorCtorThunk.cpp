// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CountermeasuresBehavior constructor, reconstructed from retail layout.
// The first base is represented by its retail ICF owner, SlowDeathBehavior;
// UpgradeMux models the secondary virtual subobject at +0x50.

class Thing;
class ModuleData;

class SlowDeathBehavior
{
protected:
    unsigned char m_padding04[8];
    unsigned long m_slot0c;
    unsigned long m_slot10;
    unsigned char m_padding14[12];
    unsigned long m_slot20;
    unsigned long m_slot24;
    unsigned char m_padding28[0x28];

public:
    SlowDeathBehavior(Thing *, const ModuleData *);
    virtual ~SlowDeathBehavior() {}
};

class UpgradeMux
{
public:
    virtual ~UpgradeMux() {}
};

class CountermeasuresBehavior : public SlowDeathBehavior, public UpgradeMux
{
public:
    CountermeasuresBehavior(Thing *, const ModuleData *);
};

// ??0CountermeasuresBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
CountermeasuresBehavior::CountermeasuresBehavior(
    Thing *thing,
    const ModuleData *moduleData)
    : SlowDeathBehavior(thing, moduleData)
{
    m_slot0c = 0x010A3018;
    m_slot10 = 0x010A3008;
    m_slot20 = 0x010A3004;
    m_slot24 = 0x010A2FF0;
    *reinterpret_cast<unsigned long *>(reinterpret_cast<unsigned char *>(this) + 0x50) = 0x010A2FE0;
}
