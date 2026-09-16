// ?d_00886b00@@YAXXZ
// partial score=0.9899 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWDownload
// stlport

#include <string>
#include <algorithm>
#include <stdio.h>
#include "registry.h"

extern "C" __declspec(dllimport) int __cdecl tolower(int character);

extern char *d_00886ac0(const char *start, const char *end, char *dst,
	int (*func)(int));

void FormatURLFromRegistry( std::string& gamePatchURL, std::string& mapPatchURL,
	std::string& configURL, std::string& motdURL )
{
	std::string sku = "lotrbfme";
	std::string language = "ENGLISH";
	unsigned int versions[2] = { 0, 0 };
	std::string baseURL = "http://servserv.generals.ea.com/servserv/";
	baseURL.append(sku);
	baseURL.append("/");

	GetStringFromRegistry("", "BaseURL", baseURL);
	GetStringFromRegistry("", "Language", language);
	GetUnsignedIntFromRegistry("", "Version", versions[0]);
	GetUnsignedIntFromRegistry("", "MapPackVersion", versions[1]);
	std::transform(baseURL.begin(), baseURL.end(), baseURL.begin(), tolower);

	char buf[256];
	_snprintf(buf, 256, "%s%s-%d.txt", baseURL.c_str(), language.c_str(), versions[0]);
	gamePatchURL = buf;
	_snprintf(buf, 256, "%smaps-%d.txt", baseURL.c_str(), versions[1]);
	mapPatchURL = buf;
	_snprintf(buf, 256, "%sconfig.txt", baseURL.c_str());
	configURL = buf;
	_snprintf(buf, 256, "%sMOTD-%s.txt", baseURL.c_str(), language.c_str());
	motdURL = buf;
}
