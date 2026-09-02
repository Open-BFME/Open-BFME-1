// cl: /DNDEBUG /MD /EHs-c-
// gdiplus.dll GdipCloneImage import stub at 0x009F6C2E: FF 25 [IAT].

extern "C" __declspec(dllimport) int __stdcall GdipCloneImageIat(void *image, void **cloneImage);

extern "C" int __stdcall GdipCloneImage(void *image, void **cloneImage)
{
	return GdipCloneImageIat(image, cloneImage);
}
