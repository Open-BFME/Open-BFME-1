// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// The carved boundary at 0x00385730 contains one ret byte. Its caller does not
// prove a semantic owner, so the name keeps the retail address.
void Rva00385730NoOp()
{
}
