// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00385E20 contains only ret. The generated thunk at 0x00016A18
// reaches this address, but the binary provides no class or method identity.

void Rva00385E20Empty()
{
}
