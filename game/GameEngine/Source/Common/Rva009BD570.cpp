// cl: /Z7
struct Rva009BD570PatternFrame
{
	unsigned char patternA[16];
	unsigned char patternB[16];
	unsigned char patternC[16];
	int padding;
	int width;
	int stride;
	int remainingRows;
	unsigned char *destination;
	unsigned char *source;
};

// Open BFME 2: Code/GameEngine/Source/Common/BfmeConv9BD470.cpp
// ?Rva009BD570@@YAXPAXHHHH@Z
void __cdecl Rva009BD570(
	void *context, int byteArgumentA, int byteArgumentB,
	int sourceOffset, int destinationOffset)
{
	__declspec(align(8)) Rva009BD570PatternFrame patterns;

	__asm {
		mov eax, context
		mov ecx, [eax + 90h]
		mov edx, sourceOffset
		shl ecx, 3
		mov dword ptr patterns.width, ecx
		mov ecx, [eax + 78h]
		add edx, ecx
		mov dword ptr patterns.source, edx
		mov edx, destinationOffset
		add ecx, edx
		mov dl, byte ptr byteArgumentA
		mov esi, [eax + 94h]
		mov eax, [eax + 98h]
		mov dword ptr patterns.stride, eax
		mov eax, byteArgumentB
		mov dword ptr patterns.destination, ecx
		mov cl, al
		add cl, dl
		mov dl, cl
		mov dh, dl
		shl esi, 3
		mov ecx, edx
		shl ecx, 10h
		mov cx, dx
		mov dword ptr patterns.patternB, ecx
		mov dword ptr patterns.patternB[4], ecx

		mov cl, al
		mov ch, cl
		mov eax, ecx
		shl eax, 10h
		mov ax, cx
		mov dword ptr patterns.patternC, eax
		mov dword ptr patterns.patternC[4], eax

		mov eax, byteArgumentA
		mov dl, al
		mov dh, dl
		mov eax, edx
		shl eax, 10h
		test esi, esi
		mov ax, dx
		mov dword ptr patterns.patternA, eax
		mov dword ptr patterns.patternA[4], eax

		jle filter_done
		mov edx, dword ptr patterns.stride
		mov dword ptr patterns.remainingRows, esi
		align 16
	filter_outer:
		mov ecx, dword ptr patterns.width
		mov esi, dword ptr patterns.source
		mov edi, dword ptr patterns.destination
		xor eax, eax
	filter_inner:
		movq mm1, qword ptr [esi + eax]
		psubusb mm1, qword ptr [patterns.patternA]
		paddusb mm1, qword ptr [patterns.patternB]
		psubusb mm1, qword ptr [patterns.patternC]
		movq qword ptr [edi + eax], mm1
		add eax, 8
		cmp eax, ecx
		jl filter_inner
		mov esi, dword ptr patterns.source
		mov ecx, dword ptr patterns.destination
		mov eax, dword ptr patterns.remainingRows
		add esi, edx
		add ecx, edx
		dec eax
		mov dword ptr patterns.source, esi
		mov dword ptr patterns.destination, ecx
		mov dword ptr patterns.remainingRows, eax
		jne filter_outer
	filter_done:
	}
}
