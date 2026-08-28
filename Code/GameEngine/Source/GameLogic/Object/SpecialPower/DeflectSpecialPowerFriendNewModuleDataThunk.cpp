// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DeflectSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DeflectSpecialPowerModuleData
{
public:
	DeflectSpecialPowerModuleData();
	virtual ~DeflectSpecialPowerModuleData();

private:
	unsigned char m_pad[0x1CC];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DeflectSpecialPowerFieldParse;

class DeflectSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DeflectSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeflectSpecialPower::friend_newModuleData(INI *ini)
{
	DeflectSpecialPowerModuleData *data = new DeflectSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &DeflectSpecialPowerFieldParse);
	return (ModuleData *)data;
}
