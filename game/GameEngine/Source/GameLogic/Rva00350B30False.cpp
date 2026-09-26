// cl: /DNDEBUG /MD /EHsc
// Retail 0x00350B30 returns false and has no identity evidence beyond its
// address-derived thunk, so the source keeps that address in its name.

bool Rva00350B30False()
{
	return false;
}
