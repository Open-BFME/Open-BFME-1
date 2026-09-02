// cl: /Od

class BfmeStrV38
{
public:
	void bfmeThrowV38();
	void bfmeLenErrV38();
	BfmeStrV38 *bfmeFillInsV38(char *a, char *b, unsigned n, char ch);

	char *b;
	char *e;
};

void __stdcall bfmeInsertChV38(int pos, int n, unsigned count, char ch)
{
	char pad[28];

	__asm
	{
		mov dword ptr [ebp-0x18], ecx
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+8], edx
		jbe skip_throw
		mov ecx, dword ptr [ebp-0x18]
		call BfmeStrV38::bfmeThrowV38
	skip_throw:
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+8]
		mov dword ptr [ebp-8], edx
		mov eax, dword ptr [ebp-8]
		cmp eax, dword ptr [ebp+0x0C]
		jnb use_n
		lea ecx, dword ptr [ebp-8]
		mov dword ptr [ebp-0x1C], ecx
		jmp got_n
	use_n:
		lea edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x1C], edx
	got_n:
		mov eax, dword ptr [ebp-0x1C]
		mov dword ptr [ebp-0x0C], eax
		mov ecx, dword ptr [ebp-0x0C]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-4], edx
		cmp dword ptr [ebp+0x10], -2
		ja len_err
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp-4]
		mov eax, 0xFFFFFFFE
		sub eax, dword ptr [ebp+0x10]
		cmp edx, eax
		jb do_ins
	len_err:
		mov ecx, dword ptr [ebp-0x18]
		call BfmeStrV38::bfmeLenErrV38
	do_ins:
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x10], edx
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x14], ecx
		mov dl, byte ptr [ebp+0x14]
		push edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		mov ecx, dword ptr [ebp-0x10]
		add ecx, dword ptr [ebp+8]
		add ecx, dword ptr [ebp-4]
		push ecx
		mov edx, dword ptr [ebp-0x14]
		add edx, dword ptr [ebp+8]
		push edx
		mov ecx, dword ptr [ebp-0x18]
		call BfmeStrV38::bfmeFillInsV38
	}
}
