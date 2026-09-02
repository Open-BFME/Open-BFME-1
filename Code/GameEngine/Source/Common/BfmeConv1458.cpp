// cl: /Od

void *bfmeBigAllocPR(unsigned n);
void *bfmeNodeAllocSmall(unsigned n);
void bfmeImplVMY(int a, int b, int c);

void *__stdcall bfmeMakeV18(unsigned n, int a, int b)
{
	char pad[32];

	__asm
	{
		mov dword ptr [ebp-0x18], ecx
		cmp dword ptr n, 0
		je zero_path
		mov eax, dword ptr n
		shl eax, 2
		mov dword ptr [ebp-0x0C], eax
		cmp dword ptr [ebp-0x0C], 0x80
		jbe small_alloc
		mov ecx, dword ptr [ebp-0x0C]
		push ecx
		call bfmeBigAllocPR
		add esp, 4
		mov dword ptr [ebp-0x1C], eax
		jmp got_ptr
	small_alloc:
		mov edx, dword ptr [ebp-0x0C]
		push edx
		call bfmeNodeAllocSmall
		add esp, 4
		mov dword ptr [ebp-0x1C], eax
	got_ptr:
		mov eax, dword ptr [ebp-0x1C]
		mov dword ptr [ebp-0x20], eax
		jmp after
	zero_path:
		mov dword ptr [ebp-0x20], 0
	after:
		mov ecx, dword ptr [ebp-0x20]
		mov dword ptr [ebp-4], ecx
		xor edx, edx
		mov byte ptr [ebp-5], dl
		xor eax, eax
		mov byte ptr [ebp-0x0E], al
		mov cl, byte ptr [ebp-0x0E]
		mov byte ptr [ebp-0x0D], cl
		xor edx, edx
		mov byte ptr [ebp-0x11], dl
		mov al, byte ptr [ebp-0x11]
		mov byte ptr [ebp-0x0F], al
		xor ecx, ecx
		mov byte ptr [ebp-0x12], cl
		mov dl, byte ptr [ebp-0x12]
		mov byte ptr [ebp-0x10], dl
		mov eax, dword ptr [ebp-4]
		push eax
		mov ecx, dword ptr b
		push ecx
		mov edx, dword ptr a
		push edx
		call bfmeImplVMY
		add esp, 0x0C
		mov eax, dword ptr [ebp-4]
	}
}
