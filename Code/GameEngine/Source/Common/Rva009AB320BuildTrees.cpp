// VP6 prefix-code table rebuild, retail [0x009AB320,0x009AB529).
// Called once per frame by the codec frame setup at 0x009ABFC0 when the
// context word at +0x4520 is set. For every coefficient model it expands the
// probability bytes into leaf weights (0x009AB0B0 / 0x009AB200), builds the
// tree (0x009B60E0), expands the six-bit lookup (0x009B62A0) and walks the
// tree for code words and lengths (0x009B6320). The offsets below are the
// retail lea displacements; the owner type is not proven, so every name keeps
// the address token.

struct Rva009B6320Node { unsigned m_first, m_second, m_unused; };

void Rva009AB0B0ExpandWeights(const unsigned char *input, unsigned int *output);
void __cdecl Rva009AB200BuildWeights(unsigned char *source, int *destination);
void Rva009B60E0BuildTree(Rva009B6320Node *nodes, unsigned int *weights, int count);
void Rva009B62A0ExpandTable(const unsigned *tree, unsigned short *output);
void Rva009B6320DecodeTree(Rva009B6320Node *nodes, int node, int *codes, unsigned char *lengths, int code, int depth);

struct Rva009AB320Context
{
	unsigned char m_pad0[0x3a0];
	unsigned char m_dcProbs[2][11];            // 0x3a0
	unsigned char m_acProbs[2][3][6][11];      // 0x3b6
	unsigned char m_pad542[0x560 - 0x542];
	unsigned char m_runProbs[2][14];           // 0x560
	unsigned char m_pad57c[0x948 - 0x57c];
	int m_dcCodes[2][12];                      // 0x948
	unsigned char m_dcLengths[2][12];          // 0x9a8
	unsigned int m_dcWeights[2][12];           // 0x9c0
	Rva009B6320Node m_dcTree[2][12];           // 0xa20
	int m_acCodes[3][2][6][12];                // 0xb40
	unsigned char m_acLengths[3][2][6][12];    // 0x1200
	unsigned int m_acWeights[3][2][6][12];     // 0x13b0
	Rva009B6320Node m_acTree[3][2][6][12];     // 0x1a70
	int m_runCodes[2][14];                     // 0x2eb0
	unsigned char m_runLengths[2][14];         // 0x2f20
	unsigned int m_runWeights[2][14];          // 0x2f3c
	Rva009B6320Node m_runTree[2][14];          // 0x2fac
	unsigned short m_dcTable[2][64];           // 0x30fc
	unsigned short m_acTable[3][2][6][64];     // 0x31fc
	unsigned short m_runTable[2][64];          // 0x43fc
};

void Rva009AB320BuildTrees(Rva009AB320Context *ctx)
{
	int plane;
	for (plane = 0; plane < 2; ++plane) {
		Rva009AB0B0ExpandWeights(ctx->m_dcProbs[plane], ctx->m_dcWeights[plane]);
		Rva009B60E0BuildTree(ctx->m_dcTree[plane], ctx->m_dcWeights[plane], 12);
		Rva009B62A0ExpandTable((const unsigned *)ctx->m_dcTree[plane], ctx->m_dcTable[plane]);
		Rva009B6320DecodeTree(ctx->m_dcTree[plane], 0, ctx->m_dcCodes[plane], ctx->m_dcLengths[plane], 0, 0);
	}

	for (plane = 0; plane < 2; ++plane) {
		Rva009AB200BuildWeights(ctx->m_runProbs[plane], (int *)ctx->m_runWeights[plane]);
		Rva009B60E0BuildTree(ctx->m_runTree[plane], ctx->m_runWeights[plane], 9);
		Rva009B62A0ExpandTable((const unsigned *)ctx->m_runTree[plane], ctx->m_runTable[plane]);
		Rva009B6320DecodeTree(ctx->m_runTree[plane], 0, ctx->m_runCodes[plane], ctx->m_runLengths[plane], 0, 0);
	}

	for (int kind = 0; kind < 3; ++kind) {
		for (plane = 0; plane < 2; ++plane) {
			for (int band = 0; band < 6; ++band) {
				Rva009AB0B0ExpandWeights(ctx->m_acProbs[plane][kind][band], ctx->m_acWeights[kind][plane][band]);
				Rva009B60E0BuildTree(ctx->m_acTree[kind][plane][band], ctx->m_acWeights[kind][plane][band], 12);
				Rva009B62A0ExpandTable((const unsigned *)ctx->m_acTree[kind][plane][band], ctx->m_acTable[kind][plane][band]);
				Rva009B6320DecodeTree(ctx->m_acTree[kind][plane][band], 0, ctx->m_acCodes[kind][plane][band], ctx->m_acLengths[kind][plane][band], 0, 0);
			}
		}
	}
}
