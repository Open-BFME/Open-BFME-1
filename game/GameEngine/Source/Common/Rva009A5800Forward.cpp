// The middle stack argument is passed to the callee in EAX, outside the
// MSVC C++ calling conventions. Keep the proven register setup in inline asm.
void __cdecl d_009a5620(void);

void __cdecl Rva009A5800Forward(int, int, int)
{
	__asm {
		mov eax, dword ptr [esp + 0Ch]
		mov ecx, dword ptr [esp + 04h]
		push eax
		mov eax, dword ptr [esp + 0Ch]
		push ecx
		call d_009a5620
		add esp, 8
	}
}
