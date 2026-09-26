// ?wideFill@@YAPAGPAGIG@Z
unsigned short* wideFill(unsigned short* dst, unsigned int n, unsigned short v)
{
	unsigned short* p = dst;
	while (n > 0) { *p++ = v; --n; }
	return dst;
}
