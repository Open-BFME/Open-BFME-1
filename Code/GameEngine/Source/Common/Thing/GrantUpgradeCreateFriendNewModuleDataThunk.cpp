// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GrantUpgradeCreate::friend_newModuleData factory, retail 0x0011E560,
// converted out of a machine byte dump and repointed off 0x001171F0.
//
// The registration block pairs the AsciiString "GrantUpgradeCreate" with this address. The
// allocation size settles it against the row the name sat on: this body hands
// operator new 0x18, which is sizeof(GrantUpgradeCreateModuleData) with its vptr, where
// 0x001171F0 hands it 0x14.
//
// The constructor is reached through link thunk 0x00008B89, landing on
// 0x0024FA80.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeCreate.h
class GrantUpgradeCreateModuleData
{
public:
	GrantUpgradeCreateModuleData();
	virtual ~GrantUpgradeCreateModuleData();

private:
	unsigned char m_pad[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GrantUpgradeCreateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeCreate.h
class GrantUpgradeCreate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GrantUpgradeCreate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GrantUpgradeCreate::friend_newModuleData(INI *ini)
{
	GrantUpgradeCreateModuleData *data = new GrantUpgradeCreateModuleData;
	if (ini)
		ini->initFromINI(data, &GrantUpgradeCreateFieldParse);
	return (ModuleData *)data;
}
