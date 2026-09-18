// cl: /DNDEBUG /MD /EHsc

#include "../../../../Include/GameLogic/Rva0039D550.h"
// Open-BFME5: AutoDepositUpdateModuleData dtor.
// Retail 67B SEH: release indexed handle @+0x1c, base vtbl store. Handle destructor route 0x1A401 -> 0x39D550.

// Retail call 0x00125988 passes owner+0x1c to ILT 0x0001A401
// -> 0x0039D550. That body reads/writes one four-byte pool index and
// releases its entry. The original C++ type and this member's role are unknown.


class AutoDepositUpdateModuleDataBase
{
public:
	virtual ~AutoDepositUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x18];
};

class __declspec(novtable) AutoDepositUpdateModuleData
	: public AutoDepositUpdateModuleDataBase
{
public:
	virtual ~AutoDepositUpdateModuleData();

private:
	Rva0039D550 m_handle1C;
};

// ??1AutoDepositUpdateModuleData@@UAE@XZ
AutoDepositUpdateModuleData::~AutoDepositUpdateModuleData()
{
}
