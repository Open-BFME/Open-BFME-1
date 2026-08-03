// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: HordeContainModuleData ctor.

class ModuleDataBase_HordeContainModuleData
{
public:
	ModuleDataBase_HordeContainModuleData();
	virtual ~ModuleDataBase_HordeContainModuleData();
private:
	unsigned char m_base[356];
};

class HordeContainModuleData : public ModuleDataBase_HordeContainModuleData
{
public:
	HordeContainModuleData();
	virtual ~HordeContainModuleData();
private:
	unsigned int m_zero;
};

// ??0HordeContainModuleData@@QAE@XZ
HordeContainModuleData::HordeContainModuleData()
	: ModuleDataBase_HordeContainModuleData()
{
	m_zero = 0;
}
