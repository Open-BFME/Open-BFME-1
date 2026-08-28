// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterProductionExitUpdate.h
class SupplyCenterProductionExitUpdateModuleData
{
public:
	SupplyCenterProductionExitUpdateModuleData();
	virtual ~SupplyCenterProductionExitUpdateModuleData();

private:
	int m_pad;
	int m0, m1, m2, m3, m4, m5;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SupplyCenterProductionExitUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterProductionExitUpdate.h
class SupplyCenterProductionExitUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

SupplyCenterProductionExitUpdateModuleData::SupplyCenterProductionExitUpdateModuleData()
	: m0(0), m1(0), m2(0), m3(0), m4(0), m5(0)
{
}

ModuleData *SupplyCenterProductionExitUpdate::friend_newModuleData(INI *ini)
{
	SupplyCenterProductionExitUpdateModuleData *data = new SupplyCenterProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &SupplyCenterProductionExitUpdateFieldParse);
	return (ModuleData *)data;
}
