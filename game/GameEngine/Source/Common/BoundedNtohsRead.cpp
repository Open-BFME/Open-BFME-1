// Two byte-identical 57-byte bodies at 0x0068D830 and 0x0068D8E0.
// Bounds-checked u16 read: on success the word is spilled into the dead
// limit slot, then a shared tail does ntohs of that slot. volatile forces
// the reload so the fail path does not CSE the original limit in eax.

extern "C" __declspec(dllimport) unsigned short __stdcall ntohs(unsigned short netshort);

unsigned char *rva68d830(unsigned char *cursor, unsigned short *out, unsigned char *limit)
{
	if (limit != 0 && (cursor > limit || cursor + 2 > limit))
		goto convert;

	*(unsigned short *)&limit = *(unsigned short *)cursor;
	cursor += 2;

convert:
	*out = ntohs(*(volatile unsigned short *)&limit);
	return cursor;
}

unsigned char *rva68d8e0(unsigned char *cursor, unsigned short *out, unsigned char *limit)
{
	if (limit != 0 && (cursor > limit || cursor + 2 > limit))
		goto convert;

	*(unsigned short *)&limit = *(unsigned short *)cursor;
	cursor += 2;

convert:
	*out = ntohs(*(volatile unsigned short *)&limit);
	return cursor;
}
