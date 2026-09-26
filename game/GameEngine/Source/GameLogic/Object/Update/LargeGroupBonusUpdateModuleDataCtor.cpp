// cl: /DNDEBUG /MD /EHsc

// The class was named GrantStealthBehaviorModuleData from the ZH header of that
// name. BFME never shipped it: "GrantStealthBehavior" appears zero times in
// lotrbfme.exe, while "LargeGroupBonusUpdate" appears twice and
// targets/game/reverse/module_registry.tsv registers it with new_module_data_rva 0x00118BB0 --
// which is exactly where the ledger already puts
// ?friend_newModuleData@LargeGroupBonusUpdate@@. The ModuleData that factory
// builds is this one, so this body is its constructor.
// Base's own ctor is trivial and inlines away, so this ctor installs the
// derived vtable directly (same elision as DelayedDeathBodyConstructor.cpp).
// +0x4 is left untouched, matching retail.
class LargeGroupBonusUpdateModuleDataBase
{
public:
	virtual ~LargeGroupBonusUpdateModuleDataBase() {}

protected:
	unsigned int m_unused04;
};

// Already-landed interned attribute handle: game/GameEngine/Source/GameLogic/Object/Update/Gen003A0410Constructor.cpp
class Gen003A0410
{
public:
	Gen003A0410();

private:
	unsigned int m_handle;
};

class LargeGroupBonusUpdateModuleData : public LargeGroupBonusUpdateModuleDataBase
{
public:
	LargeGroupBonusUpdateModuleData();
	virtual ~LargeGroupBonusUpdateModuleData();

private:
	unsigned int m_healingAmount; // +0x08
	Gen003A0410 m_kindOfHandle;   // +0x0c
	volatile unsigned int m_gap10;         // +0x10
	volatile unsigned int m_gap14;         // +0x14
	volatile bool m_flag18;                // +0x18
	volatile float m_realVal1c;            // +0x1c
	volatile unsigned int m_gap20;         // +0x20
	volatile unsigned int m_gap24;         // +0x24
	volatile unsigned int m_gap28;         // +0x28
	volatile unsigned int m_gap2c;         // +0x2c
};

// ??0LargeGroupBonusUpdateModuleData@@QAE@XZ
LargeGroupBonusUpdateModuleData::LargeGroupBonusUpdateModuleData()
	: m_healingAmount( 5 )
{
	m_gap10 = 0;
	m_gap14 = 0;
	m_flag18 = true;
	m_realVal1c = 20.0f;
	m_gap20 = 0;
	m_gap24 = 0;
	m_gap28 = 0;
	m_gap2c = 0;
}
