// ?Rva009B2A50Vp6Filter@@YAXPAURva009B2A50Context@@PAX1@Z
// partial score=0.22 date=2026-09-03
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B2A50Context
{
	int m_mode;
	unsigned char m_pad04[4];
	int m_filterMode;
	int m_alpha;
	unsigned char m_pad10[0x18];
	int *m_metric;
	unsigned char m_pad2c[0x4c];
	int m_plane0;
	int m_plane1;
	int m_plane2;
	unsigned char m_pad84[0x0c];
	unsigned int m_inner;
	unsigned int m_outer;
	unsigned int m_width;
};

typedef void (__cdecl *Rva009B2A50FilterProc)(
	void *, void *, void *, int, int, int *);
typedef void (__cdecl *Rva009B2A50CopyProc)(void *, void *, int);

extern Rva009B2A50FilterProc g_rva009b2a50Filter;
extern Rva009B2A50CopyProc g_rva009b2a50Copy;
extern Rva009B2A50FilterProc g_rva009b2a50Bilinear;

void __cdecl Rva009B2A50Vp6Filter(
	Rva009B2A50Context *state, void *sourceArgument, void *destinationArgument)
{
	int mode = state->m_mode;
	int alpha = state->m_alpha;
	int smallThreshold;
	int mediumThreshold;
	int largeThreshold;
	int copyThreshold;
	int *filterTable;

	if (state->m_mode >= 5) {
		smallThreshold = 0x180;
		mediumThreshold = 0x900;
		largeThreshold = 0xb40;
		copyThreshold = 0x1680;
	} else {
		smallThreshold = 0x800;
		mediumThreshold = 0x7800;
		largeThreshold = 0x16800;
		copyThreshold = 0x1e000;
	}

	if (state->m_mode >= 5)
		goto profile5;
	if (state->m_mode >= 2)
		goto profile2;
	filterTable = (int *)0x01356940;
	goto profileDone;
profile2:
	filterTable = (int *)0x012d7f58;
	goto profileDone;
profile5:
	filterTable = (int *)0x012d8058;
profileDone:

	unsigned char *source0 = (unsigned char *)sourceArgument;
	unsigned char *destination0 = (unsigned char *)destinationArgument;
	source0 += state->m_plane0;
	destination0 += state->m_plane0;
	unsigned int inner = state->m_inner;
	unsigned int outer = state->m_outer >> 1;
	unsigned int width = state->m_width;
	int stride = (int)(width << 1);
	unsigned int index = 0;
	unsigned int innerIndex = 0;
	unsigned int outerIndex = 0;

	if (outer != 0) {
		do {
			innerIndex = 0;
			if (inner != 0) {
				unsigned int upOffset = (index - inner) << 2;
				unsigned int downOffset = (index + inner) << 2;
				int delta = (int)(destination0 - source0);

				do {
					int metric = state->m_metric[index];

					if (state->m_filterMode > 5 && metric > largeThreshold) {
						g_rva009b2a50Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);

						if (downOffset > 0) {
							if (state->m_metric[index - 1] > copyThreshold)
								goto tripleFilter0;
						}
						if (innerIndex + 1 < inner) {
							if (state->m_metric[index + 1] > copyThreshold)
								goto tripleFilter0;
						}
						if (outerIndex + 1 < outer) {
							if (*(int *)((unsigned char *)state->m_metric + upOffset) > copyThreshold)
								goto tripleFilter0;
						}
						if (outerIndex > 0) {
							if (*(int *)((unsigned char *)state->m_metric + downOffset) > copyThreshold)
								goto tripleFilter0;
						}
						goto filtered0;

					tripleFilter0:
							g_rva009b2a50Filter(state, source0, source0 + delta,
								stride, alpha, filterTable);
							g_rva009b2a50Filter(state, source0,
								source0 + (unsigned int)state,
								stride, alpha, filterTable);
					filtered0:;
					} else if (metric > mediumThreshold) {
						g_rva009b2a50Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);
					} else if (metric > smallThreshold) {
						g_rva009b2a50Bilinear(state, source0,
							source0 + (unsigned int)state,
							stride, alpha, filterTable);
					} else {
						g_rva009b2a50Copy(source0, source0 + delta, stride);
					}

					++index;
					upOffset += 4;
					downOffset += 4;
					++innerIndex;
					source0 += 8;
				} while (innerIndex < inner);
			}

			source0 += stride * 8;
			destination0 += stride * 8;
			++outerIndex;
		} while (outerIndex < outer);
	}

	source0 = (unsigned char *)sourceArgument;
	destination0 = (unsigned char *)destinationArgument;
	source0 += state->m_plane0 + state->m_width;
	destination0 += state->m_plane0 + state->m_width;
	outerIndex = 0;
	if (outer != 0) {
		do {
			innerIndex = 0;
			if (inner != 0) {
				unsigned int upOffset = (index - inner) << 2;
				unsigned int downOffset = (index + inner) << 2;
				int delta = (int)(destination0 - source0);

				do {
					int metric = state->m_metric[index];

					if (state->m_filterMode > 5 && metric > largeThreshold) {
						g_rva009b2a50Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);

						if (upOffset > 0) {
							if (state->m_metric[index - 1] > copyThreshold)
								goto tripleFilter0Reverse;
						}
						if (innerIndex + 1 < inner) {
							if (state->m_metric[index + 1] > copyThreshold)
								goto tripleFilter0Reverse;
						}
						if (outerIndex + 1 < outer) {
							if (*(int *)((unsigned char *)state->m_metric + downOffset) > copyThreshold)
								goto tripleFilter0Reverse;
						}
						if (outerIndex > 0) {
							if (*(int *)((unsigned char *)state->m_metric + upOffset) > copyThreshold)
								goto tripleFilter0Reverse;
						}
						goto filtered0Reverse;

					tripleFilter0Reverse:
						g_rva009b2a50Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);
						g_rva009b2a50Filter(state, source0,
							source0 + (unsigned int)state,
							stride, alpha, filterTable);
					filtered0Reverse:;
					} else if (metric > mediumThreshold) {
						g_rva009b2a50Filter(state, source0, source0 + delta,
							stride, alpha, filterTable);
					} else if (metric > smallThreshold) {
						g_rva009b2a50Bilinear(state, source0,
							source0 + (unsigned int)state,
							stride, alpha, filterTable);
					} else {
						g_rva009b2a50Copy(source0, source0 + delta, stride);
					}

					++index;
					upOffset += 4;
					downOffset += 4;
					++innerIndex;
					source0 += 8;
				} while (innerIndex < inner);
			}

			source0 += stride * 8;
			destination0 += stride * 8;
			++outerIndex;
		} while (outerIndex < outer);
	}

	inner >>= 1;
	unsigned char *source1 = (unsigned char *)sourceArgument + state->m_plane1;
	unsigned char *destination1 = (unsigned char *)destinationArgument + state->m_plane1;
	stride >>= 2;
	unsigned int outer1 = outer;

	while (outer1 != 0) {
		if (inner != 0) {
			unsigned int count = inner;
			int delta = (int)(destination1 - source1);
			do {
				int metric = state->m_metric[index];
				if (state->m_filterMode > 5 && metric > copyThreshold) {
					g_rva009b2a50Filter(state, source1, source1 + delta,
						stride, alpha, filterTable);
					g_rva009b2a50Filter(state, source1,
						source1 + (unsigned int)state,
						stride, alpha, filterTable);
					g_rva009b2a50Filter(state, source1,
						source1 + (unsigned int)state,
						stride, alpha, filterTable);
				} else if (metric > mediumThreshold) {
					g_rva009b2a50Filter(state, source1, source1 + delta,
						stride, alpha, filterTable);
				} else if (metric > smallThreshold) {
					g_rva009b2a50Bilinear(state, source1,
						source1 + (unsigned int)state,
						stride, alpha, filterTable);
				} else {
					g_rva009b2a50Copy(source1, source1 + delta, stride);
				}

				++index;
				--count;
				source1 += 8;
			} while (count != 0);
		}

		source1 += stride * 8;
		destination1 += stride * 8;
		--outer1;
	}

	unsigned char *source2 = (unsigned char *)sourceArgument + state->m_plane2;
	unsigned char *destination2 = (unsigned char *)destinationArgument + state->m_plane2;
	unsigned int outer2 = outer;
	unsigned int count2 = inner;

	while (outer2 != 0) {
		if (inner != 0) {
			count2 = inner;
			int delta = (int)(destination2 - source2);
			do {
				int metric = state->m_metric[index];
				if (state->m_filterMode > 5 && metric > copyThreshold) {
					g_rva009b2a50Filter(state, source2, source2 + delta,
						stride, alpha, filterTable);
					g_rva009b2a50Filter(state, source2,
						source2 + (unsigned int)state,
						stride, alpha, filterTable);
					g_rva009b2a50Filter(state, source2,
						source2 + (unsigned int)state,
						stride, alpha, filterTable);
				} else if (metric > mediumThreshold) {
					g_rva009b2a50Filter(state, source2, source2 + delta,
						stride, alpha, filterTable);
				} else if (metric > smallThreshold) {
					g_rva009b2a50Bilinear(state, source2,
						source2 + (unsigned int)state,
						stride, alpha, filterTable);
				} else {
					g_rva009b2a50Copy(source2, source2 + delta, stride);
				}

				++index;
				--count2;
				source2 += 8;
			} while (count2 != 0);
		}

		source2 += stride * 8;
		destination2 += stride * 8;
		--outer2;
	}
}
