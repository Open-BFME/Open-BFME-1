// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002A2B20 (1158 bytes). All twelve error literals name this method.
// Share the default-rule parser's record and INI ABI. Preserve retail's
// case-sensitive Cost/Time/Health dispatch and diagnostic typos verbatim.
// Copy default fields in AutoSpawn/Cost/Time/Health order: VC7.1 schedules
// their independent loads/stores into the exact retail sequence.
// The existing INI header lacks these parser declarations. The 0x205E ILT
// insert uses the caller-proven {iterator,bool} return and record reference.

#include <set>
#include <string.h>
#pragma intrinsic(strcmp)
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
class INIException
{
  public:
	INIException(int, const char *, ...);
	INIException(const INIException &);
	~INIException();
	char *message;
	int code;
};
class INI
{
  public:
	char m_pad00[0x41c];
	const char *m_sepsColon;
	const char *getSepsColon() const
	{
		return m_sepsColon;
	}
	const char *getNextToken(const char *);
	const char *getNextTokenOrNull(const char *);
	static void parseBool(INI *, void *, void *, const void *);
	static void parseUnsignedInt(INI *, void *, void *, const void *);
	static void parseInt(INI *, void *, void *, const void *);
	static void parsePercentToReal(INI *, void *, void *, const void *);
};
struct Rva002A23B0Record
{
	unsigned level;
	int m_cost, m_time;
	float m_health;
	bool m_autoSpawn;
	Rva002A23B0Record(unsigned v)
		: level(v), m_cost(0), m_time(0), m_health(1.0f), m_autoSpawn(false)
	{
	}
	bool operator<(const Rva002A23B0Record &other) const
	{
		return level < other.level;
	}
};
typedef _STL::set<Rva002A23B0Record> Records;
extern void j_0000205e();

class RespawnUpdate
{
  public:
	static void iniParseNewRuleForLevel(INI *, void *, void *, const void *);
};
void RespawnUpdate::iniParseNewRuleForLevel(INI *ini, void *instance, void *store, const void *)
{
	Records *records = (Records *)store;
	Records::iterator it = records->find(Rva002A23B0Record(1));
	if (it == records->end())
		throw INIException(
			3,
			"RespawnUpdate::iniParseNewRuleForLevel -- You cannot parse a 'RespawnEntry' before 'RespawnRules'. Please add a 'RespawnRules' -- which represents level 1.");
	Rva002A23B0Record defaults = *it;
	Rva002A23B0Record rule(0);
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (token && !_strcmpi(token, "Level"))
	{
		if (strcmp(token, "Level"))
			throw INIException(
				3,
				"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry for 'Level' is case sensitive. You specified %s.",
				token);
		INI::parseUnsignedInt(ini, instance, &rule.level, 0);
		if (records->find(rule) != records->end())
			throw INIException(
				3,
				"RespawnUpdate::iniParseNewRuleForLevel -- Multiple 'RespawnEntry' with the same level of %d. You may only have one!",
				rule.level);
		rule.m_autoSpawn = defaults.m_autoSpawn;
		rule.m_cost = defaults.m_cost;
		rule.m_time = defaults.m_time;
		rule.m_health = defaults.m_health;
		token = ini->getNextTokenOrNull(ini->getSepsColon());
		bool seenAuto = false, seenCost = false, seenTime = false, seenHealth = false;
		while (token)
		{
			if (!_strcmpi(token, "AutoSpawn"))
			{
				if (seenAuto)
					throw INIException(
						3,
						"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'AutoSpawn:Yes' or 'AutoSpawn:No' exists multiple times. Please remove one!",
						rule.level);
				if (strcmp(token, "AutoSpawn"))
					throw INIException(
						3,
						"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'AutoSpawn:Yes' or 'AutoSpawn:No' is case sensitive. You specified %s.",
						rule.level, token);
				INI::parseBool(ini, instance, &rule.m_autoSpawn, 0);
				seenAuto = true;
			}
			else if (!strcmp(token, "Cost"))
			{
				if (seenCost)
					throw INIException(
						3,
						"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'Cost' exists multiple times. Please remove one!",
						rule.level);
				if (strcmp(token, "Cost"))
					throw INIException(
						3,
						"RespawnUpdate::iniParseNewRuleForLevel -- RespawnRules Level:%d entry for 'Cost' is case sensitive. You specified %s.",
						rule.level, token);
				INI::parseUnsignedInt(ini, instance, &rule.m_cost, 0);
				seenCost = true;
			}
			else if (!strcmp(token, "Time"))
			{
				if (seenTime)
					throw INIException(
						3,
						"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d Level:%d entry for 'Cost' exists multiple times. Please remove one!",
						rule.level);
				if (strcmp(token, "Time"))
					throw INIException(
						3,
						"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'Time' is case sensitive. You specified %s.",
						rule.level, token);
				INI::parseInt(ini, instance, &rule.m_time, 0);
				seenTime = true;
			}
			else if (!strcmp(token, "Health"))
			{
				if (seenHealth)
					throw INIException(
						3,
						"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'Cost' exists multiple times. Please remove one!",
						rule.level);
				if (strcmp(token, "Health"))
					throw INIException(
						3,
						"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'Health' is case sensitive. You specified %s.",
						rule.level, token);
				INI::parsePercentToReal(ini, instance, &rule.m_health, 0);
				seenHealth = true;
			}
			token = ini->getNextTokenOrNull(ini->getSepsColon());
		}
		union {
			void (*f)();
			_STL::pair<Records::iterator, bool> (Records::*m)(const Rva002A23B0Record &);
		} call;
		call.f = j_0000205e;
		(records->*call.m)(rule);
	}
	else
		throw INIException(
			3,
			"RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry expecting 'Level' entry. You specified %s.",
			token);
}
