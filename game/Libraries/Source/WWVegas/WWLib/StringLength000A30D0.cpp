// cl: /DNDEBUG
// Open-BFME7: string_base.cpp's stringLength(const char*) at 0x000A30D0 (17 B).
// The ledger had claimed it 4 bytes late as a 13-byte body (0x000A30D4); this
// is the whole function: walk to the terminator, return the count.
int stringLength(const char *s)
{
	const char *next = s + 1;
	const char *p = s;
	char c;
	do { c = *p++; } while (c);
	return p - next;
}
