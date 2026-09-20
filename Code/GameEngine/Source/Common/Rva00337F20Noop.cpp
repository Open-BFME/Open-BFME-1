// The carved boundary at 0x00337F20 contains only a return instruction.
// The generated thunk at 0x0001BF6D calls this address, but no evidence names
// a semantic owner for the empty cdecl body.
void Rva00337F20Noop()
{
}
