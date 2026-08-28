// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HeroDie::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HeroDieModuleData
{
public:
	HeroDieModuleData();
	virtual ~HeroDieModuleData();

private:
	unsigned char m_pad[0x34];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HeroDieFieldParse;

class HeroDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HeroDie@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HeroDie::friend_newModuleData(INI *ini)
{
	HeroDieModuleData *data = new HeroDieModuleData;
	if (ini)
		ini->initFromINI(data, &HeroDieFieldParse);
	return (ModuleData *)data;
}
