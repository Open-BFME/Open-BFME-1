// ?utf8EncodedLength@@YAHH@Z
// Open-BFME7: UTF-8 encoded length of a code point (46 B at 0x0089DD10; the
// lead-byte twin at 0x0089DCE0 lives in Rva0089DCE0Utf8SeqLen.cpp).
int utf8EncodedLength(int c)
{
	if (c < 0x80)
		return 1;
	if (c < 0x800)
		return 2;
	if (c < 0x10000)
		return 3;
	return 4;
}
