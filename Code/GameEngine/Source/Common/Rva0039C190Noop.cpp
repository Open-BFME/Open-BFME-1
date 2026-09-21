// The carved boundary at retail RVA 0x0039C190 contains only ret.
// The generated thunk caller proves the boundary but not a semantic owner.
// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-

void Rva0039C190Noop(void)
{
}
