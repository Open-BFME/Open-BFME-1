// ?Rva009B5200DecodeMotionVector@@YAXPAXPAFH@Z
// partial score=0.9 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// VP6-style motion-vector component decoder: for each of the X/Y
// components, decodes either a short (3-node) tree yielding 0-7 or a long
// (7-8 bit) magnitude via a shared binary arithmetic decoder
// (Rva009B4600DecodeBool, landed sibling at 0x009B4600), decodes an
// optional sign bit, adds a per-component predictor selected by mode, and
// stores the signed 16-bit result into outMv[0] (x) / outMv[1] (y).
// Predictor A (ctx+0x3c/0x3e, valid flag ctx+0x44) is used when mode==2;
// predictor B (ctx+0x48/0x4a, valid flag ctx+0x50) otherwise. The coder
// state lives at ctx+0x150. Probability bytes: sign[2] at 0x704, tree-
// selector[2] at 0x706, short-tree[2][7] at 0x708 (component stride 7,
// the class-6/7 leaf read through a distinct (comp+0x102)*7 index --
// retail keeps that one out of the shared base register), long-tree[2][8]
// at 0x71c (component stride 8). Address-derived name; no ghidra
// boundary/identity beyond the byte-proven extent.

extern int Rva009B4600DecodeBool(void *coder, int prob);

void Rva009B5200DecodeMotionVector(void *ctxRaw, short *outMv, int mode)
{
	unsigned char *ctx = (unsigned char *)ctxRaw;
	int predX = 0;
	int predY = 0;

	if (mode == 2) {
		if (*(int *)(ctx + 0x44) < 2) {
			predX = *(short *)(ctx + 0x3c);
			predY = *(short *)(ctx + 0x3e);
		}
	} else {
		if (*(int *)(ctx + 0x50) < 2) {
			predX = *(short *)(ctx + 0x48);
			predY = *(short *)(ctx + 0x4a);
		}
	}

	void *coder = ctx + 0x150;

	for (int comp = 0; comp < 2; ++comp) {
		int delta;

		if (!Rva009B4600DecodeBool(coder, ctx[0x706 + comp])) {
			unsigned char *base = ctx + comp * 7;
			if (Rva009B4600DecodeBool(coder, base[0x708])) {
				if (Rva009B4600DecodeBool(coder, base[0x70c])) {
					delta = Rva009B4600DecodeBool(coder, ctx[(comp + 0x102) * 7]) + 6;
				} else {
					delta = Rva009B4600DecodeBool(coder, base[0x70d]) + 4;
				}
			} else {
				if (Rva009B4600DecodeBool(coder, base[0x709])) {
					delta = Rva009B4600DecodeBool(coder, base[0x70b]) + 2;
				} else {
					delta = Rva009B4600DecodeBool(coder, base[0x70a]);
				}
			}
		} else {
			delta = Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x71c]);
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x71d]) * 2;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x71e]) * 4;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x723]) << 7;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x722]) << 6;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x721]) << 5;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x720]) << 4;
			if (delta & 0xf0) {
				delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x71f]) << 3;
			} else {
				delta += 8;
			}
		}

		if (delta && Rva009B4600DecodeBool(coder, ctx[0x704 + comp])) {
			delta = -delta;
		}

		if (comp) {
			outMv[1] = (short)(delta + predY);
		} else {
			outMv[0] = (short)(delta + predX);
		}
	}
}
