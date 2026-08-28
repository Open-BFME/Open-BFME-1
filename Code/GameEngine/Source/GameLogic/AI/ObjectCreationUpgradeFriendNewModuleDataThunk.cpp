// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ObjectCreationUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h
class ObjectCreationUpgradeModuleData
{
public:
	ObjectCreationUpgradeModuleData();
	virtual ~ObjectCreationUpgradeModuleData();

private:
	unsigned char m_pad[0xa0];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ObjectCreationUpgradeFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h
class ObjectCreationUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ObjectCreationUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ObjectCreationUpgrade::friend_newModuleData(INI *ini)
{
	ObjectCreationUpgradeModuleData *data = new ObjectCreationUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &ObjectCreationUpgradeFieldParse);
	return (ModuleData *)data;
}
