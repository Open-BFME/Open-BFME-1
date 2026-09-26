// cl: /Od

void *bfmeAllocQL(int n, void *p);

class BfmeVecV34
{
public:
	void bfmeOverflowV34(int *pos, int *val, char *t, unsigned n, bool b);

	int *b;
	int *e;
	int *c;
};

void __stdcall bfmePushV34(int *val)
{
	void *at;
	char pad[68];

	__asm
	{
		mov dword ptr [ebp-0x48], ecx
		mov eax, dword ptr [ebp-0x48]
		mov ecx, dword ptr [ebp-0x48]
		mov edx, dword ptr [eax+4]
		cmp edx, dword ptr [ecx+8]
		jz overflow_path
		mov eax, dword ptr [ebp-0x48]
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x0C], ecx
		mov edx, dword ptr [ebp-0x0C]
		push edx
		push 4
		call bfmeAllocQL
		add esp, 8
		mov dword ptr [ebp-8], eax
		cmp dword ptr [ebp-8], 0
		jz null_obj
		mov eax, dword ptr [ebp-8]
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [ecx]
		mov dword ptr [eax], edx
		mov eax, dword ptr [ebp-8]
		mov dword ptr [ebp-0x4C], eax
		jmp constructed
	null_obj:
		mov dword ptr [ebp-0x4C], 0
	constructed:
		mov ecx, dword ptr [ebp-0x48]
		mov edx, dword ptr [ecx+4]
		add edx, 4
		mov eax, dword ptr [ebp-0x48]
		mov dword ptr [eax+4], edx
		jmp done
	overflow_path:
		xor ecx, ecx
		mov byte ptr [ebp-1], cl
		push 1
		push 1
		lea edx, dword ptr [ebp-1]
		push edx
		mov eax, dword ptr [ebp+8]
		push eax
		mov ecx, dword ptr [ebp-0x48]
		mov edx, dword ptr [ecx+4]
		push edx
		mov ecx, dword ptr [ebp-0x48]
		call BfmeVecV34::bfmeOverflowV34
	done:
	}
}
