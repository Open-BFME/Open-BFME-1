// cl: /Od

class BfmeStrV36
{
public:
	void bfmeThrowV36();
	void bfmeAppendV36(char *a, char *b, char *tag);

	char *b;
	char *e;
};

void __stdcall bfmeAppendRangeV36(BfmeStrV36 *other, int pos, int n)
{
	char pad[104];

	__asm
	{
		mov dword ptr [ebp-0x64], ecx
		mov eax, dword ptr [ebp+8]
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x0C], edx
		jbe skip_throw
		mov ecx, dword ptr [ebp-0x64]
		call BfmeStrV36::bfmeThrowV36
	skip_throw:
		mov eax, dword ptr [ebp+8]
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-4], edx
		mov eax, dword ptr [ebp-4]
		cmp eax, dword ptr [ebp+0x10]
		jnb use_n
		lea ecx, dword ptr [ebp-4]
		mov dword ptr [ebp-0x68], ecx
		jmp got_n
	use_n:
		lea edx, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x68], edx
	got_n:
		mov eax, dword ptr [ebp-0x68]
		mov dword ptr [ebp-8], eax
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [ecx]
		add edx, dword ptr [ebp+0x0C]
		mov eax, dword ptr [ebp-8]
		add edx, dword ptr [eax]
		mov dword ptr [ebp-0x5C], edx
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [ecx]
		add edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x60], edx
		xor eax, eax
		mov byte ptr [ebp-9], al
		lea ecx, dword ptr [ebp-0x0A]
		push ecx
		mov edx, dword ptr [ebp-0x5C]
		push edx
		mov eax, dword ptr [ebp-0x60]
		push eax
		mov ecx, dword ptr [ebp-0x64]
		call BfmeStrV36::bfmeAppendV36
	}
}
