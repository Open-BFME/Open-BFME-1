// Retail uses ESI as its incoming object register; inline assembly preserves that custom ABI.
void j_0003a5b7();
void j_00010e88();

void dup_004af9b0()
{
	__asm
	{
		mov ecx, esi
		call j_0003a5b7
		test al, al
		jz check_button
		xor al, al
		ret
	check_button:
		push esi
		call j_00010e88
		add esp, 4
		test eax, eax
		jz false_result
		mov ecx, dword ptr [eax + 144h]
		test ecx, ecx
		jle false_result
		mov eax, 1
		ret
	false_result:
		xor eax, eax
	}
}
