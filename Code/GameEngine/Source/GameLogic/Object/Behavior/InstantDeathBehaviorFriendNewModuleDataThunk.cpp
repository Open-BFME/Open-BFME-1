// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: InstantDeathBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class InstantDeathBehaviorModuleData
{
public:
	InstantDeathBehaviorModuleData();
	virtual ~InstantDeathBehaviorModuleData();

private:
	unsigned char m_pad[0x60];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char InstantDeathBehaviorFieldParse;

class InstantDeathBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@InstantDeathBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *InstantDeathBehavior::friend_newModuleData(INI *ini)
{
	InstantDeathBehaviorModuleData *data = new InstantDeathBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &InstantDeathBehaviorFieldParse);
	return (ModuleData *)data;
}
