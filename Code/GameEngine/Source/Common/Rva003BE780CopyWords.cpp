namespace Rva003BE780
{
void copyWords(unsigned short *first, unsigned short *last, unsigned short *dst);

void copyWords(unsigned short *first, unsigned short *last, unsigned short *dst)
{
	unsigned short *source = first;
	unsigned short *end = last;
	unsigned short *output = dst;
	int count = end - source;
	if (count <= 0)
		return;
	int offset = (char *)source - (char *)output;
	while (count > 0)
	{
		*output = *(unsigned short *)((char *)output + offset);
		++output;
		--count;
	}
}
}
