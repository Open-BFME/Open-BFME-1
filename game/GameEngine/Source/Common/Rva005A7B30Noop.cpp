// The carved boundary at retail RVA 0x005A7B30 contains only ret.
// The generated thunk caller proves the boundary but not a semantic owner.
// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-

void Rva005A7B30Noop(void)
{
}
