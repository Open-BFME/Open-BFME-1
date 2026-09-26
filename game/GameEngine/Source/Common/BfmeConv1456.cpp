// cl: /Od

char *bfmeFillV16(char *p, unsigned n, char v);

class BfmeStrV16
{
public:
	BfmeStrV16 *bfmeAssignV16(unsigned n, char v);
	void bfmeEraseV16(char *first, char *last);
	void bfmeAppendV16(unsigned n, char v);

	char *b;
	char *e;
};

BfmeStrV16 *BfmeStrV16::bfmeAssignV16(unsigned n, char v)
{
	char pad[16];

	__asm
	{
		mov eax, this
		mov ecx, this
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr n, edx
		ja grow_path
		mov al, byte ptr v
		push eax
		mov ecx, dword ptr n
		push ecx
		mov edx, this
		mov eax, dword ptr [edx]
		push eax
		call bfmeFillV16
		add esp, 0x0C
		mov ecx, this
		mov edx, dword ptr [ecx+4]
		mov dword ptr [ebp-4], edx
		mov eax, this
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-8], ecx
		mov edx, dword ptr [ebp-4]
		push edx
		mov eax, dword ptr [ebp-8]
		add eax, dword ptr n
		push eax
		mov ecx, this
		call bfmeEraseV16
		jmp done
	grow_path:
		mov cl, byte ptr v
		push ecx
		mov edx, this
		mov eax, this
		mov ecx, dword ptr [edx+4]
		sub ecx, dword ptr [eax]
		push ecx
		mov edx, this
		mov eax, dword ptr [edx]
		push eax
		call bfmeFillV16
		add esp, 0x0C
		mov cl, byte ptr v
		push ecx
		mov edx, this
		mov eax, this
		mov ecx, dword ptr [edx+4]
		sub ecx, dword ptr [eax]
		mov edx, dword ptr n
		sub edx, ecx
		push edx
		mov ecx, this
		call bfmeAppendV16
	done:
		mov eax, this
	}
}
