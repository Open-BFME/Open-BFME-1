// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
extern const unsigned char g_bfmeClampTable[];

void Rva009AF570FilterVert(void *, unsigned char *ptr, int stride, const int *bounding)
{
	for (int i = 0; i < 8; ++i) {
		int value = (ptr[0] - ptr[3]) + 3 * (ptr[2] - ptr[1]);
		int delta = bounding[(value + 4) >> 3];
		ptr[1] = g_bfmeClampTable[ptr[1] + delta];
		ptr[2] = g_bfmeClampTable[ptr[2] - delta];
		ptr += stride;
	}
}
