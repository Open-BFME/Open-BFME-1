// ?dup_009b2530@@YAXPAURva009B2530Context@@PAX1@Z
// partial score=0.14 date=2026-09-17
// ?dup_009b2530@@YAXPAURva009B2530Context@@PAX1@Z
// Anonymous BFME VP6 scalar plane filter.  The address token is retained:
// the codec callers and dispatch tables prove the codec family, but no named
// owner for this body is established.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B2530Context
{
	int m_mode;
	unsigned char m_pad04[4];
	int m_filterMode;
	int m_alpha;
	unsigned char m_pad10[0x14];
	int *m_levelTable;
	int *m_metric;
	unsigned char m_pad2c[0x4c];
	int m_plane0;
	int m_plane1;
	int m_plane2;
	unsigned char m_pad84[0x0c];
	unsigned int m_cols;
	unsigned int m_rows;
	unsigned int m_stride;
};

typedef void (__cdecl *Rva009B2530FilterProc)(
	void *, void *, void *, int, int, int *);
typedef void (__cdecl *Rva009B2530CopyProc)(void *, void *, int);

#define g_rva009b2530Filter (*(Rva009B2530FilterProc *)0x01356ec0)
#define g_rva009b2530Copy (*(Rva009B2530CopyProc *)0x01356b44)
#define g_rva009b2530Bilinear (*(Rva009B2530FilterProc *)0x01356ea0)

void __cdecl dup_009b2530(
	Rva009B2530Context *state, void *sourceArgument, void *destinationArgument)
{
	register int alpha = state->m_alpha;
	int mode = state->m_mode;
	int smallThreshold;
	int mediumThreshold;
	int copyThreshold;
	int *filterTable;
	volatile int thresholdPad[2];
	if (mode >= 5)
	{
		smallThreshold = 0x180;
		mediumThreshold = 0x900;
		thresholdPad[1] = 0xb40;
		copyThreshold = 0x1680;
	}
	else
	{
		smallThreshold = 0x800;
		mediumThreshold = 0x7800;
		thresholdPad[1] = 0x16800;
		copyThreshold = 0x1e000;
	}
	if (mode >= 5)
		filterTable = (int *)0x012d8058;
	else if (mode >= 2)
		filterTable = (int *)0x012d7f58;
	else
		filterTable = (int *)0x01356940;

	unsigned char * volatile source0 = (unsigned char *)sourceArgument + state->m_plane0;
	unsigned int rows = state->m_rows;
	unsigned int cols = state->m_cols;
	unsigned char *destination0 = (unsigned char *)destinationArgument + state->m_plane0;
	int stride = (int)state->m_stride;
	unsigned int index = 0;
	unsigned int row = 0;

	if (rows > 0)
	{
		do
		{
			unsigned int column = 0;
			if (cols > 0)
			{
				int upOffset = ((int)index - (int)cols) << 2;
				int downOffset = ((int)index + (int)cols) << 2;
				int delta = (int)(destination0 - source0);
				do
				{
					int metric = state->m_metric[index];

					if (state->m_filterMode > 5 && metric > thresholdPad[1])
					{
						g_rva009b2530Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);
						if (state->m_metric[index - 1] > copyThreshold)
							goto tripleFilter0;
						if (column + 1 < cols &&
							state->m_metric[index + 1] > copyThreshold)
							goto tripleFilter0;
						if (row + 1 < rows &&
							*(int *)((unsigned char *)state->m_metric + downOffset) > copyThreshold)
							goto tripleFilter0;
						if (row > 0 &&
							*(int *)((unsigned char *)state->m_metric + upOffset) > copyThreshold)
							goto tripleFilter0;
						goto filtered0;

					tripleFilter0:
						g_rva009b2530Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);
						g_rva009b2530Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);
					filtered0:;
					}
					else if (metric > mediumThreshold)
					{
						g_rva009b2530Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);
					}
					else if (metric > smallThreshold)
					{
						g_rva009b2530Bilinear(state, source0, source0 + delta,
							stride, alpha, filterTable);
					}
					else
					{
						g_rva009b2530Copy(source0, source0 + delta, stride);
					}

					++index;
					upOffset += 4;
					downOffset += 4;
					++column;
					source0 += 8;
				}
				while (column < cols);
			}
			source0 += stride * 8;
			destination0 += stride * 8;
			++row;
		}
		while (row < rows);
	}

	unsigned char *source1 = (unsigned char *)sourceArgument + state->m_plane1;
	unsigned char *destination1 = (unsigned char *)destinationArgument + state->m_plane1;
	unsigned int rows1 = rows >> 1;
	unsigned int cols1 = cols >> 1;
	int stride1 = stride >> 1;
	unsigned int outer1 = rows1;

	while (outer1 > 0)
	{
		if (cols1 > 0)
		{
			unsigned int count = cols1;
			int delta = (int)(destination1 - source1);
			do
			{
				int metric = state->m_metric[index];
				
				if (state->m_mode < 5)
					alpha = state->m_levelTable[index];

				if (state->m_filterMode > 5 && metric > copyThreshold)
				{
					g_rva009b2530Filter(state, source1, source1 + delta,
						stride1, alpha, filterTable);
					g_rva009b2530Filter(state, source1, source1 + delta,
						stride1, alpha, filterTable);
					g_rva009b2530Filter(state, source1, source1 + delta,
						stride1, alpha, filterTable);
				}
				else if (metric > mediumThreshold)
				{
					g_rva009b2530Filter(state, source1, source1 + delta,
						stride1, alpha, filterTable);
				}
				else if (metric > smallThreshold)
				{
					g_rva009b2530Bilinear(state, source1, source1 + delta,
						stride1, alpha, filterTable);
				}
				else
				{
					g_rva009b2530Copy(source1, source1 + delta, stride1);
				}

				++index;
				--count;
				source1 += 8;
			}
			while (count != 0);
		}
		source1 += stride1 * 8;
		destination1 += stride1 * 8;
		--outer1;
	}

	unsigned char *source2 = (unsigned char *)sourceArgument + state->m_plane2;
	unsigned char *destination2 = (unsigned char *)destinationArgument + state->m_plane2;
	unsigned int outer2 = rows1;

	while (outer2 > 0)
	{
		if (cols1 > 0)
		{
			unsigned int count = cols1;
			int delta = (int)(destination2 - source2);
			do
			{
				int metric = state->m_metric[index];

				if (state->m_mode < 5)
					alpha = state->m_levelTable[index];

				if (state->m_filterMode > 5 && metric > copyThreshold)
				{
					g_rva009b2530Filter(state, source2, source2 + delta,
						stride1, alpha, filterTable);
					g_rva009b2530Filter(state, source2, source2 + delta,
						stride1, alpha, filterTable);
					g_rva009b2530Filter(state, source2, source2 + delta,
						stride1, alpha, filterTable);
				}
				else if (metric > mediumThreshold)
				{
					g_rva009b2530Filter(state, source2, source2 + delta,
						stride1, alpha, filterTable);
				}
				else if (metric > smallThreshold)
				{
					g_rva009b2530Bilinear(state, source2, source2 + delta,
						stride1, alpha, filterTable);
				}
				else
				{
					g_rva009b2530Copy(source2, source2 + delta, stride1);
				}

				++index;
				--count;
				source2 += 8;
			}
			while (count != 0);
		}
		source2 += stride1 * 8;
		destination2 += stride1 * 8;
		--outer2;
	}
}
