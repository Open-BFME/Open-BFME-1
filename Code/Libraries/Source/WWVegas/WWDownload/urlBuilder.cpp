// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWDownload
// stlport

#include <string>
#include <stdio.h>
#include <ctype.h>
#include "registry.h"

// Lowercasing loop at 0x00886AC0 (a transform-style helper; identity unproven).
extern char *d_00886ac0(const char *start, const char *end, char *dst,
	int (*func)(int));

void FormatURLFromRegistry( std::string& gamePatchURL, std::string& mapPatchURL,
	std::string& configURL, std::string& motdURL )
{
	// BFME variant of the Zero Hour urlBuilder.cpp body: new SKU and default
	// language, and the language is lowercased after the registry reads.
	std::string sku = "lotrbfme";
	std::string language = "ENGLISH";
	unsigned int version = 0;
	unsigned int mapVersion = 0;
	std::string baseURL = "http://servserv.generals.ea.com/servserv/";
	baseURL.append(sku);
	baseURL.append("/");

	GetStringFromRegistry("", "BaseURL", baseURL);
	GetStringFromRegistry("", "Language", language);
	GetUnsignedIntFromRegistry("", "Version", version);
	GetUnsignedIntFromRegistry("", "MapPackVersion", mapVersion);
	d_00886ac0(language.begin(), language.end(), language.begin(), tolower);

	char buf[256];
	_snprintf(buf, 256, "%s%s-%d.txt", baseURL.c_str(), language.c_str(), version);
	gamePatchURL = buf;
	_snprintf(buf, 256, "%smaps-%d.txt", baseURL.c_str(), mapVersion);
	mapPatchURL = buf;
	_snprintf(buf, 256, "%sconfig.txt", baseURL.c_str());
	configURL = buf;
	_snprintf(buf, 256, "%sMOTD-%s.txt", baseURL.c_str(), language.c_str());
	motdURL = buf;
}
