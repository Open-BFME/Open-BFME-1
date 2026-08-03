// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialPowerCompletionDie::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpecialPowerCompletionDieModuleData
{
public:
	SpecialPowerCompletionDieModuleData();
	virtual ~SpecialPowerCompletionDieModuleData();

private:
	unsigned char m_pad[0x34];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SpecialPowerCompletionDieFieldParse;

class SpecialPowerCompletionDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SpecialPowerCompletionDie@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialPowerCompletionDie::friend_newModuleData(INI *ini)
{
	SpecialPowerCompletionDieModuleData *data = new SpecialPowerCompletionDieModuleData;
	if (ini)
		ini->initFromINI(data, &SpecialPowerCompletionDieFieldParse);
	return (ModuleData *)data;
}
