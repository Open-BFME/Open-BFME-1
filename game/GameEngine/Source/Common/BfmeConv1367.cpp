// Open-BFME5 conversions.

struct BfmeLuaVHR;

const char *__cdecl bfmeCheckStrVHR(BfmeLuaVHR *L, int n, unsigned *len);
void __cdecl bfmePushNilVHR(BfmeLuaVHR *L);
void __cdecl bfmePushNumVHR(BfmeLuaVHR *L, double v);
void __cdecl bfmePushStrVHR(BfmeLuaVHR *L, const char *s);
void __cdecl bfmePushUserVHR(BfmeLuaVHR *L, void *u, int tag);

__declspec(dllimport) int __cdecl bfmeRemoveVHR(const char *path);

int __cdecl bfmeGoVHR(BfmeLuaVHR *L)
{
	if (bfmeRemoveVHR(bfmeCheckStrVHR(L, 1, 0)) == 0)
	{
		bfmePushUserVHR(L, 0, 0);
		return 1;
	}
	bfmePushNilVHR(L);
	bfmePushStrVHR(L, "generic I/O error");
	bfmePushNumVHR(L, -1.0);
	return 3;
}

__declspec(dllimport) int __cdecl bfmeRenameVHS(const char *from, const char *to);

int __cdecl bfmeGoVHS(BfmeLuaVHR *L)
{
	if (bfmeRenameVHS(bfmeCheckStrVHR(L, 1, 0), bfmeCheckStrVHR(L, 2, 0)) == 0)
	{
		bfmePushUserVHR(L, 0, 0);
		return 1;
	}
	bfmePushNilVHR(L);
	bfmePushStrVHR(L, "generic I/O error");
	bfmePushNumVHR(L, -1.0);
	return 3;
}
