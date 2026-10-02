// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AutoAbilityBehaviorModuleData default ctor.
// This constructor also emits the public scalar-deleting destructor at
// 0x001ED860 (30 bytes), selected by vtable 0x010A1A70 slot zero via
// ILT 0x0002775F. Keep that wrapper here: a separate default-construction
// forcing TU otherwise emits a competing, vptr-only default constructor.

class AutoAbilityBehaviorModuleData
{
public:
	AutoAbilityBehaviorModuleData();
	virtual ~AutoAbilityBehaviorModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
};

// ??0AutoAbilityBehaviorModuleData@@QAE@XZ
AutoAbilityBehaviorModuleData::AutoAbilityBehaviorModuleData()
{
	m_08 = 0;
}