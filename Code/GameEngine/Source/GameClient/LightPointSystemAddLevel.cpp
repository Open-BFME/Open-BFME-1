// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
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

class INIException
{
public:
	INIException(int code, const char *message, ...);
	INIException(const INIException &other);

private:
	int m_code;
	const char *m_message;
};

LightPointLevel *__stdcall findLightPointLevel(void *vec, AsciiString *name);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_lightPointThrowInfo;

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
		INIException exc(3, "A light point level %s already exists.", s);
		_CxxThrowException(&exc, &g_lightPointThrowInfo);
	}
	m_levels.push_back(level);
}
