// ?Gen003859B0@@YAHHH@Z
// partial score=0.99 date=2026-09-13
// ?Gen003859B0@@YAHHH@Z
// This protection fallback belongs to the Rva003897C0 hook wrapper. The
// wrapper family and this two-argument fallback share the same retail call
// sites and obfuscated marker sequence.

void j_00010ca3();
void j_0002c7fa();
void j_00008d69();
void j_00049224();
void j_00025716();

struct BigObfFallbackFrame
{
	char m_padding[11];
	unsigned char m_state;
	int m_result;
	int m_compare;
	int m_unused;
	int m_second;
	int m_first;
};

int __cdecl Gen003859B0(int a, int b)
{
	volatile BigObfFallbackFrame frame;

	__asm
	{
		push eax
		mov eax, 0xcfcecdcc
		mov eax, 0x7859bd
		mov eax, 1
		mov eax, 0
		mov eax, 0xcfcecdcc
		pop eax

		and dword ptr [ebp-0Ch], 0
		call j_00010ca3
		mov dword ptr [ebp-4], eax
		push dword ptr [ebp+8]
		push dword ptr [ebp-4]
		call j_0002c7fa
		pop ecx
		pop ecx
		mov dword ptr [ebp-8], eax
		push dword ptr [ebp+0Ch]
		push dword ptr [ebp-4]
		call j_0002c7fa
		pop ecx
		pop ecx
		mov dword ptr [ebp-14h], eax
		xor eax, eax
		lea edi, [ebp-15h]
		stosb
		push dword ptr [ebp-14h]
		push dword ptr [ebp-8]
		lea ecx, [ebp-15h]
		call j_00008d69
		mov dword ptr [ebp-10h], eax
		push dword ptr [ebp-10h]
		push dword ptr [ebp-14h]
		push dword ptr [ebp-8]
		push 1
		push 5
		call j_00049224
		add esp, 14h
		mov dword ptr [ebp-10h], eax
		xor eax, eax
		je first_dead
		cmp dword ptr [ebp-8], 1
		jne first_dead
		mov eax, dword ptr [ebp-4]
		and dword ptr [eax+18h], 0
	first_dead:
		xor eax, eax
		je second_dead
		mov eax, dword ptr [ebp+0Ch]
		mov dword ptr [ebp-10h], eax
	second_dead:
		xor eax, eax
		je call_path
		mov eax, dword ptr [ebp-8]
		mov dword ptr [ebp-0Ch], eax
		jmp after_call
	call_path:
		push dword ptr [ebp-10h]
		push dword ptr [ebp-4]
		call j_00025716
		pop ecx
		pop ecx
		mov dword ptr [ebp-0Ch], eax
	after_call:
		push eax
		mov eax, 0xcfcecdcc
		mov eax, 0x7859bd
		mov eax, 0
		mov eax, 0
		mov eax, 0xcecdcccb
		pop eax
	}

	return frame.m_unused;
}
