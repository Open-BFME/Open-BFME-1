// The carved boundary at 0x002B7620 contains only a return instruction.
// The generated thunk at 0x000443FA calls this address, but no evidence names
// a semantic owner for the empty cdecl body.
void Rva002B7620Noop()
{
}
