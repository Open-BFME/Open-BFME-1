// Installs the per-CPU-tier "spread table" function-pointer blob for the
// BFME video/image codec: two 65-slot arrays (offsets 0xA4 and 0x1C4 from
// this blob, indexed by byte offset 0..0x100 in steps of 4, split 2/9/54
// between a low-, mid- and tail-range filler) plus twelve individually
// named slots scattered through the same blob.  Sibling of the plain
// (non-looping) installer in BfmeCodecCpuDispatch.cpp (0x009B0D60): same
// bfmeQueryCpuTierFlags probe and same tier-C / tier-A / generic order,
// but this one only ever loads its filler set into two big arrays and a
// dozen named cells, never into the small dispatch table there.
//
// g_bfmeTableJX (retail 0x01356B60, pinned elsewhere as a plain int) is
// array1's first slot; every other field in the blob is reached by a
// constant byte offset from its address, since nothing else in the blob
// carries a name yet.

extern void __cdecl bfmeQueryCpuTierFlags(int *pTierA, int *pTierB, int *pTierC);
extern int g_bfmeTableJX;

// Individually named blob cells (not part of either 65-slot array); no real
// identity yet, address-derived names, pinned in reverse/symbols.csv.
extern void *g_bfmeSlotABC;
extern void *g_bfmeSlotB40;
extern void *g_bfmeSlotB44;
extern void *g_bfmeSlotB48;
extern void *g_bfmeSlotB4C;
extern void *g_bfmeSlotB50;
extern void *g_bfmeSlotB54;
extern void *g_bfmeSlotB58;
extern void *g_bfmeSlotB5C;
extern void *g_bfmeSlotD84;
extern void *g_bfmeSlotD88;
extern void *g_bfmeSlotD8C;

// Landed callees, declared with their real signatures so the mangled name
// matches their existing row.
extern void __cdecl widen8x8(const unsigned char *, unsigned short *, int);
struct Rva009C6DA0Vec3;
extern void __cdecl copyTwelveVec3(const Rva009C6DA0Vec3 *, Rva009C6DA0Vec3 *, int, int);
extern void __cdecl bfmeAvg8to16Mmx(const void *, const void *, void *, int);
extern void __cdecl bfmeUnpack8to16Mmx(const void *, void *, int);
extern void __cdecl bfmeSub8to16Mmx(const void *, void *, int);
extern void __cdecl bfmeAddPack8Mmx(const void *, const void *, void *, int);
extern void __cdecl bfmeAddPack8Sse(void *, void *, const void *, const void *, int);
extern void __cdecl bfmeAddPack8MmxRow(void *, void *, const void *, const void *, int);
extern void __cdecl bfmePackXor80Sse(void *, void *, const void *, int);
extern void __cdecl bfmePackXor80Mmx(void *, void *, const void *, int);

// Unconverted gen-dump callees that already carry a functions.csv row (the
// row is the candidate; no new pin needed).
extern void __cdecl d_009c5080(void);
extern void __cdecl d_009c6cb0(void);
extern void __cdecl d_009c6d30(void);
extern void __cdecl d_009c74f0(void);
extern void __cdecl d_009c7760(void);
extern void __cdecl d_009c7cc0(void);

// Slot fillers with neither a real identity nor a ghidra-boundary row yet;
// address-derived names, pinned in reverse/symbols.csv.
extern void __cdecl Rva009C7380(void);
extern void __cdecl Rva009C6900(void);
extern void __cdecl Rva009A8110(void);
extern void __cdecl Rva009A74D0(void);
extern void __cdecl Rva009C6D20(void);
extern void __cdecl Rva009A7030(void);
extern void __cdecl Rva009A7040(void);
extern void __cdecl Rva009C6A30(void);
extern void __cdecl Rva009A7B00(void);
extern void __cdecl Rva009A7300(void);
extern void __cdecl Rva009C4E90(void);
extern void __cdecl Rva009C5360(void);
extern void __cdecl Rva009C4DF0(void);
extern void __cdecl Rva009C80C0(void);
extern void __cdecl Rva009C77C0(void);
extern void __cdecl Rva009C3630(void);
extern void __cdecl Rva009C2CE0(void);
extern void __cdecl Rva009C3CF0(void);
extern void __cdecl Rva009C4450(void);
extern void __cdecl Rva009C3D50(void);
extern void __cdecl Rva009C6360(void);
extern void __cdecl Rva009C5D60(void);
extern void __cdecl Rva009C5890(void);

typedef void (__cdecl *BfmeSpreadFn)();

