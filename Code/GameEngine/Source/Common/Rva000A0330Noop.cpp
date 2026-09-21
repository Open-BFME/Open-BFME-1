// The carved boundary at retail RVA 0x000A0330 contains only ret.
// The generated thunk caller proves the boundary but not a semantic owner.
// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-

void Rva000A0330Noop(void)
{
}
