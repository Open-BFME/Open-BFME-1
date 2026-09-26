// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Deblocking loop filter run across a horizontal block edge, eight columns
// wide.  The four taps live at -2*stride .. +1*stride; the filter strength is
// looked up in a caller-supplied bounding-value table indexed by (f + 4) >> 3
// and every write goes through the saturating clamp table at 0x01356FE0.
//
// Retail carries two byte-identical copies of this routine, at 0x009B3560 and
// 0x009B3710.  Neither call site names it, so both keep address-derived names.

extern const unsigned char g_bfmeClampTable[];			// retail 0x01356FE0 (zero point)

void Rva009B3560FilterHoriz(void *, unsigned char *ptr, int stride, const int *bounding)
{
	int count, value, flag, diff, delta;

	for (count = 8; count != 0; --count) {
		value = 3 * (ptr[0] - ptr[-stride]);

		diff = ptr[-2 * stride] - ptr[-stride];
		if (diff > 0)
			diff = ptr[-2 * stride] - ptr[-stride];
		else
			diff = ptr[-stride] - ptr[-2 * stride];
		if (diff > 1)
			goto steep;

		diff = ptr[0] - ptr[stride];
		if (diff > 0)
			diff = ptr[0] - ptr[stride];
		else
			diff = ptr[stride] - ptr[0];
		if (diff <= 1) {
			flag = 0;
			goto filter;
		}

steep:
		flag = 1;
		value += ptr[-2 * stride] - ptr[stride];

filter:
		delta = bounding[(value + 4) >> 3];
		ptr[-stride] = g_bfmeClampTable[ptr[-stride] + delta];
		ptr[0] = g_bfmeClampTable[ptr[0] - delta];

		if (flag == 0) {
			int half = delta >> 1;
			ptr[-2 * stride] = g_bfmeClampTable[ptr[-2 * stride] + half];
			ptr[stride] = g_bfmeClampTable[ptr[stride] - half];
		}

		++ptr;
	}
}

void Rva009B3710FilterHoriz(void *, unsigned char *ptr, int stride, const int *bounding)
{
	int count, value, flag, diff, delta;

	for (count = 8; count != 0; --count) {
		value = 3 * (ptr[0] - ptr[-stride]);

		diff = ptr[-2 * stride] - ptr[-stride];
		if (diff > 0)
			diff = ptr[-2 * stride] - ptr[-stride];
		else
			diff = ptr[-stride] - ptr[-2 * stride];
		if (diff > 1)
			goto steep;

		diff = ptr[0] - ptr[stride];
		if (diff > 0)
			diff = ptr[0] - ptr[stride];
		else
			diff = ptr[stride] - ptr[0];
		if (diff <= 1) {
			flag = 0;
			goto filter;
		}

steep:
		flag = 1;
		value += ptr[-2 * stride] - ptr[stride];

filter:
		delta = bounding[(value + 4) >> 3];
		ptr[-stride] = g_bfmeClampTable[ptr[-stride] + delta];
		ptr[0] = g_bfmeClampTable[ptr[0] - delta];

		if (flag == 0) {
			int half = delta >> 1;
			ptr[-2 * stride] = g_bfmeClampTable[ptr[-2 * stride] + half];
			ptr[stride] = g_bfmeClampTable[ptr[stride] - half];
		}

		++ptr;
	}
}
