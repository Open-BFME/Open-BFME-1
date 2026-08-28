// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EnragedBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class EnragedBehaviorModuleData
{
public:
	EnragedBehaviorModuleData();
	virtual ~EnragedBehaviorModuleData();

private:
	unsigned char m_pad[0x28];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char EnragedBehaviorFieldParse;

class EnragedBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@EnragedBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EnragedBehavior::friend_newModuleData(INI *ini)
{
	EnragedBehaviorModuleData *data = new EnragedBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &EnragedBehaviorFieldParse);
	return (ModuleData *)data;
}
