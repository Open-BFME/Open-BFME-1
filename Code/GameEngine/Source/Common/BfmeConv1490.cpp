// cl: /Od

void *bfmeBigAllocPR(unsigned n);
void *bfmeNodeAllocV46(unsigned n);
void *bfmeAllocQL(int n, void *p);

class BfmeVecV47
{
public:
	void bfmeFreeV47();
	int *b;
	int *e;
	int *c;
};

void __stdcall bfmeAssignRangeV47(int *first, int *last, int extra, unsigned n, char ch)
{
	char pad[128];

	__asm
	{
		mov dword ptr [ebp-0x64], ecx
		mov eax, dword ptr [ebp-0x64]
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sar edx, 2
		mov dword ptr [ebp-0xC], edx
		mov eax, dword ptr [ebp-0xC]
		cmp eax, dword ptr [ebp+0x14]
		jnb L1
		lea ecx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x68], ecx
		jmp L2
	L1:
		lea edx, dword ptr [ebp-0xC]
		mov dword ptr [ebp-0x68], edx
	L2:
		mov eax, dword ptr [ebp-0x68]
		mov dword ptr [ebp-0x18], eax
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [ebp-0xC]
		add edx, dword ptr [ecx]
		mov dword ptr [ebp-0x4], edx
		jz L5
		mov eax, dword ptr [ebp-0x4]
		shl eax, 2
		mov dword ptr [ebp-0x1C], eax
		cmp dword ptr [ebp-0x1C], 0x80
		jbe L3
		mov ecx, dword ptr [ebp-0x1C]
		push ecx
		call bfmeBigAllocPR
		add esp, 4
		mov dword ptr [ebp-0x6C], eax
		jmp L4
	L3:
		mov edx, dword ptr [ebp-0x1C]
		push edx
		call bfmeNodeAllocV46
		add esp, 4
		mov dword ptr [ebp-0x6C], eax
	L4:
		mov eax, dword ptr [ebp-0x6C]
		mov dword ptr [ebp-0x70], eax
		jmp L6
	L5:
		mov dword ptr [ebp-0x70], 0x0
	L6:
		mov ecx, dword ptr [ebp-0x70]
		mov dword ptr [ebp-0x8], ecx
		mov edx, dword ptr [ebp-0x8]
		mov dword ptr [ebp-0x10], edx
		xor eax, eax
		mov byte ptr [ebp-0x11], al
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x28], edx
		mov eax, dword ptr [ebp-0x8]
		mov dword ptr [ebp-0x20], eax
		jmp L8
	L7:
		mov ecx, dword ptr [ebp-0x28]
		add ecx, 4
		mov dword ptr [ebp-0x28], ecx
		mov edx, dword ptr [ebp-0x20]
		add edx, 4
		mov dword ptr [ebp-0x20], edx
	L8:
		mov eax, dword ptr [ebp-0x28]
		cmp eax, dword ptr [ebp+0x8]
		jz L11
		mov ecx, dword ptr [ebp-0x20]
		push ecx
		push 4
		call bfmeAllocQL
		add esp, 8
		mov dword ptr [ebp-0x24], eax
		cmp dword ptr [ebp-0x24], 0
		jz L9
		mov edx, dword ptr [ebp-0x24]
		mov eax, dword ptr [ebp-0x28]
		mov ecx, dword ptr [eax]
		mov dword ptr [edx], ecx
		mov edx, dword ptr [ebp-0x24]
		mov dword ptr [ebp-0x74], edx
		jmp L10
	L9:
		mov dword ptr [ebp-0x74], 0x0
	L10:
		jmp L7
	L11:
		mov eax, dword ptr [ebp-0x20]
		mov dword ptr [ebp-0x10], eax
		cmp dword ptr [ebp+0x14], 1
		jnz L14
		mov ecx, dword ptr [ebp-0x10]
		push ecx
		push 4
		call bfmeAllocQL
		add esp, 8
		mov dword ptr [ebp-0x2C], eax
		cmp dword ptr [ebp-0x2C], 0
		jz L12
		mov edx, dword ptr [ebp-0x2C]
		mov eax, dword ptr [ebp+0xC]
		mov ecx, dword ptr [eax]
		mov dword ptr [edx], ecx
		mov edx, dword ptr [ebp-0x2C]
		mov dword ptr [ebp-0x78], edx
		jmp L13
	L12:
		mov dword ptr [ebp-0x78], 0x0
	L13:
		mov eax, dword ptr [ebp-0x10]
		add eax, 4
		mov dword ptr [ebp-0x10], eax
		jmp L20
	L14:
		xor ecx, ecx
		mov byte ptr [ebp-0x12], cl
		mov edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x38], edx
		mov eax, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x30], eax
		jmp L16
	L15:
		mov ecx, dword ptr [ebp-0x38]
		sub ecx, 1
		mov dword ptr [ebp-0x38], ecx
		mov edx, dword ptr [ebp-0x30]
		add edx, 4
		mov dword ptr [ebp-0x30], edx
	L16:
		cmp dword ptr [ebp-0x38], 0
		jbe L19
		mov eax, dword ptr [ebp-0x30]
		push eax
		push 4
		call bfmeAllocQL
		add esp, 8
		mov dword ptr [ebp-0x34], eax
		cmp dword ptr [ebp-0x34], 0
		jz L17
		mov ecx, dword ptr [ebp-0x34]
		mov edx, dword ptr [ebp+0xC]
		mov eax, dword ptr [edx]
		mov dword ptr [ecx], eax
		mov ecx, dword ptr [ebp-0x34]
		mov dword ptr [ebp-0x7C], ecx
		jmp L18
	L17:
		mov dword ptr [ebp-0x7C], 0x0
	L18:
		jmp L15
	L19:
		mov edx, dword ptr [ebp-0x30]
		mov dword ptr [ebp-0x10], edx
	L20:
		movzx eax, byte ptr [ebp+0x18]
		test eax, eax
		jnz L26
		xor ecx, ecx
		mov byte ptr [ebp-0x13], cl
		mov edx, dword ptr [ebp-0x64]
		mov eax, dword ptr [edx+0x4]
		mov dword ptr [ebp-0x44], eax
		mov ecx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x48], ecx
		mov edx, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x3C], edx
		jmp L22
	L21:
		mov eax, dword ptr [ebp-0x48]
		add eax, 4
		mov dword ptr [ebp-0x48], eax
		mov ecx, dword ptr [ebp-0x3C]
		add ecx, 4
		mov dword ptr [ebp-0x3C], ecx
	L22:
		mov edx, dword ptr [ebp-0x48]
		cmp edx, dword ptr [ebp-0x44]
		jz L25
		mov eax, dword ptr [ebp-0x3C]
		push eax
		push 4
		call bfmeAllocQL
		add esp, 8
		mov dword ptr [ebp-0x40], eax
		cmp dword ptr [ebp-0x40], 0
		jz L23
		mov ecx, dword ptr [ebp-0x40]
		mov edx, dword ptr [ebp-0x48]
		mov eax, dword ptr [edx]
		mov dword ptr [ecx], eax
		mov ecx, dword ptr [ebp-0x40]
		mov dword ptr [ebp-0x80], ecx
		jmp L24
	L23:
		mov dword ptr [ebp-0x80], 0x0
	L24:
		jmp L21
	L25:
		mov edx, dword ptr [ebp-0x3C]
		mov dword ptr [ebp-0x10], edx
	L26:
		mov ecx, dword ptr [ebp-0x64]
		call BfmeVecV47::bfmeFreeV47
		mov eax, dword ptr [ebp-0x64]
		mov ecx, dword ptr [ebp-0x8]
		mov dword ptr [eax], ecx
		mov edx, dword ptr [ebp-0x64]
		mov eax, dword ptr [ebp-0x10]
		mov dword ptr [edx+0x4], eax
		mov ecx, dword ptr [ebp-0x4]
		mov edx, dword ptr [ebp-0x8]
		lea eax, dword ptr [edx+ecx*4]
		mov ecx, dword ptr [ebp-0x64]
		mov dword ptr [ecx+0x8], eax
	}
}
