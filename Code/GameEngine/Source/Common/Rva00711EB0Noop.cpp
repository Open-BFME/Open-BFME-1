// The carved boundary at 0x00711EB0 contains only a return instruction.
// The generated thunk at 0x000120DA calls this address, but no evidence names
// a semantic owner for the empty cdecl body.
void Rva00711EB0Noop()
{
}
