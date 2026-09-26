// cl: /O2 /DNDEBUG /MD

// The carved boundary at 0x00150240 contains only ret.
// The generated thunk caller does not prove a semantic owner, so the name keeps the address.
void Rva00150240Noop(void)
{
}
