// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeAIUpdate::friend_newModuleData
// Retail SEH factory: new(0x64); ModuleData ctor; optional initFromINI.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeAIUpdateModuleData
{
public:
	SiegeAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x60];
};

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

// Retail pushes the address 0x0043D9FB (RVA 0x0003d9fb) as the field-parse
// proc; that address is the 5-byte ILT thunk ?j_0003d9fb@@YAXXZ, which routes
// to the matched forwarder at 0x002C5300. The proc is taken by address only, so
// the thunk's no-argument cdecl declaration is the honest view; the
// cast restores the MultiIniFieldParse ABI.
extern "C" void __cdecl __identifier("SiegeAIUpdateFieldParse")();

class SiegeAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeAIUpdate::friend_newModuleData(INI *ini)
{
	SiegeAIUpdateModuleData *data = new SiegeAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&__identifier("SiegeAIUpdateFieldParse")));
	return (ModuleData *)data;
}
