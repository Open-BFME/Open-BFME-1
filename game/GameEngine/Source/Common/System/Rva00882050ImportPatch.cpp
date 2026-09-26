// ?rva00882050PatchImport@@YA_NPBD00PAX@Z
// Replace one imported function pointer in a loaded PE image.

typedef void *RvaModuleHandle;
typedef void *RvaProcAddress;

extern "C" __declspec(dllimport) RvaModuleHandle __stdcall GetModuleHandleA(const char *name);
extern "C" __declspec(dllimport) RvaProcAddress __stdcall GetProcAddress(RvaModuleHandle module, const char *name);
extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(const void *address, unsigned long size);
extern "C" __declspec(dllimport) RvaModuleHandle __stdcall GetCurrentProcess(void);
extern "C" __declspec(dllimport) int __stdcall VirtualProtect(void *address, unsigned long size, unsigned long protection, unsigned long *oldProtection);
extern "C" __declspec(dllimport) int __stdcall WriteProcessMemory(RvaModuleHandle process, void *address, const void *buffer, unsigned long size, unsigned long *written);

extern "C" RvaModuleHandle (__stdcall *g_rva0130E988LoadLibraryA)(const char *name);

bool rva00882050PatchImport(const char *moduleName, const char *dllName,
                            const char *functionName, void *replacement)
{
    RvaProcAddress target = GetProcAddress(g_rva0130E988LoadLibraryA(dllName), functionName);
    if (target == 0)
        return false;

    unsigned char *image = (unsigned char *)GetModuleHandleA(moduleName);
    if (IsBadReadPtr(image, 4))
        return false;

    if (*(unsigned short *)image != 0x5a4d)
        return false;

    unsigned char *ntHeaders = image + *(unsigned long *)(image + 0x3c);
    if (*(unsigned long *)ntHeaders != 0x4550)
        return false;

    unsigned char *imports = image + *(unsigned long *)(ntHeaders + 0x80);
    if (imports == ntHeaders)
        return false;

    unsigned char *descriptor = imports + 0xc;
    while (*(unsigned long *)descriptor != 0)
    {
        unsigned long *iat = (unsigned long *)(image + *(unsigned long *)(descriptor + 4));
        while (*iat != 0)
        {
            if ((RvaProcAddress)*iat == target)
            {
                unsigned long restoredProtection = 4;
                unsigned long oldProtection;
                VirtualProtect(iat, 4, 4, &oldProtection);
                WriteProcessMemory(GetCurrentProcess(), iat, &replacement, 4, 0);
                VirtualProtect(iat, 4, oldProtection, &restoredProtection);
                return true;
            }
            ++iat;
        }
        descriptor += 0x14;
    }

    return false;
}
