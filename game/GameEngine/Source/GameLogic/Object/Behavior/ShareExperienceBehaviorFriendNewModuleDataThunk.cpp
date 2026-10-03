// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ShareExperienceBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ShareExperienceBehaviorModuleData
{
public:
	ShareExperienceBehaviorModuleData();
	virtual ~ShareExperienceBehaviorModuleData();

private:
	unsigned char m_pad[0x14];
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

// Retail pushes the address 0x0043A657 (RVA 0x0003a657) as the field-parse
// proc; that address is the 5-byte ILT thunk ?j_0003a657@@YAXXZ, which routes
// to the matched forwarder at 0x00205720. The proc is taken by address only, so
// the thunk's no-argument cdecl declaration is the honest view; the
// cast restores the MultiIniFieldParse ABI.
void j_0003a657();

class ShareExperienceBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ShareExperienceBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ShareExperienceBehavior::friend_newModuleData(INI *ini)
{
	ShareExperienceBehaviorModuleData *data = new ShareExperienceBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_0003a657));
	return (ModuleData *)data;
}
