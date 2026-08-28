// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BoneFXDamageModuleData
{
public:
	BoneFXDamageModuleData();
	virtual ~BoneFXDamageModuleData();

private:
	int m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char BoneFXDamageFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXDamage.h
class BoneFXDamage
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

BoneFXDamageModuleData::BoneFXDamageModuleData()
{
}

// ?friend_newModuleData@BoneFXDamage@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BoneFXDamage::friend_newModuleData(INI *ini)
{
	BoneFXDamageModuleData *data = new BoneFXDamageModuleData;
	if (ini)
		ini->initFromINI(data, &BoneFXDamageFieldParse);
	return (ModuleData *)data;
}
