// cl: /DNDEBUG /DWIN32 /MD /EHsc

// Retail RVA 0x00112A00 contains only ret.
// The carved boundary and generated thunk caller prove an empty cdecl body,
// but no evidence proves a semantic owner.
void Rva00112A00Noop()
{
}
