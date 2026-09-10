// ?Rva009B5200DecodeMotionVector@@YAXPAXPAFH@Z
// Retail RVA 0x009B5200, 539 bytes.  This is the VP6 motion-vector
// component decoder paired with the matched arithmetic decoder at 0x009B4600.
// The codec island and the typed callers of the adjacent block decoder prove
// the state layout and this cdecl ABI; the name is deliberately address
// qualified because no original source symbol is available.
//
// The long branch loads the next probability before combining the previous
// decoded bit. The Y output accumulates in its short destination; MSVC folds
// the two assignments into retail's one add and one short store.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern int Rva009B4600DecodeBool(void *coder, int prob);

void Rva009B5200DecodeMotionVector(void *ctxRaw, short *outMv, int mode)
{
	unsigned char *ctx = (unsigned char *)ctxRaw;
	int predX = 0;
	int predY = 0;

	if (mode == 2)
	{
		if (*(int *)(ctx + 0x44) < 2)
		{
			predX = *(short *)(ctx + 0x3c);
			predY = *(short *)(ctx + 0x3e);
		}
	}
	else
	{
		if (*(int *)(ctx + 0x50) < 2)
		{
			predX = *(short *)(ctx + 0x48);
			predY = *(short *)(ctx + 0x4a);
		}
	}

	void *coder = ctx + 0x150;

	for (unsigned int comp = 0; comp < 2; ++comp)
	{
		int delta;

		if (!Rva009B4600DecodeBool(coder, ctx[0x706 + comp]))
		{
			if (Rva009B4600DecodeBool(coder, ctx[comp * 7 + 0x708]))
			{
				unsigned char *base = ctx + comp * 7;
				if (Rva009B4600DecodeBool(coder, base[0x70c]))
				{
					delta = Rva009B4600DecodeBool(coder,
						ctx[(comp + 0x102) * 7]) + 6;
				}
				else
				{
					delta = Rva009B4600DecodeBool(coder, base[0x70d]) + 4;
				}
			}
			else
			{
				if (Rva009B4600DecodeBool(coder, (ctx + comp * 7)[0x709]))
				{
					delta = Rva009B4600DecodeBool(coder,
						(ctx + comp * 7)[0x70b]) + 2;
				}
				else
				{
					delta = Rva009B4600DecodeBool(coder, (ctx + comp * 7)[0x70a]);
				}
			}
		}
		else
		{
			delta = Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x71c]);
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x71d]) * 2;
			unsigned char prob2 = ctx[comp * 8 + 0x71e];
			delta += Rva009B4600DecodeBool(coder, prob2) * 4;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x723]) << 7;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x722]) << 6;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x721]) << 5;
			delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x720]) << 4;
			if (delta & 0xf0)
			{
				delta += Rva009B4600DecodeBool(coder, ctx[comp * 8 + 0x71f]) << 3;
			}
			else
			{
				delta += 8;
			}
		}

		if (delta && Rva009B4600DecodeBool(coder, ctx[0x704 + comp]))
		{
			delta = -delta;
		}

		if (comp)
		{
			outMv[1] = (short)predY;
			outMv[1] += (short)delta;
		}
		else
		{
			outMv[0] = (short)(delta + predX);
		}
	}
}
