// cl: /DNDEBUG /MD /EHsc
// The carved boundary at retail 0x002B2B00 returns integer zero.

// ?b_002b2b00@@YAHXZ
int b_002b2b00(void)
{
	return 0;
}

// The carved retail body at 0x002B2AF0 contains only ret.
void Rva002B2AF0Noop(void)
{
}
