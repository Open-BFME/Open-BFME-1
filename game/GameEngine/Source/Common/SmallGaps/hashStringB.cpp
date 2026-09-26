// ?hashStringB@@YGIPAPBDI@Z
unsigned int __stdcall hashStringB(const char** key, unsigned int buckets)
{
	const char* s = *key;
	unsigned int h = 0;
	for (; *s; ++s)
		h = h * 5 + *s;
	return h % buckets;
}
