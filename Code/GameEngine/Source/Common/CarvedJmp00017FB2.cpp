// cl: /DNDEBUG /MD /O2 /EHsc
// Retail 0x00017FB2 is a five-byte ILT to the matched HorzLine vector
// overflow body at RVA 0x00069070; the address-derived pin preserves ECX.
void d_00069070(void);

void j_00017fb2(void)
{
	d_00069070();
}
