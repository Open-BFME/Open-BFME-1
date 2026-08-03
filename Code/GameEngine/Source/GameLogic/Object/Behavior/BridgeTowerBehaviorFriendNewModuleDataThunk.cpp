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

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

// Retail field-parse table address
extern "C" char BridgeTowerBehaviorFieldParse;

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
		ini->initFromINI(data, &BridgeTowerBehaviorFieldParse);
	return (ModuleData *)data;
}
