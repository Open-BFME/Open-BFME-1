// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StopSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class StopSpecialPowerModuleData
{
public:
	StopSpecialPowerModuleData();
	virtual ~StopSpecialPowerModuleData();

private:
	unsigned char m_pad[0x210];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char StopSpecialPowerFieldParse;

class StopSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@StopSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StopSpecialPower::friend_newModuleData(INI *ini)
{
	StopSpecialPowerModuleData *data = new StopSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &StopSpecialPowerFieldParse);
	return (ModuleData *)data;
}
