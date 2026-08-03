// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ExperienceScalarUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ExperienceScalarUpgradeModuleData
{
public:
	ExperienceScalarUpgradeModuleData();
	virtual ~ExperienceScalarUpgradeModuleData();

private:
	unsigned char m_pad[0x70];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ExperienceScalarUpgradeFieldParse;

class ExperienceScalarUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ExperienceScalarUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ExperienceScalarUpgrade::friend_newModuleData(INI *ini)
{
	ExperienceScalarUpgradeModuleData *data = new ExperienceScalarUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &ExperienceScalarUpgradeFieldParse);
	return (ModuleData *)data;
}
