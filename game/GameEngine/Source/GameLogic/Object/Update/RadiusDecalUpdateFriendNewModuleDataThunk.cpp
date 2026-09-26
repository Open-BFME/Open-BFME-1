// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h
class RadiusDecalUpdateModuleData
{
public:
	RadiusDecalUpdateModuleData();
	virtual ~RadiusDecalUpdateModuleData();

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

extern "C" void __cdecl RadiusDecalUpdateFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h
class RadiusDecalUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

RadiusDecalUpdateModuleData::RadiusDecalUpdateModuleData()
{
}

// ?friend_newModuleData@RadiusDecalUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RadiusDecalUpdate::friend_newModuleData(INI *ini)
{
	RadiusDecalUpdateModuleData *data = new RadiusDecalUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &RadiusDecalUpdateFieldParse);
	return (ModuleData *)data;
}
