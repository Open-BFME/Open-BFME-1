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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl BoneFXDamageFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXDamage.h
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
		ini->initFromINIMultiProc(data, &BoneFXDamageFieldParse);
	return (ModuleData *)data;
}
