// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoPickUpUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AutoPickUpUpdateModuleData
{
public:
	AutoPickUpUpdateModuleData();
	virtual ~AutoPickUpUpdateModuleData();

private:
	unsigned char m_pad[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AutoPickUpUpdateFieldParse;

class AutoPickUpUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AutoPickUpUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AutoPickUpUpdate::friend_newModuleData(INI *ini)
{
	AutoPickUpUpdateModuleData *data = new AutoPickUpUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &AutoPickUpUpdateFieldParse);
	return (ModuleData *)data;
}
