// Retail RVA009A92D0, 157 bytes; RET at009A936C, INT3 at009A936D.
// Opaque scalar codec dispatch helper installed at VA01356E7C by009B1073.
// EAX returns source + bytes, including unchanged source for a zero count.
// Keep the count guard outside pointer setup and preweight the third sample.

// ?Rva009A92D0@@YAPAEPAEHI@Z
unsigned char *__cdecl Rva009A92D0(unsigned char *source, int stride,
                                 unsigned int bytes)
{
	if (bytes > 0)
	{
		unsigned char *row3 = source + stride * 2;
		row3 += stride;

		while (bytes > 0)
		{
			unsigned int second = source[stride];
			unsigned int first = source[0];
			source[stride] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

			unsigned int third = source[stride * 2] * 154;
			unsigned int fourth = row3[0];
			source[stride * 2] = (unsigned char)((second * 102 + third + 128) >> 8);
			row3[0] = (unsigned char)((third + fourth * 102 + 128) >> 8);
			row3[stride] = (unsigned char)((fourth * 205 + source[stride * 5] * 51 + 128) >> 8);

			++source;
			++row3;
			--bytes;
		}
	}
	return source;
}
