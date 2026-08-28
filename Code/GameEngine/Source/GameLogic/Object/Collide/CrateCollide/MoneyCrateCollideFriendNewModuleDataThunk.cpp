// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MoneyCrateCollide::friend_newModuleData factory

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class MoneyCrateCollideModuleDataBaseShim
{
public:
	void construct();
};

class MoneyCrateCollideModuleDataVtbl
{
public:
	MoneyCrateCollideModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x54];
};

class __declspec(novtable) MoneyCrateCollideModuleData
{
public:
	MoneyCrateCollideModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x54];
};

MoneyCrateCollideModuleData::MoneyCrateCollideModuleData()
{
	((MoneyCrateCollideModuleDataBaseShim *)this)->construct();
	((MoneyCrateCollideModuleDataVtbl *)this)->MoneyCrateCollideModuleDataVtbl::MoneyCrateCollideModuleDataVtbl();
	*(unsigned int *)((char *)this + 0x54) = 0x0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char MoneyCrateCollideFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MoneyCrateCollide.h
class MoneyCrateCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *MoneyCrateCollide::friend_newModuleData(INI *ini)
{
	MoneyCrateCollideModuleData *data = new MoneyCrateCollideModuleData;
	if (ini)
		ini->initFromINI(data, &MoneyCrateCollideFieldParse);
	return (ModuleData *)data;
}
