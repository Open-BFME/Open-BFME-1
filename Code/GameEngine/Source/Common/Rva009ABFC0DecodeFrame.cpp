// VP6 per-frame setup and block loop, retail [0x009ABFC0,0x009AC231).
// Byte +0x1ac zero takes the default-table branch: fixed tables are copied
// into the context, the order table at +0x63c is rebuilt (0x009AAFE0).
// Otherwise the probability loaders at 0x009B6A30 and 0x009B65F0 read the
// updates from the bool decoder at +0x150. Both branches then read the
// coefficient probabilities (0x009AB530), rebuild the prefix-code tables when
// +0x4520 is set (0x009AB320), reset the block state (0x009AB7F0) and decode
// every inner block (0x009B5DB0). The owner type is not proven, so every
// name keeps the address token.

extern "C" void * __cdecl memcpy(void *, const void *, unsigned int);
extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memcpy, memset)

struct Rva009AAFE0Context;
struct Rva009AB320Context;
struct Rva009AB760Context;
struct Rva009AB7F0Context;

void Rva009B6A30LoadTables(unsigned char *ctx);
void Rva009B65F0UpdateProbs(unsigned char *ctx, unsigned char frameType);
void __cdecl Rva009AAFE0BuildTable(Rva009AAFE0Context *self, const unsigned char *source);
void Rva009AB530UpdateTreeProbs(unsigned char *ctx, unsigned char frameType);
void Rva009AB320BuildTrees(Rva009AB320Context *ctx);
int bfmeGoUSC(void *state, int count);
void Rva009AB7F0Reset(Rva009AB7F0Context *self);
void Rva009AB760Initialize(Rva009AB760Context *self);
void Rva009B5DB0Vp6DecodeBlock(unsigned char *ctx, int outer, unsigned int column);

extern unsigned char g_rva01143758Table[80];
extern unsigned char g_rva0114338cPair[2];
extern unsigned char g_rva0114336cRows[14];
extern unsigned char g_rva01143390Pair[2];
extern unsigned char g_rva0114337cRows[16];
extern unsigned char g_rva01142b60Order[64];
extern unsigned char g_rva01142b20Order[64];

struct Rva009ABFC0Source
{
	unsigned char m_pad0[0x13c];
	int *m_values;                           // 0x13c
};

struct Rva009ABFC0Context
{
	unsigned char m_pad0[0x4];
	unsigned char *m_blockState;             // 0x004
	unsigned char m_pad8[0x13c - 0x8];
	Rva009ABFC0Source *m_source;             // 0x13c
	unsigned char m_pad140[0x150 - 0x140];
	unsigned char m_bits[0x1ac - 0x150];     // 0x150
	unsigned char m_frameType;               // 0x1ac
	unsigned char m_pad1ad[0x1dc - 0x1ad];
	int m_mode;                              // 0x1dc
	unsigned char m_pad1e0[0x228 - 0x1e0];
	unsigned int m_fillCount;                // 0x228
	unsigned int m_rows;                     // 0x22c
	unsigned int m_columns;                  // 0x230
	unsigned char m_pad234[0x39c - 0x234];
	int m_word39c;                           // 0x39c
	unsigned char m_pad3a0[0x57c - 0x3a0];
	unsigned char m_mapped[64];              // 0x57c
	unsigned char m_order[64];               // 0x5bc
	unsigned char m_pad5fc[0x63c - 0x5fc];
	unsigned char m_scan[64];                // 0x63c
	unsigned char m_probs67c[11];            // 0x67c
	unsigned char m_probs687[11];            // 0x687
	unsigned char m_pad692[0x6e8 - 0x692];
	int m_probability;                       // 0x6e8
	unsigned char m_pad6ec[0x6f0 - 0x6ec];
	unsigned char *m_fill;                   // 0x6f0
	unsigned char m_pad6f4[0x704 - 0x6f4];
	unsigned char m_pair704[2];              // 0x704
	unsigned char m_pair706[2];              // 0x706
	unsigned char m_rows708[14];             // 0x708
	unsigned char m_pad716[0x71c - 0x716];
	unsigned char m_rows71c[16];             // 0x71c
	unsigned char m_table72c[80];            // 0x72c
	unsigned char m_pad77c[0x4520 - 0x77c];
	int m_rebuildTrees;                      // 0x4520
	int m_counts[4];                         // 0x4524
};

void Rva009ABFC0DecodeFrame(Rva009ABFC0Context *ctx)
{
	unsigned int rows = ctx->m_rows;
	unsigned int columns = ctx->m_columns;

	if (ctx->m_frameType != 0) {
		Rva009B6A30LoadTables((unsigned char *)ctx);
		Rva009B65F0UpdateProbs((unsigned char *)ctx, ctx->m_frameType);
		ctx->m_word39c = 0;
	} else {
		memcpy(ctx->m_table72c, g_rva01143758Table, sizeof(ctx->m_table72c));
		memcpy(ctx->m_pair706, g_rva0114338cPair, sizeof(ctx->m_pair706));
		memcpy(ctx->m_rows708, g_rva0114336cRows, sizeof(ctx->m_rows708));
		memcpy(ctx->m_pair704, g_rva01143390Pair, sizeof(ctx->m_pair704));
		memcpy(ctx->m_rows71c, g_rva0114337cRows, sizeof(ctx->m_rows71c));
		memset(ctx->m_probs67c, 0x80, sizeof(ctx->m_probs67c));
		memset(ctx->m_probs687, 0x80, sizeof(ctx->m_probs687));
		memset(ctx->m_fill, 1, ctx->m_fillCount);
		if (ctx->m_mode == 1)
			memcpy(ctx->m_scan, g_rva01142b60Order, sizeof(ctx->m_scan));
		else
			memcpy(ctx->m_scan, g_rva01142b20Order, sizeof(ctx->m_scan));
		Rva009AAFE0BuildTable((Rva009AAFE0Context *)ctx, ctx->m_scan);
	}

	Rva009AB530UpdateTreeProbs((unsigned char *)ctx, ctx->m_frameType);

	for (int i = 0; i < 64; ++i)
		ctx->m_mapped[i] = (unsigned char)ctx->m_source->m_values[ctx->m_order[i]];

	if (ctx->m_rebuildTrees != 0)
		Rva009AB320BuildTrees((Rva009AB320Context *)ctx);

	if (ctx->m_mode == 1)
		ctx->m_probability = (unsigned char)bfmeGoUSC(ctx->m_bits, 8);

	Rva009AB7F0Reset((Rva009AB7F0Context *)ctx);
	memset(ctx->m_blockState, 0, 0x300);
	ctx->m_counts[0] = 0;
	ctx->m_counts[1] = 0;
	ctx->m_counts[2] = 0;
	ctx->m_counts[3] = 0;

	for (unsigned int row = 3; row < rows - 3; ++row) {
		Rva009AB760Initialize((Rva009AB760Context *)ctx);
		for (unsigned int column = 3; column < columns - 3; ++column)
			Rva009B5DB0Vp6DecodeBlock((unsigned char *)ctx, row, column);
	}
}
