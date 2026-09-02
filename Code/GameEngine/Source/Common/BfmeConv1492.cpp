// cl: /Od

void *bfmeCopyTrivialV46(void *a, void *b, void *c);
void bfmeCopyFwdV49(void *a, void *b, void *c);
void *bfmeBigAllocPR(unsigned n);
void *bfmeNodeAllocV46(unsigned n);
void bfmeFreeV46(void *p, unsigned n);
static void *bfmeMemmoveSlotV46 = (void *)0x0135945C;

class BfmeStrV49
{
public:
	void bfmeDeallocV49();
	char *b;
	char *e;
	char *c;
};

void __stdcall bfmeInsertRangeV49(char *pos, char *first, char *last, char *tag)
{
	void *at;
	char pad[132];

	__asm
	{
		mov dword ptr [ebp-0x74], ecx
		mov eax, dword ptr [ebp+0xC]
		cmp eax, dword ptr [ebp+0x10]
		jz done
		mov ecx, dword ptr [ebp+0x10]
		sub ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x4], ecx
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [edx+0x8]
		sub ecx, dword ptr [eax+0x4]
		mov edx, dword ptr [ebp-0x4]
		add edx, 1
		cmp ecx, edx
		jl L8
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax+0x4]
		sub ecx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x8], ecx
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [edx+0x4]
		mov dword ptr [ebp-0xC], eax
		mov ecx, dword ptr [ebp-0x8]
		cmp ecx, dword ptr [ebp-0x4]
		jl L5
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [edx+0x4]
		add eax, 1
		push eax
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ecx+0x4]
		add edx, 1
		push edx
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax+0x4]
		sub ecx, dword ptr [ebp-0x4]
		add ecx, 1
		push ecx
		call bfmeCopyTrivialV46
		add esp, 12
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [edx+0x4]
		add eax, dword ptr [ebp-0x4]
		mov ecx, dword ptr [ebp-0x74]
		mov dword ptr [ecx+0x4], eax
		mov edx, dword ptr [ebp-0x8]
		sub edx, dword ptr [ebp-0x4]
		add edx, 1
		mov dword ptr [ebp-0x30], edx
		mov eax, dword ptr [ebp+0x8]
		add eax, dword ptr [ebp-0x4]
		mov dword ptr [ebp-0x34], eax
		cmp dword ptr [ebp-0x30], 0
		jnz L1
		mov ecx, dword ptr [ebp-0x34]
		mov dword ptr [ebp-0x78], ecx
		jmp L2
	L1:
		mov edx, dword ptr [ebp-0x30]
		push edx
		mov eax, dword ptr [ebp+0x8]
		push eax
		mov ecx, dword ptr [ebp-0x34]
		push ecx
		call dword ptr [bfmeMemmoveSlotV46]
		add esp, 12
		mov dword ptr [ebp-0x78], eax
	L2:
		mov edx, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x3C], edx
		mov eax, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x40], eax
		mov ecx, dword ptr [ebp-0x3C]
		sub ecx, dword ptr [ebp-0x40]
		mov dword ptr [ebp-0x38], ecx
		jnz L3
		mov edx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x7C], edx
		jmp L4
	L3:
		mov eax, dword ptr [ebp-0x38]
		push eax
		mov ecx, dword ptr [ebp-0x40]
		push ecx
		mov edx, dword ptr [ebp+0x8]
		push edx
		call dword ptr [bfmeMemmoveSlotV46]
		add esp, 12
		mov dword ptr [ebp-0x7C], eax
	L4:
		jmp L7
	L5:
		mov eax, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x10], eax
		mov ecx, dword ptr [ebp-0x8]
		mov edx, dword ptr [ebp-0x10]
		lea eax, dword ptr [edx+ecx*1+0x1]
		mov dword ptr [ebp-0x10], eax
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ecx+0x4]
		add edx, 1
		push edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		mov ecx, dword ptr [ebp-0x10]
		push ecx
		call bfmeCopyFwdV49
		add esp, 12
		mov edx, dword ptr [ebp-0x4]
		sub edx, dword ptr [ebp-0x8]
		mov eax, dword ptr [ebp-0x74]
		add edx, dword ptr [eax+0x4]
		mov ecx, dword ptr [ebp-0x74]
		mov dword ptr [ecx+0x4], edx
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [edx+0x4]
		push eax
		mov ecx, dword ptr [ebp-0xC]
		add ecx, 1
		push ecx
		mov edx, dword ptr [ebp+0x8]
		push edx
		call bfmeCopyTrivialV46
		add esp, 12
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax+0x4]
		add ecx, dword ptr [ebp-0x8]
		mov edx, dword ptr [ebp-0x74]
		mov dword ptr [edx+0x4], ecx
		mov eax, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x50], eax
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x54], ecx
		mov edx, dword ptr [ebp-0x50]
		sub edx, dword ptr [ebp-0x54]
		mov dword ptr [ebp-0x4C], edx
		jnz L6
		mov eax, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x80], eax
		jmp L7
	L6:
		mov ecx, dword ptr [ebp-0x4C]
		push ecx
		mov edx, dword ptr [ebp-0x54]
		push edx
		mov eax, dword ptr [ebp+0x8]
		push eax
		call dword ptr [bfmeMemmoveSlotV46]
		add esp, 12
		mov dword ptr [ebp-0x80], eax
	L7:
		jmp done
	L8:
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [ecx+0x4]
		sub eax, dword ptr [edx]
		mov dword ptr [ebp-0x1C], eax
		mov ecx, dword ptr [ebp-0x4]
		mov dword ptr [ebp-0x24], ecx
		mov edx, dword ptr [ebp-0x1C]
		cmp edx, dword ptr [ebp-0x24]
		jnb L9
		lea eax, dword ptr [ebp-0x24]
		mov dword ptr [ebp-0x84], eax
		jmp L10
	L9:
		lea ecx, dword ptr [ebp-0x1C]
		mov dword ptr [ebp-0x84], ecx
	L10:
		mov edx, dword ptr [ebp-0x84]
		mov dword ptr [ebp-0x58], edx
		mov eax, dword ptr [ebp-0x58]
		mov ecx, dword ptr [eax]
		mov edx, dword ptr [ebp-0x1C]
		lea eax, dword ptr [edx+ecx*1+0x1]
		mov dword ptr [ebp-0x14], eax
		cmp dword ptr [ebp-0x14], 0
		jz L13
		cmp dword ptr [ebp-0x14], 0x80
		jbe L11
		mov ecx, dword ptr [ebp-0x14]
		push ecx
		call bfmeBigAllocPR
		add esp, 4
		mov dword ptr [ebp-0x88], eax
		jmp L12
	L11:
		mov edx, dword ptr [ebp-0x14]
		push edx
		call bfmeNodeAllocV46
		add esp, 4
		mov dword ptr [ebp-0x88], eax
	L12:
		mov eax, dword ptr [ebp-0x88]
		mov dword ptr [ebp-0x8C], eax
		jmp L14
	L13:
		mov dword ptr [ebp-0x8C], 0x0
	L14:
		mov ecx, dword ptr [ebp-0x8C]
		mov dword ptr [ebp-0x18], ecx
		mov edx, dword ptr [ebp-0x18]
		mov dword ptr [ebp-0x20], edx
		mov eax, dword ptr [ebp-0x18]
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [edx]
		push eax
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x20], eax
		mov ecx, dword ptr [ebp-0x20]
		push ecx
		mov edx, dword ptr [ebp+0x10]
		push edx
		mov eax, dword ptr [ebp+0xC]
		push eax
		call bfmeCopyFwdV49
		add esp, 12
		mov dword ptr [ebp-0x20], eax
		mov ecx, dword ptr [ebp-0x20]
		push ecx
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [edx+0x4]
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x20], eax
		xor edx, edx
		mov byte ptr [ebp-0x67], dl
		mov eax, dword ptr [ebp-0x20]
		mov byte ptr [eax], 0
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ecx+0x4]
		add edx, 1
		push edx
		mov eax, dword ptr [ebp-0x74]
		mov ecx, dword ptr [eax]
		push ecx
		call bfmeFreeV46
		add esp, 8
		mov ecx, dword ptr [ebp-0x74]
		call BfmeStrV49::bfmeDeallocV49
		mov edx, dword ptr [ebp-0x74]
		mov eax, dword ptr [ebp-0x18]
		mov dword ptr [edx], eax
		mov ecx, dword ptr [ebp-0x74]
		mov edx, dword ptr [ebp-0x20]
		mov dword ptr [ecx+0x4], edx
		mov eax, dword ptr [ebp-0x18]
		add eax, dword ptr [ebp-0x14]
		mov ecx, dword ptr [ebp-0x74]
		mov dword ptr [ecx+0x8], eax
	done:
	}
}
