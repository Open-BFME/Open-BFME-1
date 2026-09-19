// cl: /DNDEBUG /MD /EHsc

#include "../../../../Include/GameLogic/Rva0039D550.h"

// Open-BFME5: LevelGrantSpecialPowerModuleData scalar deleting destructor.
// The matched constructor at 0x0025FEF0 installs vtable 0x010B5CD8;
// slot zero reaches this wrapper through ILT 0x00048E14.

// The AcceptanceFilter parse-table entry is at owner +0x260. Its constructor
// calls ILT 0x0003747A -> 0x003A0410 and stores a four-byte pool index;
// iniParseObjectFilter 0x0039F470 updates that same index via the same interner.
// Retail destruction at 0x0026001B passes owner+0x260 to ILT 0x0001A401
// -> 0x0039D550, which releases the indexed pool entry. The original C++
// type is unknown; this address-qualified view makes no Buffer identity claim.


// Emission surrogate: this 0x260-byte prefix includes the actual 0x254-byte
// base plus three derived scalar fields. It is not the base class layout.
class LevelGrantSpecialPowerModuleDataBase
{
public:
	virtual ~LevelGrantSpecialPowerModuleDataBase();

private:
	unsigned char m_pad[ 0x25c ];
};

class LevelGrantSpecialPowerModuleData : public LevelGrantSpecialPowerModuleDataBase
{
public:
	__declspec(noinline) virtual ~LevelGrantSpecialPowerModuleData();

private:
	Rva0039D550 m_acceptanceFilter;
};

LevelGrantSpecialPowerModuleData::~LevelGrantSpecialPowerModuleData()
{
}
