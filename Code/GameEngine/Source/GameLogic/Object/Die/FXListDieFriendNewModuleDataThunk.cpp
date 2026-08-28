// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FXListDie::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FXListDie.h
class FXListDieModuleData
{
public:
	FXListDieModuleData();
	virtual ~FXListDieModuleData();

private:
	unsigned char m_pad[0x38];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char FXListDieFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FXListDie.h
class FXListDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FXListDie@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FXListDie::friend_newModuleData(INI *ini)
{
	FXListDieModuleData *data = new FXListDieModuleData;
	if (ini)
		ini->initFromINI(data, &FXListDieFieldParse);
	return (ModuleData *)data;
}
