// cl: /DNDEBUG /MD /O2 /EHsc
// Retail 0x00014475 is a five-byte ILT to Dict::releaseData at RVA 0x000681C0.
// The address-derived callee pin is independently established by that REL32.
void d_000681c0(void);

void j_00014475(void)
{
	d_000681c0();
}
