// cl: /O2 /MD
// FESL's three-argument base64 encoder at retail RVA 0x007FF100.
//
// The surrounding blob service computes the output size and calls this helper
// with (length, source, destination).  Retail indexes the executable's
// encoder alphabet at VA 0x0112C178, emits '=' for one- and two-byte tails,
// and appends a NUL after the four-character packet stream.  The table is an
// address-backed retail table; no upstream-library identity is assumed here.

void rva007FF100Encode(unsigned int length, const char *source, void *destination)
{
	int outputOffset = 0;
	int inputOffset = 0;
	if ((int)length >= 3)
	{
		unsigned int group = length / 3;
		length += group * -3;
		do
		{
			((unsigned char *)destination)[outputOffset] =
				((const unsigned char *)0x0112C178)[
					((const unsigned char *)source)[inputOffset] >> 2];
			((unsigned char *)destination)[outputOffset + 1] =
				((const unsigned char *)0x0112C178)[
					(((const unsigned char *)source)[inputOffset + 1] >> 4) |
					 (((source)[inputOffset] & 3) << 4)];
			((unsigned char *)destination)[outputOffset + 2] =
				((const unsigned char *)0x0112C178)[
					(((source)[inputOffset + 1] & 0xf) << 2) |
					 (((const unsigned char *)source)[inputOffset + 2] >> 6)];
			((unsigned char *)destination)[outputOffset + 3] =
				((const unsigned char *)0x0112C178)[
					(source)[inputOffset + 2] & 0x3f];
			outputOffset += 4;
			inputOffset += 3;
			--group;
		}
		while (group != 0);
	}
	if (--length != 0)
	{
		if (--length == 0)
		{
			((unsigned char *)destination)[outputOffset] =
				((const unsigned char *)0x0112C178)[
					((const unsigned char *)source)[inputOffset] >> 2];
			((unsigned char *)destination)[outputOffset + 1] =
				((const unsigned char *)0x0112C178)[
					((source[inputOffset] & 3) << 4) |
						 (((const unsigned char *)source)[inputOffset + 1] >> 4)];
			((unsigned char *)destination)[outputOffset + 2] =
				((const unsigned char *)0x0112C178)[(source[inputOffset + 1] & 0xf) << 2];
			((unsigned char *)destination)[outputOffset + 3] = '=';
			outputOffset += 4;
		}
	}
	else
	{
		((unsigned char *)destination)[outputOffset] =
			((const unsigned char *)0x0112C178)[
				((const unsigned char *)source)[inputOffset] >> 2];
		((unsigned char *)destination)[outputOffset + 1] =
			((const unsigned char *)0x0112C178)[(source[inputOffset] & 3) << 4];
		((unsigned char *)destination)[outputOffset + 2] = '=';
		((unsigned char *)destination)[outputOffset + 3] = '=';
		outputOffset += 4;
	}

	((unsigned char *)destination)[outputOffset] = 0;
}
