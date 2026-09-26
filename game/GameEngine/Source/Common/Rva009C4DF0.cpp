// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Address-derived identity; the body offsets an 8x8 signed sample block
// before passing it to the verified byte clamp routine.
void __cdecl bfmeClampBlock(unsigned char *dst, short *src, int dstStride, int srcStride);

void __cdecl Rva009C4DF0(short *work, unsigned char *dst, const short *samples,
	int dstStride)
{
	int rows = 8;
	short *out = work + 2;
	do {
		out[-2] = (short)(samples[0] + 128);
		out[-1] = (short)(samples[1] + 128);
		out[0] = (short)(samples[2] + 128);
		out[1] = (short)(samples[3] + 128);
		out[2] = (short)(samples[4] + 128);
		out[3] = (short)(samples[5] + 128);
		out[4] = (short)(samples[6] + 128);
		out[5] = (short)(samples[7] + 128);
		out += 8;
		samples += 8;
	} while (--rows);

	bfmeClampBlock(dst, work, dstStride, 8);
}
