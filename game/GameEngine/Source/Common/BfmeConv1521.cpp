// Open-BFME5 conversions.

extern "C" char *strcpy(char *d, const char *s);
#pragma intrinsic(strcpy)

extern void(__cdecl *g_bfmePrepVNV)(const char *s);

char bfmeExistsVNV(const char *s);

char bfmeHasVNV(const char *s)
{
	char n1[512];

	if (s == 0)
		return 0;

	strcpy(n1, "a*");
	strcpy(n1 + 2, s);
	g_bfmePrepVNV(n1);
	return bfmeExistsVNV(n1);
}
