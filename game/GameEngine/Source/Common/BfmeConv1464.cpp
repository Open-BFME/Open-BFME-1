// cl: /Od

void bfmeCopyChV24(char *a, char *b);

class BfmeStrV24
{
public:
	BfmeStrV24 *bfmeReplaceV24(char *first, char *last, char *sf, char *sl, int extra);
	void bfmeEraseV24(char *first, char *last);
	void bfmeImplV24(char *a, char *b, char *c, char *d);

	char *b;
	char *e;
};

BfmeStrV24 *BfmeStrV24::bfmeReplaceV24(char *first, char *last, char *sf, char *sl, int extra)
{
	char pad[208];

	__asm
	{
		mov eax, dword ptr sl
		sub eax, dword ptr sf
		mov dword ptr [ebp-8], eax
		mov ecx, dword ptr last
		sub ecx, dword ptr first
		mov dword ptr [ebp-4], ecx
		mov edx, dword ptr [ebp-4]
		cmp edx, dword ptr [ebp-8]
		jl grow_path
		mov eax, dword ptr first
		mov dword ptr [ebp-0x14], eax
		mov ecx, dword ptr sl
		mov dword ptr [ebp-0x18], ecx
		mov edx, dword ptr sf
		mov dword ptr [ebp-0x1C], edx
		jmp cmp1
	inc1:
		mov eax, dword ptr [ebp-0x1C]
		add eax, 1
		mov dword ptr [ebp-0x1C], eax
		mov ecx, dword ptr [ebp-0x14]
		add ecx, 1
		mov dword ptr [ebp-0x14], ecx
	cmp1:
		mov edx, dword ptr [ebp-0x1C]
		cmp edx, dword ptr [ebp-0x18]
		je done1
		mov eax, dword ptr [ebp-0x1C]
		push eax
		mov ecx, dword ptr [ebp-0x14]
		push ecx
		call bfmeCopyChV24
		add esp, 8
		jmp inc1
	done1:
		mov edx, dword ptr last
		push edx
		mov eax, dword ptr first
		add eax, dword ptr [ebp-8]
		push eax
		mov ecx, this
		call bfmeEraseV24
		jmp done
	grow_path:
		mov ecx, dword ptr sf
		mov dword ptr [ebp-0x0C], ecx
		mov edx, dword ptr [ebp-0x0C]
		add edx, dword ptr [ebp-4]
		mov dword ptr [ebp-0x0C], edx
		mov eax, dword ptr first
		mov dword ptr [ebp-0x2C], eax
		mov ecx, dword ptr [ebp-0x0C]
		mov dword ptr [ebp-0x30], ecx
		mov edx, dword ptr sf
		mov dword ptr [ebp-0x34], edx
		jmp cmp2
	inc2:
		mov eax, dword ptr [ebp-0x34]
		add eax, 1
		mov dword ptr [ebp-0x34], eax
		mov ecx, dword ptr [ebp-0x2C]
		add ecx, 1
		mov dword ptr [ebp-0x2C], ecx
	cmp2:
		mov edx, dword ptr [ebp-0x34]
		cmp edx, dword ptr [ebp-0x30]
		je done2
		mov eax, dword ptr [ebp-0x34]
		push eax
		mov ecx, dword ptr [ebp-0x2C]
		push ecx
		call bfmeCopyChV24
		add esp, 8
		jmp inc2
	done2:
		mov edx, dword ptr sl
		mov dword ptr [ebp-0xCC], edx
		mov eax, dword ptr [ebp-0x0C]
		mov dword ptr [ebp-0xD0], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x35], cl
		lea edx, [ebp-0x36]
		push edx
		mov eax, dword ptr [ebp-0xCC]
		push eax
		mov ecx, dword ptr [ebp-0xD0]
		push ecx
		mov edx, dword ptr last
		push edx
		mov ecx, this
		call bfmeImplV24
	done:
		mov eax, this
	}
}
