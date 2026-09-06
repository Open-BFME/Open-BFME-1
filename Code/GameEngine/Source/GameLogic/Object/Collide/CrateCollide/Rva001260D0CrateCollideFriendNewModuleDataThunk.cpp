// cl: /DNDEBUG /MD /EHsc
// Open-BFME: friend_newModuleData factory, same shape as
// ConvertToCarBombCrateCollideFriendNewModuleDataThunk.cpp (fuzzy twin of
// 0x00125FD0, r0.855): base ctor is the pinned still-a-dump
// ??0CrateCollideModuleData@@QAE@XZ (0x000441CA), but this body then
// overwrites the vtable with a DIFFERENT constant (0x0108E998) and inits
// eight derived fields (0/0/0.5f/100.0f/0.5f/100/5000/false) instead of the
// twin's two, and parses with INI::initFromINIMultiProc + a function-pointer
// buildFieldParse table (0x004336BD) instead of initFromINI + an extern
// table -- see S4NewModuleData.cpp for that callee's recovered signature.
// Object size is 0x74B (push 0x74), so the derived-only storage is 0x74-4=
// 0x70 bytes starting at +0x54. Owning class name is not recovered; the
// address-derived class below only carries the evidence above.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class Gen_001260D0ModuleDataBaseShim
{
public:
	void construct();
};

class Gen_001260D0ModuleDataVtbl
{
public:
	Gen_001260D0ModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x70];
};

class __declspec(novtable) Gen_001260D0ModuleData
{
public:
	Gen_001260D0ModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x70];
};

Gen_001260D0ModuleData::Gen_001260D0ModuleData()
{
	((Gen_001260D0ModuleDataBaseShim *)this)->construct();
	((Gen_001260D0ModuleDataVtbl *)this)->Gen_001260D0ModuleDataVtbl::Gen_001260D0ModuleDataVtbl();
	*(unsigned int *)((char *)this + 0x54) = 0;
	*(unsigned int *)((char *)this + 0x58) = 0;
	*(float *)((char *)this + 0x5c) = 0.5f;
	*(float *)((char *)this + 0x60) = 100.0f;
	*(float *)((char *)this + 0x64) = 0.5f;
	*(unsigned int *)((char *)this + 0x68) = 100;
	*(unsigned int *)((char *)this + 0x6c) = 5000;
	*(unsigned char *)((char *)this + 0x70) = 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse;
class INI
{
public:
	void initFromINIMultiProc(void *what, void (*proc)(MultiIniFieldParse &));
};

class Gen_001260D0
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@Gen_001260D0@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *Gen_001260D0::friend_newModuleData(INI *ini)
{
	Gen_001260D0ModuleData *data = new Gen_001260D0ModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, Gen_001260D0::buildFieldParse);
	return (ModuleData *)data;
}
