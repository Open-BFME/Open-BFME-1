// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ExperienceLevelCreate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ExperienceLevelCreateModuleData
{
public:
	ExperienceLevelCreateModuleData();
	virtual ~ExperienceLevelCreateModuleData();

private:
	unsigned char m_pad[0xc];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ExperienceLevelCreateFieldParse;

class ExperienceLevelCreate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ExperienceLevelCreate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ExperienceLevelCreate::friend_newModuleData(INI *ini)
{
	ExperienceLevelCreateModuleData *data = new ExperienceLevelCreateModuleData;
	if (ini)
		ini->initFromINI(data, &ExperienceLevelCreateFieldParse);
	return (ModuleData *)data;
}
