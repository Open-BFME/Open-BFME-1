// cl: /Od

void *bfmeCopyTrivialV46(void *a, void *b, void *c);
void bfmeCopyOneV50(void *a, void *b);
void *bfmeBigAllocPR(unsigned n);
void *bfmeNodeAllocV46(unsigned n);
void bfmeFreeV46(void *p, unsigned n);
static void *bfmeMemmoveSlotV46 = (void *)0x0135945C;

class BfmeStrV50
{
public:
	void bfmeDeallocV50();
	char *b;
	char *e;
	char *c;
};

void __stdcall bfmeInsertRangeV50(char *pos, char *first, char *last, char *tag)
{
	void *at;
	char pad[140];

	__asm
	{
		mov dword ptr [ebp-0x84], ecx
		mov eax, dword ptr [ebp+0xC]
		cmp eax, dword ptr [ebp+0x10]
		jz done
		mov ecx, dword ptr [ebp+0x10]
		sub ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x4], ecx
		mov edx, dword ptr [ebp-0x84]
		mov eax, dword ptr [ebp-0x84]
		mov ecx, dword ptr [edx+0x8]
		sub ecx, dword ptr [eax+0x4]
		mov edx, dword ptr [ebp-0x4]
		add edx, 0x1
		cmp ecx, edx
		jl L10
		mov eax, dword ptr [ebp-0x84]
		mov ecx, dword ptr [eax+0x4]
		sub ecx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x8], ecx
		mov edx, dword ptr [ebp-0x84]
		mov eax, dword ptr [edx+0x4]
		mov dword ptr [ebp-0xC], eax
		mov ecx, dword ptr [ebp-0x8]
		cmp ecx, dword ptr [ebp-0x4]
		jl L6
		mov edx, dword ptr [ebp-0x84]
		mov eax, dword ptr [edx+0x4]
		add eax, 0x1
		push eax
		mov ecx, dword ptr [ebp-0x84]
		mov edx, dword ptr [ecx+0x4]
		add edx, 0x1
		push edx
		mov eax, dword ptr [ebp-0x84]
		mov ecx, dword ptr [eax+0x4]
		sub ecx, dword ptr [ebp-0x4]
		add ecx, 0x1
		push ecx
		call bfmeCopyTrivialV46
		add esp, 12
		mov edx, dword ptr [ebp-0x84]
		mov eax, dword ptr [edx+0x4]
		add eax, dword ptr [ebp-0x4]
		mov ecx, dword ptr [ebp-0x84]
		mov dword ptr [ecx+0x4], eax
		mov edx, dword ptr [ebp-0x8]
		sub edx, dword ptr [ebp-0x4]
		add edx, 0x1
		mov dword ptr [ebp-0x30], edx
		mov eax, dword ptr [ebp+0x8]
		add eax, dword ptr [ebp-0x4]
		mov dword ptr [ebp-0x34], eax
		cmp dword ptr [ebp-0x30], 0x0
		jnz L1
		mov ecx, dword ptr [ebp-0x34]
		mov dword ptr [ebp-0x88], ecx
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
		mov dword ptr [ebp-0x88], eax
	L2:
		mov edx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x38], edx
		mov eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x3C], eax
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x40], ecx
		jmp L4
	L3:
		mov edx, dword ptr [ebp-0x40]
		add edx, 0x1
		mov dword ptr [ebp-0x40], edx
		mov eax, dword ptr [ebp-0x38]
		add eax, 0x1
		mov dword ptr [ebp-0x38], eax
	L4:
		mov ecx, dword ptr [ebp-0x40]
		cmp ecx, dword ptr [ebp-0x3C]
		jz L5
		mov edx, dword ptr [ebp-0x40]
		push edx
		mov eax, dword ptr [ebp-0x38]
		push eax
		call bfmeCopyOneV50
		add esp, 8
		jmp L3
	L5:
		jmp L9
	L6:
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp-0x8]
		mov eax, dword ptr [ebp-0x10]
		lea ecx, [eax+edx+0x1]
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp-0x84]
		mov eax, dword ptr [edx+0x4]
		add eax, 0x1
		push eax
		mov ecx, dword ptr [ebp+0x10]
		push ecx
		mov edx, dword ptr [ebp-0x10]
		push edx
		call bfmeCopyTrivialV46
		add esp, 12
		mov eax, dword ptr [ebp-0x4]
		sub eax, dword ptr [ebp-0x8]
		mov ecx, dword ptr [ebp-0x84]
		add eax, dword ptr [ecx+0x4]
		mov edx, dword ptr [ebp-0x84]
		mov dword ptr [edx+0x4], eax
		mov eax, dword ptr [ebp-0x84]
		mov ecx, dword ptr [eax+0x4]
		push ecx
		mov edx, dword ptr [ebp-0xC]
		add edx, 0x1
		push edx
		mov eax, dword ptr [ebp+0x8]
		push eax
		call bfmeCopyTrivialV46
		add esp, 12
		mov ecx, dword ptr [ebp-0x84]
		mov edx, dword ptr [ecx+0x4]
		add edx, dword ptr [ebp-0x8]
		mov eax, dword ptr [ebp-0x84]
		mov dword ptr [eax+0x4], edx
		mov ecx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x54], ecx
		mov edx, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x58], edx
		mov eax, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x5C], eax
		jmp L8
	L7:
		mov ecx, dword ptr [ebp-0x5C]
		add ecx, 0x1
		mov dword ptr [ebp-0x5C], ecx
		mov edx, dword ptr [ebp-0x54]
		add edx, 0x1
		mov dword ptr [ebp-0x54], edx
	L8:
		mov eax, dword ptr [ebp-0x5C]
		cmp eax, dword ptr [ebp-0x58]
		jz L9
		mov ecx, dword ptr [ebp-0x5C]
		push ecx
		mov edx, dword ptr [ebp-0x54]
		push edx
		call bfmeCopyOneV50
		add esp, 8
		jmp L7
	L9:
		jmp done
	L10:
		mov eax, dword ptr [ebp-0x84]
		mov ecx, dword ptr [ebp-0x84]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		mov dword ptr [ebp-0x1C], edx
		mov eax, dword ptr [ebp-0x4]
		mov dword ptr [ebp-0x24], eax
		mov ecx, dword ptr [ebp-0x1C]
		cmp ecx, dword ptr [ebp-0x24]
		jae L11
		lea edx, [ebp-0x24]
		mov dword ptr [ebp-0x8C], edx
		jmp L12
	L11:
		lea eax, [ebp-0x1C]
		mov dword ptr [ebp-0x8C], eax
	L12:
		mov ecx, dword ptr [ebp-0x8C]
		mov dword ptr [ebp-0x60], ecx
		mov edx, dword ptr [ebp-0x60]
		mov eax, dword ptr [edx]
		mov ecx, dword ptr [ebp-0x1C]
		lea edx, [ecx+eax+0x1]
		mov dword ptr [ebp-0x14], edx
		cmp dword ptr [ebp-0x14], 0x0
		jz L15
		cmp dword ptr [ebp-0x14], 0x80
		jbe L13
		mov eax, dword ptr [ebp-0x14]
		push eax
		call bfmeBigAllocPR
		add esp, 4
		mov dword ptr [ebp-0x90], eax
		jmp L14
	L13:
		mov ecx, dword ptr [ebp-0x14]
		push ecx
		call bfmeNodeAllocV46
		add esp, 4
		mov dword ptr [ebp-0x90], eax
	L14:
		mov edx, dword ptr [ebp-0x90]
		mov dword ptr [ebp-0x94], edx
		jmp L16
	L15:
		mov dword ptr [ebp-0x94], 0x0
	L16:
		mov eax, dword ptr [ebp-0x94]
		mov dword ptr [ebp-0x18], eax
		mov ecx, dword ptr [ebp-0x18]
		mov dword ptr [ebp-0x20], ecx
		mov edx, dword ptr [ebp-0x18]
		push edx
		mov eax, dword ptr [ebp+0x8]
		push eax
		mov ecx, dword ptr [ebp-0x84]
		mov edx, dword ptr [ecx]
		push edx
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x20], eax
		mov eax, dword ptr [ebp-0x20]
		push eax
		mov ecx, dword ptr [ebp+0x10]
		push ecx
		mov edx, dword ptr [ebp+0xC]
		push edx
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x20], eax
		mov eax, dword ptr [ebp-0x20]
		push eax
		mov ecx, dword ptr [ebp-0x84]
		mov edx, dword ptr [ecx+0x4]
		push edx
		mov eax, dword ptr [ebp+0x8]
		push eax
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x20], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x76], cl
		mov edx, dword ptr [ebp-0x20]
		mov byte ptr [edx], 0x0
		mov eax, dword ptr [ebp-0x84]
		mov ecx, dword ptr [eax+0x4]
		add ecx, 0x1
		push ecx
		mov edx, dword ptr [ebp-0x84]
		mov eax, dword ptr [edx]
		push eax
		call bfmeFreeV46
		add esp, 8
		mov ecx, dword ptr [ebp-0x84]
		call BfmeStrV50::bfmeDeallocV50
		mov ecx, dword ptr [ebp-0x84]
		mov edx, dword ptr [ebp-0x18]
		mov dword ptr [ecx], edx
		mov eax, dword ptr [ebp-0x84]
		mov ecx, dword ptr [ebp-0x20]
		mov dword ptr [eax+0x4], ecx
		mov edx, dword ptr [ebp-0x18]
		add edx, dword ptr [ebp-0x14]
		mov eax, dword ptr [ebp-0x84]
		mov dword ptr [eax+0x8], edx
	done:
	}
}
