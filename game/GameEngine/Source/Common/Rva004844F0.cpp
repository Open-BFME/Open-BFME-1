// Retail enters with the source in ECX and the output pointer in EAX; this register-only ABI requires inline assembly.
extern "C" int __declspec(dllimport) __cdecl sscanf(const char *source, const char *format, ...);

void dup_004844f0()
{
	__asm
	{
		push eax
		push 107c7b4h
		push ecx
		call dword ptr [sscanf]
		add esp, 0ch
	}
}
