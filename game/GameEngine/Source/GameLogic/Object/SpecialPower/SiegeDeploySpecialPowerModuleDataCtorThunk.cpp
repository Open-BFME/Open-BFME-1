// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeDeploySpecialPowerModuleData ctor.
// Base size 0x1d0; zeros; bools; floats 500.0f / 200.0f.

class SiegeDeploySpecialPowerModuleDataBase
{
public:
	SiegeDeploySpecialPowerModuleDataBase();
	virtual ~SiegeDeploySpecialPowerModuleDataBase();

private:
	unsigned char m_pad[0x1cc];
};

class SiegeDeploySpecialPowerModuleData : public SiegeDeploySpecialPowerModuleDataBase
{
public:
	SiegeDeploySpecialPowerModuleData();
	virtual ~SiegeDeploySpecialPowerModuleData();

private:
	unsigned int m_1d0;
	unsigned int m_1d4;
	unsigned char m_1d8;
	unsigned char m_1d9;
	unsigned char m_1da;
	unsigned char m_pad1db;
	float m_1dc;
	float m_1e0;
};

// ??0SiegeDeploySpecialPowerModuleData@@QAE@XZ
SiegeDeploySpecialPowerModuleData::SiegeDeploySpecialPowerModuleData()
{
	m_1d0 = 0;
	m_1d4 = 0;
	m_1d9 = 0;
	m_1da = 0;
	m_1d8 = 1;
	m_1dc = 500.0f;
	m_1e0 = 200.0f;
}
