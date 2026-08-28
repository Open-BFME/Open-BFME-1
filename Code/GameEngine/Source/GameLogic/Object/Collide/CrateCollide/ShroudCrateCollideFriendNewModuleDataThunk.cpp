// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ShroudCrateCollide::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ShroudCrateCollideModuleData
{
public:
	ShroudCrateCollideModuleData();
	virtual ~ShroudCrateCollideModuleData();

private:
	unsigned char m_pad[0x50];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ShroudCrateCollideFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ShroudCrateCollide.h
class ShroudCrateCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ShroudCrateCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ShroudCrateCollide::friend_newModuleData(INI *ini)
{
	ShroudCrateCollideModuleData *data = new ShroudCrateCollideModuleData;
	if (ini)
		ini->initFromINI(data, &ShroudCrateCollideFieldParse);
	return (ModuleData *)data;
}
