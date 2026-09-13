// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
// The registration-named ModuleFactory entry allocates the 0x18-byte BFME
// EvacuateDamage and reaches this constructor through ILT 0x0003BD40.

#include <list>

class Thing;
class ModuleData;

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

private:
    const ModuleData *m_moduleData;
    void *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class EvacuateDamageInterface { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModule : public PB_DeepBase,
                     public PB_Iface1,
                     public EvacuateDamageInterface
{
public:
    DamageModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData) {}
};

struct EvacuationRecord
{
    unsigned int m_data[2];
};

class EvacuateDamage : public DamageModule
{
public:
    EvacuateDamage(Thing *, const ModuleData *);

private:
    std::list<EvacuationRecord> m_pendingEvacuations;
};

// ??0EvacuateDamage@@QAE@PAVThing@@PBVModuleData@@@Z
EvacuateDamage::EvacuateDamage(Thing *thing, const ModuleData *moduleData)
    : DamageModule(thing, moduleData)
{
    m_pendingEvacuations.clear();
}
