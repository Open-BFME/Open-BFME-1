// cl: /O2 /DNDEBUG /MD
// Retail 0x002EED90 returns with ret 0xC, so the body consumes three stack arguments.
// No caller or table proves a semantic owner, so the helper keeps its address.

void __stdcall Rva002EED90(void *, void *, void *)
{
}
