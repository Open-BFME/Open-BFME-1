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
