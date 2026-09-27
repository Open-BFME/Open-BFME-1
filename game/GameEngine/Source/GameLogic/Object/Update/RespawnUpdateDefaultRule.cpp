// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002A2750 (778 bytes). All nine error literals name this method.
// Parser token strings prove the record fields; INI+0x41C supplies colon
// separators. Its accessor is required for the retail scratch-register order.
// INI/INI.h lacks these static parsers, hence the minimal declaration here.
// Native INIException produces the retail ThrowInfo. A final INT3 is padding.
// ILT 0x205E -> 0x2A24E0 returns {iterator,bool} with a hidden result pointer
// and takes a record reference. Its inherited pointer-set ledger spelling
// is not used as type evidence; the typed union retains the proven ABI.

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
	static void iniParseDefaultRule(INI *, void *, void *, const void *);
};
void RespawnUpdate::iniParseDefaultRule(INI *ini, void *instance, void *store, const void *)
{
	Records *records = (Records *)store;
	Rva002A23B0Record rule(1);
	if (records->find(rule) != records->end())
		throw INIException(3,
						   "RespawnUpdate::iniParseDefaultRule -- Duplicate RespawnRules entry.");
	{
		const char *token = ini->getNextToken(ini->getSepsColon());
		if (token && !_strcmpi(token, "AutoSpawn"))
		{
			if (strcmp(token, "AutoSpawn"))
				throw INIException(
					3,
					"RespawnUpdate::iniParseDefaultRule -- RespawnRules entry for 'AutoSpawn:Yes' or 'AutoSpawn:No' is case sensitive. You specified %s.",
					token);
			INI::parseBool(ini, instance, &rule.m_autoSpawn, 0);
			{
				const char *token = ini->getNextToken(ini->getSepsColon());
				if (token && !_strcmpi(token, "Cost"))
				{
					if (strcmp(token, "Cost"))
						throw INIException(
							3,
							"RespawnUpdate::iniParseDefaultRule -- RespawnRules entry for 'Cost' is case sensitive. You specified %s.",
							token);
					INI::parseUnsignedInt(ini, instance, &rule.m_cost, 0);
					{
						const char *token = ini->getNextToken(ini->getSepsColon());
						if (token && !_strcmpi(token, "Time"))
						{
							if (strcmp(token, "Time"))
								throw INIException(
									3,
									"RespawnUpdate::iniParseDefaultRule -- RespawnRules entry for 'Time' is case sensitive. You specified %s.",
									token);
							INI::parseInt(ini, instance, &rule.m_time, 0);
							{
								const char *token = ini->getNextToken(ini->getSepsColon());
								if (token && !_strcmpi(token, "Health"))
								{
									if (strcmp(token, "Health"))
										throw INIException(
											3,
											"RespawnUpdate::iniParseDefaultRule -- RespawnRules entry for 'Health' is case sensitive. You specified %s.",
											token);
									INI::parsePercentToReal(ini, instance, &rule.m_health, 0);
									union {
										void (*f)();
										_STL::pair<Records::iterator, bool> (Records::*m)(
											const Rva002A23B0Record &);
									} call;
									call.f = j_0000205e;
									(records->*call.m)(rule);
								}
								else
									throw INIException(
										3,
										"RespawnUpdate::iniParseDefaultRule -- RespawnRules entry expecting 'Health' entry. You specified %s.",
										token);
							}
						}
						else
							throw INIException(
								3,
								"RespawnUpdate::iniParseDefaultRule -- RespawnRules entry expecting 'Time' entry. You specified %s.",
								token);
					}
				}
				else
					throw INIException(
						3,
						"RespawnUpdate::iniParseDefaultRule -- RespawnRules entry expecting 'Cost' entry. You specified %s.",
						token);
			}
		}
		else
			throw INIException(
				3,
				"RespawnUpdate::iniParseDefaultRule -- RespawnRules entry expecting 'AutoSpawn:Yes' or 'AutoSpawn:No' entry. You specified %s.",
				token);
	}
}
