// The carved boundary at 0x0037AF40 contains only a one-byte ret.
// The caller and nearby bodies prove the boundary, but not a semantic owner.

// cl: /O2 /DNDEBUG /MD
void Rva0037AF40Noop()
{
}
