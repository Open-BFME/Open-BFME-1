#include <stddef.h>
// cl: /DNDEBUG /MD /EHs-c-

typedef unsigned long RvaDword821D0;
typedef void *RvaModuleHandle821D0;
typedef RvaModuleHandle821D0 (__stdcall *RvaLoadLibraryW821D0)(
	const unsigned short *fileName);
typedef RvaModuleHandle821D0 (__stdcall *RvaLoadLibraryExA821D0)(
	const char *fileName, RvaModuleHandle821D0 module, RvaDword821D0 flags);
typedef RvaModuleHandle821D0 (__stdcall *RvaLoadLibraryExW821D0)(
	const unsigned short *fileName, RvaModuleHandle821D0 module,
	RvaDword821D0 flags);

struct RvaOSVersionInfo821D0
{
	RvaDword821D0 dwOSVersionInfoSize;
	RvaDword821D0 dwMajorVersion;
	RvaDword821D0 dwMinorVersion;
	RvaDword821D0 dwBuildNumber;
	RvaDword821D0 dwPlatformId;
	char szCSDVersion[128];
};

extern "C" __declspec(dllimport) RvaModuleHandle821D0 __stdcall LoadLibraryA(
	const char *fileName);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(
	RvaModuleHandle821D0 module, const char *procName);
extern "C" __declspec(dllimport) int __stdcall GetVersionExA(
	RvaOSVersionInfo821D0 *info);

extern "C" RvaModuleHandle821D0 (__stdcall *g_rva0130E988LoadLibraryA)(
	const char *name) = 0;

extern void *rva00882140PatchAllModules(const char *dllName,
	const char *functionName, void *replacement);

extern unsigned char g_0130E990;
extern RvaLoadLibraryW821D0 g_0130E984;
extern RvaLoadLibraryExA821D0 g_0130E980;
extern RvaLoadLibraryExW821D0 g_0130E97C;

extern RvaModuleHandle821D0 __stdcall d_00881fb0(const char *name);
extern RvaModuleHandle821D0 __stdcall d_00881fd0(const unsigned short *name);
extern RvaModuleHandle821D0 __stdcall d_00881ff0(const char *name,
	RvaModuleHandle821D0 module, RvaDword821D0 flags);
extern RvaModuleHandle821D0 __stdcall d_00882020(const unsigned short *name,
	RvaModuleHandle821D0 module, RvaDword821D0 flags);
extern void *d_00881ca0(unsigned int count, unsigned int size);
extern void *d_00881ce0(unsigned int count, unsigned int size);
extern void d_00881d20(void *ptr);
extern void rva00881D40(void *, int);
extern void *d_00881d70(unsigned int size);
extern void *d_00881d90(unsigned int size);
extern void d_00881db0(void);
extern size_t rva00881DC0(void *, int);
extern void *rva00881DD0(void *, size_t);
extern void *d_00881df0(void *ptr, unsigned int size);
extern char *d_00881e10(const char *src);
extern unsigned short *d_00881e60(const unsigned short *src);
extern void d_00881ea0(void);

// ?rva008821d0LoaderPatch@@YAXXZ
void rva008821d0LoaderPatch(void)
{
	if (g_0130E990 != 0)
		return;

	if (g_rva0130E988LoadLibraryA != 0)
	{
		g_0130E990 = 1;
	}
	else
	{
		g_0130E990 = 1;
		g_rva0130E988LoadLibraryA =
			(RvaModuleHandle821D0 (__stdcall *)(const char *))GetProcAddress(
				LoadLibraryA("kernel32.dll"), "LoadLibraryA");
	}

	RvaOSVersionInfo821D0 osvi = {};
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionExA(&osvi);

	if (osvi.dwPlatformId > 1)
	{
		rva00882140PatchAllModules("kernel32.dll", "LoadLibraryA",
			(void *)d_00881fb0);
		g_0130E984 =
			(RvaLoadLibraryW821D0)rva00882140PatchAllModules(
				"kernel32.dll", "LoadLibraryW", (void *)d_00881fd0);
		g_0130E980 =
			(RvaLoadLibraryExA821D0)rva00882140PatchAllModules(
				"kernel32.dll", "LoadLibraryExA", (void *)d_00881ff0);
		g_0130E97C =
			(RvaLoadLibraryExW821D0)rva00882140PatchAllModules(
				"kernel32.dll", "LoadLibraryExW", (void *)d_00882020);
	}

	rva00882140PatchAllModules("msvcr71.dll", "calloc", (void *)d_00881ca0);
	rva00882140PatchAllModules("msvcr71.dll", "_calloc_dbg", (void *)d_00881ce0);
	rva00882140PatchAllModules("msvcr71.dll", "free", (void *)d_00881d20);
	rva00882140PatchAllModules("msvcr71.dll", "_free_dbg", (void *)rva00881D40);
	rva00882140PatchAllModules("msvcr71.dll", "malloc", (void *)d_00881d70);
	rva00882140PatchAllModules("msvcr71.dll", "_malloc_dbg", (void *)d_00881d90);
	rva00882140PatchAllModules("msvcr71.dll", "_msize", (void *)d_00881db0);
	rva00882140PatchAllModules("msvcr71.dll", "_msize_dbg", (void *)rva00881DC0);
	rva00882140PatchAllModules("msvcr71.dll", "realloc", (void *)rva00881DD0);
	rva00882140PatchAllModules("msvcr71.dll", "_realloc_dbg", (void *)d_00881df0);
	rva00882140PatchAllModules("msvcr71.dll", "_strdup", (void *)d_00881e10);
	rva00882140PatchAllModules("msvcr71.dll", "_wcsdup", (void *)d_00881e60);
	rva00882140PatchAllModules("msvcr71.dll", "_mbsdup", (void *)d_00881ea0);

	g_0130E990 = 0;
}
