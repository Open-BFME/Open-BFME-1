// cl: /O2 /DNDEBUG /MD

// The carved boundary at 0x00122E80 contains only ret.
// The generated thunk caller does not prove a semantic owner, so the name keeps the address.
void Rva00122E80Noop(void)
{
}
