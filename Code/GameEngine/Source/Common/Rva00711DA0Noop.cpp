// cl: /DNDEBUG /DWIN32 /MD /EHsc

// Retail RVA 0x00711DA0 contains only ret.
// The carved boundary and its caller prove an empty cdecl body,
// but no evidence proves a semantic owner.
void Rva00711DA0Noop()
{
}
