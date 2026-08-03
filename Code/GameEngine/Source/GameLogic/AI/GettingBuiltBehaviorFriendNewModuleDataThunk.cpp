// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GettingBuiltBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GettingBuiltBehaviorModuleData
{
public:
	GettingBuiltBehaviorModuleData();
	virtual ~GettingBuiltBehaviorModuleData();

private:
	unsigned char m_pad[0x3C];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GettingBuiltBehaviorFieldParse;

class GettingBuiltBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GettingBuiltBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GettingBuiltBehavior::friend_newModuleData(INI *ini)
{
	GettingBuiltBehaviorModuleData *data = new GettingBuiltBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &GettingBuiltBehaviorFieldParse);
	return (ModuleData *)data;
}
