// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/iniexception
// stlport
// LightPointSystem::addLevel. Throws INIException if a level with that name
// is already in the +0x08 vector. The format string at 0x010EBE00 is
// "A light point level %s already exists."

#include <vector>

class AsciiString
{
public:
	char *m_data;
};

class LightPointLevel
{
public:
	char m_pad[0x0C];
	AsciiString m_name;
};

#include "Common/INIException.h"

// ILT 0x28AF6 -> 0x0039C1A0, the matched 153-byte pointer-range name search
// BfmeAttributeNamedEntryFinder::find
// (BfmeAttributeNamedEntryFind.cpp); it ignores ECX, which retail leaves
// holding the system across the call.
struct BfmeAttributeNamedEntry;
struct BfmeAttributeNamedEntryRange;
class BfmeAttributeNamedEntryFinder
{
public:
	BfmeAttributeNamedEntry *find(const BfmeAttributeNamedEntryRange *range,
		const AsciiString *name) const;
};

class LightPointSystem
{
public:
	void addLevel(LightPointLevel *level);

private:
	char m_pad[8];
	std::vector<LightPointLevel *> m_levels;
};

void LightPointSystem::addLevel(LightPointLevel *level)
{
	if (LightPointLevel *found = (LightPointLevel *)
			reinterpret_cast<const BfmeAttributeNamedEntryFinder *>(this)->find(
				(const BfmeAttributeNamedEntryRange *)&m_levels, &level->m_name))
	{
		const char *s = found->m_name.m_data ? found->m_name.m_data + 8 : "";
		throw INIException(3, "A light point level %s already exists.", s);
	}
	m_levels.push_back(level);
}
