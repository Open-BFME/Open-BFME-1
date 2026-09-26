// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDeploySpecialPowerModuleData dtor.
// Four same-type members @+0xc/+0x7c/+0xec/+0x15c.

class SiegeDeploySpecialPowerModuleDataMemberA
{
public:
	~SiegeDeploySpecialPowerModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class SiegeDeploySpecialPowerModuleDataBase
{
public:
	virtual ~SiegeDeploySpecialPowerModuleDataBase() {}
private:
	unsigned char m_pad[0x8];
};

class __declspec(novtable) SiegeDeploySpecialPowerModuleData
	: public SiegeDeploySpecialPowerModuleDataBase
{
public:
	virtual ~SiegeDeploySpecialPowerModuleData();
private:
	SiegeDeploySpecialPowerModuleDataMemberA m_a;
	unsigned char m_gap1[0x6c];
	SiegeDeploySpecialPowerModuleDataMemberA m_b;
	unsigned char m_gap2[0x6c];
	SiegeDeploySpecialPowerModuleDataMemberA m_c;
	unsigned char m_gap3[0x6c];
	SiegeDeploySpecialPowerModuleDataMemberA m_d;
};

// ??1SiegeDeploySpecialPowerModuleData@@UAE@XZ
SiegeDeploySpecialPowerModuleData::~SiegeDeploySpecialPowerModuleData()
{
}
