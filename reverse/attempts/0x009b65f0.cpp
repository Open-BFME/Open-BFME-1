// ?Rva009B65F0LoadProbs@@YAXPAE@Z
// partial score=0.9 date=2026-09-02
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

int Rva009B4600DecodeBool(void *state, int probability);
int bfmeGoUSC(void *state, int count);

extern unsigned char g_bfmeProbUpdate[2][17];		// retail 0x01143348

void Rva009B65F0LoadProbs(unsigned char *ctx)
{
	int i = 0;
	unsigned j;
	void *state = ctx + 0x150;

	for (; i < 2; ++i) {
		if (Rva009B4600DecodeBool(state, g_bfmeProbUpdate[i][0])) {
			ctx[0x706 + i] = (unsigned char)(bfmeGoUSC(state, 7) << 1);
			if (ctx[0x706 + i] == 0)
				ctx[0x706 + i] = 1;
		}
		if (Rva009B4600DecodeBool(state, g_bfmeProbUpdate[i][1])) {
			ctx[0x704 + i] = (unsigned char)(bfmeGoUSC(state, 7) << 1);
			if (ctx[0x704 + i] == 0)
				ctx[0x704 + i] = 1;
		}
	}

	for (i = 0; i < 2; ++i) {
		const unsigned char *p = &g_bfmeProbUpdate[i][2];
		for (j = 0; j < 7; ++j) {
			if (Rva009B4600DecodeBool(state, *p++)) {
				ctx[0x708 + i * 7 + j] = (unsigned char)(bfmeGoUSC(state, 7) << 1);
				if (ctx[0x708 + i * 7 + j] == 0)
					ctx[0x708 + i * 7 + j] = 1;
			}
		}
	}

	for (i = 0; i < 2; ++i) {
		const unsigned char *p = &g_bfmeProbUpdate[i][9];
		for (j = 0; j < 8; ++j) {
			if (Rva009B4600DecodeBool(state, *p++)) {
				ctx[0x71C + i * 8 + j] = (unsigned char)(bfmeGoUSC(state, 7) << 1);
				if (ctx[0x71C + i * 8 + j] == 0)
					ctx[0x71C + i * 8 + j] = 1;
			}
		}
	}
}
