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
	const char *name);

extern void *rva00882140PatchAllModules(const char *dllName,
	const char *functionName, void *replacement);

// ?rva008821d0LoaderPatch@@YAXXZ
void rva008821d0LoaderPatch(void)
{
	if (*(volatile unsigned char *)0x0130E990 != 0)
		return;

	if (g_rva0130E988LoadLibraryA != 0)
	{
		*(volatile unsigned char *)0x0130E990 = 1;
	}
	else
	{
		*(volatile unsigned char *)0x0130E990 = 1;
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
			(void *)0x00C81FB0);
		*(RvaLoadLibraryW821D0 *)0x0130E984 =
			(RvaLoadLibraryW821D0)rva00882140PatchAllModules(
				"kernel32.dll", "LoadLibraryW", (void *)0x00C81FD0);
		*(RvaLoadLibraryExA821D0 *)0x0130E980 =
			(RvaLoadLibraryExA821D0)rva00882140PatchAllModules(
				"kernel32.dll", "LoadLibraryExA", (void *)0x00C81FF0);
		*(RvaLoadLibraryExW821D0 *)0x0130E97C =
			(RvaLoadLibraryExW821D0)rva00882140PatchAllModules(
				"kernel32.dll", "LoadLibraryExW", (void *)0x00C82020);
	}

	rva00882140PatchAllModules("msvcr71.dll", "calloc", (void *)0x00C81CA0);
	rva00882140PatchAllModules("msvcr71.dll", "_calloc_dbg", (void *)0x00C81CE0);
	rva00882140PatchAllModules("msvcr71.dll", "free", (void *)0x00C81D20);
	rva00882140PatchAllModules("msvcr71.dll", "_free_dbg", (void *)0x00C81D40);
	rva00882140PatchAllModules("msvcr71.dll", "malloc", (void *)0x00C81D70);
	rva00882140PatchAllModules("msvcr71.dll", "_malloc_dbg", (void *)0x00C81D90);
	rva00882140PatchAllModules("msvcr71.dll", "_msize", (void *)0x00C81DB0);
	rva00882140PatchAllModules("msvcr71.dll", "_msize_dbg", (void *)0x00C81DC0);
	rva00882140PatchAllModules("msvcr71.dll", "realloc", (void *)0x00C81DD0);
	rva00882140PatchAllModules("msvcr71.dll", "_realloc_dbg", (void *)0x00C81DF0);
	rva00882140PatchAllModules("msvcr71.dll", "_strdup", (void *)0x00C81E10);
	rva00882140PatchAllModules("msvcr71.dll", "_wcsdup", (void *)0x00C81E60);
	rva00882140PatchAllModules("msvcr71.dll", "_mbsdup", (void *)0x00C81EA0);

	*(volatile unsigned char *)0x0130E990 = 0;
}
