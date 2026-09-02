// ?Rva009B3650FilterVert@@YAXPAXPAEHPBH@Z
// partial score=0.9 date=2026-09-02
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
extern const unsigned char g_bfmeClampTable[];

void Rva009B3650FilterVert(void *, unsigned char *ptr, int stride, const int *bounding)
{
	int count, value, flag, diff, delta;

	for (count = 8; count != 0; --count) {
		value = 3 * (ptr[2] - ptr[1]);

		diff = ptr[0] - ptr[1];
		if (diff <= 0)
			diff = ptr[1] - ptr[0];
		if (diff > 1)
			goto steep;

		diff = ptr[2] - ptr[3];
		if (diff <= 0)
			diff = ptr[3] - ptr[2];
		if (diff <= 1) {
			flag = 0;
			goto filter;
		}

steep:
		flag = 1;
		value += ptr[0] - ptr[3];

filter:
		delta = bounding[(value + 4) >> 3];
		ptr[1] = g_bfmeClampTable[ptr[1] + delta];
		ptr[2] = g_bfmeClampTable[ptr[2] - delta];

		if (flag == 0) {
			int half = delta >> 1;
			ptr[0] = g_bfmeClampTable[ptr[0] + half];
			ptr[3] = g_bfmeClampTable[ptr[3] - half];
		}

		ptr += stride;
	}
}
