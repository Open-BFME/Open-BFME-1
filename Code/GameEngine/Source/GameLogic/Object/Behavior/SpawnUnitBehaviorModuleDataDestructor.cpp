// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnUnitBehaviorModuleData dtor.
// Retail 80B SEH: destroy AsciiString @+0xc then @+0x8, base vtbl store. AsciiString pin 0x887940 (ICF with Oathbreakers).

// Retail destroys AsciiString members at +0x0c and +0x08 through
// releaseBuffer 0x00887940. Use the canonical four-byte string definition.
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class SpawnUnitBehaviorModuleDataBase
{
public:
	virtual ~SpawnUnitBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) SpawnUnitBehaviorModuleData
	: public SpawnUnitBehaviorModuleDataBase
{
public:
	virtual ~SpawnUnitBehaviorModuleData();

private:
	// Named factory 0x00125D70 passes callback ILT 0x0000A727 ->
	// 0x0020D260. Its FieldParse table at RVA 0x00CA6FE8 binds
	// UnitName/+8 and UnitCommand/+0x0c to INI::parseAsciiString
	// (0x00851EE0). These are table witnesses, not inferred layout names.
	AsciiString m_unitName;
	AsciiString m_unitCommand;
};

// ??1SpawnUnitBehaviorModuleData@@UAE@XZ
SpawnUnitBehaviorModuleData::~SpawnUnitBehaviorModuleData()
{
}
