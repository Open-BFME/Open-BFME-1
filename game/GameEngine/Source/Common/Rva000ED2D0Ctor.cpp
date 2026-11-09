// cl: /O2 /Ob0

// The vfptr stored at m_00 is retail's own DamageInfoInput vftable,
// ??_7DamageInfoInput@@6B@ at 0x01085DE0 (dir32_addresses.csv), declared here
// under its real name, so no linker alias directive is needed.
extern "C" const void *__identifier("??_7DamageInfoInput@@6B@")[];

class DamageInfoInput
{
	void *m_00;
	int m_sourceID;
	unsigned short m_sourcePlayerMask;
	int m_damageType;
	int m_10;
	int m_14;
	int m_18;
	char m_1C;
	char m_1D;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;

public:
	DamageInfoInput();
};

DamageInfoInput::DamageInfoInput()
{
	m_00 = (void *)__identifier("??_7DamageInfoInput@@6B@");
	m_sourceID = 0;
	m_sourcePlayerMask = 0;
	m_damageType = 0x16;
	m_10 = 0x0F;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_1D = 1;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_40 = 0;
	m_44 = 0x3F800000;
}
