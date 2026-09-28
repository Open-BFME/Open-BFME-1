// The callback globals are address-derived; the second call passes two stack slots.
extern "C" void (__cdecl *g_012F3934)(void);
extern "C" void (__cdecl *g_012F3930)(void);

void j_00042a50(void);
void j_0002fcb1(void);

void dup_004c6a40()
{
	j_00042a50();
	__asm
	{
		mov eax, dword ptr [g_012F3934]
		mov ecx, dword ptr [g_012F3930]
		push eax
		push ecx
		call j_0002fcb1
		add esp, 8
	}
}
