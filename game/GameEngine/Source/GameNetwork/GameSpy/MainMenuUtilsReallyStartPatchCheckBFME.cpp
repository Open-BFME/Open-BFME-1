// BFME patch-check continuation reached by the matched HTTPThinkWrapper's
// successful-DNS branch. Callback addresses are the retail call operands.
// cl: /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/GameEngine/Source/GameNetwork /Igame/Libraries/Source/WWVegas/WWDownload /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDownload /Iinputs/reference/shims/gamespy
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
extern void j_0087ad40();
typedef int (__cdecl *GhiSetProxyFn)(const char *server);

enum GHTTPBool { GHTTPFalse, GHTTPTrue };
enum GHTTPResult { GHTTPSuccess };
void d_0062fe40();
GHTTPBool __cdecl configHeadCallback(int request, GHTTPResult result, char *buffer, __int64 bufferLen, void *param);
GHTTPBool rva0062EE00MainMenuOnlineCallback(int request, int result, char *buffer, __int64 bufferLen, void *param);

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
		if (!proxy.empty()) reinterpret_cast<GhiSetProxyFn>(j_0087ad40)(proxy.c_str());
	}

	// These callback VAs are the direct operands in the retail call sites.
	ghttpGetA(gameURL.c_str(), 1,
		reinterpret_cast<GHTTPCompletedCallback>(d_0062fe40),
		reinterpret_cast<void *>(timeThroughOnline));
	ghttpGetA(mapURL.c_str(), 1,
		reinterpret_cast<GHTTPCompletedCallback>(d_0062fe40),
		reinterpret_cast<void *>(timeThroughOnline));
	ghttpHeadA(configURL.c_str(), 1,
		reinterpret_cast<GHTTPCompletedCallback>(configHeadCallback),
		reinterpret_cast<void *>(timeThroughOnline));
	ghttpGetA(motdURL.c_str(), 1,
		reinterpret_cast<GHTTPCompletedCallback>(rva0062EE00MainMenuOnlineCallback),
		reinterpret_cast<void *>(timeThroughOnline));

	bfmeRequestEUG();
}
