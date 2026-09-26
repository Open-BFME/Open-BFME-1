// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BridgeTowerBehaviorModuleData
{
public:
	BridgeTowerBehaviorModuleData();
	virtual ~BridgeTowerBehaviorModuleData();

private:
	int m_pad; // force 8-byte allocation like retail
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

// Retail field-parse table address
extern "C" void __cdecl BridgeTowerBehaviorFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeTowerBehavior.h
class BridgeTowerBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

BridgeTowerBehaviorModuleData::BridgeTowerBehaviorModuleData()
{
}

// ?friend_newModuleData@BridgeTowerBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BridgeTowerBehavior::friend_newModuleData(INI *ini)
{
	BridgeTowerBehaviorModuleData *data = new BridgeTowerBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &BridgeTowerBehaviorFieldParse);
	return (ModuleData *)data;
}
