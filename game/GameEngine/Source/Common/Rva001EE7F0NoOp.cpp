// cl: /DNDEBUG /MD /EHsc
// Three-pointer no-op at retail RVA 0x001EE7F0. The retail ret 0xC proves the
// stdcall stack cleanup, but the binary provides no class or method identity.

void __stdcall Rva001EE7F0NoOp( void *, void *, void * )
{
}
