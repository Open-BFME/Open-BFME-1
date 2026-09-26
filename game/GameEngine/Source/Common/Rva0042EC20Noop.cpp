// The carved boundary at 0x0042EC20 contains only a one-byte ret.
// The caller and nearby bodies prove the boundary, but not a semantic owner.

// cl: /O2 /DNDEBUG /MD
void Rva0042EC20Noop()
{
}
