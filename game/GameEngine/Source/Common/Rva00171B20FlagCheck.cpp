// Retail 0x00171B20 reads bit four through the +0x1c and +0x10 links.
bool __cdecl rva00171b20FlagCheck(const void *object)
{
	const char *const first = *(const char *const *)((const char *)object + 0x1c);
	const char *const second = *(const char *const *)(first + 0x10);
	return !((*(const unsigned int *)(second + 0x94) >> 4) & 1);
}
