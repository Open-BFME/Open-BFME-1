// cl: /Od

class BfmeVecV17
{
public:
	void bfmeResizeV17(unsigned n, int v);
	void bfmeEraseV17(int *first, int *last);
	void bfmeInsertV17(int *at, unsigned n, int *pv);

	int *b;
	int *e;
};

void BfmeVecV17::bfmeResizeV17(unsigned n, int v)
{
	char pad[36];

	__asm
	{
		mov eax, this
		mov ecx, this
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sar edx, 2
		cmp dword ptr n, edx
		jae grow_path
		mov eax, this
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-4], ecx
		mov edx, this
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-8], eax
		mov ecx, dword ptr [ebp-4]
		push ecx
		mov edx, dword ptr n
		mov eax, dword ptr [ebp-8]
		lea ecx, [eax+edx*4]
		push ecx
		mov ecx, this
		call bfmeEraseV17
		jmp done
	grow_path:
		mov edx, this
		mov eax, dword ptr [edx+4]
		mov dword ptr [ebp-0x20], eax
		mov ecx, this
		mov edx, this
		mov eax, dword ptr [ecx+4]
		sub eax, dword ptr [edx]
		sar eax, 2
		mov ecx, dword ptr n
		sub ecx, eax
		mov dword ptr [ebp-0x24], ecx
		lea edx, [ebp+0x0C]
		push edx
		mov eax, dword ptr [ebp-0x24]
		push eax
		mov ecx, dword ptr [ebp-0x20]
		push ecx
		mov ecx, this
		call bfmeInsertV17
	done:
	}
}
