// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Address-derived spread-table body. Two byte source blocks are averaged and
// added to the signed residual block, then the verified clamp routine writes
// the resulting 8x8 block to the output.
void __cdecl bfmeClampBlock(unsigned char *dst, short *src, int dstStride, int srcStride);

void __cdecl Rva009C5080(short *work, unsigned char *output,
	const unsigned char *first, const unsigned char *second, const short *residual,
	int stride)
{
	short *out = work + 2;
	int passes = 2;
	do {
		out[-2] = (short)(((first[0] + second[0]) >> 1) + residual[0]);
		out[-1] = (short)(((first[1] + second[1]) >> 1) + residual[1]);
		out[0] = (short)(((first[2] + second[2]) >> 1) + residual[2]);
		out[1] = (short)(((first[3] + second[3]) >> 1) + residual[3]);
		out[2] = (short)(((first[4] + second[4]) >> 1) + residual[4]);
		out[3] = (short)(((first[5] + second[5]) >> 1) + residual[5]);
		out[4] = (short)(((first[6] + second[6]) >> 1) + residual[6]);
		out[5] = (short)(((first[7] + second[7]) >> 1) + residual[7]);
		first += stride;
		second += stride;

		out[6] = (short)(((first[0] + second[0]) >> 1) + residual[8]);
		out[7] = (short)(((first[1] + second[1]) >> 1) + residual[9]);
		out[8] = (short)(((first[2] + second[2]) >> 1) + residual[10]);
		out[9] = (short)(((first[3] + second[3]) >> 1) + residual[11]);
		out[10] = (short)(((first[4] + second[4]) >> 1) + residual[12]);
		out[11] = (short)(((first[5] + second[5]) >> 1) + residual[13]);
		out[12] = (short)(((first[6] + second[6]) >> 1) + residual[14]);
		out[13] = (short)(((first[7] + second[7]) >> 1) + residual[15]);
		first += stride;
		second += stride;

		out[14] = (short)(((first[0] + second[0]) >> 1) + residual[16]);
		out[15] = (short)(((first[1] + second[1]) >> 1) + residual[17]);
		out[16] = (short)(((first[2] + second[2]) >> 1) + residual[18]);
		out[17] = (short)(((first[3] + second[3]) >> 1) + residual[19]);
		out[18] = (short)(((first[4] + second[4]) >> 1) + residual[20]);
		out[19] = (short)(((first[5] + second[5]) >> 1) + residual[21]);
		out[20] = (short)(((first[6] + second[6]) >> 1) + residual[22]);
		out[21] = (short)(((first[7] + second[7]) >> 1) + residual[23]);
		first += stride;
		second += stride;

		out[22] = (short)(((first[0] + second[0]) >> 1) + residual[24]);
		out[23] = (short)(((first[1] + second[1]) >> 1) + residual[25]);
		out[24] = (short)(((first[2] + second[2]) >> 1) + residual[26]);
		out[25] = (short)(((first[3] + second[3]) >> 1) + residual[27]);
		out[26] = (short)(((first[4] + second[4]) >> 1) + residual[28]);
		out[27] = (short)(((first[5] + second[5]) >> 1) + residual[29]);
		out[28] = (short)(((first[6] + second[6]) >> 1) + residual[30]);
		out[29] = (short)(((first[7] + second[7]) >> 1) + residual[31]);
		first += stride;
		second += stride;
		residual += 32;
		out += 32;
	} while (--passes);

	bfmeClampBlock(output, work, stride, 8);
}
