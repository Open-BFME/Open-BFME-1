// The carved boundary at 0x00384CA0 contains only a one-byte ret.
// The padding and the separate ret 4 body at +0x10 prove the extent.

// cl: /O2 /DNDEBUG /DWIN32 /MD
void Rva00384CA0Noop()
{
}
