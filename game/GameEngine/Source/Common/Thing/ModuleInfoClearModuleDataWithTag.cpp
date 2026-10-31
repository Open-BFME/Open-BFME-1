// cl: /O2 /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Converted from game/gen_asm/d_00140de0.asm at retail RVA 0x001415D0.
// The ThingTemplate.cpp caller and the ModuleInfo method name identify this
// body. The 20-byte Nugget layout and STLport vector erase reproduce its calls.

#include <vector>

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

// AsciiString::compare(const AsciiString &), expanded in place.  Calling the
// member emits a ?compare@AsciiString@@QBEHABV1@@Z COMDAT that is not retail's
// 0x0005FEB0 body.  The buffer pointer is the string's first word; its length
// is the unsigned short at +4 and the characters start at +8.
struct AsciiCompareView
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};
	Header *m_data;
};

static __forceinline int asciiCompare( const AsciiString &left, const AsciiString &right )
{
	const AsciiCompareView &s = reinterpret_cast<const AsciiCompareView &>(right);
	const AsciiCompareView &t = reinterpret_cast<const AsciiCompareView &>(left);
	int thatLen = s.m_data ? s.m_data->length : 0;
	const char *thatData = s.m_data ? &s.m_data->data[0] : (const char *)"";
	int thisLen = t.m_data ? t.m_data->length : 0;
	const char *thisData = t.m_data ? &t.m_data->data[0] : (const char *)"";
	int n = thisLen < thatLen ? thisLen : thatLen;
	int c = memcmp(thisData, thatData, n);
	if (c != 0)
		return c;
	return thisLen - thatLen;
}

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
		if (asciiCompare(it->m_moduleTag, tagToClear) == 0)
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
