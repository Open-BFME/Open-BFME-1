// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// VP6 macroblock setup at retail RVA 0x009B5DB0: decodes the block flag at +0xc8, then
// points the four luma and two chroma 8x8 block decodes (0x009B58F0) at their plane offsets.
struct Rva009B4800State;
extern int Rva009B4800DecodeBool(Rva009B4800State *, int);

extern void d_009b58f0(void);
extern void d_009b5af0(void);

typedef void (__cdecl *Rva009B58F0Fn)(unsigned char *, int, unsigned int, int);
typedef void (__cdecl *Rva009B5AF0Fn)(unsigned char *, int, unsigned int);

void Rva009B5DB0Vp6DecodeBlock(unsigned char *ctx, int outer, unsigned int column)
{
	if (*(int *)(ctx + 0x1dc) != 0) {
		unsigned char probability = ctx[0x6e8];

		if (column > 3) {
			if (*(int *)(ctx + 0xc8) != 0) {
				probability -= probability >> 1;
			} else {
				probability += (unsigned char)((0x100 - probability) >> 1);
			}
		}

		*(int *)(ctx + 0xc8) = Rva009B4800DecodeBool(
			(Rva009B4800State *)(ctx + 0x150), probability);
	} else {
		*(int *)(ctx + 0xc8) = 0;
	}

	if (ctx[0x1ac] == 0) {
		*(int *)(ctx + 0x8) = 1;
	} else {
		((Rva009B5AF0Fn)d_009b5af0)(ctx, outer, column);
	}

	int width = *(int *)(ctx + 0x1b8);
	int stride;
	if (*(int *)(ctx + 0xc8) == 0) {
		stride = 8;
		*(int *)(ctx + 0x74) = width;
	} else {
		stride = 1;
		*(int *)(ctx + 0x74) = width * 2;
	}
	*(unsigned char **)(ctx + 0xc4) = ctx + 0x124;
	int row16 = outer * 16;
	*(int *)(ctx + 0x64) = row16;
	*(int *)(ctx + 0x88) = width;
	*(int *)(ctx + 0x78) = 0;
	int col16 = column * 16;
	int rowOffset = row16 * width + *(int *)(ctx + 0x21c) + col16;
	*(int *)(ctx + 0x70) = rowOffset;
	int col32 = column * 32;
	*(int *)(ctx + 0x7c) = 2;
	*(int *)(ctx + 0x80) = 3;
	*(int *)(ctx + 0x68) = col16;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + col32;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xcc;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, column, 0);

	*(int *)(ctx + 0x70) += 8;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + 0x10 + col32;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xcc;
	*(int *)(ctx + 0x68) += 8;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, column, 1);

	*(int *)(ctx + 0x70) = *(int *)(ctx + 0x1b8) * stride + rowOffset;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + col32;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xdc;
	*(int *)(ctx + 0x68) -= 8;
	*(int *)(ctx + 0x64) += stride;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, column, 2);

	*(int *)(ctx + 0x70) += 8;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + 0x10 + col32;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xdc;
	*(int *)(ctx + 0x68) += 8;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, column, 3);

	int height = *(int *)(ctx + 0x1bc);
	int row8 = outer * 8;
	*(int *)(ctx + 0x64) = row8;
	*(int *)(ctx + 0x88) = height;
	*(int *)(ctx + 0x74) = height;
	int col8 = column * 8;
	*(int *)(ctx + 0x68) = col8;
	*(int *)(ctx + 0x70) = row8 * height + *(int *)(ctx + 0x220) + col8;
	*(int *)(ctx + 0x7c) = 3;
	*(int *)(ctx + 0x80) = 7;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x110) + col16;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xec;
	*(unsigned char **)(ctx + 0xc4) = ctx + 0x12c;
	*(int *)(ctx + 0x78) = 1;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, column, 4);

	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x114) + col16;
	*(unsigned char **)(ctx + 0xc0) = ctx + 0xfc;
	*(int *)(ctx + 0x70) = *(int *)(ctx + 0x74) * *(int *)(ctx + 0x64)
		+ *(int *)(ctx + 0x224) + *(int *)(ctx + 0x68);
	*(unsigned char **)(ctx + 0xc4) = ctx + 0x134;
	*(int *)(ctx + 0x78) = 2;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, column, 5);
}
