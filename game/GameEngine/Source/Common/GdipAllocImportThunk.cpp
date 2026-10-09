// cl: /DNDEBUG /MD /EHs-c-
// gdiplus.dll GdipAlloc import stub at 0x009F6C28: FF 25 [IAT].

// The IAT is the imported GdipAlloc slot; read it directly so the stub
// can define GdipAlloc without redeclaring that function as dllimport.
extern "C" void *(__stdcall *__identifier("_imp__GdipAlloc@4"))(unsigned int size);

extern "C" void *__stdcall GdipAlloc(unsigned int size)
{
	return __identifier("_imp__GdipAlloc@4")(size);
}
