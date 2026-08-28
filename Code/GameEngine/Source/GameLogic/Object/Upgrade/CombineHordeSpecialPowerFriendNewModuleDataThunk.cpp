// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CombineHordeSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CombineHordeSpecialPowerModuleData
{
public:
	CombineHordeSpecialPowerModuleData();
	virtual ~CombineHordeSpecialPowerModuleData();

private:
	unsigned char m_pad[0x210];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char CombineHordeSpecialPowerFieldParse;

class CombineHordeSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CombineHordeSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CombineHordeSpecialPower::friend_newModuleData(INI *ini)
{
	CombineHordeSpecialPowerModuleData *data = new CombineHordeSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &CombineHordeSpecialPowerFieldParse);
	return (ModuleData *)data;
}
