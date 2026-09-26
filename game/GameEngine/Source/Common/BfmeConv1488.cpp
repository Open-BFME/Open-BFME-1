// cl: /Od

void bfmeCopyChV24(char *a, char *b);
static void *bfmeMemmoveSlotV46 = (void *)0x0135945C;
void *bfmeBigAllocPR(unsigned n);
void *bfmeNodeAllocV46(unsigned n);
void *bfmeCopyTrivialV46(void *a, void *b, void *c);
void *bfmeAllocQL(int n, void *p);
void bfmeFreeV46(void *p, unsigned n);

class BfmeStrV46
{
public:
	void bfmeDeallocV46();
	char *b;
	char *e;
	char *c;
};

char *__stdcall bfmeInsertChV46(char *at, char ch)
{
	char pad[96];

	__asm
	{
		mov dword ptr [ebp-0x4C], ecx
		mov eax, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x4], eax
		mov ecx, dword ptr [ebp-0x4C]
		mov edx, dword ptr [ecx+0x4]
		add edx, 1
		mov eax, dword ptr [ebp-0x4C]
		cmp edx, dword ptr [eax+0x8]
		jnb L3
		mov ecx, dword ptr [ebp-0x4C]
		mov edx, dword ptr [ecx+0x4]
		add edx, 1
		mov dword ptr [ebp-0x20], edx
		xor eax, eax
		mov byte ptr [ebp-0x19], al
		mov ecx, dword ptr [ebp-0x20]
		mov byte ptr [ecx], 0
		mov edx, dword ptr [ebp-0x4C]
		mov eax, dword ptr [edx+0x4]
		sub eax, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x24], eax
		mov ecx, dword ptr [ebp+0x8]
		add ecx, 1
		mov dword ptr [ebp-0x28], ecx
		cmp dword ptr [ebp-0x24], 0
		jnz L1
		mov edx, dword ptr [ebp-0x28]
		mov dword ptr [ebp-0x50], edx
		jmp L2
	L1:
		mov eax, dword ptr [ebp-0x24]
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		mov edx, dword ptr [ebp-0x28]
		push edx
		call dword ptr [bfmeMemmoveSlotV46]
		add esp, 12
		mov dword ptr [ebp-0x50], eax
	L2:
		lea eax, dword ptr [ebp+0xC]
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		call bfmeCopyChV24
		add esp, 8
		mov edx, dword ptr [ebp-0x4C]
		mov eax, dword ptr [edx+0x4]
		add eax, 1
		mov ecx, dword ptr [ebp-0x4C]
		mov dword ptr [ecx+0x4], eax
		jmp L12
	L3:
		mov edx, dword ptr [ebp-0x4C]
		mov eax, dword ptr [ebp-0x4C]
		mov ecx, dword ptr [edx+0x4]
		sub ecx, dword ptr [eax]
		mov dword ptr [ebp-0x10], ecx
		mov dword ptr [ebp-0x18], 0x1
		mov edx, dword ptr [ebp-0x10]
		cmp edx, dword ptr [ebp-0x18]
		jnb L4
		lea eax, dword ptr [ebp-0x18]
		mov dword ptr [ebp-0x54], eax
		jmp L5
	L4:
		lea ecx, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x54], ecx
	L5:
		mov edx, dword ptr [ebp-0x54]
		mov dword ptr [ebp-0x2C], edx
		mov eax, dword ptr [ebp-0x2C]
		mov ecx, dword ptr [eax]
		mov edx, dword ptr [ebp-0x10]
		lea eax, dword ptr [edx+ecx*1+0x1]
		mov dword ptr [ebp-0x8], eax
		cmp dword ptr [ebp-0x8], 0
		jz L8
		cmp dword ptr [ebp-0x8], 0x80
		jbe L6
		mov ecx, dword ptr [ebp-0x8]
		push ecx
		call bfmeBigAllocPR
		add esp, 4
		mov dword ptr [ebp-0x58], eax
		jmp L7
	L6:
		mov edx, dword ptr [ebp-0x8]
		push edx
		call bfmeNodeAllocV46
		add esp, 4
		mov dword ptr [ebp-0x58], eax
	L7:
		mov eax, dword ptr [ebp-0x58]
		mov dword ptr [ebp-0x5C], eax
		jmp L9
	L8:
		mov dword ptr [ebp-0x5C], 0x0
	L9:
		mov ecx, dword ptr [ebp-0x5C]
		mov dword ptr [ebp-0xC], ecx
		mov edx, dword ptr [ebp-0xC]
		mov dword ptr [ebp-0x14], edx
		mov eax, dword ptr [ebp-0xC]
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		mov edx, dword ptr [ebp-0x4C]
		mov eax, dword ptr [edx]
		push eax
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x4], eax
		mov ecx, dword ptr [ebp-0x4]
		push ecx
		push 1
		call bfmeAllocQL
		add esp, 8
		mov dword ptr [ebp-0x38], eax
		cmp dword ptr [ebp-0x38], 0
		jz L10
		mov edx, dword ptr [ebp-0x38]
		mov al, byte ptr [ebp+0xC]
		mov byte ptr [edx], al
		mov ecx, dword ptr [ebp-0x38]
		mov dword ptr [ebp-0x60], ecx
		jmp L11
	L10:
		mov dword ptr [ebp-0x60], 0x0
	L11:
		mov edx, dword ptr [ebp-0x4]
		add edx, 1
		mov dword ptr [ebp-0x14], edx
		mov eax, dword ptr [ebp-0x14]
		push eax
		mov ecx, dword ptr [ebp-0x4C]
		mov edx, dword ptr [ecx+0x4]
		push edx
		mov eax, dword ptr [ebp+0x8]
		push eax
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x14], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x40], cl
		mov edx, dword ptr [ebp-0x14]
		mov byte ptr [edx], 0
		mov eax, dword ptr [ebp-0x4C]
		mov ecx, dword ptr [eax+0x4]
		add ecx, 1
		push ecx
		mov edx, dword ptr [ebp-0x4C]
		mov eax, dword ptr [edx]
		push eax
		call bfmeFreeV46
		add esp, 8
		mov ecx, dword ptr [ebp-0x4C]
		call BfmeStrV46::bfmeDeallocV46
		mov ecx, dword ptr [ebp-0x4C]
		mov edx, dword ptr [ebp-0xC]
		mov dword ptr [ecx], edx
		mov eax, dword ptr [ebp-0x4C]
		mov ecx, dword ptr [ebp-0x14]
		mov dword ptr [eax+0x4], ecx
		mov edx, dword ptr [ebp-0xC]
		add edx, dword ptr [ebp-0x8]
		mov eax, dword ptr [ebp-0x4C]
		mov dword ptr [eax+0x8], edx
	L12:
		mov eax, dword ptr [ebp-0x4]
	}
}
