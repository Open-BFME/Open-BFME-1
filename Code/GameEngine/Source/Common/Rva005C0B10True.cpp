// Retail RVA 0x005C0B10 returns true with mov al, 1; ret.
// The caller thunk at 0x0002FE8C does not identify the owning class or method.

bool Rva005C0B10(void)
{
	return true;
}
