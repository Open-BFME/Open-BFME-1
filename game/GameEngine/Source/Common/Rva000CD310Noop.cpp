// cl: /DNDEBUG /MD /EHs-c-

// ?Rva000CD310Noop@@YAXXZ
// Retail 0x000CD310 contains only ret. The carved boundary and generated thunk
// caller at 0x00031CDC prove an empty cdecl body, but no evidence identifies its owner.
void Rva000CD310Noop()
{
}
