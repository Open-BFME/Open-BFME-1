// Lane 01 scratch: VP6 probability-table loader.
// This file is intentionally outside Code/; root integrates only after probe
// proves the clean source and identity evidence.

int Rva009B4600DecodeBool(void *state, int probability);
int bfmeGoUSC(void *state, int count);
int Rva009B6950DecodeScale(unsigned char *ctx);
void Rva009B6740BuildTable(unsigned char *ctx);

extern unsigned char g_bfmeQuantRow[];

// ?Rva009B6A30LoadTables@@YAXPAE@Z
void Rva009B6A30LoadTables(unsigned char *ctx)
{
    void *state = ctx + 0x150;
    int plane = 0;
    struct Rows {
        unsigned char a[10];
        unsigned char b[10];
    };
    Rows *rows = (Rows *)(ctx + 0x737);

    do {
        if (Rva009B4600DecodeBool(state, 0xAE)) {
            int index = bfmeGoUSC(state, 4) + plane;
            ((unsigned char *)rows)[-1] = g_bfmeQuantRow[((index + index * 4) << 2) + 0];
            ((unsigned char *)rows)[-11] = g_bfmeQuantRow[((index + index * 4) << 2) + 1];
            ((unsigned char *)rows)[0] = g_bfmeQuantRow[((index + index * 4) << 2) + 2];
            ((unsigned char *)rows)[-10] = g_bfmeQuantRow[((index + index * 4) << 2) + 3];
            ((unsigned char *)rows)[1] = g_bfmeQuantRow[((index + index * 4) << 2) + 4];
            ((unsigned char *)rows)[-9] = g_bfmeQuantRow[((index + index * 4) << 2) + 5];
            ((unsigned char *)rows)[2] = g_bfmeQuantRow[((index + index * 4) << 2) + 6];
            ((unsigned char *)rows)[-8] = g_bfmeQuantRow[((index + index * 4) << 2) + 7];
            ((unsigned char *)rows)[3] = g_bfmeQuantRow[((index + index * 4) << 2) + 8];
            ((unsigned char *)rows)[-7] = g_bfmeQuantRow[((index + index * 4) << 2) + 9];
            ((unsigned char *)rows)[4] = g_bfmeQuantRow[((index + index * 4) << 2) + 10];
            ((unsigned char *)rows)[-6] = g_bfmeQuantRow[((index + index * 4) << 2) + 11];
            ((unsigned char *)rows)[5] = g_bfmeQuantRow[((index + index * 4) << 2) + 12];
            ((unsigned char *)rows)[-5] = g_bfmeQuantRow[((index + index * 4) << 2) + 13];
            ((unsigned char *)rows)[6] = g_bfmeQuantRow[((index + index * 4) << 2) + 14];
            ((unsigned char *)rows)[-4] = g_bfmeQuantRow[((index + index * 4) << 2) + 15];
            ((unsigned char *)rows)[7] = g_bfmeQuantRow[((index + index * 4) << 2) + 16];
            ((unsigned char *)rows)[-3] = g_bfmeQuantRow[((index + index * 4) << 2) + 17];
            ((unsigned char *)rows)[8] = g_bfmeQuantRow[((index + index * 4) << 2) + 18];
            ((unsigned char *)rows)[-2] = g_bfmeQuantRow[((index + index * 4) << 2) + 19];
        }
        if (Rva009B4600DecodeBool(state, 0xFE)) {
            for (int i = 0; i < 10; ++i) {
                unsigned char *dst = (unsigned char *)rows + 11;
                int v = Rva009B6950DecodeScale(ctx) + dst[i - 12];
                if (v < 0)
                    v = 0;
                else if (v > 255)
                    v = 255;
                dst[i - 12] = (unsigned char)v;

                v = Rva009B6950DecodeScale(ctx) + dst[i - 22];
                if (v < 0)
                    v = 0;
                else if (v > 255)
                    v = 255;
                dst[i - 22] = (unsigned char)v;
            }
        }
        plane += 16;
        ++rows;
    } while (plane < 48);

    Rva009B6740BuildTable(ctx);
}
