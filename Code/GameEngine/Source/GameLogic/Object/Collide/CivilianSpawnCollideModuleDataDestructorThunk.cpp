// cl: /DNDEBUG /MD /EHsc

#include "../../../../Include/GameLogic/Rva0039D550.h"
// Open-BFME5: CivilianSpawnCollideModuleData dtor.
// Retail 67B SEH: release indexed handle @+0x8, base vtbl store. Handle destructor route 0x1A401 -> 0x39D550.

// Retail call 0x002175E8 passes owner+0x8 to ILT 0x0001A401
// -> 0x0039D550. That body reads/writes one four-byte pool index and
// releases its entry. The original C++ type and this member's role are unknown.


class CivilianSpawnCollideModuleDataBase
{
public:
	virtual ~CivilianSpawnCollideModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) CivilianSpawnCollideModuleData
	: public CivilianSpawnCollideModuleDataBase
{
public:
	virtual ~CivilianSpawnCollideModuleData();

private:
	Rva0039D550 m_handle08;
};

// ??1CivilianSpawnCollideModuleData@@UAE@XZ
CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData()
{
}
