// ?utf8Decode@@YAIPBE@Z
// partial score=0.8 date=2026-09-06
// 120/124 B: logic matches; retail keeps the lead byte in al and the pointer in ecx and uses movzx for the 2-byte continuation (register colour wall).
// Open-BFME7: UTF-8 decode of one sequence (124 B).
unsigned int utf8Decode(const unsigned char* p)
{
	unsigned char b = *p;
	if (b <= 0x7f)
		return b;
	if ((b & 0xe0) == 0xc0)
		return ((b & 0x1f) << 6) | (p[1] & 0x3f);
	if ((b & 0xf0) == 0xe0)
		return ((((b & 0xf) << 6) | (p[1] & 0x3f)) << 6) | (p[2] & 0x3f);
	return ((((((b & 0x7) << 6) | (p[1] & 0x3f)) << 6) | (p[2] & 0x3f)) << 6) | (p[3] & 0x3f);
}
