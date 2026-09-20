// Retail 0x00352930 contains only ret. The carved boundary proves a cdecl
// no-op, but the binary does not prove a semantic owner.
// cl: /O2 /MD

void Rva00352930NoOp()
{
}
