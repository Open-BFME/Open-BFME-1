// cl: /Od

// Both callees are five-byte ILT thunks (0x00030940 and 0x0001F4FB), so the
// only names defined at the addresses the retail calls encode are the ?j_
// thunk symbols.  A cdecl no-argument C++ global decorates to exactly that
// name, and the asm below calls it under it.
extern void j_00030940();
extern void j_0001f4fb();

// The vector is BfmeVecV34; its overflow handler is declared for its signature
// only, the asm below reaches it through the 0x0001F4FB ILT thunk.
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
		call j_00030940
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
		call j_0001f4fb
	done:
	}
}
