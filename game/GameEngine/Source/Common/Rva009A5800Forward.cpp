// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// VP6 per-frame decode at retail 0x009A5620 and its only caller 0x009A5800.
// The callee stays static in this TU so VC7.1 passes its data argument in EAX.
#include <stdio.h>

class BfmeCursorXF;
struct BfmeBits1186;
struct Rva009A6130Context;
void Rva009A8410(unsigned int *result);
void d_009acb60(void);
void bfmeReadWordXF(BfmeCursorXF *out, const unsigned char *data);
void bfmeInit1186(BfmeBits1186 *s, unsigned char *p);
void Rva009ABFC0DecodeFrame(unsigned char *s);
void __cdecl Rva009A8C50(Rva009A6130Context *, unsigned char *);
extern void (__cdecl *g_bfmeToneReady)();
extern int g_0134C7D8;
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

#define U(o) (*(unsigned *)(s + (o)))
#define B(o) (*(unsigned char *)(s + (o)))
#define P(o) (*(unsigned char **)(s + (o)))

static int Rva009A5620DecodeFrame(unsigned char *s, unsigned char *data, unsigned int size)
{
	unsigned int start;
	Rva009A8410(&start);
	U(0x1e8) = size;
	bfmeReadWordXF((BfmeCursorXF *)(s + 0x450c), data);
	if (!((int (__cdecl *)(unsigned char *))d_009acb60)(s))
		return -1;
	if (U(0x944) || !B(0x19d))
	{
		if (U(0x4520))
		{
			U(0x190) = 0;
			U(0x194) = 0;
			P(0x198) = data + U(0x451c);
		}
		else
			bfmeInit1186((BfmeBits1186 *)(s + 0x170), data + U(0x451c));
	}
	Rva009ABFC0DecodeFrame(s);
	unsigned char *swap = P(0x254);
	P(0x254) = P(0x244);
	P(0x244) = swap;
	Rva009A8C50((Rva009A6130Context *)P(0x298), P(0x254));
	if (!B(0x1ac) || U(0x698))
		memcpy(P(0x24c), P(0x254), U(0x208) + U(0x20c) * 2);
	g_bfmeToneReady();
	if (!B(0x1ac))
		U(0x6a0) = *(unsigned int *)P(0x13c);
	else
		U(0x6a0) = (*(unsigned int *)P(0x13c) + 2 + U(0x6a0) * 3) >> 2;
	unsigned int end;
	Rva009A8410(&end);
	unsigned int elapsed = (end - start) / U(0x1a4);
	U(0x910) = elapsed;
	if (!U(0x914))
		U(0x914) = elapsed;
	else
		U(0x914) = (U(0x914) * 7 + elapsed) >> 3;
	if (U(0x160) > U(0x1e8))
	{
		FILE *f = fopen("badframes.stt", "a");
		fprintf(f, "%8d %8d %8d \n", g_0134C7D8, U(0x160), U(0x1e8));
		fclose(f);
	}
	++g_0134C7D8;
	return 0;
}

void __cdecl Rva009A5800Forward(int s, int data, int size)
{
	Rva009A5620DecodeFrame((unsigned char *)s, (unsigned char *)data, (unsigned int)size);
}

#undef U
#undef B
#undef P
