// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: VeterancyCrateCollide::friend_newModuleData factory.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class VeterancyCrateCollideModuleDataBaseShim
{
public:
	void construct();
};

class VeterancyCrateCollideModuleDataVtbl
{
public:
	VeterancyCrateCollideModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x5c];
};

class __declspec(novtable) VeterancyCrateCollideModuleData
{
public:
	VeterancyCrateCollideModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x5c];
};

// ??0VeterancyCrateCollideModuleData@@ present-unmatched
VeterancyCrateCollideModuleData::VeterancyCrateCollideModuleData()
{
	((VeterancyCrateCollideModuleDataBaseShim *)this)->construct();
	((VeterancyCrateCollideModuleDataVtbl *)this)
		->VeterancyCrateCollideModuleDataVtbl::VeterancyCrateCollideModuleDataVtbl();
	unsigned int z = 0;
	*(unsigned int *)((char *)this + 0x54) = z;
	*((unsigned char *)this + 0x58) = (unsigned char)z;
	*((unsigned char *)this + 0x59) = (unsigned char)z;
	*(unsigned int *)((char *)this + 0x5c) = 0xa;
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

extern "C" void __cdecl VeterancyCrateCollideFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/VeterancyCrateCollide.h
class VeterancyCrateCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@VeterancyCrateCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *VeterancyCrateCollide::friend_newModuleData(INI *ini)
{
	VeterancyCrateCollideModuleData *data = new VeterancyCrateCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &VeterancyCrateCollideFieldParse);
	return (ModuleData *)data;
}
