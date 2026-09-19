// ?encodeUtf8Rva0089DDC0@@YAXPADH@Z
void encodeUtf8Rva0089DDC0(char* dst, int cp)
{
	if (cp < 0x80) {
		*dst = (char)cp;
		return;
	}
	if (cp < 0x800) {
		dst[0] = (char)(0xC0 | (cp >> 6));
		dst[1] = (char)(0x80 | (cp & 0x3F));
		return;
	}
	if (cp < 0x10000) {
		dst[0] = (char)(0xE0 | (cp >> 12));
		dst[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
		dst[2] = (char)(0x80 | (cp & 0x3F));
		return;
	}
	dst[0] = (char)(0xF0 | (cp >> 18));
	dst[1] = (char)(0x80 | ((cp >> 12) & 0x3F));
	dst[2] = (char)(0x80 | ((cp >> 6) & 0x3F));
	dst[3] = (char)(0x80 | (cp & 0x3F));
}
