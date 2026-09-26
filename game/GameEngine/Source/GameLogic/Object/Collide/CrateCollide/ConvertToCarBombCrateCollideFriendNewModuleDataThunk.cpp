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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl ConvertToCarBombCrateCollideFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ConvertToCarBombCrateCollide.h
class ConvertToCarBombCrateCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *ConvertToCarBombCrateCollide::friend_newModuleData(INI *ini)
{
	ConvertToCarBombCrateCollideModuleData *data = new ConvertToCarBombCrateCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &ConvertToCarBombCrateCollideFieldParse);
	return (ModuleData *)data;
}
