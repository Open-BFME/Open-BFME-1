// ?rva0013A070@@YAHPBEH@Z
// partial score=0.87 date=2026-09-22
// Retail 0x0013A070, 53 bytes, a carved extent with one caller.  A __cdecl
// little-endian byte-run decoder: accumulate bytes[i] * scale into an int and
// shift the scale left by eight each step.  Size, control flow, the jle guard,
// the loop-alignment lea nop at +0x1A, the imul/shl/inc sequence and the whole
// epilogue reproduce exactly.  Seven bytes differ and every one of them is the
// SAME ecx/edx mirror: retail zeroes the index into edx and puts the scale
// constant in ecx, VC7.1 does the reverse.
//
// Exhausted here: local definition order both ways, a split declaration with
// the scale initialised in the for-init, a while loop with the increment in the
// body, a comma for-init carrying both, unsigned versus signed scale, and the
// multiply operands reversed.  tools/shape_family_levers.py offers exactly one
// choice for this shape (the two definition orders) and both are above.

int rva0013A070(const unsigned char *bytes, int count)
{
	int value = 0;
	unsigned int scale = 1;

	for (int i = 0; i < count; i++)
	{
		value += bytes[i] * scale;
		scale <<= 8;
	}

	return value;
}
