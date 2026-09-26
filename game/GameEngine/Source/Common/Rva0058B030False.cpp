// Retail RVA 0x0058B030 returns false with xor al, al; ret.
// The generated thunk is the only known reference, so the address stays in the name.

bool Rva0058B030False(void)
{
	return false;
}
