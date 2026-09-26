// cl: /DNDEBUG /MD /O2 /EHsc

// The carved boundary at 0x00696E60 contains only a return. Its nearby
// thunk references do not prove a semantic owner, so the function keeps the
// address-derived name.
void Rva00696E60Noop()
{
}
