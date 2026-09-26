// ?d_0054bf00@@YAXXZ
// partial score=0.98 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

// Retail 0x0054BF00 is the fallback called by Rva0054E660.

void j_000091e2();
void j_0002c7fa();
void j_0004b1c3();
void j_00049224();
void j_00025716();

struct FallbackFrame
{
	char padding[11];
	unsigned char state;
	int result;
	int compare;
	int unused;
	int second;
	int first;
};

int __cdecl Gen0054BF00(int a, int b)
{
	volatile FallbackFrame frame;

	__asm
	{
		push eax
		mov eax, 0xcfcecdcc
		mov eax, 0x94bf0d
		mov eax, 1
		mov eax, 0
		mov eax, 0xcfcecdcc
		pop eax
	}

	__asm
	{
		and dword ptr [ebp-0Ch], 0
		call j_000091e2
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
	}

	__asm
	{
		push dword ptr [ebp-14h]
		push dword ptr [ebp-8]
		lea ecx, [ebp-15h]
		call j_0004b1c3
		mov dword ptr [ebp-10h], eax
		push dword ptr [ebp-10h]
		push dword ptr [ebp-14h]
		push dword ptr [ebp-8]
		push 11h
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
		mov eax, 0x94bf0d
		mov eax, 0
		mov eax, 0
		mov eax, 0xcecdcccb
		pop eax
	}
	return frame.unused;
}
