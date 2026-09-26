// cl: /DNDEBUG /DWIN32 /MD /EHsc

// Retail RVA 0x004345D0 contains only ret.
// The carved boundary and generated thunk caller prove an empty cdecl body,
// but no evidence proves a semantic owner.
void Rva004345D0Noop()
{
}
