// cl: /O2 /DNDEBUG /MD
// Retail 0x00202910 returns with ret 0xC, so the body consumes three stack arguments.
// The carved boundary proves the extent, but no evidence proves a semantic owner.

void __stdcall Rva00202910(void *, void *, void *)
{
}
