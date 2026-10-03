// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TooltipUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class TooltipUpgradeModuleData
{
public:
	TooltipUpgradeModuleData();
	virtual ~TooltipUpgradeModuleData();

private:
	unsigned char m_pad[0x74];
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

// Retail pushes the address 0x004297E9 (RVA 0x000297e9) as the field-parse
// proc; that address is the 5-byte ILT thunk ?j_000297e9@@YAXXZ, which routes
// to the matched forwarder at 0x002D93B0. The proc is taken by address only, so
// the thunk's no-argument cdecl declaration is the honest view; the
// cast restores the MultiIniFieldParse ABI.
void j_000297e9();

class TooltipUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@TooltipUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TooltipUpgrade::friend_newModuleData(INI *ini)
{
	TooltipUpgradeModuleData *data = new TooltipUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_000297e9));
	return (ModuleData *)data;
}
