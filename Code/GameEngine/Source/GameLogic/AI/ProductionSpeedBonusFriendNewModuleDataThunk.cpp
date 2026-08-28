// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ProductionSpeedBonus::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ProductionSpeedBonusModuleData
{
public:
	ProductionSpeedBonusModuleData();
	virtual ~ProductionSpeedBonusModuleData();

private:
	unsigned char m_pad[0x220];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ProductionSpeedBonusFieldParse;

class ProductionSpeedBonus
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ProductionSpeedBonus@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ProductionSpeedBonus::friend_newModuleData(INI *ini)
{
	ProductionSpeedBonusModuleData *data = new ProductionSpeedBonusModuleData;
	if (ini)
		ini->initFromINI(data, &ProductionSpeedBonusFieldParse);
	return (ModuleData *)data;
}
