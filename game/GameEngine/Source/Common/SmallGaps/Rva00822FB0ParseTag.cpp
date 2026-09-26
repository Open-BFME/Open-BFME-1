// ?rva00822FB0ParseTag@@YAIPBE@Z
// Address-derived: parse a big-endian 16-bit tag from bytes[0..1]; if it is
// 0x46FB, return the big-endian 24-bit value at bytes[2..4], else return the
// big-endian 24-bit value at bytes[5..7].
unsigned int __stdcall rva00822FB0ParseTag(const unsigned char* p)
{
	unsigned int tag = (p[0] << 8) | p[1];
	if (tag == 0x46FB)
		return (p[2] << 16) | (p[3] << 8) | p[4];
	return (p[5] << 16) | (p[6] << 8) | p[7];
}
