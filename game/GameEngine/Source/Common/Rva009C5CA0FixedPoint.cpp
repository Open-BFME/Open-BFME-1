// Fixed-point coefficient product helper at retail RVA 0x009C5CA0.
// The helper clears a 128-byte result block, then writes eleven signed
// 16-bit products into the fixed slots used by the neighboring image filters.

extern "C" void * __cdecl memset(void *destination, int value, unsigned int bytes);

#pragma intrinsic(memset)

void __cdecl Rva009C5CA0(short *first, short *second, int *result)
{
	memset(result, 0, 0x80);
	result[0] = first[0] * second[0];
	result[1] = first[1] * second[1];
	result[8] = first[2] * second[2];
	result[16] = first[3] * second[3];
	result[9] = first[4] * second[4];
	result[2] = first[5] * second[5];
	result[3] = first[6] * second[6];
	result[10] = first[7] * second[7];
	result[17] = first[8] * second[8];
	result[24] = first[9] * second[9];
	result[32] = first[10] * second[10];
}
