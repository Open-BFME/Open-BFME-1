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
	unsigned int m_unitCreatePointX;
	unsigned int m_unitCreatePointY;
	unsigned int m_unitCreatePointZ;
	unsigned int m_naturalRallyPointX;
	unsigned int m_naturalRallyPointY;
	unsigned int m_naturalRallyPointZ;
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
	m_unitCreatePointX = 0;
	m_unitCreatePointY = 0;
	m_unitCreatePointZ = 0;
	m_naturalRallyPointX = 0;
	m_naturalRallyPointY = 0;
	m_naturalRallyPointZ = 0;
}

// ?friend_newModuleData@DefaultProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DefaultProductionExitUpdate::friend_newModuleData(INI *ini)
{
	DefaultProductionExitUpdateModuleData *data = new DefaultProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &DefaultProductionExitUpdateFieldParse);
	return (ModuleData *)data;
}
