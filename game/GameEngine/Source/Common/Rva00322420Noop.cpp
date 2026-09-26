// The carved boundary at retail RVA 0x00322420 contains only ret.
// The generated thunk caller proves the boundary but not a semantic owner.
// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-

void Rva00322420Noop(void)
{
}
