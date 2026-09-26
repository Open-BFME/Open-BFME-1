// ?hashLower@@YAGPBD@Z
unsigned short hashLower(const char* s)
{
	unsigned int hash = 0x811c9dc5;
	for (;;) {
		int c = *s;
		if (!c)
			break;
		++s;
		if (c <= 0x5a && c >= 0x41)
			c += 0x20;
		hash = (hash ^ c) * 0x1000193;
	}
	if ((unsigned short)hash == 0)
		return 0x4567;
	return (unsigned short)hash;
}
