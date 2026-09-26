// cl: /DNDEBUG /MD /EHsc

#include "../../../../Include/GameLogic/Rva0039D550.h"
//
// Retail's SpecialEnemySenseUpdateModuleData vtable at 0x0108CD38 names this
// scalar deleting destructor in slot zero. Its call target is the separately
// matched destructor body at 0x00125890.

// Retail call 0x001258B8 passes owner+0x8 to ILT 0x0001A401
// -> 0x0039D550. That body reads/writes one four-byte pool index and
// releases its entry. The original C++ type and this member's role are unknown.


class SpecialEnemySenseUpdateModuleDataBase
{
public:
	virtual ~SpecialEnemySenseUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class SpecialEnemySenseUpdateModuleData
	: public SpecialEnemySenseUpdateModuleDataBase
{
public:
	virtual ~SpecialEnemySenseUpdateModuleData();

private:
	Rva0039D550 m_handle08;
};

SpecialEnemySenseUpdateModuleData::~SpecialEnemySenseUpdateModuleData()
{
}
