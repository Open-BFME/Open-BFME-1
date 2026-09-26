// cl: /DNDEBUG /MD /EHsc

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Factory 0x00117540 passes callback VA 0x0042C115 -> 0x002072E0, which
// registers table RVA 0x00CA63CC: GrantUpgrade at +0x08 and RemoveUpgrade
// at +0x0c, both parsed by INI::parseAsciiString (0x00851EE0).
// The witnessed ModuleData prefix is eight bytes; the two canonical
// AsciiString handles therefore occupy the parsed offsets directly.

class ModuleData
{
public:
	ModuleData() {}
	virtual ~ModuleData() {}

private:
	unsigned int m_moduleTagNameKey;
};

class SlaveWatcherBehaviorModuleData : public ModuleData
{
public:
	SlaveWatcherBehaviorModuleData();
	virtual ~SlaveWatcherBehaviorModuleData();

private:
	AsciiString m_grantUpgrade;
	AsciiString m_removeUpgrade;
};

// ??0SlaveWatcherBehaviorModuleData@@QAE@XZ
SlaveWatcherBehaviorModuleData::SlaveWatcherBehaviorModuleData()
{
}

// MSVC applies novtable to subsequent out-of-line definitions while retaining
// the ordinary declaration used above for constructor vtable emission.
class __declspec(novtable) SlaveWatcherBehaviorModuleData;

// ??1SlaveWatcherBehaviorModuleData@@UAE@XZ
SlaveWatcherBehaviorModuleData::~SlaveWatcherBehaviorModuleData()
{
}
