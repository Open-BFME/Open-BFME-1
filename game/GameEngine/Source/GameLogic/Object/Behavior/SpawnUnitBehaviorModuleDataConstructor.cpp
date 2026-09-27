// cl: /DNDEBUG /MD /EHsc
// SpawnUnitBehaviorModuleData constructor, RVA00125CE0,114B.
// ModuleFactory::init0012C2E0 registers literal SpawnUnitBehavior (+08BA,
// VA01090B8C) with datafactory ILT3F611 (+08F8) ->00125D70 ->this ctor.
// Oathbreakers registration instead uses ILT42078 ->001246F0.
// Installed vtable0108E890 slot0 ->ILT2A78E ->00126ED0, the matched
// SpawnUnit scalar-deleting destructor; complete destructor00126F00
// releases the strings at+8/+C. Scalar offsets retain opaque names.
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern const char g_Rva0107301CEmptyString[];

// +0x00 is the vtable this constructor installs and +0x04 is never written;
// the base is one word past it, so the derived record starts at +0x08. The
// vtable is written by the derived constructor because the base contributes no
// constructor call of its own.
class SpawnUnitBehaviorModuleDataBase
{
public:
	virtual ~SpawnUnitBehaviorModuleDataBase();

private:
	unsigned char m_bfme04[4];
};

class SpawnUnitBehaviorModuleData : public SpawnUnitBehaviorModuleDataBase
{
public:
	SpawnUnitBehaviorModuleData();

private:
	// Named factory 0x00125D70 passes callback ILT 0x0000A727 ->
	// 0x0020D260. Its FieldParse table at RVA 0x00CA6FE8 binds
	// UnitName/+8 and UnitCommand/+0x0c to INI::parseAsciiString
	// (0x00851EE0). These are table witnesses, not inferred layout names.
	AsciiString m_unitName;
	AsciiString m_unitCommand;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	bool m_bfme1c;
};

// ??0SpawnUnitBehaviorModuleData@@QAE@XZ
SpawnUnitBehaviorModuleData::SpawnUnitBehaviorModuleData()
{
	// StringBase<char>::set, not AsciiString::set: AsciiString declares its
	// own set overloads and so hides the two-argument base one. The qualified
	// call is what retail encodes -- both call sites at +0x40 and +0x4D are
	// rel32s to 0x00887D20, ?set@?$StringBase@D@@QAEXPBDH@Z.
	m_unitName.StringBase<char>::set(g_Rva0107301CEmptyString, 0);
	m_unitCommand.StringBase<char>::set(g_Rva0107301CEmptyString, 0);
	m_bfme14 = 0;
	m_bfme18 = 0;
	m_bfme10 = 0;
	m_bfme1c = false;
}
