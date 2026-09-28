// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?Rva009B2A50@@YAXPAURva009A6130Context@@PAE1@Z
// Retail 0x009B2A50, 1835 bytes (single ret at +0x72A, int3 padding to
// 0x009B3180; the generated scaffold's 1832 stopped three bytes short).
//
// VP6 interlaced dering pass: the same algorithm as On2 VP3's postproc
// DeringFrame, run over two Y fields (doubled stride, the second field one
// line down, the fragment-variance index carrying on), then the U and V
// planes at half width and a quarter of that stride.  A index whose variance
// exceeds the third threshold (fourth for chroma) is strongly derung, and
// derung twice more when a neighbour exceeds the fourth; otherwise strong,
// weak or a plain copy by the second and first thresholds.  The kernels are
// the codec's dispatch slots 0x01356EC0 (strong), 0x01356EA0 (weak) and
// 0x01356B44 (copy); the quantiser table is picked by m_mode.
//
// Identity: the only caller is the landed Rva009A6130PostFilterDispatch,
// which declares this exact (context, source, destination) signature; no
// vtable, string or symbol names it, so it keeps the address token.  The
// context view reuses that caller's field names; +0x28 (m_metric) is the per-fragment
// variance array.
//
// Shape notes: the first field spells the destination index as
// dstPtr + 8*col and the later passes as the source index plus the row
// delta, which is how retail forms them (lea base/index and the lea-vs-add
// choice at each kernel call); LineLength is unsigned (shr, not sar).

struct Rva009A6130Context
{
	int m_mode;
	int m_04;
	int m_level;
	int m_tableIndex;
	unsigned char *m_source;
	unsigned char *m_destination;
	unsigned char *m_18;
	int m_1c;
	int m_20;
	unsigned char m_pad24[0x28 - 0x24];
	int *m_metric;
	unsigned char m_pad2c[0x78 - 0x2c];
	unsigned int m_planeY;
	unsigned int m_planeU;
	unsigned int m_planeV;
	unsigned char m_pad84[0x90 - 0x84];
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
};

typedef void (__cdecl *Rva009B2A50Dering)(Rva009A6130Context *, unsigned char *,
	unsigned char *, int, int, const int *);
typedef void (__cdecl *Rva009B2A50Copy)(unsigned char *, unsigned char *, int);

extern Rva009B2A50Dering g_rva01356EC0;
extern Rva009B2A50Dering g_rva01356EA0;
extern void *g_bfmeSlotB44;
extern int g_rva01356940[64];
extern int g_rva012D7F58[64];
extern int g_rva012D8058[64];

#define BLOCK_SRC (srcPtr + 8 * col)
#define BLOCK_DST (srcPtr + 8 * col + (dstPtr - srcPtr))
#define BLOCK_DST_FIRST (dstPtr + 8 * col)

void __cdecl Rva009B2A50(Rva009A6130Context *ctx, unsigned char *src, unsigned char *dst)
{
	int thresh1, thresh2, thresh3, thresh4;
	const int *table;
	int quality;
	unsigned char *srcPtr;
	unsigned char *dstPtr;
	unsigned int blocksAcross;
	unsigned int blocksDown;
	unsigned int index;
	unsigned int row;
	unsigned int col;
	unsigned int lineLength;

	quality = ctx->m_tableIndex;
	if (ctx->m_mode >= 5)
	{
		thresh1 = 0x180;
		thresh2 = 0x900;
		thresh3 = 0xb40;
		thresh4 = 0x1680;
	}
	else
	{
		thresh1 = 0x800;
		thresh2 = 0x7800;
		thresh3 = 0x16800;
		thresh4 = 0x1e000;
	}

	if (ctx->m_mode >= 5)
		table = g_rva012D8058;
	else if (ctx->m_mode >= 2)
		table = g_rva012D7F58;
	else
		table = g_rva01356940;

	// Y plane, first field.
	blocksAcross = ctx->m_width;
	blocksDown = ctx->m_height >> 1;
	srcPtr = src + ctx->m_planeY;
	dstPtr = dst + ctx->m_planeY;
	lineLength = ctx->m_strideY << 1;
	index = 0;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh3)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
				if ((col > 0 && ctx->m_metric[index - 1] > thresh4) ||
					(col + 1 < blocksAcross && ctx->m_metric[index + 1] > thresh4) ||
					(row + 1 < blocksDown && ctx->m_metric[index + blocksAcross] > thresh4) ||
					(row > 0 && ctx->m_metric[index - blocksAcross] > thresh4))
				{
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
				}
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST_FIRST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST_FIRST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}

	// Y plane, second field.
	srcPtr = src + ctx->m_planeY + ctx->m_strideY;
	dstPtr = dst + ctx->m_planeY + ctx->m_strideY;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh3)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				if ((col > 0 && ctx->m_metric[index - 1] > thresh4) ||
					(col + 1 < blocksAcross && ctx->m_metric[index + 1] > thresh4) ||
					(row + 1 < blocksDown && ctx->m_metric[index + blocksAcross] > thresh4) ||
					(row > 0 && ctx->m_metric[index - blocksAcross] > thresh4))
				{
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				}
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}

	// U plane.
	blocksAcross >>= 1;
	srcPtr = src + ctx->m_planeU;
	dstPtr = dst + ctx->m_planeU;
	lineLength >>= 2;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh4)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}

	// V plane.
	srcPtr = src + ctx->m_planeV;
	dstPtr = dst + ctx->m_planeV;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh4)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}
}
