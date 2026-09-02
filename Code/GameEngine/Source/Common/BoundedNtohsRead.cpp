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
