// The entry consumes EAX directly; no MSVC C++ calling convention supplies this register-only input.
void dup_0042e7a0()
{
	__asm
	{
		test byte ptr [eax + 110h], 10h
		jz true_result
		mov ecx, dword ptr [eax + 0fch]
		test ecx, ecx
		jnz true_result
		xor al, al
		ret
	true_result:
		mov al, 1
	}
}
