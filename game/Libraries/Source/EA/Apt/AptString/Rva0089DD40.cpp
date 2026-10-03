// cl: /O2 /MD
// RVA0089DD40..0089DDBC, 124 bytes. Prior native leaf ends RET89DD3D,
// then two INT3; this complete stack-argument entry ends RET89DDBB, then
// four INT3 before the separate encoder at89DDC0. No caller/name witness.
// The address keeps the identity opaque. See identity_evidence/0089dd40.md.
// Preserve retail: every remaining non-ASCII lead takes the four-byte arm;
// this does not validate continuation bytes or malformed sequences.
int rva0089DD40(const char* src)
{
	const unsigned char* p = (const unsigned char*)src;
	unsigned char c = p[0];
	int value;
	if (c <= 0x7F) {
		value = c;
	} else if ((c & 0xE0) == 0xC0) {
		value = ((c & 0x1F) << 6) | (p[1] & 0x3F);
	} else if ((c & 0xF0) == 0xE0) {
		value = ((((c & 0x0F) << 6) | (p[1] & 0x3F)) << 6) | (p[2] & 0x3F);
	} else {
		value = ((((((c & 0x07) << 6) | (p[1] & 0x3F)) << 6) | (p[2] & 0x3F)) << 6) | (p[3] & 0x3F);
	}
	return value;
}
