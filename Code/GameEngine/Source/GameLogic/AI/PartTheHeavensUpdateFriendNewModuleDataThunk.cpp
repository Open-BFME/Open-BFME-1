// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PartTheHeavensUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PartTheHeavensUpdateModuleData
{
public:
	PartTheHeavensUpdateModuleData();
	virtual ~PartTheHeavensUpdateModuleData();

private:
	unsigned char m_pad[0x90];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char PartTheHeavensUpdateFieldParse;

class PartTheHeavensUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PartTheHeavensUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PartTheHeavensUpdate::friend_newModuleData(INI *ini)
{
	PartTheHeavensUpdateModuleData *data = new PartTheHeavensUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &PartTheHeavensUpdateFieldParse);
	return (ModuleData *)data;
}
