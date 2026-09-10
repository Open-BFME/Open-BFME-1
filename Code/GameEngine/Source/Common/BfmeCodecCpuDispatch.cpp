// Installs per-CPU-tier function pointers into the BFME video/image codec
// dispatch table: 26 contiguous slots plus one standalone outlier slot.
// Probes the tier via bfmeQueryCpuTierFlags (0x009B3A90, parked partial --
// declared extern and pinned since a pin does not require the callee to be
// converted): the SSE tier (top flag set) resets the spread table and
// installs the full SIMD set; the MMX tier (basic flag set) resets the
// spread table and installs the MMX-only set (mostly shared with the SSE
// tier); otherwise the generic scalar/table-driven set installs directly
// with no spread-table reset. Sibling of bfmeFilterPairMmx, bfmeExpandMmx,
// bfmeBlurRows* and BfmeLimitedEdgeFilters.cpp.

extern void __cdecl bfmeQueryCpuTierFlags(int *pTierA, int *pTierB, int *pTierC);
extern void __cdecl spreadTable(void);

// Landed siblings, declared with their real signatures so the mangled name
// matches their existing row.
struct Rva009C2930Owner;
extern void __cdecl bfmeFilterPairMmx(void *, void *, int, const void *);
extern void __cdecl initPattern(Rva009C2930Owner *, unsigned int);
extern void __cdecl bfmeExpandMmx(const void *, int, void *);
extern void __cdecl bfmeExpand3to5Mmx(const void *, int, void *);
extern void __cdecl bfmeExpand4to5Mmx(const void *, int, void *);
extern void __cdecl bfmeAverageMmx(void *, int, int);
extern void __cdecl bfmeCopyMmx(void *, int, int);
extern void __cdecl bfmeInterpRows6Mmx(void *, int, int);
extern void __cdecl bfmeInterpRows2Mmx(void *, int, int);
extern void __cdecl bfmeInterpRows5Mmx(void *, int, int);
extern void __cdecl bfmeInterpRowsMmx(void *, int, int);
extern void __cdecl bfmeBlurRowsSse(void *, void *, unsigned int, int, int);
extern void __cdecl bfmeBlurRowsMmx(void *, void *, unsigned int, int, int);
extern void __cdecl bfmeBlurRows(void *, void *, unsigned int, int, int);
struct Rva009AF490Context;
struct Rva009ACBA0Context;
extern void __cdecl Rva009AF570FilterVert(void *, unsigned char *, int, const int *);
extern void __cdecl Rva009AF6A0FilterHoriz(void *, unsigned char *, int, const int *);
extern int * __cdecl Rva009AF490SetupBounding(Rva009AF490Context *, int);
extern int * __cdecl Rva009ACBA0SetupBounding(Rva009ACBA0Context *, int);
extern void __cdecl Rva009B3650FilterVert(void *, unsigned char *, int, const int *);
extern void __cdecl Rva009B3710FilterHoriz(void *, unsigned char *, int, const int *);
extern void __cdecl Rva009AF840FilterVert(int, unsigned char *, int);
extern void __cdecl Rva009AFA60FilterHoriz(int, unsigned char *, int);
extern void __cdecl Rva009AFCA0FilterVert(int, unsigned char *, int);
extern void __cdecl Rva009AFEC0FilterHoriz(int, unsigned char *, int);

// Unconverted gen-dump callees that already carry a functions.csv row (the
// row is the candidate; no new pin needed).
extern void __cdecl bfmeFilterBlockMmx(void *, void *, int, void *);
extern "C" void __cdecl Rva009C2620Vp6FilterDiag4(void *, void *, void *, int, int, int *);
extern "C" void __cdecl Rva009C2320Vp6FilterDiag4(void *, void *, void *, int, int, int *);
extern void __cdecl d_009bebb0(void);
extern void __cdecl d_009bfa40(void);
extern void __cdecl d_009b9700(void);
extern void __cdecl d_009c1ed0(void);
struct Rva009C2170Ctx;
extern void __cdecl bfmeDeblockEdgeByIndexMmx(Rva009C2170Ctx *, void *, int);
extern void __cdecl bfmeFilterBlockByIndexMmx(int, void *, int);
extern void __cdecl bfmeFilterBlockPairByIndexMmx(int, void *, int);
extern void __cdecl bfmeFilterRowByIndex8Mmx(int, void *, int);
extern void __cdecl bfmeFilterRowByIndex12Mmx(int, void *, int);
extern void __cdecl d_009bd470(void);
extern void __cdecl d_009c0a30(void);
extern void __cdecl d_009be180(void);
extern void __cdecl d_009bd750(void);
extern void __cdecl d_009b8130(void);
extern void __cdecl d_009a5f50(void);

