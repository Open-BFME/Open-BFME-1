// Copies the first and last row verbatim, then rebuilds every row between
// them as (row-1 + 2*row + row+1 + 2) >> 2. Scalar sibling of bfmeBlurRowsSse;
// MSVC 7.1 will not emit the retail push-ecx scratch plus the [base+index]
// inner addressing from C, so this stays naked like that SSE body.

// ?bfmeBlurRows@@YAXPAX0IHH@Z
void __declspec(naked) __cdecl bfmeBlurRows(void *src, void *dst, unsigned int width, int count, int stride)
{
	__asm
	{
		push ecx
		mov edx, dword ptr [esp+8]
		push ebx
		mov ebx, dword ptr [esp+14h]
		push ebp
		push esi
		push edi
		mov edi, dword ptr [esp+1Ch]
		mov ecx, ebx
		mov eax, ecx
		shr ecx, 2
		mov ebp, edi
		mov esi, edx
		rep movsd
		mov ecx, eax
		mov eax, dword ptr [esp+28h]
		and ecx, 3
		rep movsb
		mov esi, dword ptr [esp+24h]
		dec esi
		cmp esi, 1
		jle bfmeTail
		mov ecx, edx
		add ecx, eax
		dec esi
		mov dword ptr [esp+1Ch], esi
		_emit 0x8D
		_emit 0x64
		_emit 0x24
		_emit 0x00
	bfmeLoop:
		mov edi, edx
		add edx, eax
		add ebp, eax
		add ecx, eax
		test ebx, ebx
		mov dword ptr [esp+24h], edx
		mov dword ptr [esp+10h], ebp
		jle bfmeSkip
		mov esi, edx
		sub esi, ecx
		sub edi, ecx
		mov eax, ecx
		sub ebp, ecx
		mov dword ptr [esp+18h], ebx
	bfmeInner:
		movzx ebx, byte ptr [edi+eax]
		movzx edx, byte ptr [esi+eax]
		lea edx, [ebx+edx*2+2]
		movzx ebx, byte ptr [eax]
		add edx, ebx
		shr edx, 2
		mov byte ptr [eax+ebp], dl
		mov edx, dword ptr [esp+18h]
		inc eax
		dec edx
		mov dword ptr [esp+18h], edx
		jne bfmeInner
		mov eax, dword ptr [esp+28h]
		mov ebx, dword ptr [esp+20h]
		mov edx, dword ptr [esp+24h]
		mov ebp, dword ptr [esp+10h]
	bfmeSkip:
		dec dword ptr [esp+1Ch]
		jne bfmeLoop
	bfmeTail:
		mov ecx, ebx
		lea edi, [eax+ebp]
		lea esi, [edx+eax]
		mov eax, ecx
		shr ecx, 2
		rep movsd
		mov ecx, eax
		and ecx, 3
		rep movsb
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		ret
	}
}
