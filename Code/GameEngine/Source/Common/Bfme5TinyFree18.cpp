// Retail @ 0x0005D7E0 size 18, ghidra bounds-high
// mov eax,[ecx]; add ecx,4; cmp eax,ecx; jz ret; push eax; call [0x013593D4]; pop ecx; ret
// ecx = void** p, pop ecx peephole for add esp,4
extern "C" __declspec(dllimport) void __cdecl free(void*);

void __fastcall d_0005d7e0(void** p)
{
	void* v = *p++;
	if (v != (void*)p)
		free(v);
}
