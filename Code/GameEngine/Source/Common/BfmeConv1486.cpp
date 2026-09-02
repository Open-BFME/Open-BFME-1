// cl: /Od

class BfmeStrV44
{
public:
	void bfmeEraseV44(char *a, char *b);
	void bfmeImplV44(char *a, char *b, char *c, char *d);

	char *b;
	char *e;
};

void __stdcall bfmeReplaceRangeV44(char *d0, char *d1, char *s0, char *s1, int extra)
{
	void *at;
	char pad[188];

	__asm
	{
		mov dword ptr [ebp-0xBC], ecx
		mov eax, dword ptr [ebp+0x14]
		sub eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-8], eax
		mov ecx, dword ptr [ebp+0x0C]
		sub ecx, dword ptr [ebp+8]
		mov dword ptr [ebp-4], ecx
		mov edx, dword ptr [ebp-4]
		cmp edx, dword ptr [ebp-8]
		jl grow_path
		mov eax, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x18], eax
		mov ecx, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x1C], ecx
		mov edx, dword ptr [ebp-0x18]
		sub edx, dword ptr [ebp-0x1C]
		mov dword ptr [ebp-0x14], edx
		jnz copy_src
		mov eax, dword ptr [ebp+8]
		mov dword ptr [ebp-0xC0], eax
		jmp after_copy_src
	copy_src:
		mov ecx, dword ptr [ebp-0x14]
		mov esi, dword ptr [ebp-0x1C]
		mov edi, dword ptr [ebp+8]
		mov edx, ecx
		mov eax, edi
		shr ecx, 2
		rep movsd
		mov ecx, edx
		and ecx, 3
		rep movsb
		mov dword ptr [ebp-0xC0], eax
	after_copy_src:
		mov ecx, dword ptr [ebp+0x0C]
		push ecx
		mov edx, dword ptr [ebp+8]
		add edx, dword ptr [ebp-8]
		push edx
		mov ecx, dword ptr [ebp-0xBC]
		call BfmeStrV44::bfmeEraseV44
		jmp done
	grow_path:
		mov eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x0C], eax
		mov ecx, dword ptr [ebp-0x0C]
		add ecx, dword ptr [ebp-4]
		mov dword ptr [ebp-0x0C], ecx
		mov edx, dword ptr [ebp-0x0C]
		mov dword ptr [ebp-0x30], edx
		mov eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x34], eax
		mov ecx, dword ptr [ebp-0x30]
		sub ecx, dword ptr [ebp-0x34]
		mov dword ptr [ebp-0x2C], ecx
		jnz copy_dst
		mov edx, dword ptr [ebp+8]
		mov dword ptr [ebp-0xC4], edx
		jmp after_copy_dst
	copy_dst:
		mov ecx, dword ptr [ebp-0x2C]
		mov esi, dword ptr [ebp-0x34]
		mov edi, dword ptr [ebp+8]
		mov eax, ecx
		mov edx, edi
		shr ecx, 2
		rep movsd
		mov ecx, eax
		and ecx, 3
		rep movsb
		mov dword ptr [ebp-0xC4], edx
	after_copy_dst:
		mov eax, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0xB4], eax
		mov ecx, dword ptr [ebp-0x0C]
		mov dword ptr [ebp-0xB8], ecx
		xor edx, edx
		mov byte ptr [ebp-0x35], dl
		lea eax, dword ptr [ebp-0x36]
		push eax
		mov ecx, dword ptr [ebp-0xB4]
		push ecx
		mov edx, dword ptr [ebp-0xB8]
		push edx
		mov eax, dword ptr [ebp+0x0C]
		push eax
		mov ecx, dword ptr [ebp-0xBC]
		call BfmeStrV44::bfmeImplV44
	done:
		mov eax, dword ptr [ebp-0xBC]
	}
}
