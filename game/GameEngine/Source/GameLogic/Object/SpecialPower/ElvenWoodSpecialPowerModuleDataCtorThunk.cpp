// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: ElvenWoodSpecialPowerModuleData ctor
// Base call, vtbl, zeros at +0x210..+0x220/+0x228/+0x22c, float +0x224=10.0f.

class ElvenWoodSpecialPowerModuleDataBase
{
public:
	ElvenWoodSpecialPowerModuleDataBase();
	virtual void elvenWoodModuleDataBaseAnchor();

private:
	unsigned char m_pad[0x20C];
};

extern "C" char ElvenWoodSpecialPowerModuleData_vtbl;

class __declspec(novtable) ElvenWoodSpecialPowerModuleData
	: public ElvenWoodSpecialPowerModuleDataBase
{
public:
	ElvenWoodSpecialPowerModuleData();

private:
	unsigned int m_210;
	unsigned int m_214;
	unsigned int m_218;
	unsigned int m_21c;
	unsigned int m_220;
	float m_224;
	unsigned int m_228;
	unsigned int m_22c;
};

// ??0ElvenWoodSpecialPowerModuleData@@QAE@XZ
ElvenWoodSpecialPowerModuleData::ElvenWoodSpecialPowerModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&ElvenWoodSpecialPowerModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_210) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_214) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_218) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_21c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_220) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_228) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_22c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_224) = 0x41200000u; // 10.0f
}
