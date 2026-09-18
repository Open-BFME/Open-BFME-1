// cl: /DNDEBUG /MD /EHsc

// The carved boundary at 0x0060A6F0 contains only ret. The ILT thunk proves
// the address, but no caller proves a semantic owner or function name.
void Rva0060A6F0()
{
}
