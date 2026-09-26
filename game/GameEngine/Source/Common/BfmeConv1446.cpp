// cl: /Od

void bfmeImplVMY(int a, int b, int c);
void bfmeFwdVMY(int a, int b, int c);

void bfmeFwdVMY(int a, int b, int c)
{
	char z[8];

	__asm
	{
		xor eax, eax
		mov byte ptr [ebp-2], al
		mov cl, byte ptr [ebp-2]
		mov byte ptr [ebp-1], cl
		xor edx, edx
		mov byte ptr [ebp-5], dl
		mov al, byte ptr [ebp-5]
		mov byte ptr [ebp-3], al
		xor ecx, ecx
		mov byte ptr [ebp-6], cl
		mov dl, byte ptr [ebp-6]
		mov byte ptr [ebp-4], dl
		mov eax, dword ptr c
		push eax
		mov ecx, dword ptr b
		push ecx
		mov edx, dword ptr a
		push edx
		call bfmeImplVMY
		add esp, 0x0C
	}
}
