// The body forwards an opaque EDX input; the callee is a five-slot cdecl call.
extern void *g_rva004C84C0_12b6a84;
extern void *g_rva004C84C0_12b6a88;
extern char g_rva004C84C0_12b6a8c;
extern char g_rva004C84C0_12f3a38;

// Assembler-only target name; the thunk placeholder does not encode its ABI.
void j_00047d52(void);

void dup_004c8490()
{
	__asm
	{
		mov eax, dword ptr [g_rva004C84C0_12b6a88]
		mov ecx, dword ptr [g_rva004C84C0_12b6a84]
		push offset g_rva004C84C0_12f3a38
		push offset g_rva004C84C0_12b6a8c
		push eax
		push ecx
		push edx
		call j_00047d52
		add esp, 14h
	}
}
