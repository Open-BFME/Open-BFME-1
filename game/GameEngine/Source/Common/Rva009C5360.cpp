// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Address-derived spread-table body: add two 8x8 signed blocks in place, then
// clamp the result into the byte output block.
void __cdecl bfmeClampBlock(unsigned char *dst, short *src, int dstStride, int srcStride);

void __cdecl Rva009C5360(short *work, short *addend,
	unsigned char *output, int dstStride)
{
	short *base = work;
	int passes = 2;
	do {
		work[0] += addend[0];
		work[1] += addend[1];
		work[2] += addend[2];
		work[3] += addend[3];
		work[4] += addend[4];
		work[5] += addend[5];
		work[6] += addend[6];
		work[7] += addend[7];
		work[8] += addend[8];
		work[9] += addend[9];
		work[10] += addend[10];
		work[11] += addend[11];
		work[12] += addend[12];
		work[13] += addend[13];
		work[14] += addend[14];
		work[15] += addend[15];
		work[16] += addend[16];
		work[17] += addend[17];
		work[18] += addend[18];
		work[19] += addend[19];
		work[20] += addend[20];
		work[21] += addend[21];
		work[22] += addend[22];
		work[23] += addend[23];
		work[24] += addend[24];
		work[25] += addend[25];
		work[26] += addend[26];
		work[27] += addend[27];
		work[28] += addend[28];
		work[29] += addend[29];
		work[30] += addend[30];
		work[31] += addend[31];
		work += 32;
		addend += 32;
	} while (--passes);

	bfmeClampBlock(output, base, dstStride, 8);
}
