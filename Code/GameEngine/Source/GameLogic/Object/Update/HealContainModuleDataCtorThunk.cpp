// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HealContainModuleData default ctor.
// Layout: vtable@0, gap@4 (uninit), then seven zeroed dwords @8..0x20.

class HealContainModuleData
{
public:
	HealContainModuleData();
	virtual ~HealContainModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
	unsigned int m_d;
	unsigned int m_e;
	unsigned int m_f;
	unsigned int m_g;
};

// ??0HealContainModuleData@@QAE@XZ
HealContainModuleData::HealContainModuleData()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
	m_d = 0;
	m_e = 0;
	m_f = 0;
	m_g = 0;
}