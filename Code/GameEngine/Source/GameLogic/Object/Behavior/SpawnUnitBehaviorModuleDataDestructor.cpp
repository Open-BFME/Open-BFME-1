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
	AsciiString m_a;
	AsciiString m_b;
};

// ??1SpawnUnitBehaviorModuleData@@UAE@XZ
SpawnUnitBehaviorModuleData::~SpawnUnitBehaviorModuleData()
{
}
