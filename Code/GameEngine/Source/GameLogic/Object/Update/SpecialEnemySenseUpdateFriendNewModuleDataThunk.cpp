// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialEnemySenseUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpecialEnemySenseUpdateModuleData
{
public:
	SpecialEnemySenseUpdateModuleData();
	virtual ~SpecialEnemySenseUpdateModuleData();

private:
	unsigned char m_pad[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SpecialEnemySenseUpdateFieldParse;

class SpecialEnemySenseUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SpecialEnemySenseUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialEnemySenseUpdate::friend_newModuleData(INI *ini)
{
	SpecialEnemySenseUpdateModuleData *data = new SpecialEnemySenseUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &SpecialEnemySenseUpdateFieldParse);
	return (ModuleData *)data;
}
