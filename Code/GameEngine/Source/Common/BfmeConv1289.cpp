// Open-BFME5 conversions.

struct BfmeFileSF;

__declspec(dllimport) BfmeFileSF *__cdecl bfmeOpenSF(const char *path, const char *mode);
__declspec(dllimport) int __cdecl bfmeLogSF(BfmeFileSF *f, const char *fmt, ...);
__declspec(dllimport) int __cdecl bfmeShutSF(BfmeFileSF *f);

void __stdcall bfmeGoSF(int a, int b, const char *path)
{
	BfmeFileSF *f = bfmeOpenSF(path, "at");
	bfmeLogSF(f, "\n------------------\n");
	bfmeShutSF(f);
}
