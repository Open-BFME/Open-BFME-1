// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SiegeDeployHordeSpecialPowerModuleData ctor.

class ModuleDataBase_SiegeDeployHordeSpecialPowerModuleData
{
public:
	ModuleDataBase_SiegeDeployHordeSpecialPowerModuleData();
	virtual ~ModuleDataBase_SiegeDeployHordeSpecialPowerModuleData();
private:
	unsigned char m_base[460];
};

class SiegeDeployHordeSpecialPowerModuleData : public ModuleDataBase_SiegeDeployHordeSpecialPowerModuleData
{
public:
	SiegeDeployHordeSpecialPowerModuleData();
	virtual ~SiegeDeployHordeSpecialPowerModuleData();
private:
	unsigned char m_flag;
};

// ??0SiegeDeployHordeSpecialPowerModuleData@@QAE@XZ
SiegeDeployHordeSpecialPowerModuleData::SiegeDeployHordeSpecialPowerModuleData()
	: ModuleDataBase_SiegeDeployHordeSpecialPowerModuleData()
{
	m_flag = 0;
}
