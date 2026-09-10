// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Zigzag-order coefficient multiply: reads two 8x8 arrays of 16-bit
// coefficients in JPEG/MPEG zigzag scan order and writes their per-index
// products into a 64-entry int array in natural (raster) order. Loop-free;
// retail left it as 64 unrolled multiply-store statements (no branches),
// which is what MSVC /O2 reproduces from a hand-unrolled source in this era
// of codec code -- address-derived name, no ghidra boundary/identity beyond
// the byte-proven extent.

void Rva009C54A0DequantZigzag(const short *a, const short *b, int *dst)
{
	dst[0] = (int)a[0] * (int)b[0];
	dst[1] = (int)a[1] * (int)b[1];
	dst[8] = (int)a[2] * (int)b[2];
	dst[16] = (int)a[3] * (int)b[3];
	dst[9] = (int)a[4] * (int)b[4];
	dst[2] = (int)a[5] * (int)b[5];
	dst[3] = (int)a[6] * (int)b[6];
	dst[10] = (int)a[7] * (int)b[7];
	dst[17] = (int)a[8] * (int)b[8];
	dst[24] = (int)a[9] * (int)b[9];
	dst[32] = (int)a[10] * (int)b[10];
	dst[25] = (int)a[11] * (int)b[11];
	dst[18] = (int)a[12] * (int)b[12];
	dst[11] = (int)a[13] * (int)b[13];
	dst[4] = (int)a[14] * (int)b[14];
	dst[5] = (int)a[15] * (int)b[15];
	dst[12] = (int)a[16] * (int)b[16];
	dst[19] = (int)a[17] * (int)b[17];
	dst[26] = (int)a[18] * (int)b[18];
	dst[33] = (int)a[19] * (int)b[19];
	dst[40] = (int)a[20] * (int)b[20];
	dst[48] = (int)a[21] * (int)b[21];
	dst[41] = (int)a[22] * (int)b[22];
	dst[34] = (int)a[23] * (int)b[23];
	dst[27] = (int)a[24] * (int)b[24];
	dst[20] = (int)a[25] * (int)b[25];
	dst[13] = (int)a[26] * (int)b[26];
	dst[6] = (int)a[27] * (int)b[27];
	dst[7] = (int)a[28] * (int)b[28];
	dst[14] = (int)a[29] * (int)b[29];
	dst[21] = (int)a[30] * (int)b[30];
	dst[28] = (int)a[31] * (int)b[31];
	dst[35] = (int)a[32] * (int)b[32];
	dst[42] = (int)a[33] * (int)b[33];
	dst[49] = (int)a[34] * (int)b[34];
	dst[56] = (int)a[35] * (int)b[35];
	dst[57] = (int)a[36] * (int)b[36];
	dst[50] = (int)a[37] * (int)b[37];
	dst[43] = (int)a[38] * (int)b[38];
	dst[36] = (int)a[39] * (int)b[39];
	dst[29] = (int)a[40] * (int)b[40];
	dst[22] = (int)a[41] * (int)b[41];
	dst[15] = (int)a[42] * (int)b[42];
	dst[23] = (int)a[43] * (int)b[43];
	dst[30] = (int)a[44] * (int)b[44];
	dst[37] = (int)a[45] * (int)b[45];
	dst[44] = (int)a[46] * (int)b[46];
	dst[51] = (int)a[47] * (int)b[47];
	dst[58] = (int)a[48] * (int)b[48];
	dst[59] = (int)a[49] * (int)b[49];
	dst[52] = (int)a[50] * (int)b[50];
	dst[45] = (int)a[51] * (int)b[51];
	dst[38] = (int)a[52] * (int)b[52];
	dst[31] = (int)a[53] * (int)b[53];
	dst[39] = (int)a[54] * (int)b[54];
	dst[46] = (int)a[55] * (int)b[55];
	dst[53] = (int)a[56] * (int)b[56];
	dst[60] = (int)a[57] * (int)b[57];
	dst[61] = (int)a[58] * (int)b[58];
	dst[54] = (int)a[59] * (int)b[59];
	dst[47] = (int)a[60] * (int)b[60];
	dst[55] = (int)a[61] * (int)b[61];
	dst[62] = (int)a[62] * (int)b[62];
	dst[63] = (int)a[63] * (int)b[63];
}
