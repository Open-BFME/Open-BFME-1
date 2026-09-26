// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
extern const unsigned char g_bfmeClampTable[];

void Rva009AF6A0FilterHoriz(void *, unsigned char *ptr, int stride, const int *bounding)
{
	for (int i = 0; i < 8; ++i) {
		int value = (ptr[-2 * stride] - ptr[stride]) + 3 * (ptr[0] - ptr[-stride]);
		int delta = bounding[(value + 4) >> 3];
		ptr[-stride] = g_bfmeClampTable[ptr[-stride] + delta];
		ptr[0] = g_bfmeClampTable[ptr[0] - delta];
		++ptr;
	}
}
