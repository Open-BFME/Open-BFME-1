// Retail RVA009A91D0, 247 bytes; RET at009A92C6, INT3 begins009A92C7.
// Opaque scalar codec dispatch helper: cdecl source/count/destination.
// BfmeCodecCpuDispatch installs this entry beside the matched MMX implementation.
// Compute the third sample's weighted value once to reproduce loop allocation;
// retain an unsigned-int fourth sample for retail's final MOVZX/MOV sequence.

// ?Rva009A91D0@@YAXPBXHPAX@Z
void __cdecl Rva009A91D0(const void *source, int bytes, void *destination)
{
	unsigned char *dst = (unsigned char *)destination;
	const unsigned char *src = (const unsigned char *)source;
	int remaining = bytes - 4;

	if (remaining != 0)
	{
		unsigned int groups = (unsigned int)(remaining - 1) / 4 + 1;
		do
		{
			unsigned int first = src[0];
			unsigned int second = src[1];
			dst[0] = (unsigned char)first;
			dst[1] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

			unsigned int third = src[2] * 154;
			unsigned int fourth = src[3];
			dst[2] = (unsigned char)((second * 102 + third + 128) >> 8);
			dst[3] = (unsigned char)((third + fourth * 102 + 128) >> 8);

			unsigned int fifth = src[4];
			dst[4] = (unsigned char)((fourth * 205 + fifth * 51 + 128) >> 8);
			src += 4;
			dst += 5;
			--groups;
		}
		while (groups != 0);
	}

	unsigned int first = src[0];
	unsigned int second = src[1];
	dst[0] = (unsigned char)first;
	dst[1] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

	unsigned int third = src[2] * 154;
	unsigned int fourth = src[3];
	dst[2] = (unsigned char)((second * 102 + third + 128) >> 8);
	dst[3] = (unsigned char)((third + fourth * 102 + 128) >> 8);
	dst[4] = (unsigned char)fourth;
}
