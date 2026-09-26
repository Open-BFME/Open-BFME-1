// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

int g_rva00545D60;

void rva00545D60(int n)
{
	g_rva00545D60 = n;
	if (n < 1)
		g_rva00545D60 = 1;
}
