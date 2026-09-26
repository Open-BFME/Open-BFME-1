// ?rva00882140PatchAllModules@@YAPAXPBD0PAX@Z
// Try rva00882050PatchImport against every module loaded in this process,
// then resolve the target through LoadLibraryA/GetProcAddress regardless.

typedef void *RvaModuleHandle;
typedef unsigned long RvaDword;

struct RvaModuleEntry32
{
    RvaDword dwSize;
    RvaDword th32ModuleID;
    RvaDword th32ProcessID;
    RvaDword GlblcntUsage;
    RvaDword ProccntUsage;
    unsigned char *modBaseAddr;
    RvaDword modBaseSize;
    RvaModuleHandle hModule;
    char szModule[256];
    char szExePath[260];
};

extern "C" __declspec(dllimport) RvaDword __stdcall GetCurrentProcessId(void);
extern "C" RvaModuleHandle __stdcall CreateToolhelp32Snapshot(RvaDword flags, RvaDword processId);
extern "C" int __stdcall Module32First(RvaModuleHandle snapshot, RvaModuleEntry32 *entry);
extern "C" int __stdcall Module32Next(RvaModuleHandle snapshot, RvaModuleEntry32 *entry);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(RvaModuleHandle module, const char *name);
__declspec(dllimport) void __stdcall bfmeClose1033(int h);

extern "C" RvaModuleHandle (__stdcall *g_rva0130E988LoadLibraryA)(const char *name);

extern bool rva00882050PatchImport(const char *moduleName, const char *dllName,
                                    const char *functionName, void *replacement);

void *rva00882140PatchAllModules(const char *dllName, const char *functionName, void *replacement)
{
    RvaModuleHandle snapshot = CreateToolhelp32Snapshot(8, GetCurrentProcessId());

    RvaModuleEntry32 entry;
    entry.dwSize = sizeof(RvaModuleEntry32);

    if (Module32First(snapshot, &entry))
    {
        do
        {
            rva00882050PatchImport(entry.szModule, dllName, functionName, replacement);
        } while (Module32Next(snapshot, &entry));
    }

    bfmeClose1033((int)snapshot);

    return GetProcAddress(g_rva0130E988LoadLibraryA(dllName), functionName);
}
