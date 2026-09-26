// cl: /O2 /DNDEBUG /MD
// Retail 0x002DEC30 returns with ret 8, so the body consumes two stack arguments.
// No caller or table proves a semantic owner, so the helper keeps its address.

void __stdcall Rva002DEC30(void *, void *)
{
}
