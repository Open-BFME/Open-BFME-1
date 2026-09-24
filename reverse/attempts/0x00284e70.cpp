// ?rva00284E70ParseExpLevelDraw@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.4 date=2026-09-23
// ?rva00284E70ParseExpLevelDraw@@YAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oi /D_STLP_USE_STATIC_LIB /Ireference/shims/iniexception
// stlport

#include <vector>
#include "Common/INIException.h"

typedef unsigned char Bool;

extern "C" int __cdecl strcmp(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl bfmeCmpDWK(const char *, const char *);
extern "C" unsigned int __cdecl strlen(const char *);
extern "C" unsigned char bfmeStrDWK[];
#pragma intrinsic(strcmp)
#pragma intrinsic(strlen)

class INI
{
public:
	const char *getNextTokenOrNull(const char *delimiters);
	const char *getNextToken(const char *delimiters);
	static int scanInt(const char *text);
	unsigned char m_prefix[0x41c];
	const char *m_tokenDelimiters;
};

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	void set(const char *text, int length);
	void *m_data;
};

class BannerCarrierString
{
public:
	~BannerCarrierString();
};

class BannerCarrierUpgrade
{
public:
	~BannerCarrierUpgrade();
	int m_level;
	std::vector<BannerCarrierString *> m_strings;
};

struct BannerCarrierSubObject
{
	RetailLayoutString m_name;
	Bool m_isDWK;
};

void rva00284E70ParseExpLevelDraw(
	INI *ini, void *, void *store, const void *)
{
	BannerCarrierUpgrade *record = new BannerCarrierUpgrade;
	const char *token = ini->getNextTokenOrNull(ini->m_tokenDelimiters);
	if (token == 0 || strcmp(token, "Level") != 0)
		throw INIException(3, "'ModelState' expected");

	record->m_level = INI::scanInt(
		ini->getNextToken(ini->m_tokenDelimiters));
	token = ini->getNextTokenOrNull(ini->m_tokenDelimiters);
	while (token != 0)
	{
		if (strcmp(token, "SubObject") != 0)
			throw INIException(3, "UnitType expected");

		BannerCarrierSubObject *entry = new BannerCarrierSubObject;
		const char *dwkToken = ini->getNextToken(ini->m_tokenDelimiters);
		entry->m_isDWK = bfmeCmpDWK(
			dwkToken, (const char *)bfmeStrDWK) == 0;
		const char *name = ini->getNextToken(ini->m_tokenDelimiters);
		entry->m_name.set(name, name ? (int)strlen(name) : 0);
		record->m_strings.push_back((BannerCarrierString *)entry);
		token = ini->getNextTokenOrNull(ini->m_tokenDelimiters);
	}

	((std::vector<BannerCarrierUpgrade *> *)store)->push_back(record);
}
