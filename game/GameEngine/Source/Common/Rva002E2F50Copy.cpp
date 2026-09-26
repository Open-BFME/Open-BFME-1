// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva002E2F50El
{
	int a[7];
};

void rva002E2F50(Rva002E2F50El *dst, Rva002E2F50El *src)
{
	if (dst)
		*dst = *src;
}
