// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ClearanceTestingSlowDeathBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ClearanceTestingSlowDeathBehaviorModuleData
{
public:
	ClearanceTestingSlowDeathBehaviorModuleData();
	virtual ~ClearanceTestingSlowDeathBehaviorModuleData();

private:
	unsigned char m_pad[0x21c];
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

// The proc retail passes is VA 0x004464A2, the ILT stub ?j_000464a2@@YAXXZ
// that jumps to 0x001F6EA0 (matched ?buildFieldParse@Rva001F6EA0@@SAXAAVWideMulti@@@Z).
extern void j_000464a2();

class ClearanceTestingSlowDeathBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ClearanceTestingSlowDeathBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ClearanceTestingSlowDeathBehavior::friend_newModuleData(INI *ini)
{
	ClearanceTestingSlowDeathBehaviorModuleData *data = new ClearanceTestingSlowDeathBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_000464a2);
	return (ModuleData *)data;
}
