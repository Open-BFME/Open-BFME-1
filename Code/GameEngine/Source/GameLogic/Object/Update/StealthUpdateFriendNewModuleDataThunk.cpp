// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StealthUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
class StealthUpdateModuleData
{
public:
	StealthUpdateModuleData();
	virtual ~StealthUpdateModuleData();

private:
	unsigned char m_pad[0x320];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char StealthUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
class StealthUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@StealthUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StealthUpdate::friend_newModuleData(INI *ini)
{
	StealthUpdateModuleData *data = new StealthUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &StealthUpdateFieldParse);
	return (ModuleData *)data;
}
