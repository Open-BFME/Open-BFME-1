// cl: /DNDEBUG /DWIN32 /MD
// The carved boundary at retail 0x001BF480 contains only a ret. Its caller
// proves the address, but the body provides no semantic identity.

void Rva001BF480Noop()
{
}
