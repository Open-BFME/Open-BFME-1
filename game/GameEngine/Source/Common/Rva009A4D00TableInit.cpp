// ?Rva009A4D00Init@@YAXXZ
// Address-derived: two opaque setup helpers seed a global, a 64-entry signed
// 16-bit table is halved (rounding toward zero) and offset by 2 into an int
// array, then an opaque helper and bfmeRun_009A75E0 run in tail position.

extern void d_009a8430();
extern void d_009a5aa0();
void bfmeRun_009A75E0(void);

extern void __cdecl bfmeQueryCpuTierFlags(int *pTierA, int *pTierB, int *pTierC);
extern void __cdecl initBlocksRva009B3EC0(void *self);
extern void __cdecl initBlocksRva009B3E40(void *self);

typedef int (__cdecl *Fn009A8430)();
typedef void (__cdecl *Fn009A5AA0)(void *, void *, void *, int);

static int *const g_013571E0 = (int *)0x013571E0;
static int *const g_0134C6D8 = (int *)0x0134C6D8;
static const short *const g_01141D08 = (const short *)0x01141D08;
static const short *const g_01141D88 = (const short *)0x01141D88;

typedef void (__cdecl *Rva009A8550Fn)(void *);
extern Rva009A8550Fn volatile g_rva01356DA0;

extern int g_rva01142408[];
extern int g_rva01142308[];
struct Rva009A6600Context { unsigned char prefix[0x13c]; int *table; unsigned char cells[64]; };
void Rva009A6600InitBlocks(void *self)
{
 Rva009A6600Context *ctx=(Rva009A6600Context *)self;
 ctx->table=g_rva01142408;
 for(int i=0;i<64;++i) ctx->cells[g_rva01142308[i]]=(unsigned char)i;
}


// Retail [0x009A8550, 0x009A859F): choose the codec block initializer for
// the detected CPU tier.  The generic body is the direct retail target at
// RVA 0x009A6600; its complete 37-byte body is verified above.
void Rva009A8550Init(void)
{
	int tierC;
	int tierA;
	int tierB;

	bfmeQueryCpuTierFlags(&tierA, &tierB, &tierC);

	if (tierC != 0)
	{
		g_rva01356DA0 = (Rva009A8550Fn)&initBlocksRva009B3EC0;
		return;
	}

	if (tierA != 0)
	{
		g_rva01356DA0 = (Rva009A8550Fn)&initBlocksRva009B3E40;
	}
	else
	{
		g_rva01356DA0 = (Rva009A8550Fn)&initBlocksRva009B3E40;
		g_rva01356DA0 = &Rva009A6600InitBlocks;
	}
}

void Rva009A4D00Init(void)
{
	*g_013571E0 = reinterpret_cast<Fn009A8430>(d_009a8430)();
	Rva009A8550Init();

	int *dst = g_0134C6D8;
	for (const short *src = g_01141D08; (int)src < (int)g_01141D88; ++src, ++dst)
		*dst = *src / 2 + 2;

	reinterpret_cast<Fn009A5AA0>(d_009a5aa0)(g_0134C6D8, g_0134C6D8, g_0134C6D8, 7);
	bfmeRun_009A75E0();
}
