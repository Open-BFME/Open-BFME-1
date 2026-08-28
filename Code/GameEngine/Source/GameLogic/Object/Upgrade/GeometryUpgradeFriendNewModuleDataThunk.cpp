// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GeometryUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GeometryUpgradeModuleData
{
public:
	GeometryUpgradeModuleData();
	virtual ~GeometryUpgradeModuleData();

private:
	unsigned char m_pad[0x90];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GeometryUpgradeFieldParse;

class GeometryUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GeometryUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GeometryUpgrade::friend_newModuleData(INI *ini)
{
	GeometryUpgradeModuleData *data = new GeometryUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &GeometryUpgradeFieldParse);
	return (ModuleData *)data;
}
