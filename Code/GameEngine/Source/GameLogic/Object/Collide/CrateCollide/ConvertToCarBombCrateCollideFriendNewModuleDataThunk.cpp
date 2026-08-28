// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ConvertToCarBombCrateCollide::friend_newModuleData factory

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ConvertToCarBombCrateCollideModuleDataBaseShim
{
public:
	void construct();
};

class ConvertToCarBombCrateCollideModuleDataVtbl
{
public:
	ConvertToCarBombCrateCollideModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x5C];
};

class __declspec(novtable) ConvertToCarBombCrateCollideModuleData
{
public:
	ConvertToCarBombCrateCollideModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x5C];
};

ConvertToCarBombCrateCollideModuleData::ConvertToCarBombCrateCollideModuleData()
{
	((ConvertToCarBombCrateCollideModuleDataBaseShim *)this)->construct();
	((ConvertToCarBombCrateCollideModuleDataVtbl *)this)->ConvertToCarBombCrateCollideModuleDataVtbl::ConvertToCarBombCrateCollideModuleDataVtbl();
	*(unsigned int *)((char *)this + 0x54) = 0;
	*((unsigned char *)this + 0x58) = 0;
	*((unsigned char *)this + 0x59) = 0;
	*(unsigned int *)((char *)this + 0x5C) = 10;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ConvertToCarBombCrateCollideFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ConvertToCarBombCrateCollide.h
class ConvertToCarBombCrateCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *ConvertToCarBombCrateCollide::friend_newModuleData(INI *ini)
{
	ConvertToCarBombCrateCollideModuleData *data = new ConvertToCarBombCrateCollideModuleData;
	if (ini)
		ini->initFromINI(data, &ConvertToCarBombCrateCollideFieldParse);
	return (ModuleData *)data;
}
