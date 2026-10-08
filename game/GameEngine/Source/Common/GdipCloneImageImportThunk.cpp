// cl: /DNDEBUG /MD /EHs-c-
// gdiplus.dll GdipCloneImage import stub at 0x009F6C2E: FF 25 [IAT].

extern "C" __declspec(dllimport) int __stdcall GdipCloneImage(void *image, void **cloneImage);

int __stdcall Rva009F6C2E_GdipCloneImage(void *image, void **cloneImage)
{
	return GdipCloneImage(image, cloneImage);
}
