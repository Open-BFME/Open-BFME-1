// ?Rva009C0A30Vp6AddNoise@@YAXPAEIIHH@Z
// partial score=0.55 date=2026-09-04
// cl: /O2 /Ob0 /G6 /DNDEBUG /DWIN32 /D_WINDOWS /MD

#include <math.h>
#include <stdlib.h>

extern double __cdecl bfmeGaussPdf(double, double, double);
extern "C" int (__cdecl *__imp__rand)(void);

// The VP6 postprocessor builds a byte lookup with a Gaussian distribution,
// then applies a random signed-byte plane noise stream with saturated clamps.
// The retail body combines the table setup and the plane pass in this helper.
void __cdecl Rva009C0A30Vp6AddNoise(
	unsigned char *start, unsigned int width, unsigned int height,
	int pitch, int noiseLevel)
{
	__declspec(align(16)) char noise[2048];
	__declspec(align(16)) char charDist[0x160];
	double sigma;
	double value;
	int j;
	int next;

	__asm
	{
		emms
	}

	sigma = 1.0 + (63 - noiseLevel) * (0.8 / 63.0);
	next = 0;
	for (value = -32.0; value < 32.0; value += 1.0) {
		int amount = (int)(0.5 + 256.0 * bfmeGaussPdf(sigma, 0.0, value));
		if (amount != 0) {
			for (j = 0; j < amount; ++j)
				charDist[next + j] = (char)value;
			next += j;
		}
	}
	for (; next < 256; ++next)
		charDist[next] = 0;

	for (unsigned int noiseIndex = 0; noiseIndex < 2048; ++noiseIndex)
		noise[noiseIndex] = charDist[rand() & 0xff];

	__asm
	{
		mov al, byte ptr charDist
		mov cl, al
		mov dl, 0feh
		imul dl
		mov dl, al
		mov dh, dl
		neg cl
		mov eax, edx
		shl eax, 10h
		mov ax, dx
		mov dword ptr [ebp - 50h], eax
		mov dword ptr [ebp - 4ch], eax
		mov dword ptr [ebp - 48h], eax
		mov dword ptr [ebp - 44h], eax
		mov al, cl
		mov dl, al
		mov dh, dl
		mov eax, edx
		shl eax, 10h
		mov ax, dx
		mov dword ptr [ebp - 30h], eax
		mov dword ptr [ebp - 2ch], eax
		mov dword ptr [ebp - 28h], eax
		mov dword ptr [ebp - 24h], eax
		mov al, cl
		mov ah, al
		mov ecx, eax
		shl ecx, 10h
		mov cx, ax
		mov eax, height
		test eax, eax
		mov dword ptr [ebp - 40h], ecx
		mov dword ptr [ebp - 3ch], ecx
		mov dword ptr [ebp - 38h], ecx
		mov dword ptr [ebp - 34h], ecx
		jbe rva009c0a30_done
		mov ecx, start
		mov dword ptr [ebp - 8h], ecx
		mov dword ptr [ebp - 4h], eax
	rva009c0a30_row:
		mov edx, dword ptr [ebp - 8h]
		mov dword ptr [ebp - 14h], edx
		call dword ptr ds:[01359470h]
		and eax, 0ffh
		lea eax, noise[eax]
		mov dword ptr [ebp - 0ch], eax
		mov ecx, width
		mov esi, dword ptr [ebp - 14h]
		mov edi, dword ptr [ebp - 0ch]
		xor eax, eax
	rva009c0a30_col:
		movdqu xmm1, [esi + eax]
		psubusb xmm1, [ebp - 40h]
		paddusb xmm1, [ebp - 50h]
		psubusb xmm1, [ebp - 30h]
		movdqu xmm2, [edi + eax]
		paddb xmm1, xmm2
		movdqu [esi + eax], xmm1
		add eax, 10h
		cmp eax, ecx
		jl rva009c0a30_col
		mov edx, dword ptr [ebp - 8h]
		mov ecx, pitch
		mov eax, dword ptr [ebp - 4h]
		add edx, ecx
		dec eax
		mov dword ptr [ebp - 8h], edx
		mov dword ptr [ebp - 4h], eax
		jne rva009c0a30_row
	rva009c0a30_done:
	}
}
