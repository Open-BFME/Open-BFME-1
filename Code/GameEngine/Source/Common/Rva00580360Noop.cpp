// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00580360 contains only ret.
// The generated thunk at 0x000211ED calls this body, but no evidence names it.

void Rva00580360Noop()
{
}

// Retail RVA 0x00580300 contains only ret.
void Rva00580300Noop()
{
}

// The carved boundary at 0x005803A0 contains one ret byte.
// No semantic owner is proven, so the name keeps the retail address.
void Rva005803A0Noop()
{
}
