// cl: /DNDEBUG /MD /EHa /Oy-
// RVA 0x0088E970: install the RaiseException import hook in msvcrt.dll.
// DebugConstructor_00889370.cpp is the direct caller and ignores the result.
// Retail returns bool (AL=0 on all misses; AL=1 on success). Its true boundary
// is 252 bytes: +F8 mov esp,ebp; +FA pop ebp; +FB ret; +FC starts INT3 padding.
// The previous 249-byte generated extent cut the final mov in half.
// Replacement address 0088E8D0 is executable code, not a vtable.
// Distinct barriers retain retail's distinct early failure epilogues.

extern "C" __declspec(dllimport) void *__stdcall LoadLibraryA(const char *);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(void *, const char *);
extern "C" __declspec(dllimport) void *__stdcall GetModuleHandleA(const char *);
extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(const void *, unsigned int);

struct BfmeMbi0088e970
{
	void *baseAddress;
	void *allocationBase;
	unsigned long allocationProtect;
	unsigned long regionSize;
	unsigned long state;
	unsigned long protect;
	unsigned long type;
};

extern "C" __declspec(dllimport) unsigned long __stdcall VirtualQuery(
	const void *, BfmeMbi0088e970 *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall VirtualProtect(
	void *, unsigned long, unsigned long, unsigned long *);

extern void d_0088e8d0();
void *g_rva0088e970Found = 0;

typedef unsigned short Rva0088e970Word;
typedef unsigned int Rva0088e970Dword;

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

bool installDebugImportHook0088E970(void)
{
	void *proc = GetProcAddress(LoadLibraryA("kernel32.dll"), "RaiseException");
	if (!proc) {
		_WriteBarrier();
		return false;
	}

	char *base = (char *)GetModuleHandleA("msvcrt.dll");
	if (IsBadReadPtr(base, 4)) {
		_ReadWriteBarrier();
		return false;
	}
	if (*(Rva0088e970Word *)base != 0x5A4D) {
		_ReadWriteBarrier();
		return false;
	}

	char *nt = base + *(Rva0088e970Dword *)(base + 0x3c);
	if (*(Rva0088e970Dword *)nt != 0x4550) {
		_ReadWriteBarrier();
		return false;
	}

	char *dir = base + *(Rva0088e970Dword *)(nt + 0x80);
	if (dir == nt) {
		_ReadWriteBarrier();
		return false;
	}

	char *descriptor = dir + 0xc;
	while (*(Rva0088e970Dword *)descriptor) {
		char *thunk = base + *(Rva0088e970Dword *)(descriptor + 4);
		while (*(void **)thunk) {
			if (*(void **)thunk == proc) {
				BfmeMbi0088e970 mbi;
				g_rva0088e970Found = proc;
				VirtualQuery(thunk, &mbi, sizeof(mbi));
				unsigned long newProtect = (mbi.protect & 0xFFFFFFDD) | 4;
				unsigned long oldProtect;
				VirtualProtect(thunk, 4, newProtect, &oldProtect);
				*(Rva0088e970Dword *)thunk = (Rva0088e970Dword)&d_0088e8d0;
				VirtualProtect(thunk, 4, oldProtect, &newProtect);
				return true;
			}
			thunk += 4;
		}
		descriptor += 0x14;
	}
	return false;
}
