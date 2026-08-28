// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DevastateSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DevastateSpecialPowerModuleData
{
public:
	DevastateSpecialPowerModuleData();
	virtual ~DevastateSpecialPowerModuleData();

private:
	unsigned char m_pad[0x21c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DevastateSpecialPowerFieldParse;

class DevastateSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DevastateSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DevastateSpecialPower::friend_newModuleData(INI *ini)
{
	DevastateSpecialPowerModuleData *data = new DevastateSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &DevastateSpecialPowerFieldParse);
	return (ModuleData *)data;
}
