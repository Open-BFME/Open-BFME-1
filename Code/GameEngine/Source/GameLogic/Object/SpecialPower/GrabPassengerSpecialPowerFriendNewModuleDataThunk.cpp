// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GrabPassengerSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GrabPassengerSpecialPowerModuleData
{
public:
	GrabPassengerSpecialPowerModuleData();
	virtual ~GrabPassengerSpecialPowerModuleData();

private:
	unsigned char m_pad[0x214];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GrabPassengerSpecialPowerFieldParse;

class GrabPassengerSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GrabPassengerSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GrabPassengerSpecialPower::friend_newModuleData(INI *ini)
{
	GrabPassengerSpecialPowerModuleData *data = new GrabPassengerSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &GrabPassengerSpecialPowerFieldParse);
	return (ModuleData *)data;
}
