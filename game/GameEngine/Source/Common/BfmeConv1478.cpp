// cl: /Od

class BfmeStrV37
{
public:
	void bfmeThrowV37();
	void bfmeInitV37(char *a, char *b, char *tag);

	char *b;
	char *e;
};

void __stdcall bfmeAssignRangeV37(BfmeStrV37 *other, int pos, int n)
{
	void *at;
	char pad[116];

	__asm
	{
		mov dword ptr [ebp-0x78], ecx
		mov eax, dword ptr [ebp+8]
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x0C], edx
		jbe skip_throw
		mov ecx, dword ptr [ebp-0x78]
		call BfmeStrV37::bfmeThrowV37
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
		mov dword ptr [ebp-0x7C], ecx
		jmp got_n
	use_n:
		lea edx, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x7C], edx
	got_n:
		mov eax, dword ptr [ebp-0x7C]
		mov dword ptr [ebp-8], eax
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [ecx]
		add edx, dword ptr [ebp+0x0C]
		mov eax, dword ptr [ebp-8]
		add edx, dword ptr [eax]
		mov dword ptr [ebp-0x70], edx
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [ecx]
		add edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x74], edx
		xor eax, eax
		mov byte ptr [ebp-9], al
		lea ecx, dword ptr [ebp-9]
		push ecx
		mov edx, dword ptr [ebp-0x70]
		push edx
		mov eax, dword ptr [ebp-0x74]
		push eax
		mov ecx, dword ptr [ebp-0x78]
		call BfmeStrV37::bfmeInitV37
	}
}
