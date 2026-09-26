// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib

typedef bool Bool;

#include "ascii_string.h"

class ModuleInfo
{
public:
	Bool clearModuleDataWithTag(const AsciiString &, AsciiString &);

private:
	char m_padding[12];
};

class ThingTemplate
{
	protected:
	Bool removeModuleInfo(const AsciiString &, AsciiString &);

private:
	char m_padding[0x294];
	ModuleInfo m_behaviorModuleInfo;
	ModuleInfo m_drawModuleInfo;
	ModuleInfo m_clientUpdateModuleInfo;
	ModuleInfo m_extraModuleInfo;
};

Bool ThingTemplate::removeModuleInfo(const AsciiString &moduleToRemove,
	AsciiString &clearedModuleNameOut)
{
	Bool removed = false;

	if (m_behaviorModuleInfo.clearModuleDataWithTag(moduleToRemove, clearedModuleNameOut))
	{
		removed = true;
	}
	if (m_drawModuleInfo.clearModuleDataWithTag(moduleToRemove, clearedModuleNameOut))
	{
		removed = true;
	}
	if (m_clientUpdateModuleInfo.clearModuleDataWithTag(moduleToRemove, clearedModuleNameOut))
	{
		removed = true;
	}
	if (m_extraModuleInfo.clearModuleDataWithTag(moduleToRemove, clearedModuleNameOut))
	{
		removed = true;
	}

	return removed;
}
