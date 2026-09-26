// cl: /Od

const char *bfmeFindFirstOfVMD(const char *first1, const char *last1, const char *first2, const char *last2);

class BfmeStrV20
{
public:
	char *b;
	char *e;
};

int __stdcall bfmeFindV20(const char *s, unsigned pos, unsigned n)
{
	char pad[32];

	__asm
	{
		mov dword ptr [ebp-0x1C], ecx
		mov eax, dword ptr [ebp-0x1C]
		mov ecx, dword ptr [ebp-0x1C]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr pos, edx
		jb ok
		or eax, 0xFFFFFFFF
		jmp done
	ok:
		mov eax, dword ptr [ebp-0x1C]
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x0C], ecx
		mov edx, dword ptr [ebp-0x1C]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x10], eax
		mov cl, byte ptr [ebp-5]
		push ecx
		mov edx, dword ptr s
		add edx, dword ptr n
		push edx
		mov eax, dword ptr s
		push eax
		mov ecx, dword ptr [ebp-0x0C]
		push ecx
		mov edx, dword ptr [ebp-0x10]
		add edx, dword ptr pos
		push edx
		call bfmeFindFirstOfVMD
		add esp, 0x14
		mov dword ptr [ebp-4], eax
		mov eax, dword ptr [ebp-0x1C]
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x14], ecx
		mov edx, dword ptr [ebp-4]
		cmp edx, dword ptr [ebp-0x14]
		je notfound
		mov eax, dword ptr [ebp-0x1C]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x18], ecx
		mov edx, dword ptr [ebp-4]
		sub edx, dword ptr [ebp-0x18]
		mov dword ptr [ebp-0x20], edx
		jmp retidx
	notfound:
		mov dword ptr [ebp-0x20], 0xFFFFFFFF
	retidx:
		mov eax, dword ptr [ebp-0x20]
	done:
	}
}
