// VP6 tree-probability update reader, retail [0x009AB530,0x009AB75C).
// The only caller, the exact frame setup at 0x009ABFC0, passes the context
// and its +0x1ac frame byte (zero on the default-table path). Every
// probability byte is refreshed from the bool decoder at +0x150 against the
// update tables at 0x011430B0..0x011432CC; on the default-table path a byte
// with no update takes the last decoded value of its column instead. The
// scan-order bytes at +0x63c are rebuilt through 0x009AAFE0 when updated, and
// the derived table builder at 0x009B64A0 runs last. The owner type is not
// proven, so every name keeps the address token.

extern "C" void * __cdecl memcpy(void *, const void *, unsigned int);
extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memcpy, memset)

struct Rva009AAFE0Context;
struct Rva009B4800State;

int Rva009B4800DecodeBool(Rva009B4800State *state, int probability);
int bfmeGoUSC(void *state, int count);
void __cdecl Rva009AAFE0BuildTable(Rva009AAFE0Context *self, const unsigned char *source);
void Rva009B64A0BuildTone(unsigned char *ctx);

extern unsigned char g_rva011430b0Update[2][11];
extern unsigned char g_rva011430c8OrderUpdate[64];
extern unsigned char g_rva01143108RunUpdate[2][14];
extern unsigned char g_rva01143124RunDefaults[2][14];
extern unsigned char g_rva01143140Update[3][2][6][11];

struct Rva009AB530Context
{
	unsigned char m_pad0[0x150];
	unsigned char m_state[0x1ac - 0x150];       // 0x150, bool decoder state
	unsigned char m_pad1ac[0x3a0 - 0x1ac];
	unsigned char m_probs3a0[2][11];            // 0x3a0
	unsigned char m_probs3b6[2][3][6][11];      // 0x3b6
	unsigned char m_pad542[0x560 - 0x542];
	unsigned char m_runProbs[2][14];            // 0x560
	unsigned char m_pad57c[0x63c - 0x57c];
	unsigned char m_scan[64];                   // 0x63c
};

static unsigned char Rva009AB530ReadProbability(Rva009AB530Context *ctx)
{
	unsigned char value = (unsigned char)(bfmeGoUSC(ctx->m_state, 7) << 1);
	return value + !value;
}

void Rva009AB530UpdateTreeProbs(unsigned char *base, unsigned char frameType)
{
	Rva009AB530Context *ctx = (Rva009AB530Context *)base;
	unsigned char last[11];
	unsigned int plane;
	unsigned int node;

	memset(last, 0x80, sizeof(last));

	for (plane = 0; plane < 2; ++plane) {
		for (node = 0; node < 11; ++node) {
			if (Rva009B4800DecodeBool((Rva009B4800State *)ctx->m_state, g_rva011430b0Update[plane][node])) {
				last[node] = Rva009AB530ReadProbability(ctx);
				ctx->m_probs3a0[plane][node] = last[node];
			} else if (!frameType) {
				ctx->m_probs3a0[plane][node] = last[node];
			}
		}
	}

	if (!frameType)
		memcpy(ctx->m_runProbs, g_rva01143124RunDefaults, sizeof(ctx->m_runProbs));

	if (Rva009B4800DecodeBool((Rva009B4800State *)ctx->m_state, 0x80)) {
		for (unsigned int position = 1; position < 64; ++position) {
			if (Rva009B4800DecodeBool((Rva009B4800State *)ctx->m_state, g_rva011430c8OrderUpdate[position]))
				ctx->m_scan[position] = (unsigned char)bfmeGoUSC(ctx->m_state, 4);
		}
		Rva009AAFE0BuildTable((Rva009AAFE0Context *)ctx, ctx->m_scan);
	}

	for (plane = 0; plane < 2; ++plane) {
		for (node = 0; node < 14; ++node) {
			if (Rva009B4800DecodeBool((Rva009B4800State *)ctx->m_state, g_rva01143108RunUpdate[plane][node]))
				ctx->m_runProbs[plane][node] = Rva009AB530ReadProbability(ctx);
		}
	}

	for (int kind = 0; kind < 3; ++kind) {
		for (plane = 0; plane < 2; ++plane) {
			for (unsigned int band = 0; band < 6; ++band) {
				for (node = 0; node < 11; ++node) {
					if (Rva009B4800DecodeBool((Rva009B4800State *)ctx->m_state, g_rva01143140Update[kind][plane][band][node])) {
						last[node] = Rva009AB530ReadProbability(ctx);
						ctx->m_probs3b6[plane][kind][band][node] = last[node];
					} else if (!frameType) {
						ctx->m_probs3b6[plane][kind][band][node] = last[node];
					}
				}
			}
		}
	}

	Rva009B64A0BuildTone(base);
}