// Slot fillers with neither a real identity nor a ghidra-boundary row yet;
// address-derived names, pinned in reverse/symbols.csv.
extern void __cdecl Rva009B6D40(void);
extern void __cdecl Rva009B6D80(void);
extern void __cdecl Rva009BD570(void);
extern void __cdecl Rva009BA790(void);
extern void __cdecl Rva009B18D0(void);
extern void __cdecl Rva009B10E0(void);
extern void __cdecl Rva009ACF90(void);
extern void __cdecl Rva009ADD80(void);
extern void __cdecl Rva009AE6A0(void);
extern void __cdecl Rva009A98E0(void);
extern void __cdecl Rva009A9920(void);
extern void __cdecl Rva009A9960(void);
extern void __cdecl Rva009A9550(void);
extern void __cdecl Rva009A9660(void);
extern void __cdecl Rva009A9720(void);
extern void __cdecl Rva009A91D0(void);
extern void __cdecl Rva009A92D0(void);
extern void __cdecl Rva009A9370(void);
extern void __cdecl Rva009B6BB0(void);

typedef void (__cdecl *BfmeDispatchFn)();

struct BfmeCodecDispatchTable
{
	BfmeDispatchFn slot[26];
};

static BfmeCodecDispatchTable g_bfmeCodecDispatch;
static BfmeDispatchFn g_bfmeCodecDispatchOutlier;

void __cdecl bfmeInstallCpuDispatchTable(void)
{
	int tierA, tierB, tierC;
	bfmeQueryCpuTierFlags(&tierA, &tierB, &tierC);
	if (tierC)
	{
		spreadTable();
		g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&bfmeFilterBlockMmx;
		g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&bfmeFilterPairMmx;
		g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&initPattern;
		g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&Rva009B6D40;
		g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&Rva009C2620Vp6FilterDiag4;
		g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&Rva009C2320Vp6FilterDiag4;
		g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&d_009bebb0;
		g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&d_009bfa40;
		g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&d_009b9700;
		g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&d_009c1ed0;
		g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&bfmeDeblockEdgeByIndexMmx;
		g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&bfmeExpandMmx;
		g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&bfmeExpand3to5Mmx;
		g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&bfmeExpand4to5Mmx;
		g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&bfmeAverageMmx;
		g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&bfmeCopyMmx;
		g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&bfmeInterpRows6Mmx;
		g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&bfmeInterpRows2Mmx;
		g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&bfmeInterpRows5Mmx;
		g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&bfmeInterpRowsMmx;
		g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&bfmeFilterBlockByIndexMmx;
		g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&bfmeFilterRowByIndex8Mmx;
		g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&bfmeFilterBlockPairByIndexMmx;
		g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&bfmeFilterRowByIndex12Mmx;
		g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&bfmeBlurRowsSse;
		g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&d_009bd470;
		g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&d_009c0a30;
		return;
	}
	if (tierA)
	{
		spreadTable();
		g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&bfmeFilterBlockMmx;
		g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&bfmeFilterPairMmx;
		g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&initPattern;
		g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&Rva009B6D40;
		g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&d_009be180;
		g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&d_009bd750;
		g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&Rva009B6D80;
		g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&d_009b8130;
		g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&d_009b9700;
		g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&d_009c1ed0;
		g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&bfmeDeblockEdgeByIndexMmx;
		g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&bfmeExpandMmx;
		g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&bfmeExpand3to5Mmx;
		g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&bfmeExpand4to5Mmx;
		g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&bfmeAverageMmx;
		g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&bfmeCopyMmx;
		g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&bfmeInterpRows6Mmx;
		g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&bfmeInterpRows2Mmx;
		g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&bfmeInterpRows5Mmx;
		g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&bfmeInterpRowsMmx;
		g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&bfmeFilterBlockByIndexMmx;
		g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&bfmeFilterRowByIndex8Mmx;
		g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&bfmeFilterBlockPairByIndexMmx;
		g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&bfmeFilterRowByIndex12Mmx;
		g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&bfmeBlurRowsMmx;
		g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&Rva009BD570;
		g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&Rva009BA790;
		return;
	}
	g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&Rva009AF570FilterVert;
	g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&Rva009AF6A0FilterHoriz;
	g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&Rva009AF490SetupBounding;
	g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&Rva009ACBA0SetupBounding;
	g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&Rva009B18D0;
	g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&Rva009B10E0;
	g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&Rva009ACF90;
	g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&Rva009ADD80;
	g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&Rva009AE6A0;
	g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&Rva009B3650FilterVert;
	g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&Rva009B3710FilterHoriz;
	g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&Rva009A98E0;
	g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&Rva009A9920;
	g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&Rva009A9960;
	g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&Rva009A9550;
	g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&Rva009A9660;
	g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&Rva009A9720;
	g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&Rva009A91D0;
	g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&Rva009A92D0;
	g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&Rva009A9370;
	g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&Rva009AF840FilterVert;
	g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&Rva009AFA60FilterHoriz;
	g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&Rva009AFCA0FilterVert;
	g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&Rva009AFEC0FilterHoriz;
	g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&bfmeBlurRows;
	g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&Rva009B6BB0;
	g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&d_009a5f50;
}
