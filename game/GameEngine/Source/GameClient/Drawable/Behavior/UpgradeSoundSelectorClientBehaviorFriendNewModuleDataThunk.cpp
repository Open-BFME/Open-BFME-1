// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeSoundSelectorClientBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	UpgradeSoundSelectorClientBehaviorModuleData();
	virtual ~UpgradeSoundSelectorClientBehaviorModuleData();

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

// Retail's factory does not push the field-parse builder itself: at +0x4E it
// pushes VA 0x004151A9, which is the 5-byte ILT thunk RVA 0x000151A9
// (e9 82 3f 5f 00 -> RVA 0x00609130, the 17-byte table-register forwarder
// ?Rva00609130@@YAXPAVGen00850920@@@Z in Common/MidTableRegisterForwarders.cpp,
// which registers the .rdata table 0x01115A9C).  The thunk is the address retail
// pushes, so the reference spells the thunk the ledger owns there; the real EA
// identity of the builder it reaches is
// ?buildFieldParse@UpgradeSoundSelectorClientBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// still address-derived in the ledger.
void __cdecl j_000151a9();

class UpgradeSoundSelectorClientBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@UpgradeSoundSelectorClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UpgradeSoundSelectorClientBehavior::friend_newModuleData(INI *ini)
{
	UpgradeSoundSelectorClientBehaviorModuleData *data = new UpgradeSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>( &j_000151a9 ));
	return (ModuleData *)data;
}
