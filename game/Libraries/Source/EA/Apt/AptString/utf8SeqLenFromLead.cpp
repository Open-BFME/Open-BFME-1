// ?utf8SeqLenFromLead@@YAHPBD@Z
int utf8SeqLenFromLead(const char* s)
{
	unsigned char c = *(const unsigned char*)s;
	if (c <= 0x7f) return 1;
	if ((c & 0xe0) == 0xc0) return 2;
	return (c & 0xf0) != 0xe0 ? 4 : 3;
}
