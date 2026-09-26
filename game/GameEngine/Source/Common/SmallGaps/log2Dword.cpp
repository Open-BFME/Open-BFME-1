// ?log2Dword@@YAHI@Z
int log2Dword(unsigned int v)
{
	int r = 0;
	if (v & 0xffff0000) { v >>= 16; r = 16; }
	if (v & 0xff00) { v >>= 8; r |= 8; }
	if (v & 0xf0) { v >>= 4; r |= 4; }
	if (v & 0xc) { v >>= 2; r |= 2; }
	if (v & 2) r |= 1;
	return r;
}
