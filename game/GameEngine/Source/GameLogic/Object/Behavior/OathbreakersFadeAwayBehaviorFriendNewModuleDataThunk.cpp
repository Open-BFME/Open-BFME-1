// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: OathbreakersFadeAwayBehavior::friend_newModuleData factory.
//
// Identity (ModuleFactory::init 0x0012C2E0, the named module registration
// chain, read from the retail image):
//   +0912 push 0x01090B68 "OathbreakersFadeAwayBehavior"
//   +0941 call ModuleFactory insert
//   +094A mov [eax],    0x0043D2D0  -> 0x0011E250
//   +0950 mov [eax+4],  0x00442078  -> 0x001246F0
// The [eax] slot is the module's instance factory, and 0x0011E250 is the
// matched friend_newModuleInstance@OathbreakersFadeAwayBehavior; the [eax+4]
// slot is its ModuleData factory, so 0x001246F0 IS this friend_newModuleData
// and not a shared/ICF twin of the SpawnUnit factory at 0x00125D70.
//
// Field shape, independently: the field-parse proc this body pushes
// (0x0042AEF5 -> 0x00201B90) carries the one-entry table at 0x010A502C,
// { "FadeOutTime", 0x004324DE }, and that field proc is an x87 float parser.
// The factory at 0x00125D70 allocates 0x20 bytes and instead pushes 0x0040A727 -> 0x0020D260,
// whose table (0x010A6FE8) is { "UnitName", ... } -- SpawnUnitBehavior.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);

class MultiIniFieldParse;

// 12-byte ModuleData: retail vftable 0x0108D748 plus two dwords.  The body's
// only INI field is the float "FadeOutTime" (field proc 0x004324DE is an x87
// float parser), but the ctor value retail stores at +0x08 is the immediate
// 1, not 1.0f (0x3F800000), so the member is written as the dword it is and
// is deliberately not named after the field.
class OathbreakersFadeAwayBehaviorModuleData
{
public:
	void *m_bfmeVptr;
	int m_bfme04;
	int m_bfme08;
};

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

extern "C" void __cdecl OathbreakersFadeAwayBehaviorFieldParse(MultiIniFieldParse &parse);

// Address-derived extern kept under its recorded name so the DIR32 check keeps
// resolving it: targets/game/reverse/dir32_addresses.csv carries
// ?g_bfmeRva0108D748ParseVtable@@3PAXA at 0x0108D748, which is this class's
// vftable.  The "Parse" token is historical (it was mis-read as a parse-node
// vtable) and asserts nothing beyond the address.
extern void *g_bfmeRva0108D748ParseVtable;

class OathbreakersFadeAwayBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@OathbreakersFadeAwayBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *OathbreakersFadeAwayBehavior::friend_newModuleData(INI *ini)
{
	OathbreakersFadeAwayBehaviorModuleData *data =
		(OathbreakersFadeAwayBehaviorModuleData *)operator new(0x0c);
	OathbreakersFadeAwayBehaviorModuleData *p;

	if (data) {
		data->m_bfmeVptr = &g_bfmeRva0108D748ParseVtable;
		data->m_bfme08 = 1;
		p = data;
	} else {
		p = 0;
	}

	if (ini)
		ini->initFromINIMultiProc(p, &OathbreakersFadeAwayBehaviorFieldParse);

	return (ModuleData *)p;
}
