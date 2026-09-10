// ?Rva009A4D00Init@@YAXXZ
// Address-derived: two opaque setup helpers seed a global, a 64-entry signed
// 16-bit table is halved (rounding toward zero) and offset by 2 into an int
// array, then an opaque helper and bfmeRun_009A75E0 run in tail position.

extern void d_009a8430();
extern void d_009a8550();
extern void d_009a5aa0();
void bfmeRun_009A75E0(void);

typedef int (__cdecl *Fn009A8430)();
typedef void (__cdecl *Fn009A5AA0)(void *, void *, void *, int);

static int *const g_013571E0 = (int *)0x013571E0;
static int *const g_0134C6D8 = (int *)0x0134C6D8;
static const short *const g_01141D08 = (const short *)0x01141D08;
static const short *const g_01141D88 = (const short *)0x01141D88;

void Rva009A4D00Init(void)
{
	*g_013571E0 = reinterpret_cast<Fn009A8430>(d_009a8430)();
	d_009a8550();

	int *dst = g_0134C6D8;
	for (const short *src = g_01141D08; (int)src < (int)g_01141D88; ++src, ++dst)
		*dst = *src / 2 + 2;

	reinterpret_cast<Fn009A5AA0>(d_009a5aa0)(g_0134C6D8, g_0134C6D8, g_0134C6D8, 7);
	bfmeRun_009A75E0();
}

// Retail RVA 0x009A6600: install the identity table and invert the zigzag permutation.
extern int g_rva01142408[];
extern int g_rva01142308[];
struct Rva009A6600Context { unsigned char prefix[0x13c]; int *table; unsigned char cells[64]; };
void Rva009A6600InitBlocks(void *self)
{
 Rva009A6600Context *ctx=(Rva009A6600Context *)self;
 ctx->table=g_rva01142408;
 for(int i=0;i<64;++i) ctx->cells[g_rva01142308[i]]=(unsigned char)i;
}