void __cdecl bfmeInstallSpreadTable(void)
{
	int tierA, tierB, tierC;
	unsigned int i;

	bfmeQueryCpuTierFlags(&tierA, &tierB, &tierC);

	if (tierC)
	{
		BfmeSpreadFn low = (BfmeSpreadFn)&Rva009C80C0;
		BfmeSpreadFn mid = (BfmeSpreadFn)&d_009c7cc0;
		BfmeSpreadFn tail = (BfmeSpreadFn)&Rva009C77C0;

		for (i = 0; i <= 0x100; i += 4) {
			if (i <= 4)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = low;
			else if (i <= 0x28)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = mid;
			else
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = tail;
		}

		mid = (BfmeSpreadFn)&Rva009C3630;
		tail = (BfmeSpreadFn)&Rva009C2CE0;

		for (i = 0; i <= 0x100; i += 4) {
			if (i <= 4)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = low;
			else if (i <= 0x28)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = mid;
			else
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = tail;
		}

		g_bfmeSlotD8C = (void *)&bfmePackXor80Sse;
		g_bfmeSlotD84 = (void *)&bfmeAddPack8Sse;
		g_bfmeSlotB58 = (void *)&d_009c7760;
		g_bfmeSlotB48 = (void *)&Rva009C6D20;
		g_bfmeSlotB4C = (void *)&bfmeAvg8to16Mmx;
		g_bfmeSlotB50 = (void *)&bfmeUnpack8to16Mmx;
		g_bfmeSlotD88 = (void *)&bfmeAddPack8Mmx;
		g_bfmeSlotB5C = (void *)&bfmeSub8to16Mmx;
		g_bfmeSlotB44 = (void *)&d_009c6d30;
		g_bfmeSlotABC = (void *)&Rva009C7380;
		g_bfmeSlotB54 = (void *)&d_009c74f0;
		g_bfmeSlotB40 = (void *)&copyTwelveVec3;
		return;
	}

	if (tierA)
	{
		BfmeSpreadFn low = (BfmeSpreadFn)&Rva009C3CF0;
		BfmeSpreadFn mid = (BfmeSpreadFn)&Rva009C3630;
		BfmeSpreadFn tail = (BfmeSpreadFn)&Rva009C2CE0;

		for (i = 0; i <= 0x100; i += 4) {
			if (i <= 4)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = low;
			else if (i <= 0x28)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = mid;
			else
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = tail;
		}

		mid = (BfmeSpreadFn)&Rva009C4450;
		tail = (BfmeSpreadFn)&Rva009C3D50;

		for (i = 0; i <= 0x100; i += 4) {
			if (i <= 4)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = low;
			else if (i <= 0x28)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = mid;
			else
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = tail;
		}

		g_bfmeSlotD8C = (void *)&bfmePackXor80Mmx;
		g_bfmeSlotD84 = (void *)&bfmeAddPack8MmxRow;
		g_bfmeSlotB58 = (void *)&d_009c6cb0;
		g_bfmeSlotB48 = (void *)&Rva009C6D20;
		g_bfmeSlotB4C = (void *)&bfmeAvg8to16Mmx;
		g_bfmeSlotB50 = (void *)&bfmeUnpack8to16Mmx;
		g_bfmeSlotD88 = (void *)&bfmeAddPack8Mmx;
		g_bfmeSlotB5C = (void *)&bfmeSub8to16Mmx;
		g_bfmeSlotB44 = (void *)&d_009c6d30;
		g_bfmeSlotABC = (void *)&Rva009C6900;
		g_bfmeSlotB54 = (void *)&Rva009C6A30;
		g_bfmeSlotB40 = (void *)&copyTwelveVec3;
		return;
	}

	{
		BfmeSpreadFn low = (BfmeSpreadFn)&Rva009C6360;
		BfmeSpreadFn mid = (BfmeSpreadFn)&Rva009C5D60;
		BfmeSpreadFn tail = (BfmeSpreadFn)&Rva009C5890;
		BfmeSpreadFn *cell;

		for (cell = (BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120);
		     (int)cell <= (int)((char *)&g_bfmeTableJX + 0x220);
		     cell = (BfmeSpreadFn *)((char *)cell + 4)) {
			if ((int)cell <= (int)((char *)&g_bfmeTableJX + 0x124))
				*cell = low;
			else if ((int)cell <= (int)((char *)&g_bfmeTableJX + 0x148))
				*cell = mid;
			else
				*cell = tail;
		}

		for (cell = (BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0);
		     (int)cell <= (int)((char *)&g_bfmeTableJX + 0x100);
		     cell = (BfmeSpreadFn *)((char *)cell + 4)) {
			if ((int)cell <= (int)((char *)&g_bfmeTableJX + 0x4))
				*cell = low;
			else if ((int)cell <= (int)((char *)&g_bfmeTableJX + 0x28))
				*cell = mid;
			else
				*cell = tail;
		}

		g_bfmeSlotB48 = (void *)&Rva009A7030;
		g_bfmeSlotD8C = (void *)&Rva009C4DF0;
		g_bfmeSlotD84 = (void *)&Rva009C4E90;
		g_bfmeSlotB58 = (void *)&d_009c5080;
		g_bfmeSlotB4C = (void *)&Rva009A7040;
		g_bfmeSlotB50 = (void *)&widen8x8;
		g_bfmeSlotD88 = (void *)&Rva009C5360;
		g_bfmeSlotB5C = (void *)&Rva009A7300;
		g_bfmeSlotB44 = (void *)&Rva009A74D0;
		g_bfmeSlotABC = (void *)&Rva009A8110;
		g_bfmeSlotB54 = (void *)&Rva009A7B00;
		g_bfmeSlotB40 = (void *)&copyTwelveVec3;
	}
}
