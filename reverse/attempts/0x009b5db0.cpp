// ?Rva009B5DB0Vp6DecodeBlock@@YAXPAEHHHHHHHHHHHH@Z
// partial score=0.82 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Address-derived VP6 block reconstruction helper at retail RVA 0x009B5DB0.
// The surrounding 0x009AF200 codec island identifies the format, while the
// direct call from the VP6 frame decoder at 0x009ABFC0 establishes the first
// three arguments.  The extra stack values are deliberately retained in the
// ABI view: the retail caller leaves its frame arguments in those slots and
// this helper consumes them when forming the later block addresses.

struct Rva009B4800State;
extern int Rva009B4800DecodeBool(Rva009B4800State *, int);

extern void d_009b58f0(void);
extern void d_009b5af0(void);

typedef void (__cdecl *Rva009B58F0Fn)(unsigned char *, int, int, int);
typedef void (__cdecl *Rva009B5AF0Fn)(unsigned char *, int, int);

void Rva009B5DB0Vp6DecodeBlock(unsigned char *ctx,
    int outer, int inner, int unused4, int callerBase,
    int unused6, int unused7, int unused8, int base0,
    int base1, int base2, int unused12, int base3)
{
    int zero = 0;

	if (*(int *)(ctx + 0x1dc) != zero) {
		unsigned char probability = ctx[0x6e8];

		if (inner > 3) {
			if (*(int *)(ctx + 0xc8) != zero) {
				probability -= probability >> 1;
			} else {
				probability += (unsigned char)((0x100 - probability) >> 1);
			}
		}

		*(int *)(ctx + 0xc8) = Rva009B4800DecodeBool(
			(Rva009B4800State *)(ctx + 0x150), probability);
	} else {
		*(int *)(ctx + 0xc8) = zero;
	}

	if (ctx[0x1ac] == 0) {
		*(int *)(ctx + 0x8) = 1;
	} else {
		((Rva009B5AF0Fn)d_009b5af0)(ctx, outer, inner);
	}

	int width = *(int *)(ctx + 0x1b8);
	if (*(int *)(ctx + 0xc8) == zero) {
		*(int *)(ctx + 0x74) = width;
		inner = 8;
	} else {
		*(int *)(ctx + 0x74) = width + width;
		inner = 1;
	}

	*(unsigned char **)(ctx + 0xc4) = ctx + 0x124;
	int rowOffset = outer << 4;
	*(int *)(ctx + 0x64) = rowOffset;
	rowOffset *= width;
	rowOffset += *(int *)(ctx + 0x21c);
	int colOffset = inner << 4;
	rowOffset += colOffset;
	*(int *)(ctx + 0x70) = rowOffset;
	*(int *)(ctx + 0x68) = colOffset;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + (inner << 5);
	*(int *)(ctx + 0x7c) = 2;
	*(int *)(ctx + 0x80) = 3;
	*(int *)(ctx + 0xc0) = (int)(ctx + 0xcc);
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, inner, 0);

	*(int *)(ctx + 0x70) += 8;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + callerBase + 0x10;
	*(int *)(ctx + 0x68) += 8;
	*(int *)(ctx + 0xc0) = (int)(ctx + 0xcc);
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, inner, 1);

	*(int *)(ctx + 0x70) = *(int *)(ctx + 0x1b8) * base1 + base0;
	*(int *)(ctx + 0x70) += *(int *)(ctx + 0x68);
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + base2;
	*(int *)(ctx + 0xc0) = (int)(ctx + 0xdc);
	*(int *)(ctx + 0x64) += base1;
	*(int *)(ctx + 0x68) -= 8;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, inner, 2);

	*(int *)(ctx + 0x70) += 8;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x10c) + base3 + 0x10;
	*(int *)(ctx + 0xc0) = (int)(ctx + 0xdc);
	*(int *)(ctx + 0x68) += 8;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, inner, 3);

	int height = *(int *)(ctx + 0x1bc);
	int blockOffset = outer << 3;
	*(int *)(ctx + 0x64) = blockOffset;
	blockOffset *= height;
	blockOffset += *(int *)(ctx + 0x220);
	colOffset = inner << 3;
	blockOffset += colOffset;
	*(int *)(ctx + 0x70) = blockOffset;
	*(int *)(ctx + 0x74) = height;
	*(int *)(ctx + 0x68) = colOffset;
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x110) + inner;
	*(int *)(ctx + 0xc0) = (int)(ctx + 0xec);
	*(int *)(ctx + 0xc4) = (int)(ctx + 0x12c);
	*(int *)(ctx + 0x7c) = 3;
	*(int *)(ctx + 0x80) = 7;
	*(int *)(ctx + 0x78) = 1;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, inner, 4);

	*(int *)(ctx + 0x70) = *(int *)(ctx + 0x74) * *(int *)(ctx + 0x64);
	*(int *)(ctx + 0xbc) = *(int *)(ctx + 0x114) + inner;
	*(int *)(ctx + 0xc0) = (int)(ctx + 0xfc);
	*(int *)(ctx + 0x70) += *(int *)(ctx + 0x224);
	*(int *)(ctx + 0x70) += *(int *)(ctx + 0x68);
	*(int *)(ctx + 0xc4) = (int)(ctx + 0x134);
	*(int *)(ctx + 0x78) = 2;
	((Rva009B58F0Fn)d_009b58f0)(ctx, outer, inner, 5);
}
