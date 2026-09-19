// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefectorSpecialPowerModuleData ctor.

class ModuleDataBase_DefectorSpecialPowerModuleData
{
public:
	ModuleDataBase_DefectorSpecialPowerModuleData();
	virtual ~ModuleDataBase_DefectorSpecialPowerModuleData();
private:
	unsigned char m_base[524];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DefectorSpecialPower.h
class DefectorSpecialPowerModuleData : public ModuleDataBase_DefectorSpecialPowerModuleData
{
public:
	DefectorSpecialPowerModuleData();
	virtual ~DefectorSpecialPowerModuleData();
private:
	unsigned int m_field;
};

// ??0DefectorSpecialPowerModuleData@@QAE@XZ
DefectorSpecialPowerModuleData::DefectorSpecialPowerModuleData()
	: ModuleDataBase_DefectorSpecialPowerModuleData()
{
	m_field = 0;
}
