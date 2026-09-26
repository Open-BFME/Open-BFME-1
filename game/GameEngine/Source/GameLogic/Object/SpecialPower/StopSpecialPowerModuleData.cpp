// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: StopSpecialPowerModuleData ctor.

class ModuleDataBase_StopSpecialPowerModuleData
{
public:
	ModuleDataBase_StopSpecialPowerModuleData();
	virtual ~ModuleDataBase_StopSpecialPowerModuleData();
private:
	unsigned char m_base[524];
};

class StopSpecialPowerModuleData : public ModuleDataBase_StopSpecialPowerModuleData
{
public:
	StopSpecialPowerModuleData();
	virtual ~StopSpecialPowerModuleData();
private:
	unsigned int m_zero;
};

// ??0StopSpecialPowerModuleData@@QAE@XZ
StopSpecialPowerModuleData::StopSpecialPowerModuleData()
	: ModuleDataBase_StopSpecialPowerModuleData()
{
	m_zero = 0;
}
