// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Deblocking edge filters whose correction is passed through the limited
// adjust used by this codec: the raw filter value is folded to
// sign(v) * (|v| < 2t ? min(|v|, 2t - |v|) : 0) with t read from the strength
// table behind the pointer at 0x01356A7C, then both centre taps are written
// through the saturating clamp table at 0x01356FE0.
//
// The vertical-edge pair walks rows in an eight-pixel and a twelve-pixel
// length; MSVC unrolls both four deep.  A matching horizontal-edge pair sits
// at 0x009AFA60 and 0x009AFEC0.

extern const unsigned char g_bfmeClampTable[];		// retail 0x01356FE0 (zero point)
extern int *g_bfmeFilterLimit;						// retail 0x01356A7C

#define BFME_LIMIT_ADJUST(v, t)		\
	{								\
		int s1 = (v) >> 31;			\
		int s2;						\
		(v) ^= s1;					\
		(v) -= s1;					\
		(v) *= (v) < 2 * (t);		\
		(v) -= (t);					\
		s2 = (v) >> 31;				\
		(v) ^= s2;					\
		(v) -= s2;					\
		(v) = (t) - (v);			\
		(v) += s1;					\
		(v) ^= s1;					\
	}

void Rva009AF840FilterVert(int index, unsigned char *ptr, int stride)
{
	int t = g_bfmeFilterLimit[index];

	for (int i = 0; i < 8; ++i) {
		int v = ((ptr[-2] - ptr[1]) + 3 * (ptr[0] - ptr[-1]) + 4) >> 3;
		BFME_LIMIT_ADJUST(v, t)
		ptr[-1] = g_bfmeClampTable[ptr[-1] + v];
		ptr[0] = g_bfmeClampTable[ptr[0] - v];
		ptr += stride;
	}
}

void Rva009AFCA0FilterVert(int index, unsigned char *ptr, int stride)
{
	int t = g_bfmeFilterLimit[index];

	for (int i = 0; i < 12; ++i) {
		int v = ((ptr[-2] - ptr[1]) + 3 * (ptr[0] - ptr[-1]) + 4) >> 3;
		BFME_LIMIT_ADJUST(v, t)
		ptr[-1] = g_bfmeClampTable[ptr[-1] + v];
		ptr[0] = g_bfmeClampTable[ptr[0] - v];
		ptr += stride;
	}
}
