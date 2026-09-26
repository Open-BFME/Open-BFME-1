// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CombineHordeSpecialPowerModuleData ctor.

class ModuleDataBase_CombineHordeSpecialPowerModuleData
{
public:
	ModuleDataBase_CombineHordeSpecialPowerModuleData();
	virtual ~ModuleDataBase_CombineHordeSpecialPowerModuleData();
private:
	unsigned char m_base[524];
};

class CombineHordeSpecialPowerModuleData : public ModuleDataBase_CombineHordeSpecialPowerModuleData
{
public:
	CombineHordeSpecialPowerModuleData();
	virtual ~CombineHordeSpecialPowerModuleData();
private:
	float m_field;
};

// ??0CombineHordeSpecialPowerModuleData@@QAE@XZ
CombineHordeSpecialPowerModuleData::CombineHordeSpecialPowerModuleData()
	: ModuleDataBase_CombineHordeSpecialPowerModuleData()
{
	m_field = 100.0f;
}
