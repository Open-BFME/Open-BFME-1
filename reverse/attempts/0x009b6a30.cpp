// ?d_009b6a30@@YAXXZ
// partial score=0.72 date=2026-09-02
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

int Rva009B4600DecodeBool(void *state, int probability);
int bfmeGoUSC(void *state, int count);
int Rva009B6950DecodeScale(unsigned char *ctx);
void Rva009B6740Finish(unsigned char *ctx);

extern unsigned char g_bfmeQuantRow[];		// retail 0x01143398

// ?Rva009B6A30LoadTables@@YAXPAE@Z
void Rva009B6A30LoadTables(unsigned char *ctx)
{
	unsigned char *dst = ctx + 0x737;
	int plane = 0;

	do {
		void *state = ctx + 0x150;
		if (Rva009B4600DecodeBool(state, 0xAE)) {
			int index = bfmeGoUSC(state, 4) + plane;
			const unsigned char *src = g_bfmeQuantRow + ((index + index * 4) << 2);
			dst[-1] = src[0];
			dst[-11] = src[1];
			dst[0] = src[2];
			dst[-10] = src[3];
			dst[1] = src[4];
			dst[-9] = src[5];
			dst[2] = src[6];
			dst[-8] = src[7];
			dst[3] = src[8];
			dst[-7] = src[9];
			dst[4] = src[10];
			dst[-6] = src[11];
			dst[5] = src[12];
			dst[-5] = src[13];
			dst[6] = src[14];
			dst[-4] = src[15];
			dst[7] = src[16];
			dst[-3] = src[17];
			dst[8] = src[18];
			dst[-2] = src[19];
		}
		if (Rva009B4600DecodeBool(state, 0xFE)) {
			int i = 0;
			do {
				int v = Rva009B6950DecodeScale(ctx) + dst[i - 1];
				if (v < 0)
					v = 0;
				else if (v > 255)
					v = 255;
				dst[i - 1] = (unsigned char)v;
				v = Rva009B6950DecodeScale(ctx) + dst[i - 11];
				if (v < 0)
					v = 0;
				else if (v > 255)
					v = 255;
				dst[i - 11] = (unsigned char)v;
				++i;
			} while (i < 10);
		}
		plane += 16;
		dst += 20;
	} while (plane < 48);

	Rva009B6740Finish(ctx);
}
