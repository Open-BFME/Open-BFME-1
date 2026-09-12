// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantStealthBehavior.h
// Base's own ctor is trivial and inlines away, so this ctor installs the
// derived vtable directly (same elision as DelayedDeathBodyConstructor.cpp).
// +0x4 is left untouched, matching retail.
class GrantStealthBehaviorModuleDataBase
{
public:
	virtual ~GrantStealthBehaviorModuleDataBase() {}

protected:
	unsigned int m_unused04;
};

// Already-landed interned attribute handle: Code/GameEngine/Source/GameLogic/Object/Update/Gen003A0410Constructor.cpp
class Gen003A0410
{
public:
	Gen003A0410();

private:
	unsigned int m_handle;
};

class GrantStealthBehaviorModuleData : public GrantStealthBehaviorModuleDataBase
{
public:
	GrantStealthBehaviorModuleData();
	virtual ~GrantStealthBehaviorModuleData();

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

// ??0GrantStealthBehaviorModuleData@@QAE@XZ
GrantStealthBehaviorModuleData::GrantStealthBehaviorModuleData()
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
