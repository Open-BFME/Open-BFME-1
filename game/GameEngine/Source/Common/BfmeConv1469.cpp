// cl: /Od

void *__stdcall bfmeMakeV18(unsigned n, int a, int b);
void bfmeImplVMY(int a, int b, int c);

class BfmeVecV29
{
public:
	void bfmeFreeV29();

	int *b;
	int *e;
	int *c;
};

void *__stdcall bfmeAssignV29(BfmeVecV29 *other)
{
	char pad[112];

	__asm
	{
		mov dword ptr [ebp-0x70], ecx
		mov eax, dword ptr other
		cmp eax, dword ptr [ebp-0x70]
		je done
		mov ecx, dword ptr other
		mov edx, dword ptr other
		mov eax, dword ptr [ecx+4]
		sub eax, dword ptr [edx]
		sar eax, 2
		mov dword ptr [ebp-4], eax
		mov ecx, dword ptr [ebp-0x70]
		mov edx, dword ptr [ebp-0x70]
		mov eax, dword ptr [ecx+8]
		sub eax, dword ptr [edx]
		sar eax, 2
		cmp dword ptr [ebp-4], eax
		jbe enough
		mov ecx, dword ptr other
		mov edx, dword ptr [ecx+4]
		push edx
		mov eax, dword ptr other
		mov ecx, dword ptr [eax]
		push ecx
		mov edx, dword ptr [ebp-4]
		push edx
		mov ecx, dword ptr [ebp-0x70]
		call bfmeMakeV18
		mov dword ptr [ebp-8], eax
		mov ecx, dword ptr [ebp-0x70]
		call BfmeVecV29::bfmeFreeV29
		mov eax, dword ptr [ebp-0x70]
		mov ecx, dword ptr [ebp-8]
		mov dword ptr [eax], ecx
		mov edx, dword ptr [ebp-0x70]
		mov eax, dword ptr [edx]
		mov ecx, dword ptr [ebp-4]
		lea edx, [eax+ecx*4]
		mov eax, dword ptr [ebp-0x70]
		mov dword ptr [eax+8], edx
		jmp set_e
	enough:
		mov ecx, dword ptr [ebp-0x70]
		mov edx, dword ptr [ebp-0x70]
		mov eax, dword ptr [ecx+4]
		sub eax, dword ptr [edx]
		sar eax, 2
		cmp eax, dword ptr [ebp-4]
		jb need_more
		xor ecx, ecx
		mov byte ptr [ebp-0x0D], cl
		mov edx, dword ptr [ebp-0x70]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x3C], eax
		mov ecx, dword ptr other
		mov edx, dword ptr [ecx+4]
		mov dword ptr [ebp-0x40], edx
		mov eax, dword ptr other
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x44], ecx
		mov edx, dword ptr [ebp-0x3C]
		push edx
		mov eax, dword ptr [ebp-0x40]
		push eax
		mov ecx, dword ptr [ebp-0x44]
		push ecx
		call bfmeImplVMY
		add esp, 0x0C
		mov dword ptr [ebp-0x0C], eax
		mov edx, dword ptr [ebp-0x70]
		mov eax, dword ptr [edx+4]
		mov dword ptr [ebp-0x4C], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x45], cl
		jmp set_e
	need_more:
		xor edx, edx
		mov byte ptr [ebp-0x0E], dl
		mov eax, dword ptr [ebp-0x70]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x50], ecx
		mov edx, dword ptr [ebp-0x70]
		mov eax, dword ptr [ebp-0x70]
		mov ecx, dword ptr [edx+4]
		sub ecx, dword ptr [eax]
		sar ecx, 2
		mov edx, dword ptr other
		mov eax, dword ptr [edx]
		lea ecx, [eax+ecx*4]
		mov dword ptr [ebp-0x54], ecx
		mov edx, dword ptr other
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x58], eax
		mov ecx, dword ptr [ebp-0x50]
		push ecx
		mov edx, dword ptr [ebp-0x54]
		push edx
		mov eax, dword ptr [ebp-0x58]
		push eax
		call bfmeImplVMY
		add esp, 0x0C
		xor ecx, ecx
		mov byte ptr [ebp-0x0F], cl
		mov edx, dword ptr [ebp-0x70]
		mov eax, dword ptr [edx+4]
		mov dword ptr [ebp-0x64], eax
		mov ecx, dword ptr other
		mov edx, dword ptr [ecx+4]
		mov dword ptr [ebp-0x68], edx
		mov eax, dword ptr [ebp-0x70]
		mov ecx, dword ptr [ebp-0x70]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sar edx, 2
		mov eax, dword ptr other
		mov ecx, dword ptr [eax]
		lea edx, [ecx+edx*4]
		mov dword ptr [ebp-0x6C], edx
		xor eax, eax
		mov byte ptr [ebp-0x5A], al
		mov cl, byte ptr [ebp-0x5A]
		mov byte ptr [ebp-0x59], cl
		xor edx, edx
		mov byte ptr [ebp-0x5D], dl
		mov al, byte ptr [ebp-0x5D]
		mov byte ptr [ebp-0x5B], al
		xor ecx, ecx
		mov byte ptr [ebp-0x5E], cl
		mov dl, byte ptr [ebp-0x5E]
		mov byte ptr [ebp-0x5C], dl
		mov eax, dword ptr [ebp-0x64]
		push eax
		mov ecx, dword ptr [ebp-0x68]
		push ecx
		mov edx, dword ptr [ebp-0x6C]
		push edx
		call bfmeImplVMY
		add esp, 0x0C
	set_e:
		mov eax, dword ptr [ebp-0x70]
		mov ecx, dword ptr [eax]
		mov edx, dword ptr [ebp-4]
		lea eax, [ecx+edx*4]
		mov ecx, dword ptr [ebp-0x70]
		mov dword ptr [ecx+4], eax
	done:
		mov eax, dword ptr [ebp-0x70]
	}
}
