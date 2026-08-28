// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDeploySpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeDeploySpecialPowerModuleData
{
public:
	SiegeDeploySpecialPowerModuleData();
	virtual ~SiegeDeploySpecialPowerModuleData();

private:
	unsigned char m_pad[0x1e0];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SiegeDeploySpecialPowerFieldParse;

class SiegeDeploySpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeDeploySpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDeploySpecialPower::friend_newModuleData(INI *ini)
{
	SiegeDeploySpecialPowerModuleData *data = new SiegeDeploySpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &SiegeDeploySpecialPowerFieldParse);
	return (ModuleData *)data;
}
