// ?d_0088e970@@YAXXZ
// partial score=0.30 date=2026-09-21
// ?d_0088e970@@YAXXZ [retail body 0x0088E970, 249 bytes]
// Identity proven by the landed caller Code/GameEngine/Source/Common/
// DebugConstructor_00889370.cpp, which forward-declares and calls
// `void d_0088e970(void);` from Debug::Debug().  This is an IAT hook
// installer: resolve a function via LoadLibraryA+GetProcAddress, walk the
// current process's own PE import-descriptor table looking for the IAT
// slot that currently holds that resolved address, and overwrite that
// slot with the Debug StackWalk vtable address (0x00C8E8D0) after making
// the page writable.
// cl: /DNDEBUG /MD /EHa /Oy-

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

extern char g_rva0088e970Dll[];
extern char g_rva0088e970Proc[];
extern char g_rva0088e970Module[];
extern void *g_rva0088e970Found;

typedef unsigned short Rva0088e970Word;
typedef unsigned int Rva0088e970Dword;

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
extern "C" void _ReadBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_ReadBarrier)

void d_0088e970(void)
{
	void *proc = GetProcAddress(LoadLibraryA(g_rva0088e970Dll), g_rva0088e970Proc);
	if (!proc) {
		_WriteBarrier();
		return;
	}

	char *base = (char *)GetModuleHandleA(g_rva0088e970Module);
	if (IsBadReadPtr(base, 4)) {
		_ReadWriteBarrier();
		return;
	}
	if (*(Rva0088e970Word *)base != 0x5A4D) {
		_ReadWriteBarrier();
		return;
	}

	char *nt = base + *(Rva0088e970Dword *)(base + 0x3c);
	if (*(Rva0088e970Dword *)nt != 0x4550) {
		_ReadWriteBarrier();
		return;
	}

	char *dir = base + *(Rva0088e970Dword *)(nt + 0x80);
	if (dir == nt) {
		_ReadWriteBarrier();
		return;
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
				*(Rva0088e970Dword *)thunk = 0xc8e8d0;
				VirtualProtect(thunk, 4, oldProtect, &oldProtect);
				return;
			}
			thunk += 4;
		}
		descriptor += 0x14;
	}
	_ReadBarrier();
}
