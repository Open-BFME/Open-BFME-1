// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeDeploySpecialPowerModuleData ctor.
// Base size 0x1d0; zeros; bools; floats 500.0f / 200.0f.

// Base ctor: ILT 0x00023FE7 -> 0x0026A820, the matched
// ??0WeaponModeSpecialPowerUpdateModuleDataBase@@QAE@XZ (shared module-data base).
class WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	WeaponModeSpecialPowerUpdateModuleDataBase();
	virtual ~WeaponModeSpecialPowerUpdateModuleDataBase();

private:
	unsigned char m_pad[0x1cc];
};

class SiegeDeploySpecialPowerModuleData : public WeaponModeSpecialPowerUpdateModuleDataBase
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
