// cl: /O2 /D_STLP_USE_STATIC_LIB /Ivendor/stlport /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Converted from Code/gen_asm/d_00140de0.asm at retail RVA 0x001415D0.
// The ThingTemplate.cpp caller and the ModuleInfo method name identify this
// body. The 20-byte Nugget layout and STLport vector erase reproduce its calls.

#include <vector>

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class Rva001417F0ModuleInfo
{
public:
	struct Nugget
	{
		AsciiString first;
		AsciiString m_moduleTag;
		const void *second;
		Int interfaceMask;
		Bool copiedFromDefault;
		Bool inheritable;

		Nugget(const AsciiString &n, const AsciiString &moduleTag,
			const void *d, Int i, Bool inh)
			: first(n), m_moduleTag(moduleTag), second(d), interfaceMask(i),
			  copiedFromDefault(false), inheritable(inh)
		{
		}
		~Nugget();
	};
};

class ModuleInfo
{
private:
	typedef Rva001417F0ModuleInfo::Nugget Nugget;
	std::vector<Nugget> m_info;

public:
	Bool clearModuleDataWithTag(const AsciiString &tagToClear,
		AsciiString &clearedModuleNameOut);
};

Bool ModuleInfo::clearModuleDataWithTag(const AsciiString &tagToClear,
	AsciiString &clearedModuleNameOut)
{
	Bool cleared = false;
	for (std::vector<Nugget>::iterator it = m_info.begin();
		it != m_info.end(); )
	{
		if (it->m_moduleTag.compare(tagToClear) == 0)
		{
			clearedModuleNameOut = it->first;
			it = m_info.erase(it);
			cleared = true;
		}
		else
		{
			++it;
		}
	}
	return cleared;
}
