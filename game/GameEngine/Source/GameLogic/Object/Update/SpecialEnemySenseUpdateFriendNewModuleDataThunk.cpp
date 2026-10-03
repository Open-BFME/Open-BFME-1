// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialEnemySenseUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpecialEnemySenseUpdateModuleData
{
public:
	SpecialEnemySenseUpdateModuleData();
	virtual ~SpecialEnemySenseUpdateModuleData();

private:
	unsigned char m_pad[0x10];
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

// Retail pushes the address 0x00434252 (RVA 0x00034252) as the field-parse
// proc; that address is the 5-byte ILT thunk ?j_00034252@@YAXXZ, which routes
// to the matched forwarder at 0x00123D70. The proc is taken by address only, so
// the thunk's no-argument cdecl declaration is the honest view; the
// cast restores the MultiIniFieldParse ABI.
void j_00034252();

class SpecialEnemySenseUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SpecialEnemySenseUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialEnemySenseUpdate::friend_newModuleData(INI *ini)
{
	SpecialEnemySenseUpdateModuleData *data = new SpecialEnemySenseUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_00034252));
	return (ModuleData *)data;
}
