// Open-BFME5 conversions.

struct BfmeLuaVHR;

struct BfmeTagVIF
{
	char m_bfmePad[8];
	int m_bfme08;
};

const char *__cdecl bfmeCheckStrVHR(BfmeLuaVHR *L, int n, unsigned *len);
void __cdecl bfmePushNilVHR(BfmeLuaVHR *L);
void __cdecl bfmePushNumVHR(BfmeLuaVHR *L, double v);
void __cdecl bfmePushStrVHR(BfmeLuaVHR *L, const char *s);
void __cdecl bfmePushUserVHR(BfmeLuaVHR *L, void *u, int tag);
void *__cdecl bfmeToUserVIF(BfmeLuaVHR *L, int n);
void __cdecl bfmeSetTopVIF(BfmeLuaVHR *L, int n);

__declspec(dllimport) void *__cdecl bfmeFopenVIF(const char *name, const char *mode);

int __cdecl bfmeOpenVIF(BfmeLuaVHR *L)
{
	BfmeTagVIF *tag = (BfmeTagVIF *)bfmeToUserVIF(L, -1);
	bfmeSetTopVIF(L, -2);
	void *fp = bfmeFopenVIF(bfmeCheckStrVHR(L, 1, 0), bfmeCheckStrVHR(L, 2, 0));
	if (fp)
	{
		bfmePushUserVHR(L, fp, tag->m_bfme08);
		return 1;
	}
	bfmePushNilVHR(L);
	bfmePushStrVHR(L, "generic I/O error");
	bfmePushNumVHR(L, -1.0);
	return 3;
}
