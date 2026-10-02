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

LightPointLevel *__stdcall findLightPointLevel(void *vec, AsciiString *name);

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
	if (LightPointLevel *found = findLightPointLevel(&m_levels, &level->m_name))
	{
		const char *s = found->m_name.m_data ? found->m_name.m_data + 8 : "";
		throw INIException(3, "A light point level %s already exists.", s);
	}
	m_levels.push_back(level);
}
