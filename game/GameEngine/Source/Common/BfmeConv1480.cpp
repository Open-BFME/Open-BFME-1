// cl: /Od

void bfmeGoPA(void *a, void *b, void *c, void *d, unsigned char e);

class BfmeStrV39
{
public:
	char *b;
	char *e;
};

int __stdcall bfmeFindV39(char *s, unsigned pos, unsigned n)
{
	char pad[44];

	__asm
	{
		mov dword ptr [ebp-0x20], ecx
		mov eax, dword ptr [ebp-0x20]
		mov ecx, dword ptr [ebp-0x20]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		mov dword ptr [ebp-4], edx
		mov eax, dword ptr [ebp+0x10]
		cmp eax, dword ptr [ebp-4]
		jbe check_zero
		or eax, -1
		jmp done
	check_zero:
		cmp dword ptr [ebp+0x10], 0
		jnz search
		mov ecx, dword ptr [ebp+0x0C]
		cmp ecx, dword ptr [ebp-4]
		jnb use_len
		lea edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x24], edx
		jmp got_pos
	use_len:
		lea eax, dword ptr [ebp-4]
		mov dword ptr [ebp-0x24], eax
	got_pos:
		mov ecx, dword ptr [ebp-0x24]
		mov dword ptr [ebp-0x18], ecx
		mov edx, dword ptr [ebp-0x18]
		mov eax, dword ptr [edx]
		jmp done
	search:
		mov eax, dword ptr [ebp-4]
		sub eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x10], eax
		mov ecx, dword ptr [ebp+0x0C]
		cmp ecx, dword ptr [ebp-0x10]
		jnb use_room
		lea edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x28], edx
		jmp got_room
	use_room:
		lea eax, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x28], eax
	got_room:
		mov ecx, dword ptr [ebp-0x28]
		mov dword ptr [ebp-0x1C], ecx
		mov edx, dword ptr [ebp-0x20]
		mov eax, dword ptr [edx]
		mov ecx, dword ptr [ebp-0x1C]
		add eax, dword ptr [ecx]
		add eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x0C], eax
		mov dl, byte ptr [ebp-0x11]
		push edx
		mov eax, dword ptr [ebp+8]
		add eax, dword ptr [ebp+0x10]
		push eax
		mov ecx, dword ptr [ebp+8]
		push ecx
		mov edx, dword ptr [ebp-0x0C]
		push edx
		mov eax, dword ptr [ebp-0x20]
		mov ecx, dword ptr [eax]
		push ecx
		call bfmeGoPA
		add esp, 0x14
		mov dword ptr [ebp-8], eax
		mov edx, dword ptr [ebp-8]
		cmp edx, dword ptr [ebp-0x0C]
		jz notfound
		mov eax, dword ptr [ebp-0x20]
		mov ecx, dword ptr [ebp-8]
		sub ecx, dword ptr [eax]
		mov dword ptr [ebp-0x2C], ecx
		jmp ret_idx
	notfound:
		mov dword ptr [ebp-0x2C], 0xFFFFFFFF
	ret_idx:
		mov eax, dword ptr [ebp-0x2C]
	done:
	}
}
