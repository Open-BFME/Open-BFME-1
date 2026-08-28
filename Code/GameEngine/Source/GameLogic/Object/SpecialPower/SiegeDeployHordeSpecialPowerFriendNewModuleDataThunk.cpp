// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDeployHordeSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeDeployHordeSpecialPowerModuleData
{
public:
	SiegeDeployHordeSpecialPowerModuleData();
	virtual ~SiegeDeployHordeSpecialPowerModuleData();

private:
	unsigned char m_pad[0x1d0];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SiegeDeployHordeSpecialPowerFieldParse;

class SiegeDeployHordeSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeDeployHordeSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDeployHordeSpecialPower::friend_newModuleData(INI *ini)
{
	SiegeDeployHordeSpecialPowerModuleData *data = new SiegeDeployHordeSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &SiegeDeployHordeSpecialPowerFieldParse);
	return (ModuleData *)data;
}
