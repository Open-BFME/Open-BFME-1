// cl: /DNDEBUG /MD /EHs-c-
// gdiplus.dll GdipAlloc import stub at 0x009F6C28: FF 25 [IAT].

extern "C" __declspec(dllimport) void *__stdcall GdipAllocIat(unsigned int size);

extern "C" void *__stdcall GdipAlloc(unsigned int size)
{
	return GdipAllocIat(size);
}
