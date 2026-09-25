// ?d_009b0100@@YAXXZ
// partial score=0.11 date=2026-09-25
// VP6 three-plane edge-filter driver at retail RVA 0x009B0100.
// The owner remains address-derived; the context is witnessed by adjacent plane drivers.
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

typedef int *(__cdecl *Rva009B0100Setup)(Rva009B0100Context *, int);
typedef void (__cdecl *Rva009B0100Filter)(
	Rva009B0100Context *, unsigned char *, int, const int *);

extern int g_rva012D7B58[];
extern Rva009B0100Setup g_rva01356E68;
extern Rva009B0100Filter g_rva01356E9C;
extern Rva009B0100Filter g_rva01356EBC;

extern "C" void __cdecl Rva009B0100Vp6BlockFilter(
	Rva009B0100Context *ctx, int mode, int baseOffset, int arg4,
	unsigned char *flags, int flagStride, int flagMask)
{
	ctx->m_baseOffset = baseOffset;
	volatile unsigned int secondCount = ctx->m_height;
	volatile unsigned int firstCount = ctx->m_width;
	int plane;
	unsigned char *base;
	int stride;
	register int planeOffset = 0;
	unsigned int planeWidth;
	unsigned int planeHeight;
	int row;
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

	int *work = g_rva01356E68(ctx, setupValue);
	plane = 0;

	do
	{
		switch (plane)
		{
		case 0:
			planeOffset = 0;
			planeWidth = firstCount;
			planeHeight = secondCount;
			stride = ctx->m_strideY;
			base = ctx->m_planeY;
			break;
		case 1:
			planeOffset = ctx->m_extra84;
			planeWidth = firstCount >> 1;
			planeHeight = secondCount >> 1;
			stride = ctx->m_strideUV;
			base = ctx->m_planeU;
			break;
		case 2:
			planeOffset = ctx->m_extra84 + ctx->m_extra88;
			planeWidth = firstCount >> 1;
			planeHeight = secondCount >> 1;
			stride = ctx->m_strideUV;
			base = ctx->m_planeV;
			break;
		}
		base += ctx->m_baseOffset;

		row = planeOffset;
		if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
		{
			if ((ctx->m_flags[(row + 1) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356E9C(ctx, base + 6, stride, work);
		}
		if ((ctx->m_flags[(planeWidth + row) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
			g_rva01356EBC(ctx, base + stride * 8, stride, work);

		++row;
		if (planeWidth > 2)
		{
			count = planeWidth - 2;
			edge = planeWidth + row;
			cursor = base + 14;
			do
			{
				if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
				{
					g_rva01356E9C(ctx, cursor - 8, stride, work);
					if ((ctx->m_flags[edge * ctx->m_flagStride] & ctx->m_flagMask) == 0)
						g_rva01356E9C(ctx, cursor, stride, work);
				}
				if ((ctx->m_flags[edge * ctx->m_flagStride] & ctx->m_flagMask) == 0)
					g_rva01356EBC(ctx, cursor + stride * 8 - 6, stride, work);
				cursor += 8;
				++row;
				++edge;
				--count;
			}
			while (count != 0);
		}

		if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
		{
			g_rva01356E9C(ctx, base + (planeWidth - 1) * 8 - 2, stride, work);
			if ((ctx->m_flags[(planeWidth + row) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356EBC(ctx,
					base + (planeWidth - 1) * 8 + stride * 8, stride, work);
		}

		base += stride * 8;
		++row;
		if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
		{
			g_rva01356EBC(ctx, base, stride, work);
			if ((ctx->m_flags[(row + 1) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356E9C(ctx, base + 6, stride, work);
			if ((ctx->m_flags[(row + planeWidth) * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356EBC(ctx, base + stride * 8, stride, work);
		}
		++row;
		if (planeHeight > 2)
		{
			rows = planeHeight - 2;
			do
			{
				current = row;
				next = planeWidth + current;
				cursor = base + 14;
				columns = planeWidth - 2;
				do
				{
					if ((ctx->m_flags[current * ctx->m_flagStride] & ctx->m_flagMask) != 0)
					{
						g_rva01356E9C(ctx, cursor - 8, stride, work);
						g_rva01356EBC(ctx, cursor - 6, stride, work);
						if ((ctx->m_flags[next * ctx->m_flagStride] & ctx->m_flagMask) == 0)
							g_rva01356E9C(ctx, cursor, stride, work);
					}
					if ((ctx->m_flags[next * ctx->m_flagStride] & ctx->m_flagMask) == 0)
						g_rva01356EBC(ctx, cursor + stride * 8 - 6, stride, work);
					cursor += 8;
					++current;
					++next;
					--columns;
				}
				while (columns != 0);

				if ((ctx->m_flags[current * ctx->m_flagStride] & ctx->m_flagMask) != 0)
				{
					g_rva01356E9C(ctx,
						base + (planeWidth - 1) * 8 - 2, stride, work);
					g_rva01356EBC(ctx,
						base + (planeWidth - 1) * 8, stride, work);
				}
				if ((ctx->m_flags[next * ctx->m_flagStride] & ctx->m_flagMask) == 0)
					g_rva01356EBC(ctx,
						base + (planeWidth - 1) * 8 + stride * 8, stride, work);
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
	if (planeWidth > 2)
	{
		count = planeWidth - 2;
		next = planeWidth + row;
		cursor = base + 14;
		do
		{
			if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
			{
				g_rva01356E9C(ctx, cursor - 8, stride, work);
				g_rva01356EBC(ctx, cursor - 6, stride, work);
			}
			if ((ctx->m_flags[next * ctx->m_flagStride] & ctx->m_flagMask) == 0)
				g_rva01356E9C(ctx, cursor, stride, work);
			cursor += 8;
			++row;
			++next;
			--count;
		}
		while (count != 0);
	}

	if ((ctx->m_flags[row * ctx->m_flagStride] & ctx->m_flagMask) != 0)
	{
		g_rva01356E9C(ctx,
			base + (planeWidth - 1) * 8 - 2, stride, work);
		g_rva01356EBC(ctx,
			base + (planeWidth - 1) * 8, stride, work);
	}
}
