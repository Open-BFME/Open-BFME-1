// Open-BFME5 conversions.

extern "C" unsigned strlen(const char *s);
#pragma intrinsic(strlen)

class BfmeStrVMZ
{
public:
	void bfmeReleaseVMZ();
	void bfmeSetVMZ(const char *s, int n);
};

extern char *(__cdecl *g_bfmeStrStrVMZ)(const char *a, const char *b);

char bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out)
{
	if (hay == 0 || *hay == 0)
		return 0;
	if (key == 0 || *key == 0)
		return 0;

	const char *p = g_bfmeStrStrVMZ(hay, key);

	if (p == 0)
		return 0;
	if (p != hay && p[-1] != '&')
		return 0;

	p += strlen(key);
	if (*p != '=')
		return 0;
	++p;

	const char *e = p;

	while (*e != 0 && *e != '&')
		++e;
	if (e == p)
	{
		out->bfmeReleaseVMZ();
		return 1;
	}
	out->bfmeSetVMZ(p, e - p);
	return 1;
}
