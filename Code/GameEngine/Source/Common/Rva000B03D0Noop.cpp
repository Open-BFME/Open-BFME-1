// The carved boundary at 0x000B03D0 contains only a return instruction.
// The generated thunk at 0x00042F82 calls this address, but no evidence names
// a semantic owner for the empty cdecl body.
void Rva000B03D0Noop()
{
}
