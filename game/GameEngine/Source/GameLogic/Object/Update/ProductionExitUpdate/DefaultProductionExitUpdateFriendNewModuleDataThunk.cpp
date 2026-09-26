// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DefaultProductionExitUpdate.h
class DefaultProductionExitUpdateModuleData
{
public:
	DefaultProductionExitUpdateModuleData();
	virtual ~DefaultProductionExitUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
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

extern "C" void __cdecl DefaultProductionExitUpdateFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DefaultProductionExitUpdate.h
class DefaultProductionExitUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

DefaultProductionExitUpdateModuleData::DefaultProductionExitUpdateModuleData()
{
	m_08 = 0;
	m_0c = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
}

// ?friend_newModuleData@DefaultProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DefaultProductionExitUpdate::friend_newModuleData(INI *ini)
{
	DefaultProductionExitUpdateModuleData *data = new DefaultProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &DefaultProductionExitUpdateFieldParse);
	return (ModuleData *)data;
}
