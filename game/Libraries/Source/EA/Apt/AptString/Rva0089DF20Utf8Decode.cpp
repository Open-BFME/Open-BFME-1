// ?decodeUtf8Rva0089DF20@@YAPBDPBDPAH@Z
// UTF-8 decode of one code point (162 B at 0x0089DF20), the reverse of
// encodeUtf8Rva0089DDC0 two functions earlier (Rva0089DDC0Utf8Encode.cpp).
// Reads a 1-4 byte sequence, stores the code point and returns the byte after
// it. Retail stores through `cp` once, at a shared exit that the compiler
// duplicated into each arm. No direct callers, so the name keeps the address.
const char* decodeUtf8Rva0089DF20(const char* src, int* cp)
{
	const unsigned char* p = (const unsigned char*)src;
	unsigned char c = p[0];
	int value;
	const char* next;
	if (c <= 0x7F) {
		value = c;
		next = src + 1;
	} else if ((c & 0xE0) == 0xC0) {
		value = ((c & 0x1F) << 6) | (p[1] & 0x3F);
		next = src + 2;
	} else if ((c & 0xF0) == 0xE0) {
		value = ((((c & 0x0F) << 6) | (p[1] & 0x3F)) << 6) | (p[2] & 0x3F);
		next = src + 3;
	} else {
		value = ((((((c & 0x07) << 6) | (p[1] & 0x3F)) << 6) | (p[2] & 0x3F)) << 6) | (p[3] & 0x3F);
		next = src + 4;
	}
	*cp = value;
	return next;
}
