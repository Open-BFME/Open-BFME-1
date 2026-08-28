// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DarknessSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DarknessSpecialPowerModuleData
{
public:
	DarknessSpecialPowerModuleData();
	virtual ~DarknessSpecialPowerModuleData();

private:
	unsigned char m_pad[0x214];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DarknessSpecialPowerFieldParse;

class DarknessSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DarknessSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DarknessSpecialPower::friend_newModuleData(INI *ini)
{
	DarknessSpecialPowerModuleData *data = new DarknessSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &DarknessSpecialPowerFieldParse);
	return (ModuleData *)data;
}
