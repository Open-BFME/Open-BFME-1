// BFME patch-check continuation reached by the matched HTTPThinkWrapper's
// successful-DNS branch. Callback addresses are the retail call operands.
// cl: /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /ICode/GameEngine/Source/GameNetwork /ICode/Libraries/Source/WWVegas/WWDownload /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDownload /Ireference/shims/gamespy
// stlport

#include <string>
#include "registry.h"
#include "urlBuilder.h"

// Mirror the canonical ghttp.h C ABI: its Win32 shim conflicts with this
// standalone C++/STLport translation unit when included directly.
typedef int (__cdecl *GHTTPCompletedCallback)(int request, int result,
	char *buffer, __int64 bufferLen, void *param);
extern "C" int __cdecl ghttpGetA(const char *url, int blocking,
	GHTTPCompletedCallback completed, void *param);
extern "C" int __cdecl ghttpHeadA(const char *url, int blocking,
	GHTTPCompletedCallback completed, void *param);
// Retail calls the lower-level Gamespy implementation through ILT 0x0087AD40.
extern "C" int __cdecl ghiSetProxy(const char *server);

extern void bfmeRequestEUG(void);
extern int checksLeftBeforeOnline;
extern int timeThroughOnline;

void bfmeReallyStartPatchCheck(void)
{
	checksLeftBeforeOnline = 4;

	std::string gameURL, mapURL, configURL, motdURL;
	FormatURLFromRegistry(gameURL, mapURL, configURL, motdURL);

	std::string proxy;
	if (GetStringFromRegistry("", "Proxy", proxy)) {
		if (!proxy.empty()) ghiSetProxy(proxy.c_str());
	}

	// These callback VAs are the direct operands in the retail call sites.
	ghttpGetA(gameURL.c_str(), 1,
		reinterpret_cast<GHTTPCompletedCallback>(0x00A2FE40),
		reinterpret_cast<void *>(timeThroughOnline));
	ghttpGetA(mapURL.c_str(), 1,
		reinterpret_cast<GHTTPCompletedCallback>(0x00A2FE40),
		reinterpret_cast<void *>(timeThroughOnline));
	ghttpHeadA(configURL.c_str(), 1,
		reinterpret_cast<GHTTPCompletedCallback>(0x00A2F130),
		reinterpret_cast<void *>(timeThroughOnline));
	ghttpGetA(motdURL.c_str(), 1,
		reinterpret_cast<GHTTPCompletedCallback>(0x00A2EE00),
		reinterpret_cast<void *>(timeThroughOnline));

	bfmeRequestEUG();
}
