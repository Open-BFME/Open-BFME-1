// cl: /O2 /Ob0

unsigned short *rva004be1d0(unsigned short *a, unsigned short *b)
{
	if (*a >= *b)
		a = b;
	return a;
}
