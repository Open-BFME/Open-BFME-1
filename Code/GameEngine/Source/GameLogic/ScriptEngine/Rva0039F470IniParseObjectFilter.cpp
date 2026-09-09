// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
// stlport
// The named 5-byte iniParseObjectFilter entry at 0x00039865 is an incremental-
// link jump to this 1463-byte implementation at 0x0039F470.  The implementation
// is kept under the existing TU-local shim name because the retail body has no
// independent decorated C++ owner beyond that named forwarding entry.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

typedef unsigned int UnsignedInt;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
};

typedef void *(__cdecl *LookupFn)(void *, void *);
extern LookupFn g_lookup;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
extern "C" int __cdecl strcmp(const char *, const char *);

class INIException
{
public:
	INIException(int code, const char *format, ...);
	INIException(const INIException &other);

private:
	char *m_failureMessage;
	int m_argCount;
};

extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object,
	void *throwInfo);

struct BfmeAttributeHandle
{
	UnsignedInt m_handle;
};

extern void bfmeReleaseAttributeHandle(BfmeAttributeHandle *handle);

struct BfmeAttributePlainBlock
{
	UnsignedInt m_values[6];
};

class Gen00043699
{
public:
	Gen00043699();
	~Gen00043699();

	std::vector<AsciiString> m_names;
	std::vector<AsciiString> m_values;
	std::vector<AsciiString> m_list0;
	std::vector<AsciiString> m_list1;
	std::vector<AsciiString> m_list2;
	std::vector<AsciiString> m_list3;
	BfmeAttributePlainBlock m_firstPlain;
	BfmeAttributePlainBlock m_secondPlain;
	UnsignedInt m_kind;
	UnsignedInt m_index;
	bool m_enabled;
	unsigned char m_pad[3];
	UnsignedInt m_useCount;
};

extern int bfmeLookup_000d1020(void *name);
extern UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry);

class IniParseObjectFilterShim
{
public:
	static void run(INI *ini, void *instance, void *store, const void *userData);
};

#define THROW_FILTER_ERROR(format, token) \
	do { \
		INIException error(3, format, token); \
		_CxxThrowException(&error, (void *)0x011DFC30); \
	} while (0)

#define THROW_FILTER_ERROR_NO_TOKEN(format) \
	do { \
		INIException error(3, format); \
		_CxxThrowException(&error, (void *)0x011DFC30); \
	} while (0)

void IniParseObjectFilterShim::run(INI *ini, void *, void *store, const void *)
{
	Gen00043699 entry;
	BfmeAttributeHandle *handle = (BfmeAttributeHandle *)store;
	if (handle->m_handle != 0xffffffff)
		bfmeReleaseAttributeHandle(handle);

	bool hasRuleset = false;
	const char *token = ini->getNextTokenOrNull(0);
	bool first = true;
	while (token != 0)
	{
		LookupFn compare = g_lookup;
		if (compare((void *)token, (void *)"ALL") == 0)
		{
			if (!first)
				THROW_FILTER_ERROR_NO_TOKEN("When using ALL in iniParseObjectFilter, ALL must be the first entry.");
			if (strcmp(token, "ALL") != 0)
				THROW_FILTER_ERROR("iniParseObjectFilter ALL keyword is case sensitive. You specified %s.", token);
			entry.m_kind = 3;
			entry.m_enabled = true;
			hasRuleset = true;
		}
		else if (compare((void *)token, (void *)"ANY") == 0)
		{
			if (!first)
				THROW_FILTER_ERROR_NO_TOKEN("When using ANY in iniParseObjectFilter, ANY must be the first entry.");
			if (strcmp(token, "ANY") != 0)
				THROW_FILTER_ERROR("iniParseObjectFilter ANY keyword is case sensitive. You specified %s.", token);
			entry.m_kind = 2;
			entry.m_enabled = true;
			hasRuleset = true;
		}
		else if (compare((void *)token, (void *)"NONE") == 0)
		{
			if (!first)
				THROW_FILTER_ERROR_NO_TOKEN("When using NONE in iniParseObjectFilter, NONE must be the first entry.");
			if (strcmp(token, "NONE") != 0)
				THROW_FILTER_ERROR("iniParseObjectFilter NONE keyword is case sensitive. You specified %s.", token);
			entry.m_kind = 1;
			entry.m_enabled = false;
			hasRuleset = true;
		}
		else if (compare((void *)token, (void *)"ALLIES") == 0)
		{
			if (!hasRuleset)
				THROW_FILTER_ERROR("iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (strcmp(token, "ALLIES") != 0)
				THROW_FILTER_ERROR("iniParseObjectFilter ALLIES keyword is case sensitive. You specified %s.", token);
			entry.m_index |= 1;
		}
		else if (compare((void *)token, (void *)"ENEMIES") == 0)
		{
			if (!hasRuleset)
				THROW_FILTER_ERROR("iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (strcmp(token, "ENEMIES") != 0)
				THROW_FILTER_ERROR("iniParseObjectFilter ENEMIES keyword is case sensitive. You specified %s.", token);
			entry.m_index |= 2;
		}
		else if (compare((void *)token, (void *)"NEUTRAL") == 0)
		{
			if (!hasRuleset)
				THROW_FILTER_ERROR("iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (strcmp(token, "NEUTRAL") != 0)
				THROW_FILTER_ERROR("iniParseObjectFilter NEUTRAL keyword is case sensitive. You specified %s.", token);
			entry.m_index |= 4;
		}
		else if (token[0] == '+')
		{
			if (!hasRuleset)
				THROW_FILTER_ERROR("iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			if (entry.m_kind == 3)
				THROW_FILTER_ERROR("ALL is specified for iniParseObjectFilter, so adding %s has no effect. Please remove entry.", token);
			UnsignedInt bit = (UnsignedInt)bfmeLookup_000d1020((void *)(token + 1));
			if (bit != 0xffffffff)
				entry.m_firstPlain.m_values[bit >> 5] |= 1 << (bit & 31);
			else
				entry.m_names.push_back(AsciiString(token + 1));
			entry.m_enabled = true;
		}
		else if (token[0] == '-')
		{
			if (!hasRuleset)
				THROW_FILTER_ERROR("iniParseObjectFilter: You must specify a ruleset for your data (ANY, ALL, or NONE). You specified %s.", token);
			UnsignedInt bit = (UnsignedInt)bfmeLookup_000d1020((void *)(token + 1));
			if (bit != 0xffffffff)
				entry.m_secondPlain.m_values[bit >> 5] |= 1 << (bit & 31);
			else
				entry.m_values.push_back(AsciiString(token + 1));
		}
		else
		{
			THROW_FILTER_ERROR("iniParseObjectFilter expecting a + or - token as it is required for classification. Instead it found %s", token);
		}
		token = ini->getNextTokenOrNull(0);
		first = false;
	}
	handle->m_handle = bfmeInternAttributeEntry(&entry);
}
