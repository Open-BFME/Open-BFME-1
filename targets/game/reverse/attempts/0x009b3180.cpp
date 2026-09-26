// ?Rva009B3180FilterVert@@YAXPAXPAEHPBH@Z
// partial score=0.3 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Deblocking loop filter run across a vertical block edge, eight rows
// tall.  The four taps live at ptr[0..3]; the filter strength is looked
// up in a caller-supplied bounding-value table indexed by (f + 4) >> 3
// and every write goes through the saturating clamp table at 0x01356FE0.
// Twin of the horizontal-edge copies at 0x009B3560 and 0x009B3710.

extern const unsigned char g_bfmeClampTable[];			// retail 0x01356FE0 (zero point)

void Rva009B3650FilterVert(void *, unsigned char *ptr, int stride, const int *bounding)
{
	int p0, count, value, flag, diff, delta;

	for (count = 8; count != 0; --count) {
		int p2 = ptr[2];
		int p1 = ptr[1];
		p0 = ptr[0];
		value = 3 * (p2 - p1);

		diff = p0 - p1;
		if (diff > 0)
			diff = p0 - p1;
		else
			diff = p1 - p0;
		if (diff > 1)
			goto steep;

		{
			int p3 = ptr[3];
			diff = p2 - p3;
			if (diff > 0)
				diff = p2 - p3;
			else
				diff = p3 - p2;
			if (diff <= 1) {
				flag = 0;
				goto filter;
			}
		}

steep:
		flag = 1;
		value += p0 - ptr[3];

filter:
		delta = bounding[(value + 4) >> 3];
		ptr[1] = g_bfmeClampTable[ptr[1] + delta];
		ptr[2] = g_bfmeClampTable[ptr[2] - delta];

		if (flag == 0) {
			delta >>= 1;
			ptr[0] = g_bfmeClampTable[ptr[0] + delta];
			ptr[3] = g_bfmeClampTable[ptr[3] - delta];
		}

		ptr += stride;
	}
}

