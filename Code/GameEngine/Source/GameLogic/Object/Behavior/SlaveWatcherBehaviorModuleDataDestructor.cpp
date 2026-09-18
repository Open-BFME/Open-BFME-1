// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SlaveWatcherBehaviorModuleData dtor.
// Retail 80B SEH: destroy AsciiString @+0xc then @+0x8, base vtbl store. AsciiString pin 0x887940.

// Factory 0x00117540 passes callback VA 0x0042C115 -> 0x002072E0, which
// registers table RVA 0x00CA63CC: GrantUpgrade at +0x08 and RemoveUpgrade
// at +0x0c, both parsed by INI::parseAsciiString (0x00851EE0).
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class SlaveWatcherBehaviorModuleDataBase
{
public:
	virtual ~SlaveWatcherBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) SlaveWatcherBehaviorModuleData
	: public SlaveWatcherBehaviorModuleDataBase
{
public:
	virtual ~SlaveWatcherBehaviorModuleData();

private:
	AsciiString m_grantUpgrade;
	AsciiString m_removeUpgrade;
};

// ??1SlaveWatcherBehaviorModuleData@@UAE@XZ
SlaveWatcherBehaviorModuleData::~SlaveWatcherBehaviorModuleData()
{
}
