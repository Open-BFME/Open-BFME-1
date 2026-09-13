// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
//
// Near-twin of AutoAbilityBehaviorDestructorThunk.cpp's
// ??1AutoAbilityBehavior@@UAE@XZ (0x001ED6E0): same three-vtable-install,
// destroy-one-member, reinstall-and-call-base-dtor shape, but the member at
// offset 0x14 is EvacuateDamage's own std::list<EvacuationRecord>
// m_pendingEvacuations (see EvacuateDamageCtorModuleFactoryBody.cpp,
// 0x00251060) instead of an AsciiString at 0x20. Hierarchy mirrors that
// constructor's; the vtables installed (0x010B220C/0x010B2148/0x010B2138
// then 0x010B1DC4) are confirmed by tools/vtable_lookup.py to belong to
// EvacuateDamage's own ctor.

#include <list>

class Thing;
class ModuleData;

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

private:
	const ModuleData *m_moduleData;
	void *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class EvacuateDamageInterface { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModuleBase : public PB_DeepBase,
                          public PB_Iface1
{
public:
	virtual ~DamageModuleBase() {}
};

class DamageModule : public DamageModuleBase,
                      public EvacuateDamageInterface
{
public:
	virtual ~DamageModule() {}
};

struct EvacuationRecord
{
	unsigned int m_data[2];
};

class EvacuateDamage : public DamageModule
{
public:
	virtual ~EvacuateDamage();

private:
	std::list<EvacuationRecord> m_pendingEvacuations;
};

// ??1EvacuateDamage@@UAE@XZ
EvacuateDamage::~EvacuateDamage()
{
}
