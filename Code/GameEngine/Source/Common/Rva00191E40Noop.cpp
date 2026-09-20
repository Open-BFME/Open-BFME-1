// cl: /DNDEBUG /MD /EHsc /DWIN32

// Retail 0x00191E40 is a one-byte carved boundary containing only ret.
// The following int3 padding and the next function start at 0x00191E50.
// No caller or table proves a semantic owner, so the source keeps its address.

void Rva00191E40Noop(void)
{
}
