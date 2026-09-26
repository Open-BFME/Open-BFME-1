// The carved boundary at retail RVA 0x00589B40 contains only ret.
// The caller proves the boundary but not a semantic owner, so the source keeps the address.
// cl: /O2 /EHsc- /MD /DNDEBUG

void Rva00589B40Noop(void)
{
}