// Eight-row unrolled edge filter, same clamp table and caller-supplied
// bounding table as above but a single non-branching strength formula (no
// steep/non-steep split -- the outer-tap adjustment is selected with a
// neg/sbb/inc flag instead of a branch).  Written as eight straight-line
// guarded blocks, not a loop: a row whose two centre taps already match
// (p1 == p2) is left untouched and its pointer is NOT advanced, so every
// later block re-tests the same (unmoved) row and is skipped too -- a flat
// first row cascades the whole function down to a no-op.
void Rva009B3180FilterVert(void *, unsigned char *ptr, int stride, const int *bounding)
{
	int p1 = ptr[1];
	int s = stride;
	const int *tbl = bounding;
	int p2 = ptr[2];
	if (p1 != p2) {
		int p0 = ptr[0];
		int p3 = ptr[3];
		int a = p1 - p0;
		int b = p3 - p2;
		int t = 2 * (p2 - p1) + 4;
		t -= a;
		t += b;
		int delta = tbl[t >> 3];
		ptr[1] = g_bfmeClampTable[p1 + delta];
		ptr[2] = g_bfmeClampTable[p2 - delta];
		int flag = (a | b) == 0;
		int half = delta >> 1;
		int adj = flag * half;
		ptr[0] = g_bfmeClampTable[p0 + adj];
		ptr[3] = g_bfmeClampTable[p3 - adj];
		ptr += s;
	}

	p1 = ptr[1];
	p2 = ptr[2];
	if (p1 != p2) {
		int p0 = ptr[0];
		int p3 = ptr[3];
		int a = p1 - p0;
		int b = p3 - p2;
		int t = 2 * (p2 - p1) + 4;
		t -= a;
		t += b;
		int delta = tbl[t >> 3];
		ptr[1] = g_bfmeClampTable[p1 + delta];
		ptr[2] = g_bfmeClampTable[p2 - delta];
		int flag = (a | b) == 0;
		int half = delta >> 1;
		int adj = flag * half;
		ptr[0] = g_bfmeClampTable[p0 + adj];
		ptr[3] = g_bfmeClampTable[p3 - adj];
		ptr += s;
	}

	p1 = ptr[1];
	p2 = ptr[2];
	if (p1 != p2) {
		int p0 = ptr[0];
		int p3 = ptr[3];
		int a = p1 - p0;
		int b = p3 - p2;
		int t = 2 * (p2 - p1) + 4;
		t -= a;
		t += b;
		int delta = tbl[t >> 3];
		ptr[1] = g_bfmeClampTable[p1 + delta];
		ptr[2] = g_bfmeClampTable[p2 - delta];
		int flag = (a | b) == 0;
		int half = delta >> 1;
		int adj = flag * half;
		ptr[0] = g_bfmeClampTable[p0 + adj];
		ptr[3] = g_bfmeClampTable[p3 - adj];
		ptr += s;
	}

	p1 = ptr[1];
	p2 = ptr[2];
	if (p1 != p2) {
		int p0 = ptr[0];
		int p3 = ptr[3];
		int a = p1 - p0;
		int b = p3 - p2;
		int t = 2 * (p2 - p1) + 4;
		t -= a;
		t += b;
		int delta = tbl[t >> 3];
		ptr[1] = g_bfmeClampTable[p1 + delta];
		ptr[2] = g_bfmeClampTable[p2 - delta];
		int flag = (a | b) == 0;
		int half = delta >> 1;
		int adj = flag * half;
		ptr[0] = g_bfmeClampTable[p0 + adj];
		ptr[3] = g_bfmeClampTable[p3 - adj];
		ptr += s;
	}

	p1 = ptr[1];
	p2 = ptr[2];
	if (p1 != p2) {
		int p0 = ptr[0];
		int p3 = ptr[3];
		int a = p1 - p0;
		int b = p3 - p2;
		int t = 2 * (p2 - p1) + 4;
		t -= a;
		t += b;
		int delta = tbl[t >> 3];
		ptr[1] = g_bfmeClampTable[p1 + delta];
		ptr[2] = g_bfmeClampTable[p2 - delta];
		int flag = (a | b) == 0;
		int half = delta >> 1;
		int adj = flag * half;
		ptr[0] = g_bfmeClampTable[p0 + adj];
		ptr[3] = g_bfmeClampTable[p3 - adj];
		ptr += s;
	}

	p1 = ptr[1];
	p2 = ptr[2];
	if (p1 != p2) {
		int p0 = ptr[0];
		int p3 = ptr[3];
		int a = p1 - p0;
		int b = p3 - p2;
		int t = 2 * (p2 - p1) + 4;
		t -= a;
		t += b;
		int delta = tbl[t >> 3];
		ptr[1] = g_bfmeClampTable[p1 + delta];
		ptr[2] = g_bfmeClampTable[p2 - delta];
		int flag = (a | b) == 0;
		int half = delta >> 1;
		int adj = flag * half;
		ptr[0] = g_bfmeClampTable[p0 + adj];
		ptr[3] = g_bfmeClampTable[p3 - adj];
		ptr += s;
	}

	p1 = ptr[1];
	p2 = ptr[2];
	if (p1 != p2) {
		int p0 = ptr[0];
		int p3 = ptr[3];
		int a = p1 - p0;
		int b = p3 - p2;
		int t = 2 * (p2 - p1) + 4;
		t -= a;
		t += b;
		int delta = tbl[t >> 3];
		ptr[1] = g_bfmeClampTable[p1 + delta];
		ptr[2] = g_bfmeClampTable[p2 - delta];
		int flag = (a | b) == 0;
		int half = delta >> 1;
		int adj = flag * half;
		ptr[0] = g_bfmeClampTable[p0 + adj];
		ptr[3] = g_bfmeClampTable[p3 - adj];
		ptr += s;
	}

	p1 = ptr[1];
	p2 = ptr[2];
	if (p1 != p2) {
		int p0 = ptr[0];
		int p3 = ptr[3];
		int a = p1 - p0;
		int b = p3 - p2;
		int t = 2 * (p2 - p1) + 4;
		t -= a;
		t += b;
		int delta = tbl[t >> 3];
		ptr[1] = g_bfmeClampTable[p1 + delta];
		ptr[2] = g_bfmeClampTable[p2 - delta];
		int flag = (a | b) == 0;
		int half = delta >> 1;
		int adj = flag * half;
		ptr[0] = g_bfmeClampTable[p0 + adj];
		ptr[3] = g_bfmeClampTable[p3 - adj];
	}
}
