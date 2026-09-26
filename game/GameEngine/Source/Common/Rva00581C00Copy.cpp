// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00581C00El
{
	int a[7];
};

void rva00581C00(Rva00581C00El *dst, Rva00581C00El *src)
{
	if (dst)
		*dst = *src;
}
