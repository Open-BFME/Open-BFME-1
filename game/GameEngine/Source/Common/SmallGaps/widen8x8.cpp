// ?widen8x8@@YAXPBEPAGH@Z
void __cdecl widen8x8(const unsigned char* src, unsigned short* dst, int srcStride)
{
	int rows = 8;
	do
	{
		dst[0] = src[0];
		dst[1] = src[1];
		dst[2] = src[2];
		dst[3] = src[3];
		dst[4] = src[4];
		dst[5] = src[5];
		dst[6] = src[6];
		dst[7] = src[7];
		src += srcStride;
		dst += 8;
	} while (--rows);
}
