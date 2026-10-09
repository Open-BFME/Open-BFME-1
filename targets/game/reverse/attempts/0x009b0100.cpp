// _Rva009B0100Vp6BlockFilter
// partial score=0.2685 date=2026-10-09
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B0100Context
{
	int m_pad00;
	unsigned char m_pad04[8];
	int m_mode;
	int m_baseOffset;
	int m_arg4;
	unsigned char *m_flags;
	int m_flagStride;
	int m_flagMask;
	unsigned char m_pad24[0x78 - 0x24];
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	int m_extra84;
	int m_extra88;
	int m_pad8C;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
	unsigned int m_strideUV;
};

struct Rva009AF530Context;
typedef int *(__cdecl *Rva009B0100Setup)(Rva009AF530Context *, int);
typedef void (__cdecl *Rva009B0100Filter)(
	void *, unsigned char *, int, void *);

extern int g_rva012D7B58[];
extern Rva009B0100Setup g_rva01356e68SetupBounding;
extern Rva009B0100Filter g_rva01356E9C;
extern Rva009B0100Filter g_rva01356EBC;

struct Rva009B0100Dimensions
{
	int planeWidth;
	int planeHeight;
};

extern "C" void __cdecl Rva009B0100Vp6BlockFilter(
	Rva009B0100Context *ctx, int mode, int baseOffset, int arg4,
	unsigned char *flags, int flagStride, int flagMask)
{
	ctx->m_baseOffset = baseOffset;
	Rva009B0100Dimensions dimensions;
	dimensions.planeHeight = ctx->m_height;
	dimensions.planeWidth = ctx->m_width;
	int plane;
	unsigned char *base = 0;
	int stride = 0;
	register int planeOffset = 0;
	int row;
	int lineWidth = 0;
	int count;
	int edge;
	int rows;
	int current;
	int next;
	int columns;
	unsigned char *cursor;
	ctx->m_arg4 = arg4;
	ctx->m_flags = flags;
	ctx->m_mode = mode;
	ctx->m_flagStride = flagStride;
	ctx->m_flagMask = flagMask;

	int setupValue = g_rva012D7B58[mode];
	if (setupValue == planeOffset)
		return;

	void *work = g_rva01356e68SetupBounding(reinterpret_cast<Rva009AF530Context *>(ctx), setupValue);
	plane = 0;

	do
	{
		switch (plane)
		{
		case 0:
			planeOffset = 0;
			lineWidth = dimensions.planeWidth = ctx->m_width;
			dimensions.planeHeight = ctx->m_height;
			stride = ctx->m_strideY;
			base = ctx->m_planeY + ctx->m_baseOffset;
			break;
		case 1:
			planeOffset = ctx->m_extra84;
			lineWidth = dimensions.planeWidth = ctx->m_width >> 1;
			dimensions.planeHeight = ctx->m_height >> 1;
			stride = ctx->m_strideUV;
			base = ctx->m_planeU + ctx->m_baseOffset;
			break;
		case 2:
			planeOffset = ctx->m_extra84 + ctx->m_extra88;
			lineWidth = dimensions.planeWidth = ctx->m_width >> 1;
			dimensions.planeHeight = ctx->m_height >> 1;
			stride = ctx->m_strideUV;
			base = ctx->m_planeV + ctx->m_baseOffset;
			break;
		}

		row = planeOffset;
		if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
		{
			if ((ctx->m_flags[(row + 1) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356E9C(ctx, base + 6, stride, work);
			if ((ctx->m_flags[(lineWidth + row) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356EBC(ctx, base + stride * 8, stride, work);
		}

		++row;
		int column = 1;
		for (column = 1; column < dimensions.planeWidth - 1; ++column)
		{
			cursor = base + column * 8 + 6;
			if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
			{
				g_rva01356E9C(ctx, cursor - 8, stride, work);
				if ((ctx->m_flags[(row + 1) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
					g_rva01356E9C(ctx, cursor, stride, work);
				if ((ctx->m_flags[(row + lineWidth) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
					g_rva01356EBC(ctx, cursor + stride * 8 - 6, stride, work);
			}
			++row;
		}

		if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
		{
			g_rva01356E9C(ctx, base + column * 8 - 2, stride, work);
			if ((ctx->m_flags[(lineWidth + row) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356EBC(ctx, base + column * 8 + stride * 8, stride, work);
		}

		base += stride * 8;
		++row;
		if (dimensions.planeHeight - 1 > 1)
		{
			rows = dimensions.planeHeight - 2;
			do
			{
				if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
				{
					g_rva01356EBC(ctx, base, stride, work);
					if ((ctx->m_flags[(row + 1) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
						g_rva01356E9C(ctx, base + 6, stride, work);
					if ((ctx->m_flags[(row + lineWidth) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
						g_rva01356EBC(ctx, base + stride * 8, stride, work);
				}
				++row;
				column = 1;
				for (column = 1; column < dimensions.planeWidth - 1; ++column)
				{
					cursor = base + column * 8 + 6;
					if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
					{
						g_rva01356E9C(ctx, cursor - 8, stride, work);
						g_rva01356EBC(ctx, cursor - 6, stride, work);
						if ((ctx->m_flags[(row + 1) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
							g_rva01356E9C(ctx, cursor, stride, work);
						if ((ctx->m_flags[(row + lineWidth) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
							g_rva01356EBC(ctx, cursor + stride * 8 - 6, stride, work);
					}
					++row;
				}

				if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
				{
					unsigned char *last = base + column * 8;
					g_rva01356E9C(ctx, last - 2, stride, work);
					g_rva01356EBC(ctx, last, stride, work);
					if ((ctx->m_flags[(row + lineWidth) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
						g_rva01356EBC(ctx, base + column * 8 + stride * 8, stride, work);
				}
				base += stride * 8;
				++row;
				--rows;
			}
			while (rows != 0);
		}

		++plane;
	}
	while (plane < 3);

	if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
	{
		g_rva01356EBC(ctx, base, stride, work);
		if ((ctx->m_flags[(row + 1) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
			g_rva01356E9C(ctx, base + 6, stride, work);
	}

	++row;
	int column = 1;
	for (column = 1; column < dimensions.planeWidth - 1; ++column)
	{
		cursor = base + column * 8 + 6;
		if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
		{
			g_rva01356E9C(ctx, cursor - 8, stride, work);
			g_rva01356EBC(ctx, cursor - 6, stride, work);
			if ((ctx->m_flags[(row + 1) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356E9C(ctx, cursor, stride, work);
		}
		++row;
	}

	if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
	{
		unsigned char *last = base + column * 8;
		g_rva01356E9C(ctx, last - 2, stride, work);
		g_rva01356EBC(ctx, last, stride, work);
	}
}
