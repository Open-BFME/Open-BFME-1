// cl: /DNDEBUG /MD /O2 /EHsc

// The carved boundary at 0x005701C0 contains only a return.  Its caller does
// not prove a semantic owner, so the implementation keeps the address.
void Rva005701C0Noop()
{
}
