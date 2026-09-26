// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Address-derived spread-table body. Four source rows are combined with the
// signed residual block in each pass, then the verified clamp routine writes
// the resulting 8x8 block to the output.
void __cdecl bfmeClampBlock(unsigned char *dst, short *src, int dstStride, int srcStride);

void __cdecl Rva009C4E90(short *work, unsigned char *output,
	const unsigned char *source, const short *residual, int stride)
{
	short *out = work + 2;
	int passes = 2;
	do {
		out[-2] = (short)(source[0] + residual[0]);
		out[-1] = (short)(source[1] + residual[1]);
		out[0] = (short)(source[2] + residual[2]);
		out[1] = (short)(source[3] + residual[3]);
		out[2] = (short)(source[4] + residual[4]);
		out[3] = (short)(source[5] + residual[5]);
		out[4] = (short)(source[6] + residual[6]);
		out[5] = (short)(source[7] + residual[7]);
		source += stride;

		out[6] = (short)(source[0] + residual[8]);
		out[7] = (short)(source[1] + residual[9]);
		out[8] = (short)(source[2] + residual[10]);
		out[9] = (short)(source[3] + residual[11]);
		out[10] = (short)(source[4] + residual[12]);
		out[11] = (short)(source[5] + residual[13]);
		out[12] = (short)(source[6] + residual[14]);
		out[13] = (short)(source[7] + residual[15]);
		source += stride;

		out[14] = (short)(source[0] + residual[16]);
		out[15] = (short)(source[1] + residual[17]);
		out[16] = (short)(source[2] + residual[18]);
		out[17] = (short)(source[3] + residual[19]);
		out[18] = (short)(source[4] + residual[20]);
		out[19] = (short)(source[5] + residual[21]);
		out[20] = (short)(source[6] + residual[22]);
		out[21] = (short)(source[7] + residual[23]);
		source += stride;

		out[22] = (short)(source[0] + residual[24]);
		out[23] = (short)(source[1] + residual[25]);
		out[24] = (short)(source[2] + residual[26]);
		out[25] = (short)(source[3] + residual[27]);
		out[26] = (short)(source[4] + residual[28]);
		out[27] = (short)(source[5] + residual[29]);
		out[28] = (short)(source[6] + residual[30]);
		out[29] = (short)(source[7] + residual[31]);
		source += stride;
		residual += 32;
		out += 32;
	} while (--passes);

	bfmeClampBlock(output, work, stride, 8);
}
