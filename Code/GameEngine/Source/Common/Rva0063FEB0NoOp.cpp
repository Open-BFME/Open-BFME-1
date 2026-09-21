// cl: /O2 /DNDEBUG /MD
// Retail RVA 0x0063FEB0 is an isolated one-byte return with no surviving name.

// ?Rva0063FEB0NoOp@@YAXXZ
void Rva0063FEB0NoOp()
{
}

// ?Rva0063FEC0NoOp@@YAXXZ
// The carved boundary at RVA 0x0063FEC0 contains only ret before int3
// padding, so this body keeps an address-derived name.
void Rva0063FEC0NoOp()
{
}
