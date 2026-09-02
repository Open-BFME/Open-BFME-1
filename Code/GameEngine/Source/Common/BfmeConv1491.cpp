// cl: /Od

void *bfmeCopyTrivialV46(void *a, void *b, void *c);
char *bfmeFillV14(char *p, unsigned n, char ch);
void rva0082ADB0Fill(char *a, char *b, const char &c);
void *bfmeBigAllocPR(unsigned n);
void *bfmeNodeAllocV46(unsigned n);
void bfmeFreeV46(void *p, unsigned n);
static void *bfmeMemmoveSlotV46 = (void *)0x0135945C;

class BfmeStrV48
{
public:
	void bfmeDeallocV48();
	char *b;
	char *e;
	char *c;
};

char *__stdcall bfmeInsertNChV48(char *pos, unsigned n, char ch)
{
	void *at;
	char pad[108];

	__asm
	{
		mov dword ptr [ebp-0x64], ecx
		cmp dword ptr [ebp+0xC], 0
		jz done
		mov eax, dword ptr [ebp-0x64]
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [eax+0x8]
		sub edx, dword ptr [ecx+0x4]
		mov eax, dword ptr [ebp+0xC]
		add eax, 1
		cmp edx, eax
		jb L5
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [ecx+0x4]
		sub edx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x4], edx
		mov eax, dword ptr [ebp-0x64]
		mov ecx, dword ptr [eax+0x4]
		mov dword ptr [ebp-0x8], ecx
		mov edx, dword ptr [ebp-0x4]
		cmp edx, dword ptr [ebp+0xC]
		jb L3
		mov eax, dword ptr [ebp-0x64]
		mov ecx, dword ptr [eax+0x4]
		add ecx, 1
		push ecx
		mov edx, dword ptr [ebp-0x64]
		mov eax, dword ptr [edx+0x4]
		add eax, 1
		push eax
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [ecx+0x4]
		sub edx, dword ptr [ebp+0xC]
		add edx, 1
		push edx
		call bfmeCopyTrivialV46
		add esp, 12
		mov eax, dword ptr [ebp-0x64]
		mov ecx, dword ptr [eax+0x4]
		add ecx, dword ptr [ebp+0xC]
		mov edx, dword ptr [ebp-0x64]
		mov dword ptr [edx+0x4], ecx
		mov eax, dword ptr [ebp-0x4]
		sub eax, dword ptr [ebp+0xC]
		add eax, 1
		mov dword ptr [ebp-0x24], eax
		mov ecx, dword ptr [ebp+0x8]
		add ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x28], ecx
		cmp dword ptr [ebp-0x24], 0
		jnz L1
		mov edx, dword ptr [ebp-0x28]
		mov dword ptr [ebp-0x68], edx
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
		mov dword ptr [ebp-0x68], eax
	L2:
		mov al, byte ptr [ebp+0x10]
		push eax
		mov ecx, dword ptr [ebp+0xC]
		push ecx
		mov edx, dword ptr [ebp+0x8]
		push edx
		call bfmeFillV14
		add esp, 12
		jmp L4
	L3:
		mov eax, dword ptr [ebp+0xC]
		sub eax, dword ptr [ebp-0x4]
		sub eax, 1
		mov dword ptr [ebp-0x30], eax
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [ecx+0x4]
		add edx, 1
		mov dword ptr [ebp-0x34], edx
		xor eax, eax
		mov byte ptr [ebp-0x29], al
		lea ecx, dword ptr [ebp+0x10]
		push ecx
		mov edx, dword ptr [ebp-0x34]
		add edx, dword ptr [ebp-0x30]
		push edx
		mov eax, dword ptr [ebp-0x34]
		push eax
		call rva0082ADB0Fill
		add esp, 12
		mov ecx, dword ptr [ebp+0xC]
		sub ecx, dword ptr [ebp-0x4]
		mov edx, dword ptr [ebp-0x64]
		add ecx, dword ptr [edx+0x4]
		mov eax, dword ptr [ebp-0x64]
		mov dword ptr [eax+0x4], ecx
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [ecx+0x4]
		push edx
		mov eax, dword ptr [ebp-0x8]
		add eax, 1
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		call bfmeCopyTrivialV46
		add esp, 12
		mov edx, dword ptr [ebp-0x64]
		mov eax, dword ptr [edx+0x4]
		add eax, dword ptr [ebp-0x4]
		mov ecx, dword ptr [ebp-0x64]
		mov dword ptr [ecx+0x4], eax
		mov dl, byte ptr [ebp+0x10]
		push edx
		mov eax, dword ptr [ebp-0x4]
		add eax, 1
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		call bfmeFillV14
		add esp, 12
	L4:
		jmp done
	L5:
		mov edx, dword ptr [ebp-0x64]
		mov eax, dword ptr [ebp-0x64]
		mov ecx, dword ptr [edx+0x4]
		sub ecx, dword ptr [eax]
		mov dword ptr [ebp-0x14], ecx
		mov edx, dword ptr [ebp-0x14]
		cmp edx, dword ptr [ebp+0xC]
		jnb L6
		lea eax, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x6C], eax
		jmp L7
	L6:
		lea ecx, dword ptr [ebp-0x14]
		mov dword ptr [ebp-0x6C], ecx
	L7:
		mov edx, dword ptr [ebp-0x6C]
		mov dword ptr [ebp-0x40], edx
		mov eax, dword ptr [ebp-0x40]
		mov ecx, dword ptr [eax]
		mov edx, dword ptr [ebp-0x14]
		lea eax, dword ptr [edx+ecx*1+0x1]
		mov dword ptr [ebp-0xC], eax
		cmp dword ptr [ebp-0xC], 0
		jz L10
		cmp dword ptr [ebp-0xC], 0x80
		jbe L8
		mov ecx, dword ptr [ebp-0xC]
		push ecx
		call bfmeBigAllocPR
		add esp, 4
		mov dword ptr [ebp-0x70], eax
		jmp L9
	L8:
		mov edx, dword ptr [ebp-0xC]
		push edx
		call bfmeNodeAllocV46
		add esp, 4
		mov dword ptr [ebp-0x70], eax
	L9:
		mov eax, dword ptr [ebp-0x70]
		mov dword ptr [ebp-0x74], eax
		jmp L11
	L10:
		mov dword ptr [ebp-0x74], 0x0
	L11:
		mov ecx, dword ptr [ebp-0x74]
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x18], edx
		mov eax, dword ptr [ebp-0x10]
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		mov edx, dword ptr [ebp-0x64]
		mov eax, dword ptr [edx]
		push eax
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x18], eax
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x50], ecx
		xor edx, edx
		mov byte ptr [ebp-0x48], dl
		lea eax, dword ptr [ebp+0x10]
		push eax
		mov ecx, dword ptr [ebp-0x18]
		add ecx, dword ptr [ebp-0x50]
		push ecx
		mov edx, dword ptr [ebp-0x18]
		push edx
		call rva0082ADB0Fill
		add esp, 12
		mov eax, dword ptr [ebp-0x18]
		add eax, dword ptr [ebp-0x50]
		mov dword ptr [ebp-0x18], eax
		mov ecx, dword ptr [ebp-0x18]
		push ecx
		mov edx, dword ptr [ebp-0x64]
		mov eax, dword ptr [edx+0x4]
		push eax
		mov ecx, dword ptr [ebp+0x8]
		push ecx
		call bfmeCopyTrivialV46
		add esp, 12
		mov dword ptr [ebp-0x18], eax
		xor edx, edx
		mov byte ptr [ebp-0x58], dl
		mov eax, dword ptr [ebp-0x18]
		mov byte ptr [eax], 0
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [ecx+0x4]
		add edx, 1
		push edx
		mov eax, dword ptr [ebp-0x64]
		mov ecx, dword ptr [eax]
		push ecx
		call bfmeFreeV46
		add esp, 8
		mov ecx, dword ptr [ebp-0x64]
		call BfmeStrV48::bfmeDeallocV48
		mov edx, dword ptr [ebp-0x64]
		mov eax, dword ptr [ebp-0x10]
		mov dword ptr [edx], eax
		mov ecx, dword ptr [ebp-0x64]
		mov edx, dword ptr [ebp-0x18]
		mov dword ptr [ecx+0x4], edx
		mov eax, dword ptr [ebp-0x10]
		add eax, dword ptr [ebp-0xC]
		mov ecx, dword ptr [ebp-0x64]
		mov dword ptr [ecx+0x8], eax
	done:
	}
}
