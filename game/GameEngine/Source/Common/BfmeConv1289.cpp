// Open-BFME5 conversions.

struct BfmeFileSF;

extern "C" __declspec(dllimport) BfmeFileSF *__cdecl fopen(const char *path, const char *mode);
extern "C" __declspec(dllimport) int __cdecl fprintf(BfmeFileSF *f, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl fclose(BfmeFileSF *f);

void __stdcall bfmeGoSF(int a, int b, const char *path)
{
	BfmeFileSF *f = fopen(path, "at");
	fprintf(f, "\n------------------\n");
	fclose(f);
}
