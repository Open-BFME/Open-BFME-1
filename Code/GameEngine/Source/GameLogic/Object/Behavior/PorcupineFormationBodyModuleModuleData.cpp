// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: PorcupineFormationBodyModuleModuleData ctor - base then zero two dwords.

class ModuleDataBase
{
public:
	ModuleDataBase();
	virtual ~ModuleDataBase();
private:
	unsigned char m_base[0x58]; // fields at +0x5c after vptr+0x58? 
};

// Actually retail: after base, zeros +0x5c and +0x60, then sets vtable.
// Base size is 0x5c if vtable shared... After base call, [esi+0x5c] and [esi+0x60] zeroed.
// If base includes vptr, base occupies 0..0x5b, fields at 0x5c.

class PorcupineFormationBodyModuleModuleData : public ModuleDataBase
{
public:
	PorcupineFormationBodyModuleModuleData();
	virtual ~PorcupineFormationBodyModuleModuleData();
private:
	unsigned int m_a; // +0x5c
	unsigned int m_b; // +0x60
};

// ??0PorcupineFormationBodyModuleModuleData@@QAE@XZ
PorcupineFormationBodyModuleModuleData::PorcupineFormationBodyModuleModuleData()
	: ModuleDataBase()
{
	m_a = 0;
	m_b = 0;
}
