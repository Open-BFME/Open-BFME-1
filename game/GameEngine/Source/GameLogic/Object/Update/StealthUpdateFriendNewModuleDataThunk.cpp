// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StealthUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
class StealthUpdateModuleData
{
public:
	StealthUpdateModuleData();
	virtual ~StealthUpdateModuleData();

private:
	unsigned char m_pad[0x320];
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

extern "C" void __cdecl StealthUpdateFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
class StealthUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@StealthUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StealthUpdate::friend_newModuleData(INI *ini)
{
	StealthUpdateModuleData *data = new StealthUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &StealthUpdateFieldParse);
	return (ModuleData *)data;
}
