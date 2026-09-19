// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BuildingBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BuildingBehaviorModuleData
{
public:
	BuildingBehaviorModuleData();
	virtual ~BuildingBehaviorModuleData();

private:
	unsigned char m_pad[0x20];
};

class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl BuildingBehaviorFieldParse(MultiIniFieldParse &parse);

class BuildingBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BuildingBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BuildingBehavior::friend_newModuleData(INI *ini)
{
	BuildingBehaviorModuleData *data = new BuildingBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &BuildingBehaviorFieldParse);
	return (ModuleData *)data;
}
