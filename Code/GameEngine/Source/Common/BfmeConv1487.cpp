// cl: /Od

void *bfmeAllocQL(int n, void *p);
void bfmeCopyBwdV45(int *a, int *b, int *c);

class BfmeVecV45
{
public:
	void bfmeOverflowV45(int *pos, int *val, char *t, unsigned n, bool b);

	int *b;
	int *e;
	int *c;
};

int *__stdcall bfmeInsertV45(int *pos, int *val)
{
	void *at;
	char pad[116];

	__asm
	{
		mov dword ptr [ebp-0x74], ecx
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp+8]
		sub edx, dword ptr [ebp-0x10]
		sar edx, 2
		mov dword ptr [ebp-4], edx
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [eax+4]
		cmp edx, dword ptr [ecx+8]
		jz overflow_path
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x14], ecx
		mov edx, dword ptr [ebp+8]
		cmp edx, dword ptr [ebp-0x14]
		jnz insert_mid
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x1C], ecx
		mov edx, dword ptr [ebp-0x1C]
		push edx
		push 4
		call bfmeAllocQL
		add esp, 8
		mov dword ptr [ebp-0x18], eax
		cmp dword ptr [ebp-0x18], 0
		jz null_end
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [ebp+0x0C]
		mov edx, dword ptr [ecx]
		mov dword ptr [eax], edx
		mov eax, dword ptr [ebp-0x18]
		mov dword ptr [ebp-0x78], eax
		jmp bump_end
	null_end:
		mov dword ptr [ebp-0x78], 0
	bump_end:
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ecx+4]
		add edx, 4
		mov eax, dword ptr [ebp-0x74]
		mov dword ptr [eax+4], edx
		jmp after_room
	insert_mid:
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ecx+4]
		sub edx, 4
		mov dword ptr [ebp-0x24], edx
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x28], ecx
		mov edx, dword ptr [ebp-0x28]
		push edx
		push 4
		call bfmeAllocQL
		add esp, 8
		mov dword ptr [ebp-0x20], eax
		cmp dword ptr [ebp-0x20], 0
		jz null_mid
		mov eax, dword ptr [ebp-0x20]
		mov ecx, dword ptr [ebp-0x24]
		mov edx, dword ptr [ecx]
		mov dword ptr [eax], edx
		mov eax, dword ptr [ebp-0x20]
		mov dword ptr [ebp-0x7C], eax
		jmp bump_mid
	null_mid:
		mov dword ptr [ebp-0x7C], 0
	bump_mid:
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ecx+4]
		add edx, 4
		mov eax, dword ptr [ebp-0x74]
		mov dword ptr [eax+4], edx
		mov ecx, dword ptr [ebp+0x0C]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-8], edx
		xor eax, eax
		mov byte ptr [ebp-9], al
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ecx+4]
		sub edx, 4
		mov dword ptr [ebp-0x30], edx
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax+4]
		sub ecx, 8
		mov dword ptr [ebp-0x34], ecx
		mov edx, dword ptr [ebp-0x30]
		push edx
		mov eax, dword ptr [ebp-0x34]
		push eax
		mov ecx, dword ptr [ebp+8]
		push ecx
		call bfmeCopyBwdV45
		add esp, 0x0C
		mov edx, dword ptr [ebp+8]
		mov eax, dword ptr [ebp-8]
		mov dword ptr [edx], eax
	after_room:
		jmp done_ins
	overflow_path:
		xor ecx, ecx
		mov byte ptr [ebp-0x0A], cl
		push 0
		push 1
		lea edx, dword ptr [ebp-0x0A]
		push edx
		mov eax, dword ptr [ebp+0x0C]
		push eax
		mov ecx, dword ptr [ebp+8]
		push ecx
		mov ecx, dword ptr [ebp-0x74]
		call BfmeVecV45::bfmeOverflowV45
	done_ins:
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x70], eax
		mov ecx, dword ptr [ebp-4]
		mov edx, dword ptr [ebp-0x70]
		lea eax, dword ptr [edx+ecx*4]
	}
}
